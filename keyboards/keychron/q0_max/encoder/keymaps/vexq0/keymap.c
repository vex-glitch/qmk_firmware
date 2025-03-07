/* Copyright 2024 @ Keychron (https://www.keychron.com)
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
#include "keychron_common.h"

enum layers {
    BASE,
    FN,
    LCTL,
    LGUI,
    LALT,

};
typedef enum {
    TD_NONE,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD,
    TD_QUAD_TAP,
    TD_QUAD_HOLD,


} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Common function to determine tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        return state->interrupted || !state->pressed ? TD_SINGLE_TAP : TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        return state->interrupted || !state->pressed ? TD_DOUBLE_TAP : TD_DOUBLE_HOLD;
    } else if (state->count == 3) {
        return state->interrupted || !state->pressed ? TD_TRIPLE_TAP : TD_TRIPLE_HOLD;
    } else {
        return state->interrupted || !state->pressed ? TD_QUAD_TAP : TD_QUAD_HOLD;
    }
}

// Tap Dance Declarations
enum {
    TD_UNSC,
};

// Definitions
    #define KC_UNSC TD(TD_UNSC)
    #define CTL_L   OSL(LCTL)
    #define GUI_L   OSL(LGUI)
    #define ALT_L   OSL(LALT)


void dance_unsc_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Inserts < > with the cursor between
        SEND_STRING("_");
    } else if (state->count == 2 && !state->pressed) {
        // Hold: Inserts { } with the cursor between
        SEND_STRING("____");
        tap_code(KC_LEFT);
        tap_code(KC_LEFT);
    } else if (state->count == 1 && state->pressed) {
        // Hold: Inserts { } with the cursor between
        SEND_STRING("___");
    }
}

void dance_unsc_reset(tap_dance_state_t *state, void *user_data) {
    // No reset logic needed
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_UNSC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_unsc_finished, dance_unsc_reset),
};

// Macro Declarations
enum {
    C0,
    C1,
    C2,
    C3,
    C4,
    C5,
    C6,
    C7,
    C8,
    C9,
    CDOT,
    G1,
    G2,
    G3,
    G4,
    G5,
    G6,
    G7,
    G8,
    G9,
    GDOT,
    A1,
    A2,
    A3,
    A4,
    A5,
    A6,
    A7,
    A8,
    A9,
    ADOT,
};

// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Process existing macros
    switch (keycode) {
     /// CTL Layer
    case C0:
    if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_P0);
        unregister_code(KC_LCTL);
    }
    return false;
    case C1:
    if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_P1);
        unregister_code(KC_LCTL);
    }
    return false;
    case C2:
    if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_P2);
        unregister_code(KC_LCTL);
    }
    return false;
    case C3:
    if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_P3);
        unregister_code(KC_LCTL);
    }
    return false;
    case C4:
    if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_P4);
        unregister_code(KC_LCTL);
    }
    return false;
    case C5:
    if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_P5);
        unregister_code(KC_LCTL);
    }
    return false;
    case C6:
    if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_P6);
        unregister_code(KC_LCTL);
    }
    return false;
    case C7:
    if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_P7);
        unregister_code(KC_LCTL);
    }
    return false;
    case C8:
    if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_P8);
        unregister_code(KC_LCTL);
    }
    return false;
    case C9:
    if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_P9);
        unregister_code(KC_LCTL);
    }
    return false;
    case CDOT:
    if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_PDOT);
        unregister_code(KC_LCTL);
    }
    return false;
     /// GUI Layer
    case G1:
    if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_P1);
        unregister_code(KC_LGUI);
    }
    return false;
    case G2:
    if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_P2);
        unregister_code(KC_LGUI);
    }
    return false;
    case G3:
    if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_P3);
        unregister_code(KC_LGUI);
    }
    return false;
    case G4:
    if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_P4);
        unregister_code(KC_LGUI);
    }
    return false;
    case G5:
    if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_P5);
        unregister_code(KC_LGUI);
    }
    return false;
    case G6:
    if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_P6);
        unregister_code(KC_LGUI);
    }
    return false;
    case G7:
    if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_P7);
        unregister_code(KC_LGUI);
    }
    return false;
    case G8:
    if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_P8);
        unregister_code(KC_LGUI);
    }
    return false;
    case G9:
    if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_P9);
        unregister_code(KC_LGUI);
    }
    return false;
    case GDOT:
    if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_PDOT);
        unregister_code(KC_LGUI);
    }
    return false;
     /// ALT Layer
    case A1:
    if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_P1);
        unregister_code(KC_LALT);
    }
    return false;
    case A2:
    if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_P2);
        unregister_code(KC_LALT);
    }
    return false;
    case A3:
    if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_P3);
        unregister_code(KC_LALT);
    }
    return false;
    case A4:
    if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_P4);
        unregister_code(KC_LALT);
    }
    return false;
    case A5:
    if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_P5);
        unregister_code(KC_LALT);
    }
    return false;
    case A6:
    if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_P6);
        unregister_code(KC_LALT);
    }
    return false;
    case A7:
    if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_P7);
        unregister_code(KC_LALT);
    }
    return false;
    case A8:
    if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_P8);
        unregister_code(KC_LALT);
    }
    return false;
    case A9:
    if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_P9);
        unregister_code(KC_LALT);
    }
    return false;
    case ADOT:
    if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_PDOT);
        unregister_code(KC_LALT);
    }
    return false;


    default:
    return true;  // Process all other keycodes normally
}

return true;
}

 ///RGB
void keyboard_post_init_user(void) {
    // Enable RGB Matrix
    rgb_matrix_enable();

    // Set the default effect to Starlight
    rgb_matrix_mode(RGB_MATRIX_STARLIGHT);
    rgb_matrix_sethsv(132, 102, 180);
    eeconfig_update_rgb_matrix(); // Ensure it persists across power cycles
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_tenkey_27(
        KC_MUTE, KC_GRV, KC_BSLS,KC_QUOT,KC_PCMM,
        MC_1,	 CTL_L,  GUI_L,  ALT_L,  KC_PMNS,
        MC_2,	 KC_P7,	 KC_P8,	 KC_P9,	 KC_PPLS,
        MC_3,	 KC_P4,	 KC_P5,	 KC_P6,
        MC_4,	 KC_P1,	 KC_P2,	 KC_P3,	 KC_PEQL,
        MO(FN),  KC_P0,          KC_PDOT         ),

    [FN] = LAYOUT_tenkey_27(
        RGB_TOG, BT_HST1, BT_HST2, BT_HST3, P2P4G,
        _______, RGB_MOD, RGB_VAI, RGB_HUI, _______,
        _______, RGB_RMOD,RGB_VAD, RGB_HUD, _______,
        _______, RGB_SAI, RGB_SPI, KC_MPRV,
        _______, RGB_SAD, RGB_SPD, KC_MPLY, _______,
        _______, RGB_TOG,          KC_MNXT          ),

    [LCTL] = LAYOUT_tenkey_27(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, C7,      C8,      C9,      _______,
        _______, C4,      C5,      C6,
        _______, C1,      C2,      C3,      _______,
        _______, C0,               CDOT            ),

    [LGUI] = LAYOUT_tenkey_27(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, G7,      G8,      G9,      _______,
        _______, G4,      G5,      G6,
        _______, G1,      G2,      G3,      _______,
        _______, G0,               GDOT            ),

    [LALT] = LAYOUT_tenkey_27(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, A7,      A8,      A9,      _______,
        _______, A4,      A5,      A6,
        _______, A1,      A2,      A3,      _______,
        _______, A0,               ADOT            ),
};

// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [LCTL]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LGUI]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [LALT]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
};
#endif // ENCODER_MAP_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}
