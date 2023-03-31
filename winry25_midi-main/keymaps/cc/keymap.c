// Copyright 2022 Kostiantyn Yerokhin (@err5)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "midi.h"

extern MidiDevice midi_device;

#define MIDI_CC_OFF 0
#define MIDI_CC_ON 127

int current_MIDI_ccNumber;

enum MIDI_cc_keycodes_LTRM { MI_CC01 = SAFE_RANGE, MI_CC02, MI_CC03, MI_CC04, MI_CC05, MI_CC06, MI_CC07, MI_CC08, MI_CC09, MI_CC10, MI_CC11, MI_CC12, MI_CC13, MI_CC14, MI_CC15, MI_CC16, MI_CC17, MI_CC18, MI_CC19, MI_CC20, MI_CC21, MI_CC22, MI_CC23, MI_CC24, MI_CC25 };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT(MI_CC01, MI_CC02, MI_CC03, MI_CC04, MI_CC05, MI_CC06, MI_CC07, MI_CC08, MI_CC09, MI_CC10, MI_CC11, MI_CC12, MI_CC13, MI_CC14, MI_CC15, MI_CC16, MI_CC17, MI_CC18, MI_CC19, MI_CC01, MI_CC21, MI_CC21, MI_CC22, MI_CC23, MI_CC01)};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MI_CC01:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 1;
            }
            break;
        case MI_CC02:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 2;
            }
            break;
        case MI_CC03:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 3;
            }
            break;
        case MI_CC04:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 4;
            }
            break;
        case MI_CC05:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 5;
            }
            break;
        case MI_CC06:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 6;
            }
            break;
        case MI_CC07:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 7;
            }
            break;
        case MI_CC08:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 8;
            }
            break;
        case MI_CC09:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 9;
            }
            break;
        case MI_CC10:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 10;
            }
            break;
        case MI_CC11:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 11;
            }
            break;
        case MI_CC12:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 12;
            }
            break;
        case MI_CC13:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 13;
            }
            break;
        case MI_CC14:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 14;
            }
            break;
        case MI_CC15:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 15;
            }
            break;
        case MI_CC16:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 16;
            }
            break;
        case MI_CC17:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 17;
            }
            break;
        case MI_CC18:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 18;
            }
            break;
        case MI_CC19:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 19;
            }
            break;
        case MI_CC20:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 20;
            }
            break;
        case MI_CC21:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 21;
            }
            break;
        case MI_CC22:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 22;
            }
            break;
        case MI_CC23:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 23;
            }
            break;
        case MI_CC24:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 24;
            }
            break;
        case MI_CC25:
            if (record->event.pressed) {
                current_MIDI_ccNumber = 25;
            }
            break;
        default:
            break;
    }

    if (record->event.pressed) {
        midi_send_cc(&midi_device, midi_config.channel, current_MIDI_ccNumber, MIDI_CC_ON);
    } else {
        midi_send_cc(&midi_device, midi_config.channel, current_MIDI_ccNumber, MIDI_CC_OFF);
    }
    return true;
}
