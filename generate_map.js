import { capitalize, indent, toCamelCase, digitsToEnglishArray, toPascalCase, toKebabCase, toSnakeCase, toScreamingKebabCase, toScreamingSnakeCase, toRepresentation, toString, regex, findAll, iterativelyFindAll, escapeRegexMatch, escapeRegexReplace, extractFirst, isValidIdentifier, removeCommonPrefix, didYouMean } from "https://deno.land/x/good@1.13.1.0/string.js"


const toolKit = {
    keys: {
        XXXXXXX: "XXXXXXX",
        KC_0: "KC_0",
        KC_1: "KC_1",
        KC_2: "KC_2",
        KC_3: "KC_3",
        KC_4: "KC_4",
        KC_5: "KC_5",
        KC_6: "KC_6",
        KC_7: "KC_7",
        KC_8: "KC_8",
        KC_9: "KC_9",
        KC_A: "KC_A",
        KC_AMPR: "KC_AMPR",
        KC_ASTR: "KC_ASTR",
        KC_AT: "KC_AT",
        KC_B: "KC_B",
        KC_BSLS: "KC_BSLS",
        KC_BSPC: "KC_BSPC",
        KC_BTN1: "KC_BTN1",
        KC_BTN2: "KC_BTN2",
        KC_BTN3: "KC_BTN3",
        KC_C: "KC_C",
        KC_CIRC: "KC_CIRC",
        KC_COMM: "KC_COMM",
        KC_D: "KC_D",
        KC_DEL: "KC_DEL",
        KC_DLR: "KC_DLR",
        KC_DOT: "KC_DOT",
        KC_DOWN: "KC_DOWN",
        KC_E: "KC_E",
        KC_END: "KC_END",
        KC_ENT: "KC_ENT",
        KC_ESC: "KC_ESC",
        KC_EXLM: "KC_EXLM",
        KC_F: "KC_F",
        KC_F1: "KC_F1",
        KC_F10: "KC_F10",
        KC_F11: "KC_F11",
        KC_F12: "KC_F12",
        KC_F2: "KC_F2",
        KC_F3: "KC_F3",
        KC_F4: "KC_F4",
        KC_F5: "KC_F5",
        KC_F6: "KC_F6",
        KC_F7: "KC_F7",
        KC_F8: "KC_F8",
        KC_F9: "KC_F9",
        KC_G: "KC_G",
        KC_H: "KC_H",
        KC_HASH: "KC_HASH",
        KC_HOME: "KC_HOME",
        KC_I: "KC_I",
        KC_J: "KC_J",
        KC_K: "KC_K",
        KC_L: "KC_L",
        KC_LALT: "KC_LALT",
        KC_LBRC: "KC_LBRC",
        KC_LCTL: "KC_LCTL",
        KC_LEFT: "KC_LEFT",
        KC_LGUI: "KC_LGUI",
        KC_LPRN: "KC_LPRN",
        KC_LSFT: "KC_LSFT",
        KC_M: "KC_M",
        KC_MINS: "KC_MINS",
        KC_MNXT: "KC_MNXT",
        KC_MPLY: "KC_MPLY",
        KC_MPRV: "KC_MPRV",
        KC_MUTE: "KC_MUTE",
        KC_N: "KC_N",
        KC_NO: "KC_NO",
        KC_O: "KC_O",
        KC_P: "KC_P",
        KC_P0: "KC_P0",
        KC_P1: "KC_P1",
        KC_P2: "KC_P2",
        KC_P3: "KC_P3",
        KC_P4: "KC_P4",
        KC_P5: "KC_P5",
        KC_P6: "KC_P6",
        KC_P7: "KC_P7",
        KC_P8: "KC_P8",
        KC_P9: "KC_P9",
        KC_PAST: "KC_PAST",
        KC_PDOT: "KC_PDOT",
        KC_PEQL: "KC_PEQL",
        KC_PERC: "KC_PERC",
        KC_PGDN: "KC_PGDN",
        KC_PGUP: "KC_PGUP",
        KC_PMNS: "KC_PMNS",
        KC_PPLS: "KC_PPLS",
        KC_PSLS: "KC_PSLS",
        KC_Q: "KC_Q",
        KC_QUOT: "KC_QUOT",
        KC_R: "KC_R",
        KC_RALT: "KC_RALT",
        KC_RBRC: "KC_RBRC",
        KC_RCTL: "KC_RCTL",
        KC_RGHT: "KC_RGHT",
        KC_RGUI: "KC_RGUI",
        KC_RPRN: "KC_RPRN",
        KC_RSFT: "KC_RSFT",
        KC_S: "KC_S",
        KC_SCLN: "KC_SCLN",
        KC_SPC: "KC_SPC",
        KC_T: "KC_T",
        KC_TAB: "KC_TAB",
        KC_TILD: "KC_TILD",
        KC_U: "KC_U",
        KC_UNDS: "KC_UNDS",
        KC_UP: "KC_UP",
        KC_V: "KC_V",
        KC_VOLD: "KC_VOLD",
        KC_VOLU: "KC_VOLU",
        KC_W: "KC_W",
        KC_X: "KC_X",
        KC_Y: "KC_Y",
        KC_Z: "KC_Z",
    },
    methods: {
        COMBO() {

        },
        MO() {

        },
        LT() {

        },
        LCTL() {

        },
        LSFT() {

        },
        LALT() {

        },
        LGUI() {

        },
        RCTL() {

        },
        RSFT() {

        },
        RALT() {

        },
    },
}
const maxKeyLength = 8
function createMapping() {
    const innerInfo = {
        layers: [],
        combos: [],
    }
    return {
        innerInfo: {},
        Combo: class {
            constructor(keys, result) {
                this.index = innerInfo.combos.length
                innerInfo.combos.push(this)
                this.keys = keys
                this.result = result
                this._varName = `COMBO__${this.index}`
            },
            triggerToString() {
                return `const uint16_t PROGMEM ${this._varName}[] = {${this.keys.map(each=>each.toString()).join(",")}, COMBO_END};`
            },
            toString() {
                return this._varName
            }
        },
        Layer: class {
            constructor() {
                this.index = innerInfo.layers.length
                innerInfo.layers.push(this)
                // 
                // init keys
                // 
                let keys = [ toolKit.keys.XXXXXXX, toolKit.keys.XXXXXXX, toolKit.keys.XXXXXXX, toolKit.keys.XXXXXXX, toolKit.keys.XXXXXXX ]
                this.leftHand = { homeRowUp2: [...keys], homeRowUp1: [...keys], homeRow: [...keys], homeRowDown1: [...keys], thumb: [...keys] }
                this.rightHand = { homeRowUp2: [...keys], homeRowUp1: [...keys], homeRow: [...keys], homeRowDown1: [...keys], thumb: [toolKit.keys.XXXXXXX,toolKit.keys.XXXXXXX,toolKit.keys.XXXXXXX] }
                this.leftHand.homeRowUp2[-1]    = toolKit.keys.XXXXXXX
                this.leftHand.homeRowUp1[-1]    = toolKit.keys.XXXXXXX
                this.leftHand.homeRow[-1]       = toolKit.keys.XXXXXXX
                this.leftHand.homeRowDown1[-1]  = toolKit.keys.XXXXXXX
                this.rightHand.homeRowUp2[-1]   = toolKit.keys.XXXXXXX
                this.rightHand.homeRowUp1[-1]   = toolKit.keys.XXXXXXX
                this.rightHand.homeRow[-1]      = toolKit.keys.XXXXXXX
                this.rightHand.homeRowDown1[-1] = toolKit.keys.XXXXXXX
            },
            keyArray() {
                return [
                    ...this.leftHand.homeRowUp2.toReversed(),   this.leftHand.homeRowUp2[-1]  , this.rightHand.homeRowUp2[-1]  , ...this.rightHand.homeRowUp2, 
                    ...this.leftHand.homeRowUp1.toReversed(),   this.leftHand.homeRowUp1[-1]  , this.rightHand.homeRowUp1[-1]  , ...this.rightHand.homeRowUp1, 
                    ...this.leftHand.homeRow.toReversed(),      this.leftHand.homeRow[-1]     , this.rightHand.homeRow[-1]     , ...this.rightHand.homeRow, 
                    ...this.leftHand.homeRowDown1.toReversed(), this.leftHand.homeRowDown1[-1], this.rightHand.homeRowDown1[-1], ...this.rightHand.homeRowDown1, 
                    ...this.leftHand.thumb.slice(0, 3), ...this.rightHand.thumb.slice(0, 2),
                    ...this.leftHand.thumb.slice(3, 5), ...this.rightHand.thumb.slice(2, 3),
                ]
            },
            toString() {
                const keyMapper = each=>each.toString().padStart(maxKeyLength,' ')+","
                return `
                    // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
                       ${[...this.leftHand.homeRowUp2.toReversed(),   this.leftHand.homeRowUp2[-1]  , this.rightHand.homeRowUp2[-1]  , ...this.rightHand.homeRowUp2, ].map(keyMapper).join('')}
                    // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                       ${[...this.leftHand.homeRowUp1.toReversed(),   this.leftHand.homeRowUp1[-1]  , this.rightHand.homeRowUp1[-1]  , ...this.rightHand.homeRowUp1, ].map(keyMapper).join('')}
                    // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                       ${[...this.leftHand.homeRow.toReversed(),   this.leftHand.homeRow[-1]  , this.rightHand.homeRow[-1]  , ...this.rightHand.homeRow, ].map(keyMapper).join('')}
                    // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                       ${[...this.leftHand.homeRowDown1.toReversed(),   this.leftHand.homeRowDown1[-1]  , this.rightHand.homeRowDown1[-1]  , ...this.rightHand.homeRowDown1, ].map(keyMapper).join('')}
                    // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                                  ${[...this.leftHand.thumb.slice(0, 3), ...this.rightHand.thumb.slice(0, 2),].map(keyMapper).join('')}
                                                  ${[...this.leftHand.thumb.slice(3, 5), ...this.rightHand.thumb.slice(2, 3),].map(keyMapper).join('')}
                    //                            ╰───────────────────────────╯ ╰──────────────────╯
                    `
            }
        },
        generateC() {
return `
#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
    #include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_0 = 0,
    ${innerInfo.layers.slice(1,).map(layer => `LAYER_${layer.index},`).join('\n    ')}
};

/** \\brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
    static uint16_t auto_pointer_layer_timer = 0;

    #ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
        #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
    #endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

    #ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
        #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
    #endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#ifndef POINTING_DEVICE_ENABLE
    #define DRGSCRL KC_NO
    #define DPI_MOD KC_NO
    #define S_D_MOD KC_NO
    #define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

${innerInfo.combos.map(combo => combo.triggerToString()).join('\n')}
combo_t key_combos[] = {
    ${innerInfo.combos.map(combo => `COMBO(${combo._varName}, ${combo.result.toString()})`).join(',\n    ')}
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  ${innerInfo.layers.map(layer => `[LAYER_${layer.index}] = LAYOUT(${layer.toString()})`).join('\n    ')}
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
    #ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
        report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
            if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
                if (auto_pointer_layer_timer == 0) {
                    layer_on(LAYER_POINTER);
                    #ifdef RGB_MATRIX_ENABLE
                        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
                        rgb_matrix_sethsv_noeeprom(HSV_GREEN);
                    #endif // RGB_MATRIX_ENABLE
                }
                auto_pointer_layer_timer = timer_read();
            }
            return mouse_report;
        }

        void matrix_scan_user(void) {
            if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
                auto_pointer_layer_timer = 0;
                layer_off(LAYER_POINTER);
                #ifdef RGB_MATRIX_ENABLE
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
                #endif // RGB_MATRIX_ENABLE
            }
        }
    #endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

    #ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
        layer_state_t layer_state_set_user(layer_state_t state) {
            charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
            return state;
        }
    #endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
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

bool key_is_down[MATRIX_ROWS][MATRIX_COLS] = {0};
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // setup
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;
    if (record->event.pressed) {
        key_is_down[row][col] = true;
    } else if (record->event.released) {
        key_is_down[row][col] = false;
    }
    
    // 
    // Normal logic goes here
    // 
    
    // // uint16_t which_physical_key_was_pressed = row * MATRIX_COLS + col;
    // if (keycode == KC_A && record->event.pressed) {
    //     tap_code(KC_SPC);  // simulate a spacebar tap
    //     return false;      // block the original 'A' key
    // }
    
    // switch(keycode) {
    //     case KC_ESC:
    //         if (record->event.pressed) {
    //             // SEND_STRING("This is custom keycode #1.");
    //         } else {
                
    //         }
    //         return true;
    // }
    
    return process_record_user(keycode, record);
};
`
        }
    }
}


const { Layer } = createMapping()