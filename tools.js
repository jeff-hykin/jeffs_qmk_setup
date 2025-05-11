import { indent as indenter } from 'https://esm.sh/gh/jeff-hykin/good-js@1.17.1.0/source/flattened/indent.js'

const modifierNameMap = {
    leftShift: "LSFT",
    rightShift: "RSFT",
    leftControl: "LCTL",
    rightControl: "RCTL",
    leftAlt: "LALT",
    rightAlt: "RALT",
    leftGui: "LGUI",
    rightGui: "RGUI",
}
export const sendKeyTap = (key, options={})=> {
    // {shift, leftShift, rightShift, control, leftControl, rightControl, alt, leftAlt, rightAlt, gui, leftGui, rightGui, }
    options["leftShift"] = options["leftShift"] || options["shift"]
    delete options["shift"]
    options["leftControl"] = options["leftControl"] || options["control"]
    delete options["control"]
    options["leftAlt"] = options["leftAlt"] || options["alt"]
    delete options["alt"]
    options["leftGui"] = options["leftGui"] || options["gui"]
    delete options["gui"]
    
    let count = 0
    let string = ""
    for (const [modifier, isActive] of Object.entries(options)) {
        if (isActive) {
            count++
            string += `${modifierNameMap[modifier]}(`
        }
    }
    string = `${string}${key}${")".repeat(count)}`
    if (count > 0) {
        return `tap_code16(${string})`
    }
    return `tap_code(${string})`
}
import { combinations } from 'https://esm.sh/gh/jeff-hykin/good-js@1.17.1.0/source/flattened/combinations.js'

