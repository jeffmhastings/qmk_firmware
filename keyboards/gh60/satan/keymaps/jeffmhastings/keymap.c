#include "satan.h"


// Used for SHIFT_ESC
#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

enum keyboard_layers {
  LAYER_QWERTY = 0,
  LAYER_FUNCTION,
  LAYER_ADJUST,
};

enum keyboard_macros {
  MACRO_QWERTY = 0,
  MACRO_BREATH_DEFAULT,
  MACRO_BREATH_TOGGLE
};

// Key shortcuts
#define _______ KC_TRNS
#define M_FL    MO(LAYER_FUNCTION)  // Momentary function layer
#define LT_FL   LT(LAYER_FUNCTION, KC_CAPS) // Momentary function layer / caps lock
#define M_BRTOG M(MACRO_BREATH_TOGGLE)
#define M_BRDEF M(MACRO_BREATH_DEFAULT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LAYER_QWERTY] = KEYMAP_ANSI(
//   LAYER_QWERTY: (Base Layer) Default Layer
//  .--------------------------------------------------------------------------------------------------------------------------------------.
//  | ~      | !      | @      | #      | $      | %      | ^      | &      | *      | (      | )      | _      | +      |                 |
//  | Esc    | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | Backspace       |
      F(0)   , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC         ,
//  |--------------------------------------------------------------------------------------------------------------------------------------|
//  |            |        |        |        |        |        |        |        |        |        |        | {      | ]      | |           |
//  | Tab        | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | \           |
      KC_TAB     , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS     ,
//  |--------------------------------------------------------------------------------------------------------------------------------------|
//  |               |        |        |        |        |        |        |        |        |        | :      | "      |                   |
//  | Caps Lock     | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | Enter             |
      LT_FL         , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT            ,
//  |--------------------------------------------------------------------------------------------------------------------------------------|
//  |                   |        |        |        |        |        |        |        | <      | >      | ?      |                        |
//  | Shift             | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | Shift                  |
      KC_LSFT           , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT                ,
//  |--------------------------------------------------------------------------------------------------------------------------------------|
//  |          |          |          |                                                        |          |          |          |           |
//  | Ctrl     | Gui      | Alt      | Space                                                  | Alt      | Gui      | Fn       | Ctrl      |
      KC_LCTL  , KC_LGUI  , KC_LALT,   KC_SPC                                                 , KC_RALT  , KC_RGUI  , M_FL     , KC_RCTL   ),
//  '--------------------------------------------------------------------------------------------------------------------------------------'


  /* Keymap _FL: Function Layer
   * ,-----------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |  RESET|
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |BL-|BL+|BL   |
   * |-----------------------------------------------------------|
   * |      |   |   |   |   |   | L | D | U | R |   |   |        |
   * |-----------------------------------------------------------|
   * |        | F1|F2 | F3|F4 | F5| F6| F7| F8|   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
[LAYER_FUNCTION] = KEYMAP_ANSI(
  #ifdef RGBLIGHT_ENABLE
  KC_GRV, _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,RESET,  \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,M_BRDEF,M_BRTOG, BL_DEC,BL_INC, BL_TOGG, \
  _______,_______,_______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,_______,_______,        _______, \
  _______,RGB_TOG,RGB_MOD,RGB_HUI,RGB_HUD,RGB_SAI,RGB_SAD,RGB_VAI,RGB_VAD,_______,_______,_______, \
  _______,_______,_______,                 _______,                       _______,_______,_______, _______),
  #else
  KC_GRV, _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,RESET,  \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,M_BRDEF,M_BRTOG, BL_DEC, BL_INC,BL_TOGG, \
  _______,_______,_______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,_______,_______,        _______, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, \
  _______,_______,_______,                _______,                        _______,_______,_______,_______),
  #endif
};

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch(id) {
        case MACRO_BREATH_TOGGLE:
            if (record->event.pressed) {
                breathing_toggle();
            }
            break;
        case MACRO_BREATH_DEFAULT:
            if (record->event.pressed) {
                breathing_defaults();
            }
            break;
        default:
            break;
    }
    return MACRO_NONE;
}
