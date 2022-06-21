// Copyright 2022 %YOUR_FULL_NAME% (@%YOUR_GITHUB_USERNAME%)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    openex
#define PRODUCT         openex

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 4

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { B5 }
#define MATRIX_COL_PINS { B4, E6, D7, C6 }

#define DIODE_DIRECTION COL2ROW

#define ADNS9800_CS_PIN F7
#define POINTING_DEVICE_INVERT_X

#define ENCODERS_PAD_A { D4 }
#define ENCODERS_PAD_B { D0 }
#define ENCODER_RESOLUTION 4


// generated by KBFirmware JSON to QMK Parser
// https://noroadsleft.github.io/kbf_qmk_converter/

