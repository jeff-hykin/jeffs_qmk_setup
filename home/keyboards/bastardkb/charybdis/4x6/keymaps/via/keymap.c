/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LCTL,    PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, PT_SLSH, KC_LALT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_LGUI, KC_SPC,   LOWER,      RAISE,  KC_ENT,
                                           KC_LALT, KC_BSPC,     KC_DEL
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_LBRC,   KC_P7,   KC_P8,   KC_P9, KC_RBRC, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       RGB_TOG, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    KC_PPLS,   KC_P4,   KC_P5,   KC_P6, KC_PMNS, KC_PEQL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      RGB_RMOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_PAST,   KC_P1,   KC_P2,   KC_P3, KC_PSLS, KC_PDOT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, _______,    XXXXXXX, _______,
                                           XXXXXXX, XXXXXXX,      KC_P0
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MPLY, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, KC_MUTE,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MPRV, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, XXXXXXX,    _______, XXXXXXX,
                                           _______, _______,    XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, _______, DRGSCRL, SNIPING, EE_CLR,  QK_BOOT,    QK_BOOT, EE_CLR,  SNIPING, DRGSCRL, _______, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN3, KC_BTN1,
                                           XXXXXXX, KC_BTN2,    KC_BTN2
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

bool shutdown_user(bool) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgblight_setrgb(RGB_RED);
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif // RGB_MATRIX_ENABLE
    return false;
}

// 
// 
// custom combos
// 
// 
const int8_t indexOf_leftHand_homeRowUp2_neg_1 = 5;
const int8_t indexOf_leftHand_homeRowUp2_0 = 4;
const int8_t indexOf_leftHand_homeRowUp2_1 = 3;
const int8_t indexOf_leftHand_homeRowUp2_2 = 2;
const int8_t indexOf_leftHand_homeRowUp2_3 = 1;
const int8_t indexOf_leftHand_homeRowUp2_4 = 0;
const int8_t indexOf_leftHand_homeRowUp1_neg_1 = 11;
const int8_t indexOf_leftHand_homeRowUp1_0 = 10;
const int8_t indexOf_leftHand_homeRowUp1_1 = 9;
const int8_t indexOf_leftHand_homeRowUp1_2 = 8;
const int8_t indexOf_leftHand_homeRowUp1_3 = 7;
const int8_t indexOf_leftHand_homeRowUp1_4 = 6;
const int8_t indexOf_leftHand_homeRow_neg_1 = 17;
const int8_t indexOf_leftHand_homeRow_0 = 16;
const int8_t indexOf_leftHand_homeRow_1 = 15;
const int8_t indexOf_leftHand_homeRow_2 = 14;
const int8_t indexOf_leftHand_homeRow_3 = 13;
const int8_t indexOf_leftHand_homeRow_4 = 12;
const int8_t indexOf_leftHand_homeRowDown1_neg_1 = 23;
const int8_t indexOf_leftHand_homeRowDown1_0 = 22;
const int8_t indexOf_leftHand_homeRowDown1_1 = 21;
const int8_t indexOf_leftHand_homeRowDown1_2 = 20;
const int8_t indexOf_leftHand_homeRowDown1_3 = 19;
const int8_t indexOf_leftHand_homeRowDown1_4 = 18;
const int8_t indexOf_leftHand_thumb_0 = 27;
const int8_t indexOf_leftHand_thumb_1 = 28;
const int8_t indexOf_leftHand_thumb_2 = 25;
const int8_t indexOf_leftHand_thumb_3 = 29;
const int8_t indexOf_leftHand_thumb_4 = 26;
const int8_t indexOf_rightHand_homeRowUp2_neg_1 = 35;
const int8_t indexOf_rightHand_homeRowUp2_0 = 34;
const int8_t indexOf_rightHand_homeRowUp2_1 = 33;
const int8_t indexOf_rightHand_homeRowUp2_2 = 32;
const int8_t indexOf_rightHand_homeRowUp2_3 = 31;
const int8_t indexOf_rightHand_homeRowUp2_4 = 30;
const int8_t indexOf_rightHand_homeRowUp1_neg_1 = 41;
const int8_t indexOf_rightHand_homeRowUp1_0 = 40;
const int8_t indexOf_rightHand_homeRowUp1_1 = 39;
const int8_t indexOf_rightHand_homeRowUp1_2 = 38;
const int8_t indexOf_rightHand_homeRowUp1_3 = 37;
const int8_t indexOf_rightHand_homeRowUp1_4 = 36;
const int8_t indexOf_rightHand_homeRow_neg_1 = 47;
const int8_t indexOf_rightHand_homeRow_0 = 46;
const int8_t indexOf_rightHand_homeRow_1 = 45;
const int8_t indexOf_rightHand_homeRow_2 = 44;
const int8_t indexOf_rightHand_homeRow_3 = 43;
const int8_t indexOf_rightHand_homeRow_4 = 42;
const int8_t indexOf_rightHand_homeRowDown1_neg_1 = 53;
const int8_t indexOf_rightHand_homeRowDown1_0 = 52;
const int8_t indexOf_rightHand_homeRowDown1_1 = 51;
const int8_t indexOf_rightHand_homeRowDown1_2 = 50;
const int8_t indexOf_rightHand_homeRowDown1_3 = 49;
const int8_t indexOf_rightHand_homeRowDown1_4 = 48;
const int8_t indexOf_rightHand_thumb_0 = 55;
const int8_t indexOf_rightHand_thumb_1 = 57;
const int8_t indexOf_rightHand_thumb_2 = 59;


