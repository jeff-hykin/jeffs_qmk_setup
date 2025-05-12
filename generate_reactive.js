#!/usr/bin/env -S deno run --allow-all

import { capitalize, indent, toCamelCase, digitsToEnglishArray, toPascalCase, toKebabCase, toSnakeCase, toScreamingKebabCase, toScreamingSnakeCase, toRepresentation, toString, regex, findAll, iterativelyFindAll, escapeRegexMatch, escapeRegexReplace, extractFirst, isValidIdentifier, removeCommonPrefix, didYouMean } from "https://deno.land/x/good@1.13.1.0/string.js"
    
const makeKeyboardCode = (code) => {
    return `/**
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

/** \\brief Automatically enable sniping-mode on the pointer layer. */
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

const uint16_t key_count = MATRIX_ROWS*MATRIX_COLS;
uint16_t keys_down = 0;
bool key_was_consumed[MATRIX_ROWS*MATRIX_COLS] = {0};
bool physical_key_is_down[MATRIX_ROWS*MATRIX_COLS] = {0};
bool combo_was_activated = false;
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
    
    // for (uint16_t other_index = 0; other_index < key_count; other_index++) {
    //     if (physical_key_is_down[other_index] && other_index != index) {
    //         some_other_physical_key_is_down = true;
    //         break;
    //     }
    // }
    
    ${code}
    return true;
};`
}

import { keys, sendKeyTap, sendKeyTapPermutations } from "./tools.js"
import { keyboard } from "./charybdis.js"

const leftCtrlKey = keyboard.leftHand.homeRow[4]
const leftShiftKey = keyboard.leftHand.homeRow[2]
const leftAltKey = keyboard.leftHand.homeRow[1]
const leftGuiKey = keyboard.leftHand.homeRow[0]

const rightCtrlKey = keyboard.rightHand.homeRow[4]
const rightShiftKey = keyboard.rightHand.homeRow[2]
const rightAltKey = keyboard.rightHand.homeRow[1]
const rightGuiKey = keyboard.rightHand.homeRow[0]

const modifierToVarName = { ctrl: 'ctrl_physical_key_is_down', shift: 'shift_physical_key_is_down', alt: 'alt_physical_key_is_down', gui: 'gui_physical_key_is_down' }

const rightThumbMod1 = keyboard.rightHand.thumb[1]
const rightThumbMod2 = keyboard.rightHand.thumb[0]
const backspaceKeyIndex = keyboard.rightHand.homeRowUp1[3]

