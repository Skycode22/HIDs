// Copyright 2022 Kostiantyn Yerokhin (@err5)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        MI_C,       MI_Cs,      MI_D,     	MI_Ds,      MI_E,
        MI_F,       MI_Gs,      MI_A,       MI_As,      MI_B,
        MI_C_1,     MI_Cs_1,    MI_D_1,	    MI_Ds_1,    MI_E_1,
        MI_F_1,     MI_Fs_1,    MI_G_1,   	MI_Gs_1,    MI_A_1,
        MI_As_1,    MI_B_1,     MI_C_2,     MI_Cs_2,	MI_D_2
    )
};

