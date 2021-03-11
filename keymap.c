#include QMK_KEYBOARD_H
#include <print.h>

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _MSHIFT 1
#define _SECSHIFT 2
#define _NAV 3
#define _NUM 4
#define _FPS 5
#define _LEAGUE 6
#define _SETTINGS 7

#define _______ KC_TRNS


typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
};

enum {
  TAPPER = 0
};

enum custom_keycodes {
  KC_MLBRC,
  KC_MRBRC
};

int cur_dance (qk_tap_dance_state_t *state);

void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
    KC_MLBRC, KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MRBRC,
    LT(_SETTINGS,KC_BSLS), KC_A, KC_S, KC_D, KC_F, KC_G,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    MT(MOD_LSFT, OSL(_MSHIFT)), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M,   KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, OSL(_MSHIFT)),
                               LGUI_T(KC_ESC), LALT_T(KC_BSPC), LCTL_T(KC_DEL), LT(_NAV, KC_ENT), KC_SPC, LT(_NUM, KC_TAB)
),

[_MSHIFT] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    LT(_SECSHIFT, OSL(_SECSHIFT)), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LT(_SECSHIFT, OSL(_SECSHIFT)),
                               _______, _______, _______, _______, _______, _______
),

[_SECSHIFT] = LAYOUT(
    _______, _______, _______, KC_EQL,  KC_PERC, KC_TILD, _______, _______, _______, _______, KC_PLUS, _______,
    _______, KC_AT,   KC_AMPR, KC_DLR,  KC_CIRC, KC_GRV,  KC_MINS, _______, _______, _______, _______, _______,
    MT(MOD_LSFT, KC_CAPS), _______, _______, KC_APP, _______, _______, KC_HASH, KC_ASTR, _______, _______, KC_EXLM, MT(MOD_RSFT, KC_CAPS),
                               _______, _______, _______, _______, _______, _______
),

[_NAV] = LAYOUT(
    _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _______, _______, _______, _______, _______, _______,
    _______, _______, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, TG(_NUM), _______, _______, _______, _______, _______,
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
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(_FPS), MAGIC_UNSWAP_LCTL_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(_LEAGUE), MAGIC_SWAP_LCTL_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
)

};

int cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed)  return SINGLE_TAP;
        else return SINGLE_HOLD;
    }
    else if (state->count == 2) {
        if (state->pressed || state->interrupted) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
else return 5;
};

static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void x_finished (qk_tap_dance_state_t *state, void *user_data) {
xtap_state.state = cur_dance(state);
switch (xtap_state.state) {
  case SINGLE_TAP: register_code(KC_ENT); break;
  case SINGLE_HOLD: layer_on(_NAV); break;
  case DOUBLE_TAP: layer_on(_NUM); break;
  case DOUBLE_HOLD: layer_on(_NUM); break;
    }
}
void x_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_ENT); break;
        case SINGLE_HOLD: layer_off(_NAV); break;
        case DOUBLE_HOLD: layer_off(_NUM); break;
    }
    xtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TAPPER]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,x_finished, x_reset)
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
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
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  /* return true; */

  switch (keycode) {
    case KC_MLBRC:
      if (record->event.pressed) {
        if ((keyboard_report->mods & MOD_BIT(KC_LSFT) || keyboard_report->mods & MOD_BIT(KC_RSFT)) && layer_state_is(_SECSHIFT)) {
          register_code(KC_COMM);
        } else if (IS_LAYER_ON(_SECSHIFT)) {
          register_code(KC_LSFT);
          register_code(KC_LBRC);
          unregister_code(KC_LSFT);
        } else if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
          unregister_code(KC_LSFT);
          register_code(KC_LBRC);
          register_code(KC_LSFT);
        } else if (keyboard_report->mods & MOD_BIT(KC_RSFT)) {
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
        if ((keyboard_report->mods & MOD_BIT(KC_LSFT) || keyboard_report->mods & MOD_BIT(KC_RSFT)) && layer_state_is(_SECSHIFT)) {
          register_code(KC_DOT);
        } else if (IS_LAYER_ON(_SECSHIFT)) {
          register_code(KC_LSFT);
          register_code(KC_RBRC);
          unregister_code(KC_LSFT);
        } else if (keyboard_report->mods & MOD_BIT(KC_LSFT) && IS_LAYER_OFF(_SECSHIFT)) {
          unregister_code(KC_LSFT);
          register_code(KC_RBRC);
          register_code(KC_LSFT);
        } else if (keyboard_report->mods & MOD_BIT(KC_RSFT) && IS_LAYER_OFF(_SECSHIFT)) {
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

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