export const sendKeyTapPermutations = (key, {indent, modifierToVarName})=> {
    // simplify options
    modifierToVarName["leftShift"] = modifierToVarName["leftShift"] || modifierToVarName["shift"]
    delete modifierToVarName["shift"]
    modifierToVarName["leftControl"] = modifierToVarName["leftControl"] || modifierToVarName["control"] || modifierToVarName["ctrl"]
    delete modifierToVarName["ctrl"]
    delete modifierToVarName["control"]
    modifierToVarName["leftAlt"] = modifierToVarName["leftAlt"] || modifierToVarName["alt"]
    delete modifierToVarName["alt"]
    modifierToVarName["leftGui"] = modifierToVarName["leftGui"] || modifierToVarName["gui"]
    delete modifierToVarName["gui"]
    for (const [key, value] of Object.entries(modifierToVarName)) {
        if (value == null) {
            delete modifierToVarName[key]
        }
    }
    let which
    if (Object.keys(modifierToVarName).some(each=>modifierNameMap[each] == null && (which=each, true))) {
        throw Error(`
            You have a modifier that isn't supported by sendKeyTapPermutations
            problematic one: ${which}
            Valid modifiers are: ${JSON.stringify(Object.keys(modifierNameMap))}
            Provided names were: ${JSON.stringify(Object.keys(modifierToVarName))}
        `)
    }

    let options = []
    for (const [modifierName, varName] of Object.entries(modifierToVarName)) {
        options.push(modifierName)
    }
    const outputCodeChunks = [
        `// ${key} + modifiers`,
        `if (${Object.values(modifierToVarName).map(each=>`!${each}`).join(" && ")}) {`,
        `    tap_code(${key});`,
    ]
    // start with largest combinations (it matters)
    for (const modifiers of [...combinations(options)].reverse()) {
        const varNames = modifiers.map(eachModifier=>modifierToVarName[eachModifier])
        // inefficent, but I dont care
        outputCodeChunks.push(`} else if (${varNames.join(" && ")}) {`)
        outputCodeChunks.push(`    tap_code16(${modifiers.map(eachModifier=>`${modifierNameMap[eachModifier]}(`).join("")}${key}${")".repeat(modifiers.length)});`)
        // ex: tap_code16(RSFT(LCTL(KC_A)))
    }
    outputCodeChunks.push(`}`)
    return indenter({string:outputCodeChunks.join("\n"), by: indent||"", noLead:true})
}
export const keys = {
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
    KC_B: "KC_B",
    KC_C: "KC_C",
    KC_D: "KC_D",
    KC_E: "KC_E",
    KC_F: "KC_F",
    KC_G: "KC_G",
    KC_H: "KC_H",
    KC_I: "KC_I",
    KC_J: "KC_J",
    KC_K: "KC_K",
    KC_L: "KC_L",
    KC_M: "KC_M",
    KC_N: "KC_N",
    KC_O: "KC_O",
    KC_P: "KC_P",
    KC_Q: "KC_Q",
    KC_R: "KC_R",
    KC_S: "KC_S",
    KC_T: "KC_T",
    KC_U: "KC_U",
    KC_V: "KC_V",
    KC_W: "KC_W",
    KC_X: "KC_X",
    KC_Y: "KC_Y",
    KC_Z: "KC_Z",

    KC_AMPR: "KC_AMPR",
    KC_ASTR: "KC_ASTR",
    KC_AT: "KC_AT",
    KC_BSLS: "KC_BSLS",
    KC_BSPC: "KC_BSPC",
    KC_BTN1: "KC_BTN1",
    KC_BTN2: "KC_BTN2",
    KC_BTN3: "KC_BTN3",
    KC_CIRC: "KC_CIRC",
    KC_COMM: "KC_COMM",
    KC_DEL: "KC_DEL",
    KC_DLR: "KC_DLR",
    KC_DOT: "KC_DOT",
    KC_DOWN: "KC_DOWN",
    KC_END: "KC_END",
    KC_ENT: "KC_ENT",
    KC_ESC: "KC_ESC",
    KC_EXLM: "KC_EXLM",
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
    KC_HASH: "KC_HASH",
    KC_HOME: "KC_HOME",
    KC_LALT: "KC_LALT",
    KC_LBRC: "KC_LBRC",
    KC_LCTL: "KC_LCTL",
    KC_LEFT: "KC_LEFT",
    KC_LGUI: "KC_LGUI",
    KC_LPRN: "KC_LPRN",
    KC_LSFT: "KC_LSFT",
    KC_MINS: "KC_MINS",
    KC_MNXT: "KC_MNXT",
    KC_MPLY: "KC_MPLY",
    KC_MPRV: "KC_MPRV",
    KC_MUTE: "KC_MUTE",
    KC_NO: "KC_NO",
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
    KC_QUOT: "KC_QUOT",
    KC_RALT: "KC_RALT",
    KC_RBRC: "KC_RBRC",
    KC_RCTL: "KC_RCTL",
    KC_RGHT: "KC_RGHT",
    KC_RGUI: "KC_RGUI",
    KC_RPRN: "KC_RPRN",
    KC_RSFT: "KC_RSFT",
    KC_SCLN: "KC_SCLN",
    KC_SPC: "KC_SPC",
    KC_TAB: "KC_TAB",
    KC_TILD: "KC_TILD",
    KC_UNDS: "KC_UNDS",
    KC_UP: "KC_UP",
    KC_VOLD: "KC_VOLD",
    KC_VOLU: "KC_VOLU",
    KC_TRANSPARENT: "KC_TRANSPARENT",
    KC_ENTER: "KC_ENTER",
    KC_ESCAPE: "KC_ESCAPE",
    KC_BACKSPACE: "KC_BACKSPACE",
    KC_SPACE: "KC_SPACE",
    KC_MINUS: "KC_MINUS",
    KC_EQUAL: "KC_EQUAL",
    KC_LEFT_BRACKET: "KC_LEFT_BRACKET",
    KC_RIGHT_BRACKET: "KC_RIGHT_BRACKET",
    KC_BACKSLASH: "KC_BACKSLASH",
    KC_NONUS_HASH: "KC_NONUS_HASH",
    KC_SEMICOLON: "KC_SEMICOLON",
    KC_QUOTE: "KC_QUOTE",
    KC_GRAVE: "KC_GRAVE",
    KC_COMMA: "KC_COMMA",
    KC_SLASH: "KC_SLASH",
    KC_CAPS_LOCK: "KC_CAPS_LOCK",
    KC_PRINT_SCREEN: "KC_PRINT_SCREEN",
    KC_SCROLL_LOCK: "KC_SCROLL_LOCK",
    KC_PAUSE: "KC_PAUSE",
    KC_INSERT: "KC_INSERT",
    KC_PAGE_UP: "KC_PAGE_UP",
    KC_DELETE: "KC_DELETE",
    KC_PAGE_DOWN: "KC_PAGE_DOWN",
    KC_RIGHT: "KC_RIGHT",
    KC_NUM_LOCK: "KC_NUM_LOCK",
    KC_KP_SLASH: "KC_KP_SLASH",
    KC_KP_ASTERISK: "KC_KP_ASTERISK",
    KC_KP_MINUS: "KC_KP_MINUS",
    KC_KP_PLUS: "KC_KP_PLUS",
    KC_KP_ENTER: "KC_KP_ENTER",
    KC_KP_1: "KC_KP_1",
    KC_KP_2: "KC_KP_2",
    KC_KP_3: "KC_KP_3",
    KC_KP_4: "KC_KP_4",
    KC_KP_5: "KC_KP_5",
    KC_KP_6: "KC_KP_6",
    KC_KP_7: "KC_KP_7",
    KC_KP_8: "KC_KP_8",
    KC_KP_9: "KC_KP_9",
    KC_KP_0: "KC_KP_0",
    KC_KP_DOT: "KC_KP_DOT",
    KC_NONUS_BACKSLASH: "KC_NONUS_BACKSLASH",
    KC_APPLICATION: "KC_APPLICATION",
    KC_KB_POWER: "KC_KB_POWER",
    KC_KP_EQUAL: "KC_KP_EQUAL",
    KC_F13: "KC_F13",
    KC_F14: "KC_F14",
    KC_F15: "KC_F15",
    KC_F16: "KC_F16",
    KC_F17: "KC_F17",
    KC_F18: "KC_F18",
    KC_F19: "KC_F19",
    KC_F20: "KC_F20",
    KC_F21: "KC_F21",
    KC_F22: "KC_F22",
    KC_F23: "KC_F23",
    KC_F24: "KC_F24",
    KC_EXECUTE: "KC_EXECUTE",
    KC_HELP: "KC_HELP",
    KC_MENU: "KC_MENU",
    KC_SELECT: "KC_SELECT",
    KC_STOP: "KC_STOP",
    KC_AGAIN: "KC_AGAIN",
    KC_UNDO: "KC_UNDO",
    KC_CUT: "KC_CUT",
    KC_COPY: "KC_COPY",
    KC_PASTE: "KC_PASTE",
    KC_FIND: "KC_FIND",
    KC_KB_MUTE: "KC_KB_MUTE",
    KC_KB_VOLUME_UP: "KC_KB_VOLUME_UP",
    KC_KB_VOLUME_DOWN: "KC_KB_VOLUME_DOWN",
    KC_LOCKING_CAPS_LOCK: "KC_LOCKING_CAPS_LOCK",
    KC_LOCKING_NUM_LOCK: "KC_LOCKING_NUM_LOCK",
    KC_LOCKING_SCROLL_LOCK: "KC_LOCKING_SCROLL_LOCK",
    KC_KP_COMMA: "KC_KP_COMMA",
    KC_KP_EQUAL_AS400: "KC_KP_EQUAL_AS400",
    KC_INTERNATIONAL_1: "KC_INTERNATIONAL_1",
    KC_INTERNATIONAL_2: "KC_INTERNATIONAL_2",
    KC_INTERNATIONAL_3: "KC_INTERNATIONAL_3",
    KC_INTERNATIONAL_4: "KC_INTERNATIONAL_4",
    KC_INTERNATIONAL_5: "KC_INTERNATIONAL_5",
    KC_INTERNATIONAL_6: "KC_INTERNATIONAL_6",
    KC_INTERNATIONAL_7: "KC_INTERNATIONAL_7",
    KC_INTERNATIONAL_8: "KC_INTERNATIONAL_8",
    KC_INTERNATIONAL_9: "KC_INTERNATIONAL_9",
    KC_LANGUAGE_1: "KC_LANGUAGE_1",
    KC_LANGUAGE_2: "KC_LANGUAGE_2",
    KC_LANGUAGE_3: "KC_LANGUAGE_3",
    KC_LANGUAGE_4: "KC_LANGUAGE_4",
    KC_LANGUAGE_5: "KC_LANGUAGE_5",
    KC_LANGUAGE_6: "KC_LANGUAGE_6",
    KC_LANGUAGE_7: "KC_LANGUAGE_7",
    KC_LANGUAGE_8: "KC_LANGUAGE_8",
    KC_LANGUAGE_9: "KC_LANGUAGE_9",
    KC_ALTERNATE_ERASE: "KC_ALTERNATE_ERASE",
    KC_SYSTEM_REQUEST: "KC_SYSTEM_REQUEST",
    KC_CANCEL: "KC_CANCEL",
    KC_CLEAR: "KC_CLEAR",
    KC_PRIOR: "KC_PRIOR",
    KC_RETURN: "KC_RETURN",
    KC_SEPARATOR: "KC_SEPARATOR",
    KC_OUT: "KC_OUT",
    KC_OPER: "KC_OPER",
    KC_CLEAR_AGAIN: "KC_CLEAR_AGAIN",
    KC_CRSEL: "KC_CRSEL",
    KC_EXSEL: "KC_EXSEL",
    KC_SYSTEM_POWER: "KC_SYSTEM_POWER",
    KC_SYSTEM_SLEEP: "KC_SYSTEM_SLEEP",
    KC_SYSTEM_WAKE: "KC_SYSTEM_WAKE",
    KC_AUDIO_MUTE: "KC_AUDIO_MUTE",
    KC_AUDIO_VOL_UP: "KC_AUDIO_VOL_UP",
    KC_AUDIO_VOL_DOWN: "KC_AUDIO_VOL_DOWN",
    KC_MEDIA_NEXT_TRACK: "KC_MEDIA_NEXT_TRACK",
    KC_MEDIA_PREV_TRACK: "KC_MEDIA_PREV_TRACK",
    KC_MEDIA_STOP: "KC_MEDIA_STOP",
    KC_MEDIA_PLAY_PAUSE: "KC_MEDIA_PLAY_PAUSE",
    KC_MEDIA_SELECT: "KC_MEDIA_SELECT",
    KC_MEDIA_EJECT: "KC_MEDIA_EJECT",
    KC_MAIL: "KC_MAIL",
    KC_CALCULATOR: "KC_CALCULATOR",
    KC_MY_COMPUTER: "KC_MY_COMPUTER",
    KC_WWW_SEARCH: "KC_WWW_SEARCH",
    KC_WWW_HOME: "KC_WWW_HOME",
    KC_WWW_BACK: "KC_WWW_BACK",
    KC_WWW_FORWARD: "KC_WWW_FORWARD",
    KC_WWW_STOP: "KC_WWW_STOP",
    KC_WWW_REFRESH: "KC_WWW_REFRESH",
    KC_WWW_FAVORITES: "KC_WWW_FAVORITES",
    KC_MEDIA_FAST_FORWARD: "KC_MEDIA_FAST_FORWARD",
    KC_MEDIA_REWIND: "KC_MEDIA_REWIND",
    KC_BRIGHTNESS_UP: "KC_BRIGHTNESS_UP",
    KC_BRIGHTNESS_DOWN: "KC_BRIGHTNESS_DOWN",
    KC_CONTROL_PANEL: "KC_CONTROL_PANEL",
    KC_ASSISTANT: "KC_ASSISTANT",
    KC_MS_UP: "KC_MS_UP",
    KC_MS_DOWN: "KC_MS_DOWN",
    KC_MS_LEFT: "KC_MS_LEFT",
    KC_MS_RIGHT: "KC_MS_RIGHT",
    KC_MS_BTN1: "KC_MS_BTN1",
    KC_MS_BTN2: "KC_MS_BTN2",
    KC_MS_BTN3: "KC_MS_BTN3",
    KC_MS_BTN4: "KC_MS_BTN4",
    KC_MS_BTN5: "KC_MS_BTN5",
    KC_MS_BTN6: "KC_MS_BTN6",
    KC_MS_BTN7: "KC_MS_BTN7",
    KC_MS_BTN8: "KC_MS_BTN8",
    KC_MS_WH_UP: "KC_MS_WH_UP",
    KC_MS_WH_DOWN: "KC_MS_WH_DOWN",
    KC_MS_WH_LEFT: "KC_MS_WH_LEFT",
    KC_MS_WH_RIGHT: "KC_MS_WH_RIGHT",
    KC_MS_ACCEL0: "KC_MS_ACCEL0",
    KC_MS_ACCEL1: "KC_MS_ACCEL1",
    KC_MS_ACCEL2: "KC_MS_ACCEL2",
    KC_LEFT_CTRL: "KC_LEFT_CTRL",
    KC_LEFT_SHIFT: "KC_LEFT_SHIFT",
    KC_LEFT_ALT: "KC_LEFT_ALT",
    KC_LEFT_GUI: "KC_LEFT_GUI",
    KC_RIGHT_CTRL: "KC_RIGHT_CTRL",
    KC_RIGHT_SHIFT: "KC_RIGHT_SHIFT",
    KC_RIGHT_ALT: "KC_RIGHT_ALT",
    KC_RIGHT_GUI: "KC_RIGHT_GUI",

    // my names
    Spacebar: "KC_SPC",
    Enter: "KC_ENT",
    Backspace: "KC_BSPC",
    Up: "KC_UP",
    Down: "KC_DOWN",
    Left: "KC_LEFT",
    Right: "KC_RGHT",
    Home: "KC_HOME",
    End: "KC_END",
    PageUp: "KC_PGUP",
    PageDown: "KC_PGDN",
    Insert: "KC_INSERT",
    Delete: "KC_DEL",
    Escape: "KC_ESC",
    Tab: "KC_TAB",
    CapsLock: "KC_CAPS",
    LeftShift: "KC_LSFT",
    RightShift: "KC_RSFT",
    LeftControl: "KC_LCTL",
    RightControl: "KC_RCTL",
    LeftAlt: "KC_LALT",
    RightAlt: "KC_RALT",
    LeftGui: "KC_LGUI",
    RightGui: "KC_RGUI",
    LeftMouse: "KC_MS_BTN1",
    RightMouse: "KC_MS_BTN2",
}