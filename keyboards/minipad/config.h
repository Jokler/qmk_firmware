#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xB00B
#define DEVICE_VER      0x0001
#define MANUFACTURER    Jokler
#define PRODUCT         MiniPad
#define DESCRIPTION     4x4 numpad based on ProMicro with Mini USB

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

// wiring of each half
#define MATRIX_ROW_PINS { D4, C6, F4, F5 }
#define MATRIX_COL_PINS { B4, B5, B2, B6 }

#define ENCODERS_PAD_A { E6, F6 }
#define ENCODERS_PAD_B { D7, F7 }
#define ENCODER_DIRECTION_FLIP
#define ENCODER_RESOLUTION 4

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* define tapping term */
#define TAPPING_TERM 120

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN D3
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 4
