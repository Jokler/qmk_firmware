#include QMK_KEYBOARD_H


#define _COLEMAK 0
#define _QWERTY 1
#define _GAME 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  MPUBKEY,
  SPAMSPACE,
  SPAMAD,
  MREMOVE,
  MHOME1,
  MHOME2,
  MHOME3,
  MTPA,
  MTPRAPI,
  MTPISUK,
};

#define GAME TG(_GAME)
#define QWERTY TG(_QWERTY)
#define BOTHCTL LCTL(KC_RCTL)
#define SHT_INS SH_T(KC_INS)

uint16_t space_interval = 150;
uint16_t ad_interval = 110;
uint16_t interval_time = 110;
uint16_t keypress_timer = 0;
bool space_spam = false;
bool ad_spam = false;
bool last_was_t = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Colemak-dh
   * ,------------------------------------------------------------------------------------------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |   -  |                      |   =  |   6  |   7  |   8  |   9  |   0  |Pscree|
   * |------+------+------+------+------+------+------+----------------------+------+------+------+------+------+------+------|
   * |  `   |   Q  |   W  |   F  |   P  |   B  |   [  |                      |   ]  |   J  |   L  |   U  |   Y  |   ;  |  \   |
   * |------+------+------+------+------+------+------+----------------------+------+------+------+------+------+------+------|
   * | Tab  |   A  |   R  |   S  |   T  |   G  | HOME |                      |  END |   K  |   N  |   E  |   I  |   O  |  "   |
   * |------+------+------+------+------+------+------+----------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   D  |   V  |  Ins |                      |  Del |   M  |   H  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+-------+------+-------+------+------+------+------+------+------+------|
   * | Ctrl | PGDN | PGUP | LAlt |||||||| LGui | Lower| Space |||||||| Enter | Raise| Bksp |||||||| Left | Down |  Up  | Right|
   * ,------------------------------------------------------------------------------------------------------------------------.
   */
  [_COLEMAK] = LAYOUT( \
    KC_ESC , KC_1   , KC_2   , KC_3   , KC_4, KC_5   , KC_MINS,                 KC_EQL , KC_6   , KC_7, KC_8   , KC_9   , KC_0   , KC_PSCR, \
    KC_GRV , KC_Q   , KC_W   , KC_F   , KC_P, KC_B   , KC_LBRC,                 KC_RBRC, KC_J   , KC_L, KC_U   , KC_Y   , KC_SCLN, KC_BSLS, \
    KC_TAB , KC_A   , KC_R   , KC_S   , KC_T, KC_G   , KC_HOME,                 KC_END , KC_K   , KC_N, KC_E   , KC_I   , KC_O   , KC_QUOT, \
    KC_LSPO, KC_Z   , KC_X   , KC_C   , KC_D, KC_V   , SHT_INS,                 KC_DEL , KC_M   , KC_H, KC_COMM, KC_DOT , KC_SLSH, KC_RSPC, \
    KC_LCTL, KC_PGDN, KC_PGUP, KC_LALT,       KC_LGUI, LOWER  , KC_SPC, KC_ENT, RAISE  , KC_BSPC,       KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT  \
  ),

  /* Qwerty
   * ,------------------------------------------------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |      |                      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+----------------------+------+------+------+------+------+------+------|
   * |      |   Q  |   W  |   E  |   R  |   T  |      |                      |      |   Y  |   U  |   I  |   O  |   P  |      |
   * |------+------+------+------+------+------+------+----------------------+------+------+------+------+------+------+------|
   * |      |   A  |   S  |   D  |   F  |   G  |      |                      |      |   H  |   J  |   K  |   L  |   ;  |      |
   * |------+------+------+------+------+------+------+----------------------+------+------+------+------+------+------+------|
   * |      |   Z  |   X  |   C  |   V  |   B  |      |                      |      |   N  |   M  |   ,  |   .  |   /  |      |
   * |------+------+------+------+------+------+------+-------+------+-------+------+------+------+------+------+------+------|
   * |      |      |      |      ||||||||      | Lower|       ||||||||       | Raise|      ||||||||      |      |      |      |
   * ,------------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT( \
    _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, \
    _______, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , _______,                   _______, KC_Y   , KC_U,    KC_I   , KC_O   , KC_P   , _______, \
    _______, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , _______,                   _______, KC_H   , KC_J,    KC_K   , KC_L   , KC_SCLN, _______, \
    _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , _______,                   _______, KC_N   , KC_M,    KC_COMM, KC_DOT , KC_SLSH, _______, \
    _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______  \
  ),

  /* Game
   * ,------------------------------------------------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |   6  |                      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+----------------------+------+------+------+------+------+------+------|
   * |      |  Tab |   Q  |   W  |   E  |   R  |   T  |                      |      |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+----------------------+------+------+------+------+------+------+------|
   * |      | Shift|   A  |   S  |   D  |   F  |   G  |                      |      |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+------+----------------------+------+------+------+------+------+------+------|
   * |      | Ctrl |   Z  |   X  |   C  |   V  |   B  |                      |      |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+-------+------+-------+------+------+------+------+------+------+------|
   * |      |      |      |      ||||||||      | Lower|       ||||||||       | Raise|      ||||||||      |      |      |      |
   * ,------------------------------------------------------------------------------------------------------------------------.
   */
  [_GAME] = LAYOUT( \
    _______, _______, _______, _______, _______, _______, KC_6   ,                   _______, _______, _______, _______, _______, _______, _______, \
    _______, KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   _______, KC_Y   , KC_U,    KC_I   , KC_O   , KC_P   , KC_BSLS, \
    _______, KC_LSFT, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   _______, KC_H   , KC_J,    KC_K   , KC_L   , KC_SCLN, KC_QUOT, \
    _______, KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                   _______, KC_N   , KC_M,    KC_COMM, KC_DOT , KC_SLSH, KC_RSFT, \
    _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______  \
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  | REMV |                    |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      | MWDN | MOUP | MWUP |      |      |                    |      |      |  M1  |  M2  |  M3  |  M4  |  M5  |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | BCTL | WHLE | MOLE | MODN | MORE | WHRI |      |                    |      |   H  |   J  |   K  |   L  |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      | MSS0 | MSS1 | MSS2 |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      | Lower|      ||||||||      | Raise|      |||||||| Home |PageDn|PageUp|  End |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
    KC_F11 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , MREMOVE,                    _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F12 , \
    _______, _______, KC_WH_D, KC_MS_U, KC_WH_U, _______, _______,                    _______, _______, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5, \
    BOTHCTL, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, _______,                    _______, KC_H   , KC_J   , KC_K   , KC_L   , _______, _______, \
    KC_LOCK, _______, _______, _______, _______, _______, _______,                    _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, \
    _______, _______, _______, _______,          _______, _______, _______,  _______, _______, _______,          KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
  ),

  /* Raise
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |   {  |                    |   }  |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |   !  |   @  |   #  |   $  |   %  |   _  |                    |   +  |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |   1  |   2  |   3  |   4  |   5  |      |                    |      |   6  |   7  |   8  |   9  |   0  |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      |||||||| Lower|      |      ||||||||      |      | Raise|||||||| Home |PageDn|PageUp|  End |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_RAISE] = LAYOUT(
    KC_F11 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_LCBR,                    KC_RCBR, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F12 , \
    _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_UNDS,                    KC_PLUS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , _______,                    _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______, \
    _______, _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______, _______, _______,  _______, _______, _______,          KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
  ),

  /* Adjust
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | NKRO | HOM1 | HOM2 | HOM3 |      |      |      |                    | RESET|      |      |      |      |      | SSHK |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |QWERTY|      |RGBTOG| BLTOG|  BL- |  BL+ |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |COLMAK| TPA  | TPRA | TPIS |      | GAME |      |                    |ADSPAM|      |      |      |      |      |SPSPAM|
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      |||||||| Lower|      |      ||||||||      |      | Raise||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
    NK_TOGG, MHOME1 , MHOME2 , MHOME3 , _______, _______, _______,                   RESET  , _______, _______, _______, _______, _______, MPUBKEY, \
    QWERTY , _______, RGB_TOG, BL_TOGG, BL_DEC , BL_INC , _______,                   _______, _______, _______, _______, _______, _______, _______, \
    COLEMAK, MTPA   , MTPRAPI, MTPISUK, _______, GAME   , _______,                   SPAMAD , _______, _______, _______, _______, _______, SPAMSPACE, \
    _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______  \

  )
};


#ifdef SWAP_HANDS_ENABLE
// swap-hands action needs a matrix to define the swap
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{0,5}, {1,5}, {2,5}, {3,5}, {4,5}, {5,5}, {6,5}},
    {{0,6}, {1,6}, {2,6}, {3,6}, {4,6}, {5,6}, {6,6}},
    {{0,7}, {1,7}, {2,7}, {3,7}, {4,7}, {5,7}, {6,7}},
    {{0,8}, {1,8}, {2,8}, {3,8}, {4,8}, {5,8}, {6,8}},
    {{0,9}, {1,9}, {2,9}, {3,9}, {4,9}, {5,9}, {6,9}},
    /* Right hand, matrix positions */
    {{0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,1}},
    {{0,1}, {1,1}, {2,1}, {3,1}, {4,1}, {5,1}, {6,2}},
    {{0,2}, {1,2}, {2,2}, {3,2}, {4,2}, {5,2}, {6,3}},
    {{0,3}, {1,3}, {2,3}, {3,3}, {4,3}, {5,3}, {6,4}},
    {{0,4}, {1,4}, {2,4}, {3,4}, {4,4}, {5,4}, {6,5}},
};
#endif

const uint16_t RGBLED_GRADIENT_RANGES[] PROGMEM = {100};

void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom();
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT);
  rgblight_sethsv_noeeprom(160, 0xff, 0x3f);

  backlight_level(1);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
  case _COLEMAK:
      rgblight_sethsv_noeeprom(160, 0xff, 0x3f);
      break;
  case _QWERTY:
      rgblight_sethsv_noeeprom(30, 0xff, 0x3f);
      break;
  case _LOWER:
      rgblight_sethsv_noeeprom(130, 0xff, 0x3f);
      break;
  case _RAISE:
      rgblight_sethsv_noeeprom(190, 0xff, 0x3f);
      break;
  case _ADJUST:
      rgblight_sethsv_noeeprom(220, 0xff, 0x3f);
      break;
  case _GAME:
      rgblight_sethsv_noeeprom(250, 0xff, 0x3f);
      break;
  default:
      rgblight_setrgb(0xff, 0, 0);
      break;
  }
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case MPUBKEY:
      if (record->event.pressed) {
        // public key
        SEND_STRING("ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIOvrn/AGpAUCGYGOYv+h6VztmOAUeajrE4NRT01r4ASF jokler@iwatani");
      }
      break;
    case SPAMSPACE:
      if (record->event.pressed) {
          keypress_timer = timer_read();
          space_spam = !space_spam;
      }
      break;
    case SPAMAD:
      if (record->event.pressed) {
          keypress_timer = timer_read();
          ad_spam = !ad_spam;
      }
      break;
    // Weird rust stuff
    case MREMOVE:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ENTER) "/remove" SS_TAP(X_ENTER));
      }
      break;
    case MHOME1:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ENTER) "/home 1" SS_TAP(X_ENTER));
      }
      break;
    case MHOME2:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ENTER) "/home 2" SS_TAP(X_ENTER));
      }
      break;
    case MHOME3:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ENTER) "/home 3" SS_TAP(X_ENTER));
      }
      break;
    case MTPRAPI:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ENTER) "/tpr Rapid" SS_TAP(X_ENTER));
      }
      break;
    case MTPISUK:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ENTER) "/tpr Isuk" SS_TAP(X_ENTER));
      }
      break;
    case MTPA:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ENTER));
        SEND_STRING("t"SS_DELAY(1000)"t");
        SEND_STRING("/tpa" SS_TAP(X_ENTER));
      }
      break;
  }
  return true;
}

// Dead by Daylight fix terrible gameplay
void matrix_scan_user(void) {
  if (space_spam && timer_elapsed(keypress_timer) > space_interval) {
    keypress_timer += space_interval;
    SEND_STRING(" ");
    return;
  }

  if (ad_spam && timer_elapsed(keypress_timer) > ad_interval) {
    keypress_timer += ad_interval;
    if (last_was_t) {
        SEND_STRING("r");
    } else {
        SEND_STRING("t");
    }
    last_was_t = !last_was_t;
    return;
  }
}
