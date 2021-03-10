/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once

#undef TAPPING_TERM
#define TAPPING_TERM 200
#define NKRO_ENABLE
#define SWAP_HANDS_ENABLE

#define MK_3_SPEED
#define MK_C_OFFSET_0 	4
#define MK_C_INTERVAL_0 16
#define MK_C_OFFSET_1 	32
#define MK_C_INTERVAL_1 16
#define MK_C_OFFSET_2 	64
#define MK_C_INTERVAL_2 8

#undef RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT

/* Use I2C or Serial, not both */
#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */
// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS
