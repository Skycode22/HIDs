// Copyright 2022 %YOUR_FULL_NAME% (@%YOUR_GITHUB_USERNAME%)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    opentrack
#define PRODUCT         opentrack

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 2

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
#define MATRIX_ROW_PINS { E6 }
#define MATRIX_COL_PINS { B5, B4 }

#define DIODE_DIRECTION COL2ROW

#define PMW3360_CS_PIN B6
#define POINTING_DEVICE_INVERT_Y

// generated by KBFirmware JSON to QMK Parser
// https://noroadsleft.github.io/kbf_qmk_converter/