uint16_t keys_down = 0;
bool physical_key_is_down[MATRIX_ROWS*MATRIX_COLS] = {0};
bool ignore_keyup_of[MATRIX_ROWS*MATRIX_COLS] = {0};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // setup
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;
    uint16_t index = row * MATRIX_COLS + col;
    const bool key_is_going_down = record->event.pressed;
    bool some_other_physical_key_is_down = keys_down >= 1;
    if (key_is_going_down) {
        keys_down++;
        physical_key_is_down[index] = true;
    } else {
        keys_down--;
        physical_key_is_down[index] = false;
    }
    if (false && some_other_physical_key_is_down) {} // defeat the "warning not used" check
        
    // 
    // boot key
    // 
    if (index == indexOf_rightHand_homeRowUp2_4) {
        reset_keyboard();
        return false;
    }
    
    // // happens because of combos
    // if (!key_is_going_down && ignore_keyup_of[index]) {
    //     // reset
    //     ignore_keyup_of[index] = false;
    //     return false;
    // }
    
    //
    // hold space press m equals
    // 
    const int8_t f_index = indexOf_leftHand_homeRow_0;
    const int8_t c_index = indexOf_leftHand_homeRowDown1_0;
    const int8_t r_index = indexOf_leftHand_homeRowUp1_0;
    const int8_t n_index = indexOf_rightHand_homeRowDown1_0;
    if (key_is_going_down && index == n_index) {
        if (physical_key_is_down[f_index]) {
            tap_code(KC_U);
            tap_code(KC_N);
            tap_code(KC_C);
            tap_code(KC_T);
            tap_code(KC_I);
            tap_code(KC_O);
            tap_code(KC_N);
            ignore_keyup_of[f_index] = true;
            ignore_keyup_of[n_index] = true;
            return false;
        } else if (physical_key_is_down[c_index]) {
            tap_code(KC_O);
            tap_code(KC_N);
            tap_code(KC_S);
            tap_code(KC_T);
            tap_code(KC_SPC);
            ignore_keyup_of[c_index] = true;
            ignore_keyup_of[n_index] = true;
            return false;
        } else if (physical_key_is_down[r_index]) {
            tap_code(KC_E);
            tap_code(KC_T);
            tap_code(KC_U);
            tap_code(KC_R);
            tap_code(KC_N);
            tap_code(KC_SPC);
            ignore_keyup_of[r_index] = true;
            ignore_keyup_of[n_index] = true;
            return false;
        }
    }
    // const int m_or_equals_index = indexOf_leftHand_homeRowDown1_1;
    // if (index == m_or_equals_index && physical_key_is_down[right_thumb_mod1_index]) {
    //     if (key_is_going_down) {
    //         return false;
    //     }
    //     // delete the junk thing that will be typed
    //     tap_code(KC_EQL);
    //     // tap_code(KC_SPC);
    //     return false;
    // }
    
    // return handle_key_event(keycode, record, physical_key_is_down, keys_down, index, row, col, key_is_going_down, some_other_physical_key_is_down);
    return true;
};