let code = makeKeyboardCode(`
    // available data: uint16_t keycode, keyrecord_t *record, bool keydown, row, col, keys_down, some_other_physical_key_is_down, physical_key_is_down[row][col]
    bool key_pressed_on_left_hand = ${Object.values(keyboard.leftHand).map(Object.values).flat(1).map(each=>`index == ${each}`).join(" || ")};
    
    bool ctrl_physical_key_is_down = physical_key_is_down[(key_pressed_on_left_hand ? ${rightCtrlKey} : ${leftCtrlKey})];
    bool shift_physical_key_is_down = physical_key_is_down[(key_pressed_on_left_hand ? ${rightShiftKey} : ${leftShiftKey})];
    bool alt_physical_key_is_down = physical_key_is_down[(key_pressed_on_left_hand ? ${rightAltKey} : ${leftAltKey})];
    bool gui_physical_key_is_down = physical_key_is_down[(key_pressed_on_left_hand ? ${rightGuiKey} : ${leftGuiKey})];
    
    // do nothing on keyup of any "consumed" key
    if (!keydown && key_was_consumed[index]) {
        key_was_consumed[index] = false;
        return false;
    }
    
    // 
    // boot key
    // 
    if (index == ${keyboard.rightHand.homeRowUp2[4]}) {
        reset_keyboard();
        return false;
    }

    // 
    // rightThumbMod1 (arrowLayer)
    // 
        if (index == ${rightThumbMod1}) {
            if (keydown) {
                return false; // do nothing on keydown (other than remember it)
            // if not "consumed" 
            } else {
                // activate the normal key
                ${sendKeyTapPermutations(keys.Spacebar, { indent: "                ", modifierToVarName})}
                return false;
            }
        }
    
    // 
    // rightThumbMod2 (numberLayer)
    // 
        if (index == ${rightThumbMod2}) {
            if (keydown) {
                return false; // do nothing on keydown (other than remember it)
            // if not "consumed" 
            } else {
                // activate the normal key
                ${sendKeyTapPermutations(keys.Spacebar, { indent: "                ", modifierToVarName})}
                return false;
            }
        }
    // 
    // spacebar modifier
    // 
        if (physical_key_is_down[${rightThumbMod1}] || physical_key_is_down[${rightThumbMod2}]) {
            // 
            // backspace
            // 
            if (index == ${backspaceKeyIndex}) {
                ${sendKeyTapPermutations(keys.Backspace, { indent: "                    ", modifierToVarName})}
                key_was_consumed[${backspaceKeyIndex}] = true;
                key_was_consumed[${rightThumbMod1}] = true;
                // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed));
                return false;
            }
        }
        if (physical_key_is_down[${rightThumbMod1}]) {
            // 
            // arrow keys
            // 
                // 
                // up
                // 
                if (index == ${keyboard.rightHand.homeRowUp1[1]}) {
                    ${sendKeyTapPermutations(keys.Up, { indent: "                    ", modifierToVarName})}
                    key_was_consumed[${keyboard.rightHand.homeRowUp1[1]}] = true;
                    key_was_consumed[${rightThumbMod1}] = true;
                    // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed));
                    return false;
                }
                // 
                // down
                // 
                if (index == ${keyboard.rightHand.homeRow[1]}) {
                    ${sendKeyTapPermutations(keys.Down, { indent: "                    ", modifierToVarName})}
                    key_was_consumed[${rightThumbMod1}] = true;
                    key_was_consumed[${keyboard.rightHand.homeRow[1]}] = true;
                    // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed));
                    return false;
                }
                // 
                // left
                // 
                if (index == ${keyboard.rightHand.homeRow[0]}) {
                    ${sendKeyTapPermutations(keys.Left, { indent: "                    ", modifierToVarName})}
                    key_was_consumed[${rightThumbMod1}] = true;
                    key_was_consumed[${keyboard.rightHand.homeRow[0]}] = true;
                    //memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed));
                    return false;
                }
                // 
                // right
                // 
                if (index == ${keyboard.rightHand.homeRow[2]}) {
                    ${sendKeyTapPermutations(keys.Right, { indent: "                    ", modifierToVarName})}
                    key_was_consumed[${rightThumbMod1}] = true;
                    key_was_consumed[${keyboard.rightHand.homeRow[2]}] = true;
                    // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed)); 
                    return false;
                }
            // 
            // parentheses 
            // 
            if (physical_key_is_down[${rightThumbMod2}]) {
                // 
                // left
                // 
                if (index == ${keyboard.rightHand.homeRowUp1[0]}) {
                    ${sendKeyTapPermutations(keys.KC_9, { indent: "                    ", modifierToVarName: {...modifierToVarName, leftShift: "true"}})}
                    key_was_consumed[${rightThumbMod1}] = true;
                    key_was_consumed[${rightThumbMod2}] = true;
                    key_was_consumed[${keyboard.rightHand.homeRowUp1[0]}] = true;
                    // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed)); 
                    return false;
                }
                // 
                // right
                // 
                if (index == ${keyboard.rightHand.homeRowUp1[2]}) {
                    ${sendKeyTapPermutations(keys.KC_0, { indent: "                    ", modifierToVarName: {...modifierToVarName, leftShift: "true"}})}
                    key_was_consumed[${rightThumbMod1}] = true;
                    key_was_consumed[${rightThumbMod2}] = true;
                    key_was_consumed[${keyboard.rightHand.homeRowUp1[2]}] = true;
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
                if (index == ${keyboard.rightHand.homeRowUp1[0]}) {
                    ${sendKeyTapPermutations(keys.KC_LEFT_BRACKET, { indent: "                    ", modifierToVarName})}
                    key_was_consumed[${rightThumbMod1}] = true;
                    key_was_consumed[${keyboard.rightHand.homeRowUp1[0]}] = true;
                    // memcpy(key_was_consumed, physical_key_is_down, sizeof(key_was_consumed)); 
                    return false;
                }
                // 
                // right
                // 
                if (index == ${keyboard.rightHand.homeRowUp1[2]}) {
                    ${sendKeyTapPermutations(keys.KC_RIGHT_BRACKET, { indent: "                    ", modifierToVarName})}
                    key_was_consumed[${rightThumbMod1}] = true;
                    key_was_consumed[${keyboard.rightHand.homeRowUp1[2]}] = true;
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
            if (index == ${leftCtrlKey}) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    ${sendKeyTapPermutations(keys.KC_A,{ indent: "                ", modifierToVarName})};
                    return false;
                }
            }
            if (index == ${leftShiftKey}) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    ${sendKeyTapPermutations(keys.KC_S,{ indent: "                ", modifierToVarName})};
                    return false;
                }
            }
            if (index == ${leftAltKey}) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    ${sendKeyTapPermutations(keys.KC_D,{ indent: "                ", modifierToVarName})};
                    return false;
                }
            }
            if (index == ${leftGuiKey}) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    ${sendKeyTapPermutations(keys.KC_F,{ indent: "                ", modifierToVarName})};
                    return false;
                }
            }
        
        // 
        // Right Hand
        // 
            if (index == ${rightCtrlKey}) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    ${sendKeyTapPermutations(keys.KC_SEMICOLON,{ indent: "                ", modifierToVarName})};
                    return false;
                }
            }
            if (index == ${rightShiftKey}) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    ${sendKeyTapPermutations(keys.KC_L,{ indent: "                ", modifierToVarName})};
                    return false;
                }
            }
            if (index == ${rightAltKey}) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    ${sendKeyTapPermutations(keys.KC_K,{ indent: "                ", modifierToVarName})};
                    return false;
                }
            }
            if (index == ${rightGuiKey}) {
                if (keydown) {
                    return false; // do nothing on keydown (other than remember it)
                // if not "consumed" 
                } else {
                    // activate the normal key
                    ${sendKeyTapPermutations(keys.KC_J,{ indent: "                ", modifierToVarName})};
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
            // []\
            // \`
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
`)

// console.log(code)
import { FileSystem, glob } from "https://deno.land/x/quickr@0.8.1/main/file_system.js"
await FileSystem.write({
    path:`${FileSystem.thisFolder}/keymaps/via/keymap.c`,
    data: code,
    overwrite: true
})