/* Copyright 2022 REPLACE_WITH_YOUR_NAME
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LALT, KC_BSPC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LCTL, KC_LSFT, KC_H,    KC_J,    KC_K,    KC_L,    MO(1),   
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_SPC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BTN1  
    ),

    [1] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_ENT,  KC_DEL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TAB,  KC_F6,   KC_F7,   KC_F8,   KC_F,    KC_UP, _______, 
        KC_BSLS, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL,  KC_QUOT, KC_SCLN, KC_GRV, KC_LEFT,  KC_DOWN, KC_RIGHT, KC_BTN2
    ),

    [2] = LAYOUT(
        RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  
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

