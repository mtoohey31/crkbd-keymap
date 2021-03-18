#include QMK_KEYBOARD_H
#include <math.h>
#include "crkbd.h"

extern uint8_t is_master;

enum crkbd_layers {
    _QWERTY,
    _SHIFT,
    _DOUBLESHIFT,
    _NAV,
    _NUM,
    _FPS,
    _LEAGUE,
    _SETTINGS
};

#define _______ KC_TRNS

enum custom_keycodes {
    KC_MLBRC,
    KC_MRBRC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
    KC_MLBRC, KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MRBRC,
    LT(_SETTINGS,KC_BSLS), KC_A, KC_S, KC_D, KC_F, KC_G,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    LM(_SHIFT, MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, LM(_SHIFT, MOD_LSFT),
                               LGUI_T(KC_ESC), LALT_T(KC_BSPC), LCTL_T(KC_DEL), LT(_NAV, KC_ENT), KC_SPC, LT(_NUM, KC_TAB)
),

[_SHIFT] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    MO(_DOUBLESHIFT), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MO(_DOUBLESHIFT),
                               _______, _______, _______, _______, _______, _______
),

[_DOUBLESHIFT] = LAYOUT(
    _______, _______, _______, KC_EQL,  KC_PERC, KC_TILD, _______, _______, _______, _______, KC_PLUS, _______,
    _______, KC_AT,   KC_AMPR, KC_DLR,  KC_CIRC, KC_GRV,  KC_MINS, _______, _______, _______, _______, _______,
    LSFT_T(KC_CAPS), _______, _______, KC_APP, _______, _______, KC_HASH, KC_ASTR, _______, _______, KC_EXLM, RSFT_T(KC_CAPS),
                               _______, _______, _______, _______, _______, _______
),

[_NAV] = LAYOUT(
    _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _______, _______, _______, _______, _______, _______,
    _______, _______, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______, _______
),

[_NUM] = LAYOUT(
    KC_MLBRC, KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_TILD, KC_SLSH, KC_7,    KC_8,    KC_9,    KC_MINS, KC_MRBRC,
    KC_LT,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_HASH, KC_ASTR, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_GT,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PERC, KC_CIRC, KC_1,    KC_2,    KC_3,    KC_EQL,  _______,
                               _______, _______, _______, TG(_NUM), KC_0,   _______
),

[_FPS] = LAYOUT(
    KC_ESC,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    _______, _______, _______, _______, _______, TG(_FPS),
    KC_1,    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    _______, _______, _______, _______, _______, _______,
    KC_2,    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    _______, _______, _______, _______, _______, _______,
                               KC_LALT, KC_SPC,  KC_LCTL, _______, _______, _______
),

[_LEAGUE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, _______, _______, _______, TG(_LEAGUE),
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______, _______, _______, _______, _______, _______,
    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______, _______, _______, _______, _______, _______,
                               KC_LCTL, KC_SPC,  KC_B,    _______, _______, _______
),

[_SETTINGS] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(_FPS), TO(_LEAGUE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
                               MAGIC_SWAP_LCTL_LGUI, XXXXXXX, MAGIC_UNSWAP_LCTL_LGUI, XXXXXXX, XXXXXXX, XXXXXXX
)

};

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

void matrix_init_user(void) {
// SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
    iota_gfx_init(!has_usb());  // turns on the display
#endif
}

// SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
char        layer_state_str[24];
const char *read_layer_state(void) {
    switch ((int)round(log(layer_state) / log(2))) {
        case _QWERTY:
            snprintf(layer_state_str, sizeof(layer_state_str), "Layer: QWERTY");
            break;
        case _SHIFT:
            snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Shift");
            break;
        case _DOUBLESHIFT:
            snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Double Shift");
            break;
        case _NAV:
            snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Navigation");
            break;
        case _NUM:
            snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Numpad");
            break;
        case _FPS:
            snprintf(layer_state_str, sizeof(layer_state_str), "Layer: FPS");
            break;
        case _LEAGUE:
            snprintf(layer_state_str, sizeof(layer_state_str), "Layer: League");
            break;
        case _SETTINGS:
            snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Settings");
            break;
        default:
            snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
    }

    return layer_state_str;
}
const char *read_logo(void);
void        set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) { iota_gfx_task(); }

void matrix_render_user(struct CharacterMatrix *matrix) {
    if (is_master) {
        // If you want to change the display of OLED, you need to change here
        matrix_write_ln(matrix, read_layer_state());
        matrix_write_ln(matrix, read_keylog());
        // matrix_write_ln(matrix, read_keylogs());
        // matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
        // matrix_write_ln(matrix, read_host_led_state());
        // matrix_write_ln(matrix, read_timelog());
    } else {
        matrix_write(matrix, read_logo());
    }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;
    matrix_clear(&matrix);
    matrix_render_user(&matrix);
    matrix_update(&display, &matrix);
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef SSD1306OLED
        set_keylog(keycode, record);
#endif
        // set_timelog();
    }

    switch (keycode) {
        case KC_MLBRC:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_DOUBLESHIFT)) {
                    register_code(KC_LSFT);
                    register_code(KC_LBRC);
                    unregister_code(KC_LSFT);
                } else if (IS_LAYER_ON(_SHIFT)) {
                    unregister_code(KC_LSFT);
                    register_code(KC_LBRC);
                    register_code(KC_LSFT);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_9);
                    unregister_code(KC_LSFT);
                }
            } else {
                unregister_code(KC_COMM);
                unregister_code(KC_LBRC);
                unregister_code(KC_9);
            }
            return false;
        case KC_MRBRC:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_DOUBLESHIFT)) {
                    register_code(KC_LSFT);
                    register_code(KC_RBRC);
                    unregister_code(KC_LSFT);
                } else if (IS_LAYER_ON(_SHIFT)) {
                    unregister_code(KC_LSFT);
                    register_code(KC_RBRC);
                    register_code(KC_LSFT);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_0);
                    unregister_code(KC_LSFT);
                }
            } else {
                unregister_code(KC_DOT);
                unregister_code(KC_RBRC);
                unregister_code(KC_0);
            }
            return false;
        default:
            return true;
    }
}

/* void keyboard_post_init_user(void) { */
/*     /1* Customise these values to desired behaviour *1/ */
/*     /1* debug_enable = true; *1/ */
/*     /1* debug_matrix = true; *1/ */
/*     /1* debug_keyboard=true; *1/ */
/*     /1* debug_mouse=true; *1/ */
/* } */
