/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 @mtoohey31

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <math.h>
#include "crkbd.h"

enum crkbd_layers {
    _QWERTY,
    _NAV,
    _NUM,
    _FPS,
    _MOBA,
    _PLOVER,
    _SETTINGS
};

#define _______ KC_TRNS

enum custom_keycodes {
    KC_MLBRC,
    KC_MRBRC,
    TG_PLV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
    KC_LPRN,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RPRN,
    LT(_SETTINGS,KC_BSLS), KC_A, KC_S, KC_D, KC_F, KC_G,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                               LALT_T(KC_ESC), LGUI_T(KC_BSPC), LCTL_T(KC_DEL), LT(_NAV, KC_ENT), KC_SPC, LT(_NUM, KC_TAB)
),

[_NAV] = LAYOUT(
    _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _______, _______, _______, _______, _______, _______,
    _______, _______, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______, _______
),

[_NUM] = LAYOUT(
    KC_LBRC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_TILD, KC_SLSH, KC_7,    KC_8,    KC_9,    KC_MINS, KC_RBRC,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_GRV,  KC_ASTR, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_APP,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_HASH, KC_PERC, KC_1,    KC_2,    KC_3,    KC_EQL,  _______,
                               _______, _______, _______, DF(_NUM), KC_0,   DF(_QWERTY)
),

[_FPS] = LAYOUT(
    KC_ESC,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    _______, _______, _______, _______, _______, TG(_FPS),
    KC_1,    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    _______, _______, _______, _______, _______, _______,
    KC_2,    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    _______, _______, _______, _______, _______, _______,
                               KC_LALT, KC_SPC,  KC_LCTL, _______, _______, _______
),

[_MOBA] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, _______, _______, _______, TG(_MOBA),
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______, _______, _______, _______, _______, _______,
    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______, _______, _______, _______, _______, _______,
                               KC_LCTL, KC_SPC,  KC_B,    _______, _______, _______
),

[_PLOVER] = LAYOUT(
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    TG_PLV,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,
                               XXXXXXX, KC_C,    KC_V,    KC_N,    KC_M,    XXXXXXX
),

[_SETTINGS] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(_FPS), TO(_MOBA), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG_PLV,  XXXXXXX, MAGIC_TOGGLE_NKRO, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
                               XXXXXXX, MAGIC_SWAP_LCTL_LGUI, MAGIC_UNSWAP_LCTL_LGUI, XXXXXXX, XXXXXXX, XXXXXXX
)

};


#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch ((int)round(log(layer_state) / log(2))) {
        case _QWERTY:
            oled_write_ln_P(PSTR("QWERTY"), false);
            break;
        case _NAV:
            oled_write_ln_P(PSTR("Navigation"), false);
            break;
        case _NUM:
            oled_write_ln_P(PSTR("Numpad"), false);
            break;
        case _FPS:
            oled_write_ln_P(PSTR("FPS"), false);
            break;
        case _MOBA:
            oled_write_ln_P(PSTR("MOBA"), false);
            break;
        case _PLOVER:
            oled_write_ln_P(PSTR("Plover"), false);
            break;
        case _SETTINGS:
            oled_write_ln_P(PSTR("Settings"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_DRIVER_ENABLE
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
#endif // OLED_DRIVER_ENABLE

    switch (keycode) {
        case TG_PLV:
            if (record->event.pressed) {
            } else {
                layer_invert(_PLOVER);
                register_code(KC_E);
                register_code(KC_R);
                register_code(KC_F);
                register_code(KC_V);
                register_code(KC_O);
                register_code(KC_L);
                unregister_code(KC_E);
                unregister_code(KC_R);
                unregister_code(KC_F);
                unregister_code(KC_V);
                unregister_code(KC_O);
                unregister_code(KC_L);
            }
            return false;
            break;
        default:
            return true;
    }
}
