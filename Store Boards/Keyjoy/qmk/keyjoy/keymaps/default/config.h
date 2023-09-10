/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

/* Mouse control configuration */

/* Cursor speed */
#define ANALOG_JOYSTICK_SPEED_MAX 3
#define ANALOG_JOYSTICK_SPEED_REGULATOR 20

#define ANALOG_JOYSTICK_Y_AXIS_PIN GP26
#define ANALOG_JOYSTICK_X_AXIS_PIN GP27

#define POINTING_DEVICE_INVERT_X
#define POINTING_DEVICE_INVERT_Y

/* Mouse inertia (keeps sliding after a flick) */
// #define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE