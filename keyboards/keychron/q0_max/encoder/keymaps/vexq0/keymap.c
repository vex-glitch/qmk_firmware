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
enum custom_keycodes {
    KC_C0,
    KC_C1,
    KC_C2,
    KC_C3,
    KC_C4,
    KC_C5,
    KC_C6,
    KC_C7,
    KC_C8,
    KC_C9,
    KC_CDOT,
    KC_CMM,
    KC_CMNS,
    KC_CPLS,
    KC_CIM,
    KC_CIIM,
    KC_CIIIM,
    KC_G0,
    KC_G1,
    KC_G2,
    KC_G3,
    KC_G4,
    KC_G5,
    KC_G6,
    KC_G7,
    KC_G8,
    KC_G9,
    KC_GDOT,
    KC_GMM,
    KC_GMNS,
    KC_GPLS,
    KC_GIM,
    KC_GIIM,
    KC_GIIIM,
    KC_A0,
    KC_A1,
    KC_A2,
    KC_A3,
    KC_A4,
    KC_A5,
    KC_A6,
    KC_A7,
    KC_A8,
    KC_A9,
    KC_ADOT,
    KC_AMM,
    KC_AMNS,
    KC_APLS,
    KC_AIM,
    KC_AIIM,
    KC_AIIIM,
    KC_IM,
    KC_IIM,
    KC_IIIM,



};

 ///RGB
void keyboard_post_init_user(void) {
    // Enable RGB Matrix
    rgb_matrix_enable();

    // Set the default effect to Starlight
    rgb_matrix_mode(RGB_MATRIX_STARLIGHT);
    rgb_matrix_sethsv(132, 102, 180);
    eeconfig_update_rgb_matrix(); // Ensure it persists across power cycles
}

