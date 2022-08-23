#include QMK_KEYBOARD_H

enum Layer_name {
    QWERTY,
    GAMING,
    BONE,
    F_KEYS,
    NUMPAD,
    M3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // qwerty
	[0] = LAYOUT(
        // left hand
        KC_ESC,  KC_1,    KC_2,       KC_3,       KC_4,         KC_5,         KC_GRV,
        KC_TAB,  KC_Q,    KC_W,       KC_E,       KC_R,         KC_T,         DF(2),
        KC_RALT, KC_A,    LT(4,KC_S), LT(3,KC_D), LSFT_T(KC_F), LCTL_T(KC_G),
        KC_LSFT, KC_Z,    KC_X,       KC_C,       KC_V,         KC_B,         KC_SPC,
        KC_LCTL, KC_LCTL, MO(4),      MO(3),      KC_CAPS,
                                                                KC_LGUI,      KC_LALT,
                                                                              KC_HOME,
                                                        KC_SPC, KC_DEL,       KC_END,
        // right hand
        KC_EQL,  KC_6,         KC_7,         KC_8,       KC_9,       KC_0,    KC_MINS,
        KC_RBRC, KC_Y,         KC_U,         KC_I,       KC_O,       KC_P,    KC_LBRC,
                 RCTL_T(KC_H), RSFT_T(KC_J), LT(3,KC_K), LT(4,KC_L), KC_SCLN, KC_QUOT,
        KC_PENT, KC_N,         KC_M,         KC_COMM,    KC_DOT,     KC_SLSH, KC_RSFT,
                               KC_CAPS,      MO(3),      MO(4),      KC_RCTL, KC_RCTL,
        KC_RALT, KC_RGUI,
        KC_PGUP,
        KC_PGDN, KC_BSPC, KC_ENT
    ),
    // pure (gaming)
	[1] = LAYOUT(
       // left hand
       KC_ESC,  KC_1,    KC_2,       KC_3,       KC_4,         KC_5,         KC_GRV,
       KC_TAB,  KC_Q,    KC_W,       KC_E,       KC_R,         KC_T,         KC_NO,
       KC_RALT, KC_A,    KC_S,       KC_D,       KC_F,         KC_G,
       KC_LSFT, KC_Z,    KC_X,       KC_C,       KC_V,         KC_B,         KC_SPC,
       KC_LCTL, KC_LCTL, MO(4),      MO(3),      KC_CAPS,
                                                               KC_LGUI,      KC_LALT,
                                                                             KC_HOME,
                                                       KC_SPC, KC_DEL,       KC_END,
       // right hand
       KC_EQL,  KC_6,         KC_7,         KC_8,       KC_9,       KC_0,    KC_MINS,
       DF(0),   KC_Y,         KC_U,         KC_I,       KC_O,       KC_P,    KC_LBRC,
                KC_H,         KC_J,         KC_K,       KC_L,       KC_SCLN, KC_QUOT,
       KC_PENT, KC_N,         KC_M,         KC_COMM,    KC_DOT,     KC_SLSH, KC_RSFT,
                              KC_CAPS,      MO(3),      MO(4),      KC_RCTL, KC_RCTL,
       KC_RALT, KC_RGUI,
       KC_PGUP,
       KC_PGDN, KC_BSPC, KC_ENT
    ),
    // bone on qwertz
	[2] = LAYOUT(
       // left hand
       KC_ESC,  KC_1,    KC_2,       KC_3,       KC_4,         KC_5,         KC_GRV,
       KC_TAB,  KC_J,    KC_D,       KC_U,       KC_A,         KC_X,         DF(0),
       KC_RALT, KC_C,    LT(4,KC_T), LT(3,KC_I), LSFT_T(KC_E), LCTL_T(KC_O),
       KC_LSFT, KC_F,    KC_V,       KC_LBRC,    KC_QUOT,      KC_SCLN,      KC_SPC,
       KC_LCTL, KC_LCTL, MO(4),      MO(3),      MO(5),
                                                               KC_LGUI,      KC_LALT,
                                                                             KC_HOME,
                                                       KC_SPC, KC_DEL,       KC_END,
       // right hand
       KC_EQL,  KC_6,         KC_7,         KC_8,       KC_9,       KC_0,    KC_MINS,
       KC_RBRC, KC_P,         KC_H,         KC_L,       KC_M,       KC_W,    KC_MINS,
                RCTL_T(KC_B), RSFT_T(KC_N), LT(3,KC_R), LT(4,KC_S), KC_G,    KC_Q,
       KC_ENT,  KC_Z,         KC_Y,         KC_COMM,    KC_DOT,     KC_K,    KC_RSFT,
                              MO(5),        MO(3),      MO(4),      KC_RCTL, KC_RCTL,
       KC_RALT, KC_RGUI,
       KC_PGUP,
       KC_PGDN, KC_BSPC, KC_ENT
    ),
    // F-Keys + Navigation + Media + Backlight
    [3] = LAYOUT(
       // left hand
       KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MUTE,
       KC_TAB,  KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, KC_NO,
       KC_RALT, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
       KC_LSFT, KC_ESC,  KC_TAB,  KC_INS,  KC_ENT,  KC_NO,   KC_SPC,
       KC_LCTL, KC_LCTL, TG(3),   KC_TRNS, KC_CAPS,
                                                               KC_LGUI,      KC_LCTL,
                                                                             KC_HOME,
                                                       KC_SPC, KC_DEL,       KC_END,
       // right hand
       KC_NO,   KC_NO,   KC_F10,  KC_F11,  KC_F12, BL_STEP, KC_NO,
       KC_NO,   KC_NO,   KC_F7,   KC_F8,   KC_F9,  BL_INC,  KC_NO,
                KC_NO,   KC_F4,   KC_F5,   KC_F6,  BL_DEC,  KC_NO,
       KC_NO,   KC_NO,   KC_F1,   KC_F2,   KC_F3,  BL_TOGG, KC_RSFT,
                         KC_CAPS, KC_TRNS, KC_NO,  KC_RCTL, KC_RCTL,
       KC_RALT, KC_RCTL,
       KC_PGUP,
       KC_PGDN, KC_BSPC, KC_ENT
    ),
    // Numpad + Navigation + Media
    [4] = LAYOUT(
       // left hand
       KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MUTE,
       KC_TAB,  KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, DF(1),
       KC_RALT, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
       KC_LSFT, KC_ESC,  KC_TAB,  KC_INS,  KC_ENT,  KC_NO,   KC_NO,
       KC_LCTL, KC_LCTL, KC_TRNS, TG(4),   KC_NO,
                                                               KC_LGUI,      KC_LALT,
                                                                             KC_HOME,
                                                       KC_SPC, KC_DEL,       KC_END,
       // right hand
       KC_PSCR, KC_ESC,  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_NO,
       KC_NO,   KC_TAB,  KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_PMNS,
                KC_SPC,  KC_P4,   KC_P5,   KC_P6,   KC_LPRN, KC_RPRN,
       KC_NO,   KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PENT, KC_RSFT,
                         KC_PEQL, KC_COMM, KC_DOT,  KC_RCTL, KC_RCTL,
       KC_RALT, KC_RGUI,
       KC_PGUP,
       KC_PGDN, KC_BSPC, KC_ENT
    ),
    // NEO M3 on qwertz
	[5] = LAYOUT(
       // left hand
       KC_NO, KC_NO,         KC_NO,   KC_NO,         KC_NO,         KC_NO,   KC_NO,
       KC_NO, KC_NO,         KC_QUES, RALT(KC_8),    RALT(KC_9),    KC_GRV,  KC_NO,
       KC_NO, RALT(KC_MINS), KC_AMPR, RALT(KC_7),    RALT(KC_0),    KC_RCBR,
       KC_NO, KC_BSLS,       KC_DLR,  RALT(KC_NUBS), RALT(KC_RBRC), KC_PLUS, KC_NO,
       KC_NO, KC_NO,         KC_NO,   KC_NO,         KC_TRNS,
                                                                    KC_NO,   KC_NO,
                                                                             KC_NO,
                                                             KC_NO, KC_NO,   KC_NO,
       // right hand
       KC_NO, KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO,
       KC_NO, KC_EXLM, KC_NUBS, LSFT(KC_NUBS), KC_RPRN, KC_CIRC, KC_NO,
              KC_UNDS, KC_ASTR, KC_LPRN,       KC_SLSH, KC_GT,   RALT(KC_Q),
       KC_NO, KC_RBRC, KC_PERC, KC_AT,         KC_PIPE, KC_LT,   KC_NO,
                       KC_TRNS, KC_NO,         KC_NO,   KC_NO,   KC_NO,
       KC_NO, KC_NO,
       KC_NO,
       KC_NO, KC_NO,   KC_NO
    )
};
