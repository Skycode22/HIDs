// Copyright 2022 %YOUR_FULL_NAME% (@%YOUR_GITHUB_USERNAME%)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    MO(1),   
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, 
        KC_LSFT, KC_LCTL, KC_SPC,  KC_BTN2, KC_BTN1, KC_COPY, KC_BSPC, KC_BSPC, KC_RALT, KC_ENT   
    ),

    [1] = LAYOUT(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, 
        KC_TAB, KC_F10, KC_F11, KC_F12, _______, _______, _______, _______, _______, _______, 
        KC_GRV, KC_FIND, _______, _______, _______, _______, _______, _______, _______, _______, 
        KC_BSLS, KC_LBRC, KC_RBRC, KC_EQL,  KC_MINS, KC_SCLN, KC_QUOT, KC_GRV,  KC_TAB,  KC_BSLS, 
        OUT_AUTO, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT  
    ),

    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,   
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  
    ),

};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code_delay(KC_WH_U, 10);
        } else {
            tap_code_delay(KC_WH_D, 10);
        }
    }
    return false;
}

