// Copyright 2022 Constantine Yerokhin (@err5)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define MATRIX_ROWS 5
#define MATRIX_COLS 5

#define MATRIX_ROW_PINS \
    { E6, F0, D6, D2, B6 }
#define MATRIX_COL_PINS \
    { F5, C7, B7, B2, B4 }

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN D5
#define RGBLED_NUM 40
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 150 /* The maximum brightness level */

#define MIDI_ADVANCED
