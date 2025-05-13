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

//   keyevent_t event {
//         keypos_t key {
//         uint8_t col
//         uint8_t row
//         }
//         bool     pressed
//         uint16_t time
//     }

bool handle_key_event(uint16_t keycode, keyrecord_t *record, bool physical_key_is_down[MATRIX_ROWS * MATRIX_COLS], uint16_t keys_down, uint16_t index, uint8_t row, uint8_t col, bool keydown, bool some_other_physical_key_is_down);


bool key_was_consumed[MATRIX_ROWS*MATRIX_COLS] = {0};
#define number_of_physical_keys_that_can_be_down_at_the_same_time 30 // realistically on a human hand (three keys per finger)
uint16_t key_press_history[number_of_physical_keys_that_can_be_down_at_the_same_time] = {0};
bool handle_key_event(uint16_t keycode, keyrecord_t *record_ptr, bool physical_key_is_down[MATRIX_ROWS * MATRIX_COLS], uint16_t keys_down, uint16_t index, uint8_t row, uint8_t col, bool keydown, bool some_other_physical_key_is_down) {
    if (keydown) {
        key_press_history[keys_down] = index;
    }
    bool key_pressed_on_left_hand = index == 5 || index == 4 || index == 3 || index == 2 || index == 1 || index == 0 || index == 11 || index == 10 || index == 9 || index == 8 || index == 7 || index == 6 || index == 17 || index == 16 || index == 15 || index == 14 || index == 13 || index == 12 || index == 23 || index == 22 || index == 21 || index == 20 || index == 19 || index == 18 || index == 27 || index == 28 || index == 25 || index == 29 || index == 26;
    
    bool ctrl_physical_key_is_down = physical_key_is_down[(key_pressed_on_left_hand ? 42 : 12)];
    bool shift_physical_key_is_down = physical_key_is_down[(key_pressed_on_left_hand ? 44 : 14)];
    bool alt_physical_key_is_down = physical_key_is_down[(key_pressed_on_left_hand ? 45 : 15)];
    bool gui_physical_key_is_down = physical_key_is_down[(key_pressed_on_left_hand ? 46 : 16)];
    
    // do nothing on keyup of any "consumed" key
    if (!keydown && key_was_consumed[index]) {
        key_was_consumed[index] = false;
        return false;
    }

    // 
    // boot key
    // 
    if (index == 30) {
        reset_keyboard();
        return false;
    }
    
    // 
    // two key combos
    // 
        // "FD" combo
        if (physical_key_is_down[16] && physical_key_is_down[15]) {
            // 
            // tab
            // 
            // KC_TAB + modifiers
                if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                    tap_code(KC_TAB);
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(LGUI(KC_TAB)))));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LALT(LGUI(KC_TAB))));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LALT(LGUI(KC_TAB))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LGUI(KC_TAB))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(KC_TAB))));
                } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LALT(LGUI(KC_TAB)));
                } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LGUI(KC_TAB)));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LCTL(LALT(KC_TAB)));
                } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LGUI(KC_TAB)));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LALT(KC_TAB)));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(KC_TAB)));
                } else if (gui_physical_key_is_down) {
                    tap_code16(LGUI(KC_TAB));
                } else if (alt_physical_key_is_down) {
                    tap_code16(LALT(KC_TAB));
                } else if (ctrl_physical_key_is_down) {
                    tap_code16(LCTL(KC_TAB));
                } else if (shift_physical_key_is_down) {
                    tap_code16(LSFT(KC_TAB));
                }
            key_was_consumed[16] = true;
            key_was_consumed[15] = true;
            // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed));
            return false;
        }
        // "AS" combo
        if (physical_key_is_down[14] && physical_key_is_down[13]) {
            // 
            // Esc
            // 
            // KC_ESC + modifiers
                if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                    tap_code(KC_ESC);
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(LGUI(KC_ESC)))));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LALT(LGUI(KC_ESC))));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LALT(LGUI(KC_ESC))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LGUI(KC_ESC))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(KC_ESC))));
                } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LALT(LGUI(KC_ESC)));
                } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LGUI(KC_ESC)));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LCTL(LALT(KC_ESC)));
                } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LGUI(KC_ESC)));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LALT(KC_ESC)));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(KC_ESC)));
                } else if (gui_physical_key_is_down) {
                    tap_code16(LGUI(KC_ESC));
                } else if (alt_physical_key_is_down) {
                    tap_code16(LALT(KC_ESC));
                } else if (ctrl_physical_key_is_down) {
                    tap_code16(LCTL(KC_ESC));
                } else if (shift_physical_key_is_down) {
                    tap_code16(LSFT(KC_ESC));
                }
            key_was_consumed[14] = true;
            key_was_consumed[13] = true;
            // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed));
            return false;
        }
    // 
    // rightThumbMod1 (arrowLayer)
    // 
        if (index == 57) {
            if (keydown) {
                return false; // do nothing on keydown (other than remember it)
            // if not "consumed" 
            } else {
                // activate the normal key
                // KC_SPC + modifiers
                if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                    tap_code(KC_SPC);
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(LGUI(KC_SPC)))));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LALT(LGUI(KC_SPC))));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LALT(LGUI(KC_SPC))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LGUI(KC_SPC))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(KC_SPC))));
                } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LALT(LGUI(KC_SPC)));
                } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LGUI(KC_SPC)));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LCTL(LALT(KC_SPC)));
                } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LGUI(KC_SPC)));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LALT(KC_SPC)));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(KC_SPC)));
                } else if (gui_physical_key_is_down) {
                    tap_code16(LGUI(KC_SPC));
                } else if (alt_physical_key_is_down) {
                    tap_code16(LALT(KC_SPC));
                } else if (ctrl_physical_key_is_down) {
                    tap_code16(LCTL(KC_SPC));
                } else if (shift_physical_key_is_down) {
                    tap_code16(LSFT(KC_SPC));
                }
                return false;
            }
        }
    
    // 
    // rightThumbMod2 (numberLayer)
    // 
        if (index == 55) {
            if (keydown) {
                return false; // do nothing on keydown (other than remember it)
            // if not "consumed" 
            } else {
                // activate the normal key
                // KC_SPC + modifiers
                if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                    tap_code(KC_SPC);
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(LGUI(KC_SPC)))));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LALT(LGUI(KC_SPC))));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LALT(LGUI(KC_SPC))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LGUI(KC_SPC))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(KC_SPC))));
                } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LALT(LGUI(KC_SPC)));
                } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LGUI(KC_SPC)));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LCTL(LALT(KC_SPC)));
                } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LGUI(KC_SPC)));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LALT(KC_SPC)));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(KC_SPC)));
                } else if (gui_physical_key_is_down) {
                    tap_code16(LGUI(KC_SPC));
                } else if (alt_physical_key_is_down) {
                    tap_code16(LALT(KC_SPC));
                } else if (ctrl_physical_key_is_down) {
                    tap_code16(LCTL(KC_SPC));
                } else if (shift_physical_key_is_down) {
                    tap_code16(LSFT(KC_SPC));
                }
                return false;
            }
        }
    // 
    // spacebar modifier
    // 
        if (physical_key_is_down[57] || physical_key_is_down[55]) {
            // 
            // backspace
            // 
            if (index == 37) {
                // KC_BSPC + modifiers
                    if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                        tap_code(KC_BSPC);
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(LGUI(KC_BSPC)))));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LALT(LGUI(KC_BSPC))));
                    } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LALT(LGUI(KC_BSPC))));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LGUI(KC_BSPC))));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(KC_BSPC))));
                    } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LALT(LGUI(KC_BSPC)));
                    } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LGUI(KC_BSPC)));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LCTL(LALT(KC_BSPC)));
                    } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LGUI(KC_BSPC)));
                    } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LALT(KC_BSPC)));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(KC_BSPC)));
                    } else if (gui_physical_key_is_down) {
                        tap_code16(LGUI(KC_BSPC));
                    } else if (alt_physical_key_is_down) {
                        tap_code16(LALT(KC_BSPC));
                    } else if (ctrl_physical_key_is_down) {
                        tap_code16(LCTL(KC_BSPC));
                    } else if (shift_physical_key_is_down) {
                        tap_code16(LSFT(KC_BSPC));
                    }
                key_was_consumed[37] = true;
                key_was_consumed[57] = true;
                // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed));
                return false;
            }
        }
        if (physical_key_is_down[57]) {
            // 
            // arrow keys
            // 
                // 
                // up
                // 
                if (index == 39) {
                    // KC_UP + modifiers
                    if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                        tap_code(KC_UP);
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(LGUI(KC_UP)))));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LALT(LGUI(KC_UP))));
                    } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LALT(LGUI(KC_UP))));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LGUI(KC_UP))));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(KC_UP))));
                    } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LALT(LGUI(KC_UP)));
                    } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LGUI(KC_UP)));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LCTL(LALT(KC_UP)));
                    } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LGUI(KC_UP)));
                    } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LALT(KC_UP)));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(KC_UP)));
                    } else if (gui_physical_key_is_down) {
                        tap_code16(LGUI(KC_UP));
                    } else if (alt_physical_key_is_down) {
                        tap_code16(LALT(KC_UP));
                    } else if (ctrl_physical_key_is_down) {
                        tap_code16(LCTL(KC_UP));
                    } else if (shift_physical_key_is_down) {
                        tap_code16(LSFT(KC_UP));
                    }
                    key_was_consumed[39] = true;
                    key_was_consumed[57] = true;
                    // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed));
                    return false;
                }
                // 
                // down
                // 
                if (index == 45) {
                    // KC_DOWN + modifiers
                    if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                        tap_code(KC_DOWN);
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(LGUI(KC_DOWN)))));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LALT(LGUI(KC_DOWN))));
                    } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LALT(LGUI(KC_DOWN))));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LGUI(KC_DOWN))));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(KC_DOWN))));
                    } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LALT(LGUI(KC_DOWN)));
                    } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LGUI(KC_DOWN)));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LCTL(LALT(KC_DOWN)));
                    } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LGUI(KC_DOWN)));
                    } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LALT(KC_DOWN)));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(KC_DOWN)));
                    } else if (gui_physical_key_is_down) {
                        tap_code16(LGUI(KC_DOWN));
                    } else if (alt_physical_key_is_down) {
                        tap_code16(LALT(KC_DOWN));
                    } else if (ctrl_physical_key_is_down) {
                        tap_code16(LCTL(KC_DOWN));
                    } else if (shift_physical_key_is_down) {
                        tap_code16(LSFT(KC_DOWN));
                    }
                    key_was_consumed[57] = true;
                    key_was_consumed[45] = true;
                    // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed));
                    return false;
                }
                // 
                // left
                // 
                if (index == 46) {
                    // KC_LEFT + modifiers
                    if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                        tap_code(KC_LEFT);
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(LGUI(KC_LEFT)))));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LALT(LGUI(KC_LEFT))));
                    } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LALT(LGUI(KC_LEFT))));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LGUI(KC_LEFT))));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(KC_LEFT))));
                    } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LALT(LGUI(KC_LEFT)));
                    } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LGUI(KC_LEFT)));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LCTL(LALT(KC_LEFT)));
                    } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LGUI(KC_LEFT)));
                    } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LALT(KC_LEFT)));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(KC_LEFT)));
                    } else if (gui_physical_key_is_down) {
                        tap_code16(LGUI(KC_LEFT));
                    } else if (alt_physical_key_is_down) {
                        tap_code16(LALT(KC_LEFT));
                    } else if (ctrl_physical_key_is_down) {
                        tap_code16(LCTL(KC_LEFT));
                    } else if (shift_physical_key_is_down) {
                        tap_code16(LSFT(KC_LEFT));
                    }
                    key_was_consumed[57] = true;
                    key_was_consumed[46] = true;
                    //memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed));
                    return false;
                }
                // 
                // right
                // 
                if (index == 44) {
                    // KC_RGHT + modifiers
                    if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                        tap_code(KC_RGHT);
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(LGUI(KC_RGHT)))));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LALT(LGUI(KC_RGHT))));
                    } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LALT(LGUI(KC_RGHT))));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LGUI(KC_RGHT))));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(KC_RGHT))));
                    } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LALT(LGUI(KC_RGHT)));
                    } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LGUI(KC_RGHT)));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LCTL(LALT(KC_RGHT)));
                    } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LGUI(KC_RGHT)));
                    } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LALT(KC_RGHT)));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(KC_RGHT)));
                    } else if (gui_physical_key_is_down) {
                        tap_code16(LGUI(KC_RGHT));
                    } else if (alt_physical_key_is_down) {
                        tap_code16(LALT(KC_RGHT));
                    } else if (ctrl_physical_key_is_down) {
                        tap_code16(LCTL(KC_RGHT));
                    } else if (shift_physical_key_is_down) {
                        tap_code16(LSFT(KC_RGHT));
                    }
                    key_was_consumed[57] = true;
                    key_was_consumed[44] = true;
                    // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed)); 
                    return false;
                }
            // 
            // return/enter
            // 
            if (index == 43) {
                // KC_9 + modifiers
                    if (!true && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                        tap_code(KC_9);
                    } else if (true && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(LGUI(KC_9)))));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LALT(LGUI(KC_9))));
                    } else if (true && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LALT(LGUI(KC_9))));
                    } else if (true && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LGUI(KC_9))));
                    } else if (true && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(KC_9))));
                    } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LALT(LGUI(KC_9)));
                    } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LGUI(KC_9)));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LCTL(LALT(KC_9)));
                    } else if (true && gui_physical_key_is_down) {
                        tap_code16(LSFT(LGUI(KC_9)));
                    } else if (true && alt_physical_key_is_down) {
                        tap_code16(LSFT(LALT(KC_9)));
                    } else if (true && ctrl_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(KC_9)));
                    } else if (gui_physical_key_is_down) {
                        tap_code16(LGUI(KC_9));
                    } else if (alt_physical_key_is_down) {
                        tap_code16(LALT(KC_9));
                    } else if (ctrl_physical_key_is_down) {
                        tap_code16(LCTL(KC_9));
                    } else if (true) {
                        tap_code16(LSFT(KC_9));
                    }
                key_was_consumed[57] = true;
                key_was_consumed[43] = true;
                // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed)); 
                return false;
            }
            // 
            // parentheses 
            // 
            if (physical_key_is_down[55]) {
                // 
                // left
                // 
                if (index == 40) {
                    // KC_9 + modifiers
                    if (!true && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                        tap_code(KC_9);
                    } else if (true && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(LGUI(KC_9)))));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LALT(LGUI(KC_9))));
                    } else if (true && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LALT(LGUI(KC_9))));
                    } else if (true && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LGUI(KC_9))));
                    } else if (true && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(KC_9))));
                    } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LALT(LGUI(KC_9)));
                    } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LGUI(KC_9)));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LCTL(LALT(KC_9)));
                    } else if (true && gui_physical_key_is_down) {
                        tap_code16(LSFT(LGUI(KC_9)));
                    } else if (true && alt_physical_key_is_down) {
                        tap_code16(LSFT(LALT(KC_9)));
                    } else if (true && ctrl_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(KC_9)));
                    } else if (gui_physical_key_is_down) {
                        tap_code16(LGUI(KC_9));
                    } else if (alt_physical_key_is_down) {
                        tap_code16(LALT(KC_9));
                    } else if (ctrl_physical_key_is_down) {
                        tap_code16(LCTL(KC_9));
                    } else if (true) {
                        tap_code16(LSFT(KC_9));
                    }
                    key_was_consumed[57] = true;
                    key_was_consumed[55] = true;
                    key_was_consumed[40] = true;
                    // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed)); 
                    return false;
                }
                // 
                // right
                // 
                if (index == 38) {
                    // KC_0 + modifiers
                    if (!true && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                        tap_code(KC_0);
                    } else if (true && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(LGUI(KC_0)))));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LALT(LGUI(KC_0))));
                    } else if (true && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LALT(LGUI(KC_0))));
                    } else if (true && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LGUI(KC_0))));
                    } else if (true && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(KC_0))));
                    } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LALT(LGUI(KC_0)));
                    } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LGUI(KC_0)));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LCTL(LALT(KC_0)));
                    } else if (true && gui_physical_key_is_down) {
                        tap_code16(LSFT(LGUI(KC_0)));
                    } else if (true && alt_physical_key_is_down) {
                        tap_code16(LSFT(LALT(KC_0)));
                    } else if (true && ctrl_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(KC_0)));
                    } else if (gui_physical_key_is_down) {
                        tap_code16(LGUI(KC_0));
                    } else if (alt_physical_key_is_down) {
                        tap_code16(LALT(KC_0));
                    } else if (ctrl_physical_key_is_down) {
                        tap_code16(LCTL(KC_0));
                    } else if (true) {
                        tap_code16(LSFT(KC_0));
                    }
                    key_was_consumed[57] = true;
                    key_was_consumed[55] = true;
                    key_was_consumed[38] = true;
                    // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed)); 
                    return false;
                }
            }
            // 
            // brackets
            // 
                // 
                // left
                // 
                if (index == 40) {
                    // KC_LEFT_BRACKET + modifiers
                    if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                        tap_code(KC_LEFT_BRACKET);
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(LGUI(KC_LEFT_BRACKET)))));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LALT(LGUI(KC_LEFT_BRACKET))));
                    } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LALT(LGUI(KC_LEFT_BRACKET))));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LGUI(KC_LEFT_BRACKET))));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(KC_LEFT_BRACKET))));
                    } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LALT(LGUI(KC_LEFT_BRACKET)));
                    } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LGUI(KC_LEFT_BRACKET)));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LCTL(LALT(KC_LEFT_BRACKET)));
                    } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LGUI(KC_LEFT_BRACKET)));
                    } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LALT(KC_LEFT_BRACKET)));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(KC_LEFT_BRACKET)));
                    } else if (gui_physical_key_is_down) {
                        tap_code16(LGUI(KC_LEFT_BRACKET));
                    } else if (alt_physical_key_is_down) {
                        tap_code16(LALT(KC_LEFT_BRACKET));
                    } else if (ctrl_physical_key_is_down) {
                        tap_code16(LCTL(KC_LEFT_BRACKET));
                    } else if (shift_physical_key_is_down) {
                        tap_code16(LSFT(KC_LEFT_BRACKET));
                    }
                    key_was_consumed[57] = true;
                    key_was_consumed[40] = true;
                    // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed)); 
                    return false;
                }
                // 
                // right
                // 
                if (index == 38) {
                    // KC_RIGHT_BRACKET + modifiers
                    if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                        tap_code(KC_RIGHT_BRACKET);
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(LGUI(KC_RIGHT_BRACKET)))));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LALT(LGUI(KC_RIGHT_BRACKET))));
                    } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LALT(LGUI(KC_RIGHT_BRACKET))));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LGUI(KC_RIGHT_BRACKET))));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(LALT(KC_RIGHT_BRACKET))));
                    } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LALT(LGUI(KC_RIGHT_BRACKET)));
                    } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LCTL(LGUI(KC_RIGHT_BRACKET)));
                    } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LCTL(LALT(KC_RIGHT_BRACKET)));
                    } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                        tap_code16(LSFT(LGUI(KC_RIGHT_BRACKET)));
                    } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                        tap_code16(LSFT(LALT(KC_RIGHT_BRACKET)));
                    } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                        tap_code16(LSFT(LCTL(KC_RIGHT_BRACKET)));
                    } else if (gui_physical_key_is_down) {
                        tap_code16(LGUI(KC_RIGHT_BRACKET));
                    } else if (alt_physical_key_is_down) {
                        tap_code16(LALT(KC_RIGHT_BRACKET));
                    } else if (ctrl_physical_key_is_down) {
                        tap_code16(LCTL(KC_RIGHT_BRACKET));
                    } else if (shift_physical_key_is_down) {
                        tap_code16(LSFT(KC_RIGHT_BRACKET));
                    }
                    key_was_consumed[57] = true;
                    key_was_consumed[38] = true;
                    // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed)); 
                    return false;
                }
            // 
        }
    
    // 
    // home row mod
    // 
        // 
        // left hand
        // 
            if (index == 12) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    // KC_A + modifiers
                if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                    tap_code(KC_A);
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(LGUI(KC_A)))));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LALT(LGUI(KC_A))));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LALT(LGUI(KC_A))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LGUI(KC_A))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(KC_A))));
                } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LALT(LGUI(KC_A)));
                } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LGUI(KC_A)));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LCTL(LALT(KC_A)));
                } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LGUI(KC_A)));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LALT(KC_A)));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(KC_A)));
                } else if (gui_physical_key_is_down) {
                    tap_code16(LGUI(KC_A));
                } else if (alt_physical_key_is_down) {
                    tap_code16(LALT(KC_A));
                } else if (ctrl_physical_key_is_down) {
                    tap_code16(LCTL(KC_A));
                } else if (shift_physical_key_is_down) {
                    tap_code16(LSFT(KC_A));
                };
                    return false;
                }
            }
            if (index == 14) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    // KC_S + modifiers
                if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                    tap_code(KC_S);
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(LGUI(KC_S)))));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LALT(LGUI(KC_S))));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LALT(LGUI(KC_S))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LGUI(KC_S))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(KC_S))));
                } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LALT(LGUI(KC_S)));
                } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LGUI(KC_S)));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LCTL(LALT(KC_S)));
                } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LGUI(KC_S)));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LALT(KC_S)));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(KC_S)));
                } else if (gui_physical_key_is_down) {
                    tap_code16(LGUI(KC_S));
                } else if (alt_physical_key_is_down) {
                    tap_code16(LALT(KC_S));
                } else if (ctrl_physical_key_is_down) {
                    tap_code16(LCTL(KC_S));
                } else if (shift_physical_key_is_down) {
                    tap_code16(LSFT(KC_S));
                };
                    return false;
                }
            }
            if (index == 15) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    // KC_D + modifiers
                if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                    tap_code(KC_D);
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(LGUI(KC_D)))));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LALT(LGUI(KC_D))));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LALT(LGUI(KC_D))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LGUI(KC_D))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(KC_D))));
                } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LALT(LGUI(KC_D)));
                } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LGUI(KC_D)));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LCTL(LALT(KC_D)));
                } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LGUI(KC_D)));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LALT(KC_D)));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(KC_D)));
                } else if (gui_physical_key_is_down) {
                    tap_code16(LGUI(KC_D));
                } else if (alt_physical_key_is_down) {
                    tap_code16(LALT(KC_D));
                } else if (ctrl_physical_key_is_down) {
                    tap_code16(LCTL(KC_D));
                } else if (shift_physical_key_is_down) {
                    tap_code16(LSFT(KC_D));
                };
                    return false;
                }
            }
            if (index == 16) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    // KC_F + modifiers
                if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                    tap_code(KC_F);
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(LGUI(KC_F)))));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LALT(LGUI(KC_F))));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LALT(LGUI(KC_F))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LGUI(KC_F))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(KC_F))));
                } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LALT(LGUI(KC_F)));
                } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LGUI(KC_F)));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LCTL(LALT(KC_F)));
                } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LGUI(KC_F)));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LALT(KC_F)));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(KC_F)));
                } else if (gui_physical_key_is_down) {
                    tap_code16(LGUI(KC_F));
                } else if (alt_physical_key_is_down) {
                    tap_code16(LALT(KC_F));
                } else if (ctrl_physical_key_is_down) {
                    tap_code16(LCTL(KC_F));
                } else if (shift_physical_key_is_down) {
                    tap_code16(LSFT(KC_F));
                };
                    return false;
                }
            }
        
        // 
        // Right Hand
        // 
            if (index == 42) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    // KC_SEMICOLON + modifiers
                if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                    tap_code(KC_SEMICOLON);
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(LGUI(KC_SEMICOLON)))));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LALT(LGUI(KC_SEMICOLON))));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LALT(LGUI(KC_SEMICOLON))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LGUI(KC_SEMICOLON))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(KC_SEMICOLON))));
                } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LALT(LGUI(KC_SEMICOLON)));
                } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LGUI(KC_SEMICOLON)));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LCTL(LALT(KC_SEMICOLON)));
                } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LGUI(KC_SEMICOLON)));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LALT(KC_SEMICOLON)));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(KC_SEMICOLON)));
                } else if (gui_physical_key_is_down) {
                    tap_code16(LGUI(KC_SEMICOLON));
                } else if (alt_physical_key_is_down) {
                    tap_code16(LALT(KC_SEMICOLON));
                } else if (ctrl_physical_key_is_down) {
                    tap_code16(LCTL(KC_SEMICOLON));
                } else if (shift_physical_key_is_down) {
                    tap_code16(LSFT(KC_SEMICOLON));
                };
                    return false;
                }
            }
            if (index == 44) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    // KC_L + modifiers
                if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                    tap_code(KC_L);
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(LGUI(KC_L)))));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LALT(LGUI(KC_L))));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LALT(LGUI(KC_L))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LGUI(KC_L))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(KC_L))));
                } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LALT(LGUI(KC_L)));
                } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LGUI(KC_L)));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LCTL(LALT(KC_L)));
                } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LGUI(KC_L)));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LALT(KC_L)));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(KC_L)));
                } else if (gui_physical_key_is_down) {
                    tap_code16(LGUI(KC_L));
                } else if (alt_physical_key_is_down) {
                    tap_code16(LALT(KC_L));
                } else if (ctrl_physical_key_is_down) {
                    tap_code16(LCTL(KC_L));
                } else if (shift_physical_key_is_down) {
                    tap_code16(LSFT(KC_L));
                };
                    return false;
                }
            }
            if (index == 45) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    // KC_K + modifiers
                if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                    tap_code(KC_K);
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(LGUI(KC_K)))));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LALT(LGUI(KC_K))));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LALT(LGUI(KC_K))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LGUI(KC_K))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(KC_K))));
                } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LALT(LGUI(KC_K)));
                } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LGUI(KC_K)));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LCTL(LALT(KC_K)));
                } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LGUI(KC_K)));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LALT(KC_K)));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(KC_K)));
                } else if (gui_physical_key_is_down) {
                    tap_code16(LGUI(KC_K));
                } else if (alt_physical_key_is_down) {
                    tap_code16(LALT(KC_K));
                } else if (ctrl_physical_key_is_down) {
                    tap_code16(LCTL(KC_K));
                } else if (shift_physical_key_is_down) {
                    tap_code16(LSFT(KC_K));
                };
                    return false;
                }
            }
            if (index == 46) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    // KC_J + modifiers
                if (!shift_physical_key_is_down && !ctrl_physical_key_is_down && !alt_physical_key_is_down && !gui_physical_key_is_down) {
                    tap_code(KC_J);
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(LGUI(KC_J)))));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LALT(LGUI(KC_J))));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LALT(LGUI(KC_J))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LGUI(KC_J))));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(LALT(KC_J))));
                } else if (alt_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LALT(LGUI(KC_J)));
                } else if (ctrl_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LCTL(LGUI(KC_J)));
                } else if (ctrl_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LCTL(LALT(KC_J)));
                } else if (shift_physical_key_is_down && gui_physical_key_is_down) {
                    tap_code16(LSFT(LGUI(KC_J)));
                } else if (shift_physical_key_is_down && alt_physical_key_is_down) {
                    tap_code16(LSFT(LALT(KC_J)));
                } else if (shift_physical_key_is_down && ctrl_physical_key_is_down) {
                    tap_code16(LSFT(LCTL(KC_J)));
                } else if (gui_physical_key_is_down) {
                    tap_code16(LGUI(KC_J));
                } else if (alt_physical_key_is_down) {
                    tap_code16(LALT(KC_J));
                } else if (ctrl_physical_key_is_down) {
                    tap_code16(LCTL(KC_J));
                } else if (shift_physical_key_is_down) {
                    tap_code16(LSFT(KC_J));
                };
                    return false;
                }
            }
    
    
    // 
    // TODO:
    // 
        // Escape
        // Tab
        // Space
        // Backspace
        // Enter
        // Click
        // Scroll
    
    // 
    // all normal keys
    // 
        // all the out of reach ones:
            // ty
            // gh
            // b
            // /
            // '
            // []            // `
            // numbers
    // TODO:
        // fast-acting keys (keydown combos)
        // modifier keys on their own (for games)
    // 
    // printout helper
    // 
        if (keydown) {
            
            if (index == 1) {
                tap_code(KC_1);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 2) {
                tap_code(KC_2);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 3) {
                tap_code(KC_3);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 4) {
                tap_code(KC_4);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 5) {
                tap_code(KC_5);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 6) {
                tap_code(KC_6);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 7) {
                tap_code(KC_7);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 8) {
                tap_code(KC_8);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 9) {
                tap_code(KC_9);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 10) {
                tap_code(KC_1);
                tap_code(KC_0);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 11) {
                tap_code(KC_1);
                tap_code(KC_1);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 12) {
                tap_code(KC_1);
                tap_code(KC_2);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 13) {
                tap_code(KC_1);
                tap_code(KC_3);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 14) {
                tap_code(KC_1);
                tap_code(KC_4);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 15) {
                tap_code(KC_1);
                tap_code(KC_5);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 16) {
                tap_code(KC_1);
                tap_code(KC_6);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 17) {
                tap_code(KC_1);
                tap_code(KC_7);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 18) {
                tap_code(KC_1);
                tap_code(KC_8);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 19) {
                tap_code(KC_1);
                tap_code(KC_9);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 20) {
                tap_code(KC_2);
                tap_code(KC_0);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 21) {
                tap_code(KC_2);
                tap_code(KC_1);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 22) {
                tap_code(KC_2);
                tap_code(KC_2);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 23) {
                tap_code(KC_2);
                tap_code(KC_3);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 24) {
                tap_code(KC_2);
                tap_code(KC_4);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 25) {
                tap_code(KC_2);
                tap_code(KC_5);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 26) {
                tap_code(KC_2);
                tap_code(KC_6);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 27) {
                tap_code(KC_2);
                tap_code(KC_7);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 28) {
                tap_code(KC_2);
                tap_code(KC_8);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 29) {
                tap_code(KC_2);
                tap_code(KC_9);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 30) {
                tap_code(KC_3);
                tap_code(KC_0);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 31) {
                tap_code(KC_3);
                tap_code(KC_1);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 32) {
                tap_code(KC_3);
                tap_code(KC_2);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 33) {
                tap_code(KC_3);
                tap_code(KC_3);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 34) {
                tap_code(KC_3);
                tap_code(KC_4);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 35) {
                tap_code(KC_3);
                tap_code(KC_5);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 36) {
                tap_code(KC_3);
                tap_code(KC_6);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 37) {
                tap_code(KC_3);
                tap_code(KC_7);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 38) {
                tap_code(KC_3);
                tap_code(KC_8);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 39) {
                tap_code(KC_3);
                tap_code(KC_9);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 40) {
                tap_code(KC_4);
                tap_code(KC_0);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 41) {
                tap_code(KC_4);
                tap_code(KC_1);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 42) {
                tap_code(KC_4);
                tap_code(KC_2);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 43) {
                tap_code(KC_4);
                tap_code(KC_3);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 44) {
                tap_code(KC_4);
                tap_code(KC_4);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 45) {
                tap_code(KC_4);
                tap_code(KC_5);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 46) {
                tap_code(KC_4);
                tap_code(KC_6);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 47) {
                tap_code(KC_4);
                tap_code(KC_7);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 48) {
                tap_code(KC_4);
                tap_code(KC_8);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 49) {
                tap_code(KC_4);
                tap_code(KC_9);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 50) {
                tap_code(KC_5);
                tap_code(KC_0);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 51) {
                tap_code(KC_5);
                tap_code(KC_1);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 52) {
                tap_code(KC_5);
                tap_code(KC_2);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 53) {
                tap_code(KC_5);
                tap_code(KC_3);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 54) {
                tap_code(KC_5);
                tap_code(KC_4);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 55) {
                tap_code(KC_5);
                tap_code(KC_5);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 56) {
                tap_code(KC_5);
                tap_code(KC_6);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 57) {
                tap_code(KC_5);
                tap_code(KC_7);
                tap_code(KC_COMMA);
                return false;
            } else if (index == 58) {
                tap_code(KC_5);
                tap_code(KC_8);
                tap_code(KC_COMMA);
                return false;
            }
            
            tap_code(KC_R);
            switch (row) {
                case 0:
                    tap_code(KC_0);
                    break;
                case 1:
                    tap_code(KC_1);
                    break;
                case 2:
                    tap_code(KC_2);
                    break;
                case 3:
                    tap_code(KC_3);
                    break;
                case 4:
                    tap_code(KC_4);
                    break;
                case 5:
                    tap_code(KC_5);
                    break;
                case 6:
                    tap_code(KC_6);
                    break;
                case 7:
                    tap_code(KC_7);
                    break;
                case 8:
                    tap_code(KC_8);
                    break;
                case 9:
                    tap_code(KC_9);
                    break;
                case 10:
                    tap_code(KC_1);
                    tap_code(KC_0);
                    break;
            }
            tap_code(KC_C);
            switch (col) {
                case 0:
                    tap_code(KC_0);
                    break;
                case 1:
                    tap_code(KC_1);
                    break;
                case 2:
                    tap_code(KC_2);
                    break;
                case 3:
                    tap_code(KC_3);
                    break;
                case 4:
                    tap_code(KC_4);
                    break;
                case 5:
                    tap_code(KC_5);
                    break;
                case 6:
                    tap_code(KC_6);
                    break;
                case 7:
                    tap_code(KC_7);
                    break;
                case 8:
                    tap_code(KC_8);
                    break;
                case 9:
                    tap_code(KC_9);
                    break;
                case 10:
                    tap_code(KC_1);
                    tap_code(KC_0);
                    break;
            }
            tap_code(KC_COMMA);
            return false;
        }

    return false;
}

uint16_t keys_down = 0;
bool physical_key_is_down[MATRIX_ROWS*MATRIX_COLS] = {0};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // setup
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;
    uint16_t index = row * MATRIX_COLS + col;
    const bool keydown = record->event.pressed;
    bool some_other_physical_key_is_down = keys_down >= 1;
    if (keydown) {
        keys_down++;
        physical_key_is_down[index] = true;
    } else {
        keys_down--;
        physical_key_is_down[index] = false;
    }
    if (false && some_other_physical_key_is_down) {} // defeat the "warning not used" check
    
    return handle_key_event(keycode, record, physical_key_is_down, keys_down, index, row, col, keydown, some_other_physical_key_is_down);
};