// Advanced user function for per-key RGB lighting
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    for (uint8_t i = led_min; i < led_max; i++) {
        if (layer == LCTL) {
        rgb_matrix_set_color(1, RGB_RED);
    }
        if (layer == LGUI) {
        rgb_matrix_set_color(2, RGB_GREEN);
    }
        if (layer == LALT) {
        rgb_matrix_set_color(0, RGB_YELLOW);
    }
}
     return false;  // Allow other matrix effects to run
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_tenkey_27(
        KC_MUTE,   ALT_L,     CTL_L,     GUI_L,     KC_IM,
        MC_1,	   KC_PCMM,   KC_PMNS,   KC_PPLS,   KC_IIM,
        MC_2,	   KC_P7,	  KC_P8,	 KC_P9,	    KC_IIIM,
        MC_3,	   KC_P4,	  KC_P5,	 KC_P6,
        MC_4,	   KC_P1,	  KC_P2,	 KC_P3,	    KC_PEQL,
        MO(FN),    KC_P0,                KC_PDOT           ),

    [FN] = LAYOUT_tenkey_27(
        RGB_TOG,   BT_HST1,   BT_HST2,   BT_HST3,   P2P4G,
        _______,   RGB_MOD,   RGB_VAI,   RGB_HUI,   _______,
        _______,   RGB_RMOD,  RGB_VAD,   RGB_HUD,   _______,
        _______,   RGB_SAI,   RGB_SPI,   KC_MPRV,
        _______,   RGB_SAD,   RGB_SPD,   KC_MPLY,   _______,
        _______,   RGB_TOG,              KC_MNXT           ),

    [LCTL] = LAYOUT_tenkey_27(
        _______,   _______,   _______,   _______,   KC_CIM,
        _______,   KC_CMM,    KC_CMNS,   KC_CPLS,   KC_CIIM,
        _______,   KC_C7,     KC_C8,     KC_C9,     KC_CIIIM,
        _______,   KC_C4,     KC_C5,     KC_C6,
        _______,   KC_C1,     KC_C2,     KC_C3,     _______,
        _______,   KC_C0,                KC_CDOT           ),

    [LGUI] = LAYOUT_tenkey_27(
        _______,   _______,   _______,   _______,   KC_GIM,
        _______,   KC_GMM,    KC_GMNS,   KC_GPLS,   KC_GIIM,
        _______,   KC_G7,     KC_G8,     KC_G9,     KC_GIIIM,
        _______,   KC_G4,     KC_G5,     KC_G6,
        _______,   KC_G1,     KC_G2,     KC_G3,     _______,
        _______,   KC_G0,                KC_GDOT           ),

    [LALT] = LAYOUT_tenkey_27(
        _______,   _______,   _______,   _______,   KC_AIM,
        _______,   KC_AMM,    KC_AMNS,   KC_APLS,   KC_AIIM,
        _______,   KC_A7,     KC_A8,     KC_A9,     KC_AIIIM,
        _______,   KC_A4,     KC_A5,     KC_A6,
        _______,   KC_A1,     KC_A2,     KC_A3,     _______,
        _______,   KC_A0,                KC_ADOT           ),
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
    switch (keycode) {
        /// CTL Layer
       case KC_C0:
       if (record->event.pressed) {
           register_code(KC_LCTL);
           tap_code(KC_P0);
           unregister_code(KC_LCTL);
       }
       return false;
       case KC_C1:
       if (record->event.pressed) {
           register_code(KC_LCTL);
           tap_code(KC_P1);
           unregister_code(KC_LCTL);
       }
       return false;
       case KC_C2:
       if (record->event.pressed) {
           register_code(KC_LCTL);
           tap_code(KC_P2);
           unregister_code(KC_LCTL);
       }
       return false;
       case KC_C3:
       if (record->event.pressed) {
           register_code(KC_LCTL);
           tap_code(KC_P3);
           unregister_code(KC_LCTL);
       }
       return false;
       case KC_C4:
       if (record->event.pressed) {
           register_code(KC_LCTL);
           tap_code(KC_P4);
           unregister_code(KC_LCTL);
       }
       return false;
       case KC_C5:
       if (record->event.pressed) {
           register_code(KC_LCTL);
           tap_code(KC_P5);
           unregister_code(KC_LCTL);
       }
       return false;
       case KC_C6:
       if (record->event.pressed) {
           register_code(KC_LCTL);
           tap_code(KC_P6);
           unregister_code(KC_LCTL);
       }
       return false;
       case KC_C7:
       if (record->event.pressed) {
           register_code(KC_LCTL);
           tap_code(KC_P7);
           unregister_code(KC_LCTL);
       }
       return false;
       case KC_C8:
       if (record->event.pressed) {
           register_code(KC_LCTL);
           tap_code(KC_P8);
           unregister_code(KC_LCTL);
       }
       return false;
       case KC_C9:
       if (record->event.pressed) {
           register_code(KC_LCTL);
           tap_code(KC_P9);
           unregister_code(KC_LCTL);
       }
       return false;
       case KC_CDOT:
       if (record->event.pressed) {
           register_code(KC_LCTL);
           tap_code(KC_PDOT);
           unregister_code(KC_LCTL);
       }
       return false;
       case KC_CMM:
       if (record->event.pressed) {
           register_code(KC_LCTL);
           tap_code(KC_PCMM);
           unregister_code(KC_LCTL);
       }
       return false;
       case KC_CMNS:
       if (record->event.pressed) {
           register_code(KC_LCTL);
           tap_code(KC_PMNS);
           unregister_code(KC_LCTL);
       }
       return false;
       case KC_CPLS:
       if (record->event.pressed) {
           register_code(KC_LCTL);
           tap_code(KC_PPLS);
           unregister_code(KC_LCTL);
       }
       return false;
        /// GUI Layer
        case KC_G0:
        if (record->event.pressed) {
            register_code(KC_LGUI);
            tap_code(KC_P0);
            unregister_code(KC_LGUI);
        }
        return false;
       case KC_G1:
       if (record->event.pressed) {
           register_code(KC_LGUI);
           tap_code(KC_P1);
           unregister_code(KC_LGUI);
       }
       return false;
       case KC_G2:
       if (record->event.pressed) {
           register_code(KC_LGUI);
           tap_code(KC_P2);
           unregister_code(KC_LGUI);
       }
       return false;
       case KC_G3:
       if (record->event.pressed) {
           register_code(KC_LGUI);
           tap_code(KC_P3);
           unregister_code(KC_LGUI);
       }
       return false;
       case KC_G4:
       if (record->event.pressed) {
           register_code(KC_LGUI);
           tap_code(KC_P4);
           unregister_code(KC_LGUI);
       }
       return false;
       case KC_G5:
       if (record->event.pressed) {
           register_code(KC_LGUI);
           tap_code(KC_P5);
           unregister_code(KC_LGUI);
       }
       return false;
       case KC_G6:
       if (record->event.pressed) {
           register_code(KC_LGUI);
           tap_code(KC_P6);
           unregister_code(KC_LGUI);
       }
       return false;
       case KC_G7:
       if (record->event.pressed) {
           register_code(KC_LGUI);
           tap_code(KC_P7);
           unregister_code(KC_LGUI);
       }
       return false;
       case KC_G8:
       if (record->event.pressed) {
           register_code(KC_LGUI);
           tap_code(KC_P8);
           unregister_code(KC_LGUI);
       }
       return false;
       case KC_G9:
       if (record->event.pressed) {
           register_code(KC_LGUI);
           tap_code(KC_P9);
           unregister_code(KC_LGUI);
       }
       return false;
       case KC_GDOT:
       if (record->event.pressed) {
           register_code(KC_LGUI);
           tap_code(KC_PDOT);
           unregister_code(KC_LGUI);
       }
       return false;
       case KC_GMM:
       if (record->event.pressed) {
           register_code(KC_LGUI);
           tap_code(KC_PCMM);
           unregister_code(KC_LGUI);
       }
       return false;
       case KC_GMNS:
       if (record->event.pressed) {
           register_code(KC_LGUI);
           tap_code(KC_PMNS);
           unregister_code(KC_LGUI);
       }
       return false;
       case KC_GPLS:
       if (record->event.pressed) {
           register_code(KC_LGUI);
           tap_code(KC_PPLS);
           unregister_code(KC_LGUI);
       }
       return false;
        /// ALT Layer
        case KC_A0:
        if (record->event.pressed) {
            register_code(KC_LALT);
            tap_code(KC_P0);
            unregister_code(KC_LALT);
        }
        return false;
       case KC_A1:
       if (record->event.pressed) {
           register_code(KC_LALT);
           tap_code(KC_P1);
           unregister_code(KC_LALT);
       }
       return false;
       case KC_A2:
       if (record->event.pressed) {
           register_code(KC_LALT);
           tap_code(KC_P2);
           unregister_code(KC_LALT);
       }
       return false;
       case KC_A3:
       if (record->event.pressed) {
           register_code(KC_LALT);
           tap_code(KC_P3);
           unregister_code(KC_LALT);
       }
       return false;
       case KC_A4:
       if (record->event.pressed) {
           register_code(KC_LALT);
           tap_code(KC_P4);
           unregister_code(KC_LALT);
       }
       return false;
       case KC_A5:
       if (record->event.pressed) {
           register_code(KC_LALT);
           tap_code(KC_P5);
           unregister_code(KC_LALT);
       }
       return false;
       case KC_A6:
       if (record->event.pressed) {
           register_code(KC_LALT);
           tap_code(KC_P6);
           unregister_code(KC_LALT);
       }
       return false;
       case KC_A7:
       if (record->event.pressed) {
           register_code(KC_LALT);
           tap_code(KC_P7);
           unregister_code(KC_LALT);
       }
       return false;
       case KC_A8:
       if (record->event.pressed) {
           register_code(KC_LALT);
           tap_code(KC_P8);
           unregister_code(KC_LALT);
       }
       return false;
       case KC_A9:
       if (record->event.pressed) {
           register_code(KC_LALT);
           tap_code(KC_P9);
           unregister_code(KC_LALT);
       }
       return false;
       case KC_ADOT:
       if (record->event.pressed) {
           register_code(KC_LALT);
           tap_code(KC_PDOT);
           unregister_code(KC_LALT);
       }
       return false;
       case KC_AMM:
       if (record->event.pressed) {
           register_code(KC_LALT);
           tap_code(KC_PCMM);
           unregister_code(KC_LALT);
       }
       return false;
       case KC_AMNS:
       if (record->event.pressed) {
           register_code(KC_LALT);
           tap_code(KC_PMNS);
           unregister_code(KC_LALT);
       }
       return false;
       case KC_APLS:
       if (record->event.pressed) {
           register_code(KC_LALT);
           tap_code(KC_PPLS);
           unregister_code(KC_LALT);
       }
       return false;
       case KC_IM:
       if (record->event.pressed) {
           register_code(KC_LSFT);
           tap_code(KC_PPLS);
           unregister_code(KC_LSFT);
       }
       return false;
       case KC_IIM:
       if (record->event.pressed) {
           register_code(KC_LSFT);
           tap_code(KC_PMNS);
           unregister_code(KC_LSFT);
       }
       return false;
       case KC_IIIM:
       if (record->event.pressed) {
           register_code(KC_LSFT);
           tap_code(KC_PCMM);
           unregister_code(KC_LSFT);
       }
       return false;
       case KC_CIM:
       if (record->event.pressed) {
           register_code(KC_LSFT);
           register_code(KC_LCTL);
           tap_code(KC_PPLS);
           register_code(KC_LCTL);
           unregister_code(KC_LSFT);
       }
       return false;
       case KC_CIIM:
       if (record->event.pressed) {
           register_code(KC_LSFT);
           register_code(KC_LCTL);
           tap_code(KC_PMNS);
            register_code(KC_LCTL);
           unregister_code(KC_LSFT);
       }
       return false;
       case KC_CIIIM:
       if (record->event.pressed) {
            register_code(KC_LCTL);
           register_code(KC_LSFT);
           tap_code(KC_PCMM);
           unregister_code(KC_LSFT);
              unregister_code(KC_LCTL);
       }
       return false;
       case KC_GIM:
       if (record->event.pressed) {
           register_code(KC_LSFT);
           register_code(KC_LGUI);
           tap_code(KC_PPLS);
           register_code(KC_LGUI);
           unregister_code(KC_LSFT);
       }
       return false;
       case KC_GIIM:
       if (record->event.pressed) {
           register_code(KC_LSFT);
           register_code(KC_LGUI);
           tap_code(KC_PMNS);
            register_code(KC_LGUI);
           unregister_code(KC_LSFT);
       }
       return false;
       case KC_GIIIM:
       if (record->event.pressed) {
            register_code(KC_LGUI);
           register_code(KC_LSFT);
           tap_code(KC_PCMM);
           unregister_code(KC_LSFT);
              unregister_code(KC_LGUI);
       }
       return false;
       case KC_AIM:
       if (record->event.pressed) {
           register_code(KC_LSFT);
           register_code(KC_LALT);
           tap_code(KC_PPLS);
           register_code(KC_LALT);
           unregister_code(KC_LSFT);
       }
       return false;
       case KC_AIIM:
       if (record->event.pressed) {
           register_code(KC_LSFT);
           register_code(KC_LALT);
           tap_code(KC_PMNS);
            register_code(KC_LALT);
           unregister_code(KC_LSFT);
       }
       return false;
       case KC_AIIIM:
       if (record->event.pressed) {
            register_code(KC_LALT);
           register_code(KC_LSFT);
           tap_code(KC_PCMM);
           unregister_code(KC_LSFT);
              unregister_code(KC_LALT);
       }
       return false;

       default:
       return true;  // Process all other keycodes normally
   }
    return true;
}
