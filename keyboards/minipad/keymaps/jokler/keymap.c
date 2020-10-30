#include QMK_KEYBOARD_H

enum layers {
  DEFAULT = 0,
  NUMPAD = 1,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * ,-----------------------,
   * | F15 | F16 | F17 | VMU |
   * |-----+-----+-----+-----|
   * | PRV | STP | NXT | F18 |
   * |-----+-----+-----+-----|
   * | F21 | F22 | F23 | F20 |
   * |-----+-----+-----+-----|
   * |HYP12| HEN | MHE | NUM |
   * `-----------------------'
   */
  [DEFAULT] = LAYOUT_ortho_4x4(
    KC_F15,       KC_F16,  KC_F17,  KC_MUTE,
    KC_MPRV,      KC_MSTP, KC_MNXT, KC_F18,
    KC_F21,       KC_F22,  KC_F23,  KC_F20,
    HYPR(KC_F12), KC_HENK, KC_MHEN, TG(NUMPAD)
  ),

  /*
   * ,-----------------------,
   * |     | NLK | KP* |     |
   * |-----+-----+-----+-----|
   * | KP7 | KP8 | KP9 | KP. |
   * |-----+-----+-----+-----|
   * | KP4 | KP5 | KP6 |     |
   * |-----+-----+-----+-----|
   * | KP1 | KP2 | KP3 |     |
   * `-----------------------'
   */
  [NUMPAD] = LAYOUT_ortho_4x4(
    _______, KC_NLCK, KC_PAST, _______,
    KC_P7,   KC_P8,   KC_P9,   KC_PDOT,
    KC_P4,   KC_P5,   KC_P6,   KC_P0,
    KC_P1,   KC_P2,   KC_P3,   _______
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case NUMPAD:
      rgblight_sethsv_at(HSV_BLUE, 3);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv_at(HSV_RED, 3);
      break;
  }
  return state;
}

// Set led state during powerup
void keyboard_post_init_user(void) {
  // Unlike rgblight_set_hsv_at these don't run rgblight_set
  // so setting multiple colors at once is more efficient like this.
  sethsv(HSV_BLUE,    (LED_TYPE *)&led[0]);
  sethsv(HSV_PURPLE,  (LED_TYPE *)&led[1]);
  sethsv(HSV_MAGENTA, (LED_TYPE *)&led[2]);
  sethsv(HSV_RED,     (LED_TYPE *)&led[3]);
  rgblight_set();
}

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {         // First encoder - top left
    if (clockwise) {
      tap_code(KC_F14);
    } else {
      tap_code(KC_F13);
    }
  } else if (index == 1) {  // Second encoder - top right
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  }
}
