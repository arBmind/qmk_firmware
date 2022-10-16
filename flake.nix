{
  description = "QMK firmware development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    poetry2nix = {
      url = "github:nix-community/poetry2nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    devshell = {
      url = "github:numtide/devshell";
      inputs = {
        flake-utils.follows = "flake-utils";
        nixpkgs.follows = "nixpkgs";
      };
    };
  };

  outputs = args@{ self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [
            args.devshell.overlay
            args.poetry2nix.overlay
            (final: prev: {
              python3 = prev.python3.override {
                packageOverrides = self: super: {
                  tomlkit = super.tomlkit.overridePythonAttrs(old: rec {
                    version = "0.11.4";
                    src = super.fetchPypi {
                      inherit (old) pname;
                      inherit version;
                      sha256 = "sha256-MjWpAQ+uVDI+cnw6wG+3IHUv5mNbNCbjedrsYPvUSoM=";
                    };
                  });
                };
              };
            })
          ];
        };
        inherit (pkgs) lib pkgsCross devshell;

        makeShell = { avr ? false, arm ? false, teensy ? false }:
          let
            avrlibc = pkgsCross.avr.libcCross;
            poetry2nix = pkgs.poetry2nix;

            avr_incflags = [
              "-isystem ${avrlibc}/avr/include"
              "-B${avrlibc}/avr/lib/avr5"
              "-L${avrlibc}/avr/lib/avr5"
              "-B${avrlibc}/avr/lib/avr35"
              "-L${avrlibc}/avr/lib/avr35"
              "-B${avrlibc}/avr/lib/avr51"
              "-L${avrlibc}/avr/lib/avr51"
            ];

            # Builds the python env based on nix/pyproject.toml and
            # nix/poetry.lock Use the "poetry update --lock", "poetry add
            # --lock" etc. in the nix folder to adjust the contents of those
            # files if the requirements*.txt files change
            pythonEnv = poetry2nix.mkPoetryEnv {
              projectDir = ./util/nix;
              overrides = poetry2nix.overrides.withDefaults (self: super: {
                pillow = super.pillow.overridePythonAttrs (old: {
                  # Use preConfigure from nixpkgs to fix library detection issues and
                  # impurities which can break the build process; this also requires
                  # adding propagatedBuildInputs and buildInputs from the same source.
                  propagatedBuildInputs = (old.buildInputs or [ ]) ++ pkgs.python3.pkgs.pillow.propagatedBuildInputs;
                  buildInputs = (old.buildInputs or [ ]) ++ pkgs.python3.pkgs.pillow.buildInputs;
                  preConfigure = (old.preConfigure or "") + pkgs.python3.pkgs.pillow.preConfigure;
                });
                qmk = super.qmk.overridePythonAttrs (old: {
                  # Allow QMK CLI to run "qmk" as a subprocess (the wrapper changes
                  # $PATH and breaks these invocations).
                  dontWrapPythonPrograms = true;
                });
              });
            };
          in
          devshell.mkShell {
            name = "qmk-firmware";

            packages = with pkgs;[
                gnumake
                clang-tools
                dfu-programmer
                dfu-util
                diffutils
                git
                pythonEnv
              ]
              ++ lib.optionals avr [
                pkgsCross.avr.buildPackages.binutils
                pkgsCross.avr.buildPackages.gcc8
                avrlibc
                avrdude
              ]
              ++ lib.optionals arm [ gcc-arm-embedded ]
              ++ lib.optionals teensy [ teensy-loader-cli ];

            env = [
                {
                  name = "NIX_CFLAGS_COMPILE_FOR_TARGET";
                  unset = true;
                }
              ]
              ++ lib.optionals avr [
                {
                  name = "AVR_CFLAGS";
                  value = lib.concatStringsSep " " avr_incflags;
                }
                {
                  name = "AVR_ASFLAGS";
                  value = lib.concatStringsSep " " avr_incflags;
                }
              ];

            commands = [
              {
                name = "json2c";
                category = "keymap";
                help = "convert keymap json to c (json2c <keyboard> <layout>)";
                command = ''
                  keyboard=''${1:-input_club/ergodox_infinity}
                  layout=''${2:-arbtype}
                  qmk json2c --output keyboards/''${keyboard}/keymaps/''${layout}/keymap.c keyboards/''${keyboard}/keymaps/''${layout}/''${layout}.json
                '';
              }
              {
                name = "ergodox";
                category = "flash";
                help = ''
                  build and flash firmware for Ergodox Infinity
                    ergodox <layout(arbtype*/default)>
                  '';
                command = ''
                  # see keyboards/ergodox_infinity/readme.md
                  keyboard=input_club/ergodox_infinity
                  layout=''${1:-arbtype}

                  rm -rf .build
                  qmk flash -kb ''${keyboard} -km ''${layout} -bl dfu-util
                  '';
              }
              {
                name = "ergodox-split";
                category = "flash";
                help = ''
                  build and flash firmware for Ergodox Infinity to initialize EE_HANDS
                    ergodox <layout(arbtype*/default)> <left*/right>
                  '';
                command = ''
                  # see keyboards/ergodox_infinity/readme.md
                  keyboard=input_club/ergodox_infinity
                  layout=''${1:-arbtype}
                  side=''${2:-left}

                  rm -rf .build
                  qmk flash -kb ''${keyboard} -km ''${layout} -bl dfu-util-split-''${side}
                  '';
              }
              {
                name = "hotdox76";
                category = "flash";
                help = ''
                  build and flash firmware for Hotdox76
                    hotdox76 <layout(arbtype*/via)> <left*/right>)
                  '';
                command = ''
                  keyboard=yandrstudio/wired/hotdox76v2
                  layout=''${1:-arbtype}
                  side=''${2:-left}

                  rm -rf .build
                  qmk flash -kb ''${keyboard} -km ''${layout} -bl dfu-util-split-''${side}
                '';
              }
            ];

            # pass through attributes so they
            # can be combined (in any order) like this:
            # nix develop .#avr.arm.teensy
            # passthru =
            #   {
            #     avr = (makeShell { inherit avr; avr = true; });
            #     arm = (makeShell { inherit arm; arm = true; });
            #     teensy = (makeShell { inherit teensy; teensy = true; });
            #   };
          };
      in
      {
        # nix develop .#arm
        # nix develop .#teensy.arm
        devShells = rec {
          default = all;

          all = makeShell { avr = true; arm = true; teensy = true; };
          avr = makeShell { avr = true; };
          avr-teensy = makeShell { avr = true; teensy = true; };
          arm = makeShell { arm = true; };
          arm-teensy = makeShell { arm = true; tennsy = true; };
        };
      }
    );
}
