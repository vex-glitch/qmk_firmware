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
~ *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "unicode.h"
#include "features/autocorrection.h"
#include "features/repeat_key.h"
#include "features/sentence_case.h"
#include "features/achordion.h"
#include "features/select_word.h"
#include "features/select_word_back.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum layers {
    MAC_BASE,    // Layer 0 - Base Layer
    MAC_FN,      // Layer 1 - Function Layer
    CMAK_BASE,   // Layer 2 - Colemak Base Layer
    EXTEND,      // Layer 3 - Extend Layer
    WINDOWS,     // Layer 4 - Windows Layer
    FUN,         // Layer 5 - Function Layer
    SYM,         // Layer 6 - Symbol Layer
    PIC,         // Layer 7 - Picto Layer
  };
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tap Dance Declarations
enum {
// F Keys
    TD_ALFRED,
    TD_HOOK,
    TD_CLEANSHOT,
    TD_DROP,
    TD_SIDENOTE,
    TD_ARC,
    TD_SNIPLAB,
    TD_PERP,
    TD_CHAT,
    TD_MUSE,
    TD_TRELLO,
    TD_OOUTLINER,
    TD_DAYONE,
    TD_FANTASTICAL,
    TD_SPARK,
    TD_ANYBOX,
    TD_EAGLE,
    TD_DEVONTHINK,
    TD_FINDER,
    TD_BEAR,
    TD_OMNIFOCUS,
    TD_DRAFTS,
// Other Tapdances
// Tap Dance Declarations::Colemak Layer
    TD_ESCAPE,
    TD_TAB,
    TD_TEXHYPE,
    TD_UNMEHZ,
    TD_KEYCUE,
    TD_QMACRO,
    TD_UNIALF,
    TD_SPACE,
    TD_CLIP,
    TD_FILEFRED,
    TD_SCREEN,
    TD_CAPS,
    TD_ALFMEH2,
    TD_HASHAT,
    TD_FORWARDDELETE,
    TD_SMILE,
    TD_SLASH,
    TD_QUESTION,
    TD_PERIOD,
    TD_COMMA,
    TD_DELWORD,
    TD_OSSHIFT,
    TD_VPASTE,
    TD_DDUPLICATE,
    TD_COPY,
    TD_XCUT,
    TD_QSELALL,
    TD_USCR,
    TD_LEADOSTROPHE,
    TD_QUICKY,
    TD_ONE,
    TD_TWO,
    TD_THREE,
// Tap Dance Declarations::Extend Layer
    TD_TIL,
// Tap Dance Declarations::Windows Layer
    TD_FULL,
// Tap Dance Declarations::Fun Layer
    TD_PORT,
    TD_CLARITY,
    TD_SLEEVE,
// Tap Dance Declarations::Symbol Layer
    TD_RB,
    TD_SBL,
    TD_SBR,
    TD_BACKT,
    TD_EQUALS,
    TD_STAR,
    TD_UNSC,
  };
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definitons
// F keys
    #define ALFRED    TD(TD_ALFRED)
    #define HOOK      TD(TD_HOOK)
    #define CLEANSHT  TD(TD_CLEANSHOT)
    #define DROP      TD(TD_DROP)
    #define SIDENOTE TD(TD_SIDENOTE)
    #define ARC       TD(TD_ARC)
    #define SNIP      TD(TD_SNIPLAB)
    #define PERP      TD(TD_PERP)
    #define CHAT      TD(TD_CHAT)
    #define MUSE      TD(TD_MUSE)
    #define TRELLO    TD(TD_TRELLO)
    #define OOUT      TD(TD_OOUTLINER)
    #define DAYONE    TD(TD_DAYONE)
    #define FANTAS    TD(TD_FANTASTICAL)
    #define SPARK     TD(TD_SPARK)
    #define ANYBOX    TD(TD_ANYBOX)
    #define EAGLE     TD(TD_EAGLE)
    #define DEVON     TD(TD_DEVONTHINK)
    #define FINDER    TD(TD_FINDER)
    #define BEAR      TD(TD_BEAR)
    #define OFOCUS    TD(TD_OMNIFOCUS)
    #define DRAFTS    TD(TD_DRAFTS)
// Other Tapdances
// Tap Dance Declarations::Colemak Layer
    #define ESCAPE    TD(TD_ESCAPE)
    #define TAB       TD(TD_TAB)
    #define TEXHYPE   TD(TD_TEXHYPE)
    #define UNMEHZ    TD(TD_UNMEHZ)
    #define KEYCUE    TD(TD_KEYCUE)
    #define QMACRO    TD(TD_QMACRO)
    #define UNIALF    TD(TD_UNIALF)
    #define SPACE     TD(TD_SPACE)
    #define CLIP      TD(TD_CLIP)
    #define FILEFRED  TD(TD_FILEFRED)
    #define SCREEN    TD(TD_SCREEN)
    #define CAPW      TD(TD_CAPS)
    #define ALFMEH2   TD(TD_ALFMEH2)
    #define HASHAT    TD(TD_HASHAT)
    #define FORDEL    TD(TD_FORWARDDELETE)
    #define SMILE     TD(TD_SMILE)
    #define SLASH     TD(TD_SLASH)
    #define QUESTION  TD(TD_QUESTION)
    #define PERIOD    TD(TD_PERIOD)
    #define COMMA     TD(TD_COMMA)
    #define DELWORD   TD(TD_DELWORD)
    #define OSSHIFT   TD(TD_OSSHIFT)
    #define VPASTE    TD(TD_VPASTE)
    #define DDUP      TD(TD_DDUPLICATE)
    #define CCOPY     TD(TD_COPY)
    #define XCUT      TD(TD_XCUT)
    #define QSELALL   TD(TD_QSELALL)
    #define USCR      TD(TD_USCR)
    #define LEADPOST  TD(TD_LEADOSTROPHE)
    #define QUICKY    TD(TD_QUICKY)
    #define ONE       TD(TD_ONE)
    #define TWO       TD(TD_TWO)
    #define THREE     TD(TD_THREE)
// Tap Dance Declarations::Extend Layer
    #define TIL       TD(TD_TIL)
// Tap Dance Declarations::Windows Layer
    #define FULL      TD(TD_FULL)
// Tap Dance Declarations::Fun Layer
    #define PORT      TD(TD_PORT)
    #define CLARITY   TD(TD_CLARITY)
    #define SLEEVE    TD(TD_SLEEVE)
// Tap Dance Declarations::Symbol Layer
    #define RB        TD(TD_RB)
    #define SBL       TD(TD_SBL)
    #define SBR       TD(TD_SBR)
    #define BACKT     TD(TD_BACKT)
    #define EQUALS    TD(TD_EQUALS)
    #define STAR      TD(TD_STAR)
    #define UNSC      TD(TD_UNSC)
// Not tapdances
    #define MOUSEUP  KC_MS_UP
    #define MOUSEDN  KC_MS_DOWN
    #define MOUSELT  KC_MS_LEFT
    #define MOUSERT  KC_MS_RIGHT
    #define MSEWHLUP KC_MS_WH_UP
    #define MSEWHLDO KC_MS_WH_DOWN
    #define MSEWHLLE KC_MS_WH_LEFT
    #define MSEWHLRI KC_MS_WH_RIGHT
    #define MSEC1    KC_MS_BTN1
    #define MSEC2    KC_MS_BTN2
    #define MSEC3    KC_MS_BTN3
    #define MSEC4    KC_MS_BTN4
    #define PAGEUP   KC_PGUP
    #define PAGEDN   KC_PGDN
    #define HOME     KC_HOME
    #define END      KC_END
    #define PLAY     KC_MEDIA_PLAY_PAUSE
    #define REWIND   KC_MEDIA_PREV_TRACK
    #define NEXT     KC_MEDIA_FAST_FORWARD
    #define MCNTRL   KC_MISSION_CONTROL
    #define LNCHPAD  KC_LAUNCHPAD
    #define POWER    KC_SYSTEM_POWER
    #define BBACK    KC_WWW_BACK
    #define BFORW    KC_WWW_FORWARD
// QWERTY Layout
// Left-hand home row mods
    #define CTL_A    LCTL_T(KC_A)
    #define ALT_S    LALT_T(KC_S)
    #define GUI_D    LGUI_T(KC_D)
    #define SFT_F    LSFT_T(KC_F)
// Right-hand home row mods
    #define SFT_J    RSFT_T(KC_J)
    #define GUI_K    RGUI_T(KC_K)
    #define ALT_L    LALT_T(KC_L)
    #define CTL_SCLN RCTL_T(KC_SCLN)
    #define SHIFTZ   MT(MOD_LSFT, KC_Z)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Leds
    static bool is_caps_active_flag = false;  // Tracks Caps Word state
    static uint32_t caps_blink_timer = 0;    // Timer for CAPS blinking

    #define CAPS_LED 0    // Set this to the correct LED index for your CAPS key
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// F KEYS - APPS
// Alfred::tapdance
void dance_alfred_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F3);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LGUI);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F3);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F3);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F3);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F3);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        tap_code(KC_F3);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LALT);
        tap_code(KC_F3);
        unregister_code(KC_LALT);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F3);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_alfred_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// Hookmark::tapdance
void dance_hook_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F7);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_F7);
         unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F7);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F7);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F7);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        tap_code(KC_F7);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LALT);
        tap_code(KC_F7);
        unregister_code(KC_LALT);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F7);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_hook_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// CleanShot::tapdance
void dance_cleanshot_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F1);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F1);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LGUI);
        tap_code(KC_F1);
        register_code(KC_LGUI);
        register_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        tap_code(KC_F1);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F1);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F1);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F1);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F1);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_cleanshot_reset(tap_dance_state_t *state, void *user_data) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
}
// DropZone::tapdance
void dance_drop_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F5);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F5);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F5);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F5);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F5);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F5);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F5);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F5);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_drop_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// Sidenotes::tapdance
void dance_sidenote_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F6 );
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_F6 );
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F6 );
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F6 );
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F6 );
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        tap_code(KC_F6 );
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LALT);
        tap_code(KC_F6);
        unregister_code(KC_LALT);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F6 );
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_sidenote_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// Arc::tapdance
void dance_arc_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F16);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F16);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F16);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F16);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F16);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F16);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F16);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F16);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_arc_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// SnippetsLab::tapdance
void dance_sniplab_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F20);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F20);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F20);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F20);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F20);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F20);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F20);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F20);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_sniplab_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// Perplexity::tapdance
void dance_perp_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F18);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F18);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F18);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F18);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F18);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F18);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F18);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F18);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_perp_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// ChatGPT::tapdance
void dance_chat_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F17);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F17);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F17);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F17);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F17);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F17);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F17);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F17);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_chat_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// Muse::tapdance
void dance_muse_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F8);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F8);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F8);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F8);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F8);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F8);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F8);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F8);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_muse_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// Trello::tapdance
void dance_trello_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F11);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F11);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F11);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F11);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F11);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F11);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F11);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F11);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_trello_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// OmniOutliner::tapdance
void dance_ooutliner_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F10);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F10);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F10);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F10);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F10);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F10);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F10);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F10);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_ooutliner_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// Dayone::tapdance
void dance_dayone_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F12);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F12);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F12);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F12);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F12);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F12);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F12);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F12);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_dayone_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// Fantastical::tapdance
void dance_fantastical_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F13);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F13);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F13);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F13);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F13);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F13);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F13);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F13);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_fantastical_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// Spark::tapdance
void dance_spark_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F14);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F14);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F14);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F14);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F14);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F14);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F14);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F14);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_spark_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// AnyBox::tapdance
void dance_anybox_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F15 );
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_F15 );
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F15 );
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F15 );
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F15 );
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        tap_code(KC_F15 );
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LALT);
        tap_code(KC_F15 );
        unregister_code(KC_LALT);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F15 );
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_anybox_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// Eagle::tapdance
void dance_eagle_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_INS);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_EQL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_INS);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_INS);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_INS);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_INS);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_INS);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_INS);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_eagle_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// DEVONTHINK::tapdance
void dance_devonthink_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_HOME);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_HOME);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_HOME);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_HOME);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_HOME);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_HOME);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_HOME);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_HOME);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_devonthink_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// Finder::tapdance
void dance_finder_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_PGUP);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_PGUP);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_PGUP);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_PGUP);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_PGUP);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_PGUP);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_PGUP);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_PGUP);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_finder_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// Bear::tapdance
void dance_bear_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_DEL);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_DEL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_DEL);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_DEL);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_DEL);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_DEL);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_DEL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_DEL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_bear_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// OmniFocus::tapdance
void dance_omnifocus_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_END);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_END);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_END);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_END);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_END);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_END);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_END);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_END);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_omnifocus_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// Drafts::tapdance
void dance_drafts_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_PGDN);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_PGDN);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_PGDN);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_PGDN);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_PGDN);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_PGDN);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_PGDN);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_PGDN);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}
void dance_drafts_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Colemak tapdance actions
// Escape::tapdance
void dance_escape_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) { //Hide
        register_code(KC_LGUI);
        tap_code(KC_H);
        unregister_code(KC_LGUI);
    } else if (state->count == 1 && !state->pressed) {  //Escape
        tap_code(KC_ESC);
    } else if (state->count == 2 && !state->pressed) {  //Close
        register_code(KC_LGUI);
        tap_code(KC_W);
        unregister_code(KC_LGUI);
    } else if (state->count == 2 && state->pressed) {  //Quit
        register_code(KC_LGUI);
        tap_code(KC_Q);
        unregister_code(KC_LGUI);
    }
}
void dance_escape_reset(tap_dance_state_t *state, void *user_data) {
}
// Tab::tapdance
void dance_tab_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        tap_code(KC_TAB);
    }   else if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        register_code(KC_LALT);
    }   else if (state->count == 2 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LALT);
        register_code(KC_LGUI);
        tap_code(KC_TAB);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
        unregister_code(KC_RSFT);
    }
}
void dance_tab_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
    unregister_code(KC_LALT);
}
// TextHype::tapdance
void dance_texhype_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        send_string(" ^^");
    } else if (state->count == 1 && state->pressed) {
        register_mods(MOD_HYPR);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F19);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F19);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        tap_code(KC_F19);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F19);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_F19);
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    }
}
void dance_texhype_reset(tap_dance_state_t *state, void *user_data) {
    unregister_mods(MOD_HYPR);
}
// UnmehZ::tapdance
void dance_unmehz_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        tap_code(KC_Z);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LGUI);
        tap_code(KC_Z);
        unregister_code(KC_LGUI);
    } else if (state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        register_code(KC_LALT);
    }
}
void dance_unmehz_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
    unregister_code(KC_LALT);
}
// Keycue::tapdance
void dance_keycue_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LALT);
    } else if (state->count == 1 && !state->pressed) {
        tap_code_delay(KC_LALT, 15);
        wait_ms(50);
        tap_code_delay(KC_LALT, 15);
    } else if (state->count == 2 && state->pressed) {
        tap_code_delay(KC_LCTL, 15);
        wait_ms(50);
        tap_code_delay(KC_LCTL, 15);
    } else if (state->count == 2 && !state->pressed) {
        tap_code_delay(KC_LGUI, 15);
        wait_ms(50);
        tap_code_delay(KC_LGUI, 15);
    } else if (state->count == 3 && state->pressed) {
        //////////////////////////
    } else if (state->count == 3 && !state->pressed) {
        tap_code_delay(KC_LSFT, 15);
        wait_ms(50);
        tap_code_delay(KC_LSFT, 15);
    } else if (state->count == 4 && state->pressed) {
        ////////////////////////////
    } else if (state->count == 4 && !state->pressed) {
        ///////////////////////////
    }
}
void dance_keycue_reset(tap_dance_state_t *state, void *user_data) {
    // Release any keys if held
    unregister_code(KC_LALT);
}
// QMacro::tapdance
void dance_qmacro_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LCTL);
        tap_code(KC_F1);
        unregister_code(KC_LCTL);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LCTL);
        tap_code(KC_H);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
    }
}
void dance_qmacro_reset(tap_dance_state_t *state, void *user_data) {
}
// UniversalAlfred::tapdance
void dance_unialf_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_L);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 1 && state->pressed) {
        layer_on(FUN);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LGUI);
        tap_code(KC_Y);
        unregister_code(KC_LGUI);
    }
}
void dance_unialf_reset(tap_dance_state_t *state, void *user_data) {
    if (layer_state_is(FUN)) {
        layer_off(FUN);
    }
}
// Space::tapdance
void dance_space_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        tap_code(KC_SPC);
    } else if (state->count == 1 && state->pressed) {
        layer_on(EXTEND);
    } else if (state->count == 2 && !state->pressed) {
        tap_code(KC_ENT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_ENT);
        unregister_code(KC_LSFT);
    }
}
void dance_space_reset(tap_dance_state_t *state, void *user_data) {
    layer_off(EXTEND);
}
// Clip::tapdance
void dance_clip_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_F3);
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 1 && state->pressed) {
        layer_on(WINDOWS);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LALT);
        tap_code(KC_F1);
        unregister_code(KC_LALT);
        unregister_code(KC_LSFT);
    }
}
void dance_clip_reset(tap_dance_state_t *state, void *user_data) {
    if (layer_state_is(WINDOWS)) {
        layer_off(WINDOWS);
    }
}
// FileFred::tapdance
void dance_filefred_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        tap_code(KC_F3);
        wait_ms(50);
        send_string("ff ");
    } else if (state->count == 1 && !state->pressed) {
        tap_code(KC_F3);
        wait_ms(50);
        send_string("open ");
    } else if (state->count == 2 && !state->pressed) {
        tap_code(KC_F3);
        wait_ms(50);
        send_string("find ");
    } else if (state->count == 2 && state->pressed) {
        tap_code(KC_F3);
        wait_ms(50);
        send_string("in ");
    }
}
void dance_filefred_reset(tap_dance_state_t *state, void *user_data) {
}
// Screen::tapdance
void dance_screen_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        tap_code(KC_LCTL);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_1);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_2);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_3);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
    }
}
void dance_screen_reset(tap_dance_state_t *state, void *user_data) {
}
// Caps::tapdance
void dance_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        caps_word_on();
        is_caps_active_flag = true;
        caps_blink_timer = timer_read32();
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_Z);
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
    } else if (state->pressed) {
        register_code(KC_LSFT);
    }
}
void dance_caps_reset(tap_dance_state_t *state, void *user_data) {
    is_caps_active_flag = false;
    unregister_code(KC_LSFT);
}
// Alfmeh2::Tapdance
void dance_alfmeh2_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        register_code(KC_LGUI);
    } else if (state->count == 1 && !state->pressed) {
        tap_code(KC_F3);
    } else if (state->count == 2 && !state->pressed) {
        tap_code(KC_F3);
        wait_ms(50);
        send_string("! ");
        set_oneshot_mods(MOD_LSFT);
    }
}
void dance_alfmeh2_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
    unregister_code(KC_LGUI);
}
// Hashat::tapdance
void dance_hashat_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        send_string("#");
    } else if (state->count == 1 && state->pressed) {
        layer_on(SYM);
    } else if (state->count == 2 && !state->pressed) {
        send_string("@");
    }
}
void dance_hashat_reset(tap_dance_state_t *state, void *user_data) {
    layer_off(SYM);
}
// Forward Delete::tapdance
void dance_forwarddelete_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        tap_code(KC_DEL);
    } else if (state->count == 1 && state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_DEL);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_RGHT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
        tap_code(KC_BSPC);
    }
}
void dance_forwarddelete_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_LALT);
    unregister_code(KC_LSFT);
    unregister_code(KC_LGUI);
}
// Smile::tapdance
void dance_smile_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        send_string("=");
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LGUI);
        tap_code(KC_SPC);
        unregister_code(KC_LGUI);
        unregister_code(KC_LCTL);
    }
}
void dance_smile_reset(tap_dance_state_t *state, void *user_data) {
}
//  Slash::tapdance
void dance_slash_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        tap_code(KC_SLSH);
    } else if (state->count == 2 && !state->pressed) {
        tap_code(KC_BSLS);
    } else if (state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_BSLS);
        unregister_code(KC_LSFT);
    }
}
void dance_slash_reset(tap_dance_state_t *state, void *user_data) {
}
// Question::tapdance
void dance_question_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        SEND_STRING("? ");
        set_oneshot_mods(MOD_LSFT);
    } else if (state->count == 1 && state->pressed) {
        SEND_STRING("?");
    } else if (state->count == 2 && !state->pressed) {
        SEND_STRING("! ");
        set_oneshot_mods(MOD_LSFT);
    } else if (state->count == 2 && state->pressed) {
        SEND_STRING("!");
    }
}
void dance_question_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        clear_oneshot_mods();
    }
}
// Period::tapdance
void dance_period_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        SEND_STRING(". ");
        set_oneshot_mods(MOD_LSFT);
    }else if (state->count == 1 && state->pressed) {
        SEND_STRING(".");
    } else if (state->count == 2 && !state->pressed) {
        SEND_STRING(": ");
        set_oneshot_mods(MOD_LSFT);
    } else if (state->count == 2 && state->pressed) {
        SEND_STRING(":");
    }
}
void dance_period_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        clear_oneshot_mods();
    }
}
// Comma::tapdance
void dance_comma_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        SEND_STRING(", ");
    } else if (state->count == 1 && state->pressed) {
        SEND_STRING(",");
    } else if (state->count == 2 && !state->pressed) {
        SEND_STRING("; ");
    } else if (state->count == 2 && state->pressed) {
        SEND_STRING(";");
    }
}
void dance_comma_reset(tap_dance_state_t *state, void *user_data) {
}
// Delword::tapdance
void dance_delword_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_BSPC);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && !state->pressed) {
        tap_code(KC_BSPC);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LGUI);
        tap_code(KC_BSPC);
        unregister_code(KC_LGUI);
    }
}
void dance_delword_reset(tap_dance_state_t *state, void *user_data) {
}
// OneShotShift::tapdance
void dance_osshift_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        set_oneshot_mods(MOD_LSFT);
    }
}
void dance_osshift_reset(tap_dance_state_t *state, void *user_data) {
}
// Paste::tapdance
void dance_vpaste_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        tap_code(KC_V);
    } else if (state->count == 1 && state->pressed) {
        register_code(KC_LGUI);
        tap_code(KC_V);
        unregister_code(KC_LGUI);
    }
}
void dance_vpaste_reset(tap_dance_state_t *state, void *user_data) {
}
// Duplicate::tapdance
void dance_dduplicate_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        tap_code(KC_D);
    } else if (state->count == 1 && state->pressed) {
        register_code(KC_LGUI);
        tap_code(KC_D);
        unregister_code(KC_LGUI);
    }
}
void dance_dduplicate_reset(tap_dance_state_t *state, void *user_data) {
}
// Copy::tapdance
void dance_copy_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        tap_code(KC_C);
    } else if (state->count == 1 && state->pressed) {
        register_code(KC_LGUI);
        tap_code(KC_C);
        unregister_code(KC_LGUI);
    }
}
void dance_copy_reset(tap_dance_state_t *state, void *user_data) {
}
// Cut::tapdance
void dance_xcut_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        tap_code(KC_X);
    } else if (state->count == 1 && state->pressed) {
        register_code(KC_LGUI);
        tap_code(KC_X);
        unregister_code(KC_LGUI);
    }
}
void dance_xcut_reset(tap_dance_state_t *state, void *user_data) {
}
// QSelAll::tapdance
void dance_qselall_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LGUI);
        tap_code(KC_A);
        unregister_code(KC_LGUI);
    } else if (state->count == 1 && !state->pressed) {
        tap_code(KC_Q);
    }
}
void dance_qselall_reset(tap_dance_state_t *state, void *user_data) {
}
// USCR::tapdance
void dance_uscr_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        SEND_STRING("-");
    } else if (state->count == 2 && !state->pressed) {
        SEND_STRING("\"");
    } else if (state->count == 1 && state->pressed) {
        SEND_STRING("_");
    }
}
void dance_uscr_reset(tap_dance_state_t *state, void *user_data) {
}
// LEADOSTROPHE::tapdance
void dance_leadostrophe_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        leader_start();
    } else if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        register_code(KC_LALT);
        tap_code(KC_K);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
    } else if (state->count == 2 && !state->pressed) {
        SEND_STRING("'");
    }
}
void dance_leadostrophe_reset(tap_dance_state_t *state, void *user_data) {
}
// Quicky::tapdance
void dance_quicky_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        tap_code(KC_Y);
    } else if (state->count == 1 && state->pressed) {
        register_code(KC_LGUI);
        tap_code(KC_Y);
        unregister_code(KC_LGUI);
    }
}
void dance_quicky_reset(tap_dance_state_t *state, void *user_data) {
}
//  One::tapdance
void dance_one_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        tap_code(KC_1);
    } else if (state->count == 1 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_1);
        unregister_code(KC_LCTL);
    }
}
void dance_one_reset(tap_dance_state_t *state, void *user_data) {
}
//  Two::tapdance
void dance_two_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        tap_code(KC_2);
    } else if (state->count == 1 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_2);
        unregister_code(KC_LCTL);
    }
}
void dance_two_reset(tap_dance_state_t *state, void *user_data) {
}
//  Three::tapdance
void dance_three_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        tap_code(KC_3);
    } else if (state->count == 1 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_3);
        unregister_code(KC_LCTL);
    }
}
void dance_three_reset(tap_dance_state_t *state, void *user_data) {
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Extend::tapdance actions
// Til::tapdance
void dance_til_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        SEND_STRING("~");
    } else if (state->count == 1 && state->pressed) {
        SEND_STRING("~~~~");
        tap_code(KC_LEFT);
        tap_code(KC_LEFT);
    } else if (state->count == 2 && !state->pressed) {
        SEND_STRING("~~");
        tap_code(KC_LEFT);
    }
}
void dance_til_reset(tap_dance_state_t *state, void *user_data) {
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Windows::tapdance actions
// Full::tapdance
void dance_full_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        tap_code(KC_LCTL);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LCMD);
        tap_code(KC_F);
        unregister_code(KC_LCMD);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F);
        unregister_code(KC_LCTL);
    }
}
void dance_full_reset(tap_dance_state_t *state, void *user_data) {
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fun::tapdance actions
// Port::tapdance
void dance_port_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        register_code(KC_LALT);
        tap_code(KC_F4);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_F6);
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
    }
}
void dance_port_reset(tap_dance_state_t *state, void *user_data) {
}
// Clarity::tapdance
void dance_clarity_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LGUI);
        tap_code(KC_C);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_C);
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
    }
}
void dance_clarity_reset(tap_dance_state_t *state, void *user_data) {
}
// Sleeve::tapdance
void dance_sleeve_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_F5);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
    } else if (state->count == 2) {
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_9);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
    }
}
void dance_sleeve_reset(tap_dance_state_t *state, void *user_data) {
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Symbols::tapdance actions
// Rb::tapdance
void dance_rb_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        SEND_STRING(">");
    } else if (state->count == 1 && state->pressed) {
        SEND_STRING(">");
        tap_code(KC_SPACE);
    }
}
void dance_rb_reset(tap_dance_state_t *state, void *user_data) {
}
// SBL::tapdance
void dance_sbl_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        SEND_STRING("[");
    } else if (state->count == 2 && !state->pressed) {
        SEND_STRING("[[");
    }
}
void dance_sbl_reset(tap_dance_state_t *state, void *user_data) {
}
// SBR::tapdance
void dance_sbr_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        SEND_STRING("]");
    } else if (state->count == 2 && !state->pressed) {
        SEND_STRING("- [ ]");
        tap_code(KC_SPACE);
    }
}
void dance_sbr_reset(tap_dance_state_t *state, void *user_data) {
}
// Backt::tapdance
void dance_backt_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        SEND_STRING("`");
    } else if (state->count == 2 && !state->pressed) {
        SEND_STRING("``");
        tap_code(KC_LEFT);
    }
}
void dance_backt_reset(tap_dance_state_t *state, void *user_data) {
}
// Equals::tapdance
void dance_equals_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        SEND_STRING("=");
    } else if (state->count == 2 && !state->pressed) {
        SEND_STRING("====");
        tap_code(KC_LEFT);
        tap_code(KC_LEFT);
    }
}
void dance_equals_reset(tap_dance_state_t *state, void *user_data) {
}
// Star::tapdance
void dance_star_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        SEND_STRING("*");
    } else if (state->count == 2 && !state->pressed) {
        SEND_STRING("****");
        tap_code(KC_LEFT);
        tap_code(KC_LEFT);
    }
}
void dance_star_reset(tap_dance_state_t *state, void *user_data) {
}
// Underscore::tapdance
void dance_unsc_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        SEND_STRING("_");
    } else if (state->count == 2 && !state->pressed) {
        SEND_STRING("____");
        tap_code(KC_LEFT);
        tap_code(KC_LEFT);
    } else if (state->count == 1 && state->pressed) {
        SEND_STRING("___");
    }
}
void dance_unsc_reset(tap_dance_state_t *state, void *user_data) {
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Per key tapping term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_ALFRED):
            return TAPPING_TERM + 100;
        case TD(TD_HOOK):
            return TAPPING_TERM + 100;
        case TD(TD_CLEANSHOT):
            return TAPPING_TERM + 100;
        case TD(TD_DROP):
            return TAPPING_TERM + 100;
        case TD(TD_SIDENOTE):
            return TAPPING_TERM + 100;
        case TD(TD_ARC):
            return TAPPING_TERM + 100;
        case TD(TD_SNIPLAB):
            return TAPPING_TERM + 100;
        case TD(TD_PERP):
            return TAPPING_TERM + 100;
        case TD(TD_CHAT):
            return TAPPING_TERM + 100;
        case TD(TD_MUSE):
            return TAPPING_TERM + 100;
        case TD(TD_TRELLO):
            return TAPPING_TERM + 100;
        case TD(TD_OOUTLINER):
            return TAPPING_TERM + 100;
        case TD(TD_DAYONE):
            return TAPPING_TERM + 100;
        case TD(TD_FANTASTICAL):
            return TAPPING_TERM + 100;
        case TD(TD_SPARK):
            return TAPPING_TERM + 100;
        case TD(TD_ANYBOX):
            return TAPPING_TERM + 100;
        case TD(TD_EAGLE):
            return TAPPING_TERM + 100;
        case TD(TD_DEVONTHINK):
            return TAPPING_TERM + 100;
        case TD(TD_FINDER):
            return TAPPING_TERM + 100;
        case TD(TD_BEAR):
            return TAPPING_TERM + 100;
        case TD(TD_OMNIFOCUS):
            return TAPPING_TERM + 100;
        case TD(TD_DRAFTS):
            return TAPPING_TERM + 100;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Colemak Per Key Tapdancing
        case TD(TD_ESCAPE):
            return TAPPING_TERM + 75;
        case TD(TD_TAB):
            return TAPPING_TERM + 75;
        case TD(TD_TEXHYPE):
            return TAPPING_TERM + 75;
     // case TD(TD_UNMEHZ):
     //     return TAPPING_TERM + 75;
        case TD(TD_KEYCUE):
            return TAPPING_TERM + 75;
     // case TD(TD_QMMACRO):
     //     return TAPPING_TERM + 75;
        case TD(TD_UNIALF):
            return TAPPING_TERM + 75;
        case TD(TD_SPACE):
            return TAPPING_TERM + 50;
        case TD(TD_CLIP):
            return TAPPING_TERM + 75;
        case TD(TD_FILEFRED):
            return TAPPING_TERM + 75;
        case TD(TD_SCREEN):
            return TAPPING_TERM + 75;
        case TD(TD_CAPS):
            return TAPPING_TERM + 25;
        case TD(TD_ALFMEH2):
            return TAPPING_TERM + 50;
        case TD(TD_HASHAT):
            return TAPPING_TERM + 50;
        case TD(TD_FORWARDDELETE):
            return TAPPING_TERM + 50;
        case TD(TD_SMILE):
            return TAPPING_TERM + 50;
        case TD(TD_SLASH):
            return TAPPING_TERM + 50;
        case TD(TD_QUESTION):
            return TAPPING_TERM + 50;
        case TD(TD_PERIOD):
            return TAPPING_TERM + 50;
        case TD(TD_COMMA):
            return TAPPING_TERM + 50;
        case TD(TD_DELWORD):
            return TAPPING_TERM + 50;
        case TD(TD_OSSHIFT):
            return TAPPING_TERM + 50;
     // case TD(TD_VPASTE):
     //     return TAPPING_TERM + 75;
     // case TD(TD_DDUPLICATE):
     //     return TAPPING_TERM + 75;
     // case TD(TD_COPY):
     //     return TAPPING_TERM + 75;
     // case TD(TD_XCUT):
     //     return TAPPING_TERM + 75;
     // case TD(TD_QSELALL):
     //     return TAPPING_TERM + 75;
        case TD(TD_USCR):
            return TAPPING_TERM + 50;
        case TD(TD_LEADOSTROPHE):
            return TAPPING_TERM + 50;
     // case TD(TD_QUICKY):
     //     return TAPPING_TERM + 75;
        case TD(TD_ONE):
            return TAPPING_TERM + 25;
        case TD(TD_TWO):
            return TAPPING_TERM + 25;
        case TD(TD_THREE):
            return TAPPING_TERM + 25;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Extend Per Key Tapdancing
        case TD(TD_TIL):
            return TAPPING_TERM + 50;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Windows Per Key Tapdancing
        case TD(TD_FULL):
            return TAPPING_TERM + 50;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fun Per Key Tapdancing
        case TD(TD_PORT):
            return TAPPING_TERM + 50;
        case TD(TD_CLARITY):
            return TAPPING_TERM + 50;
        case TD(TD_SLEEVE):
            return TAPPING_TERM + 50;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Symbols Per Key Tapdancing
        case TD(TD_RB):
            return TAPPING_TERM + 50;
        case TD(TD_SBL):
            return TAPPING_TERM + 50;
        case TD(TD_SBR):
            return TAPPING_TERM + 50;
        case TD(TD_BACKT):
            return TAPPING_TERM + 50;
        case TD(TD_EQUALS):
            return TAPPING_TERM + 50;
        case TD(TD_STAR):
            return TAPPING_TERM + 50;
        case TD(TD_UNSC):
            return TAPPING_TERM + 50;
        default:
            return TAPPING_TERM;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Caps Word User Function
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A:
        case KC_B:
        case KC_C:
        case KC_D:
        case KC_E:
        case KC_F:
        case KC_G:
        case KC_H:
        case KC_I:
        case KC_J:
        case KC_K:
        case KC_L:
        case KC_M:
        case KC_N:
        case KC_O:
        case KC_P:
        case KC_Q:
        case KC_R:
        case KC_S:
        case KC_T:
        case KC_U:
        case KC_V:
        case KC_W:
        case KC_X:
        case KC_Y:
        case KC_Z:
        case KC_MINS:
        case HOME_A:
        case HOME_R:
        case HOME_S:
        case HOME_T:
        case HOME_N:
        case HOME_E:
        case HOME_I:
        case HOME_O:
        case USCR:
        case ALT_S:
        case GUI_D:
        case SFT_F:
        case SFT_J:
        case GUI_K:
        case ALT_L:
        case CTL_SCLN:
        case UNMEHZ:
        case CCOPY:
        case VPASTE:
        case XCUT:
        case QUICKY:
        case DDUP:
        case QSELALL:
    add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift
return true; // Keep Caps Word active
// Keys that continue Caps Word without shifting
        case KC_1:
        case KC_2:
        case KC_3:
        case KC_4:
        case KC_5:
        case KC_6:
        case KC_7:
        case KC_8:
        case KC_9:
        case KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_LEFT_BRACKET:
        case KC_RIGHT_BRACKET:
        case KC_NONUS_HASH:
        case KC_SEMICOLON:
        case KC_GRAVE:
        case FORDEL:
        case OSSHIFT:
        case DELWORD:
        case QUESTION:
        case SLASH:
        case COMMA:
        case PERIOD:
        case LEADPOST:
return true;
    default:
return false; // End Caps Word for other keys
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
combo_t key_combos[] = {};
uint16_t COMBO_LEN = 0;

enum custom_keycodes {
// Moom
    WIN1_1  = SAFE_RANGE,
    WIN1_2,
    WIN1_3,
    WIN2_1,
    WIN2_2,
    WIN2_3,
    WIN2_4,
    WIN2_5,
    WIN2_6,
    WIN2_7,
    WIN3_1,
    WIN3_2,
    WIN3_3,
    WIN3_4,
    WIN3_5,
    WIN3_6,
    WIN3_7,
    WIN4_1,
    WIN4_2,
    WIN4_3,
    WIN4_4,
    WIN5_1,
    WIN5_2,
    WIN5_3,
    WIN5_4,
    WIN6_1,
    WIN6_2,
    WIN6_3,
    WIN6_4,
    WIN6_5,
    WIN7_1,
    WIN7_2,
    WIN8_1,
    WIN8_2,
    WIN8_3,
    WIN8_4,
    WIN8_5,
    WIN8_6,
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Extend Layer
    SHTDWN,
    SLEEP,
    RSTART,
    UNDO,
    COPY,
    CUT,
    PASTE,
    DUPLICA,
    SPOTIFY,
    HAZEDN,     //Encoder::Extend
    HAZEUP,     //Encoder::Extend
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fun Layer
    KMESTRO,
    SYSSET,
    PASS,
    PORTAL,
    SPEED,
    MSG,
    WHATSAPP,
    ELGATO,
    LDECK,
    ITERM,
    SLVPP,
    SLVNEXT,
    SLVPREV,
    SLVVOLU,
    SLVVOLD,
    SLVMUTE,
    SLVLIKE,
    VSCODE,
    WORK,
    TERMIN,
    ZOOMIN,     // Encoder::Fun
    ZOOMOUT,    // Encoder::Fun
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Symbol Layer
    POUND,
    DOLLAR,
    EURO,
    YEN,
    OG,
    LB,
    BB,
    AND,
    BTICK,
    ARROW,
    LARROW,
    AARROW,
    LAARROW,
    SBC,
    SBTD,
    TM,
    PLUS,
    MINUS,
    DONE,
    BRL,
    BRB,
    BRR,
    CBL,
    CBR,
    CBB,
    INF,
    PI,
    PER,
    DPIPE,
    DDOT,
    DSLASH,
    DLB,
    DRB,
    AST,
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Process Record User
// Macro Processing
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_autocorrection(keycode, record)) { return false; }
    if (!process_achordion(keycode, record)) { return false; }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
switch (keycode) {
// Moom Macros
    case WIN1_1:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LCMD);
            tap_code(KC_1);
            unregister_code(KC_LCMD);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN1_2:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LCMD);
            tap_code(KC_2);
            unregister_code(KC_LCMD);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN1_3:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LCMD);
            tap_code(KC_3);
            unregister_code(KC_LCMD);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN2_1:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LCMD);
            tap_code(KC_4);
            unregister_code(KC_LCMD);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
        }
            return false;
    WIN2_2:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LCMD);
            tap_code(KC_5);
            unregister_code(KC_LCMD);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN2_3:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LCMD);
            tap_code(KC_6);
            unregister_code(KC_LCMD);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN2_4:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LCMD);
            tap_code(KC_7);
            unregister_code(KC_LCMD);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN2_5:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LCMD);
            tap_code(KC_8);
            unregister_code(KC_LCMD);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN2_6:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LCMD);
            tap_code(KC_9);
            unregister_code(KC_LCMD);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN2_7:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LCMD);
            tap_code(KC_0);
            unregister_code(KC_LCMD);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN3_1:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LCMD);
            tap_code(KC_1);
            unregister_code(KC_LCMD);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN3_2:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LCMD);
            tap_code(KC_2);
            unregister_code(KC_LCMD);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN3_3:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LCMD);
            tap_code(KC_3);
            unregister_code(KC_LCMD);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN3_4:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LCMD);
            tap_code(KC_4);
            unregister_code(KC_LCMD);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN3_5:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LCMD);
            tap_code(KC_5);
            unregister_code(KC_LCMD);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN3_6:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LCMD);
            tap_code(KC_6);
            unregister_code(KC_LCMD);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN3_7:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LCMD);
            tap_code(KC_7);
            unregister_code(KC_LCMD);
            unregister_code(KC_LALT);
        }
            return false;
     case WIN4_1:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LCMD);
            tap_code(KC_8);
            unregister_code(KC_LCMD);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN4_2:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LCMD);
            tap_code(KC_9);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
        }
            return false;
    case WIN4_3:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LCMD);
            tap_code(KC_0);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN4_4:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LCMD);
            tap_code(KC_1);
            unregister_code(KC_LCMD);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN5_1:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            tap_code(KC_2);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN5_2:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            tap_code(KC_3);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN5_3:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            tap_code(KC_4);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN5_4:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            tap_code(KC_5);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN6_1:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            tap_code(KC_6);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN6_2:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            tap_code(KC_7);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN6_3:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            tap_code(KC_8);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN6_4:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            tap_code(KC_9);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN6_5:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            tap_code(KC_0);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN7_1:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LCMD);
            tap_code(KC_2);
            unregister_code(KC_LCMD);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN7_2:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LCMD);
            tap_code(KC_3);
            unregister_code(KC_LCMD);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN8_1:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
            tap_code(KC_7);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN8_2:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
            tap_code(KC_6);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN8_3:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
            tap_code(KC_5);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN8_4:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
            tap_code(KC_4);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN8_5:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
            tap_code(KC_3);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
            return false;
    case WIN8_6:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
            tap_code(KC_2);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
        return false;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Extend Layer
    case HAZEDN:                                // Encoder::Extend
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
            tap_code(KC_J);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
        return false;
    case HAZEUP:                                // Encoder::Extend
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
            tap_code(KC_G);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
        return false;
    case SHTDWN:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LGUI);
            register_code(KC_LCTL);
            tap_code(KC_1);
            unregister_code(KC_LCTL);
            unregister_code(KC_LGUI);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
        }
        return false;
        case SLEEP:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LGUI);
            register_code(KC_LCTL);
            tap_code(KC_2);
            unregister_code(KC_LCTL);
            unregister_code(KC_LGUI);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
        }
        return false;
    case RSTART:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LGUI);
            register_code(KC_LCTL);
            tap_code(KC_3);
            unregister_code(KC_LCTL);
            unregister_code(KC_LGUI);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
        }
        return false;
    case UNDO:
        if (record->event.pressed) {
            register_code(KC_LCMD);
            tap_code(KC_Z);
            unregister_code(KC_LCMD);
    }
        return false;
    case COPY:
        if (record->event.pressed) {
            register_code(KC_LCMD);
            tap_code(KC_C);
            unregister_code(KC_LCMD);
    }
        return false;
    case PASTE:
        if (record->event.pressed) {
            register_code(KC_LCMD);
            tap_code(KC_V);
            unregister_code(KC_LCMD);
    }
        return false;
    case CUT:
        if (record->event.pressed) {
            register_code(KC_LCMD);
            tap_code(KC_X);
            unregister_code(KC_LCMD);
    }
        return false;
    case DUPLICA:
        if (record->event.pressed) {
            register_code(KC_LCMD);
            tap_code(KC_D);
            unregister_code(KC_LCMD);
    }
        return false;
    case SPOTIFY:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F4)))));
    }
        return false;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fun Layer
    case ZOOMIN:                                // Encoder::Fun
        if (record->event.pressed) {
            register_code(KC_LALT);
            tap_code(MSEWHLDO);
            unregister_code(KC_LALT);
    }
        return false;
    case ZOOMOUT:                                // Encoder::Fun
        if (record->event.pressed) {
            register_code(KC_LALT);
            tap_code(MSEWHLUP);
            unregister_code(KC_LALT);
    }
        return false;
    case KMESTRO:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F1)))));
    }
        return false;
    case SYSSET:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F2)))));
    }
        return false;
    case PASS:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F3)))));
    }
        return false;
    case PORTAL:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F6))))); // Ctrl + Opt + Cmd + F6
    }
        return false;
    case SPEED:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F7))))); // Ctrl + Opt + Cmd + F7
    }
        return false;
    case MSG:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F8))))); // Ctrl + Opt + Cmd + F8
    }
        return false;
    case WHATSAPP:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_PGUP)))));
    }
        return false;
    case ELGATO:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F9)))));
    }
        return false;
    case LDECK:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_L))))); // Ctrl + Opt + Cmd + F10
    }
        return false;
    case ITERM:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LCMD);
            register_code(KC_LSFT);
            tap_code(KC_T);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCMD);
            unregister_code(KC_LCTL);
    }
        return false;
    case SLVPP:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_0))))); // Ctrl + Opt + Cmd + F10
    }
        return false;
    case SLVNEXT:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_TAP(X_0)))); // Ctrl + Opt + Cmd + F10
    }
        return false;
    case SLVPREV:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_9)))); // Ctrl + Opt + Cmd + F10
    }
        return false;
    case SLVVOLU:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_7)))); // Ctrl + Opt + Cmd + F10
    }
        return false;
    case SLVVOLD:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_TAP(X_8))))); // Ctrl + Opt + Cmd + F10
    }
        return false;
    case SLVMUTE:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_TAP(X_6)))); // Ctrl + Opt + Cmd + F10
    }
        return false;
    case SLVLIKE:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LALT(SS_LGUI(SS_TAP(X_0))))); // Ctrl + Opt + Cmd + F10
    }
        return false;
    case VSCODE:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT(SS_LGUI(SS_LSFT(SS_TAP(X_C))))); // Ctrl + Opt + Cmd + F10
    }
        return false;
    case WORK:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LGUI);
            tap_code(KC_DOWN);
            unregister_code(KC_LGUI);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
    }
        return false;
    case TERMIN:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LCTL);
            tap_code(KC_9);
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
    }
        return false;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Symbol Layer
    case POUND:
        if (record->event.pressed) {
            register_code(KC_LALT);
            tap_code(KC_3);
            unregister_code(KC_LALT);
    }
        return false;
    case DOLLAR:
        if (record->event.pressed) {
            SEND_STRING("$");
    }
        return false;
    case EURO:
        if (record->event.pressed) {
            register_code(KC_LALT);
            tap_code(KC_4);
            unregister_code(KC_LALT);
    }
        return false;
    case YEN:
        if (record->event.pressed) {
            register_code(KC_LALT);
            tap_code(KC_Y);
            unregister_code(KC_LALT);
    }
        return false;
    case OG:
        if (record->event.pressed) {
            register_code(KC_LALT);
            tap_code(KC_R);
            unregister_code(KC_LALT);
    }
        return false;
    case TM:
        if (record->event.pressed) {
            register_code(KC_LALT);
            tap_code(KC_2);
            unregister_code(KC_LALT);
    }
        return false;
    case LB:
        if (record->event.pressed) {
            send_string("<");
    }
        return false;
    case BB:
        if (record->event.pressed) {
            send_string("<>");
            tap_code(KC_LEFT);
    }
        return false;
    case AND:
        if (record->event.pressed) {
            send_string("&");
    }
        return false;
    case BTICK:
        if (record->event.pressed) {
            SEND_STRING("`");
    }
        return false;
    case ARROW:
        if (record->event.pressed) {
            send_string("->");
    }
        return false;
    case LARROW:
        if (record->event.pressed) {
            send_string("<-");
    }
        return false;
    case AARROW:
        if (record->event.pressed) {
            send_string("=>");
    }
        return false;
    case LAARROW:
        if (record->event.pressed) {
            send_string("<=");
    }
        return false;
    case SBC:
        if (record->event.pressed) {
            send_string("[]");
            tap_code(KC_LEFT);
    }
        return false;
    case SBTD:
        if (record->event.pressed) {
            send_string("[ ]");
    }
        return false;
    case PLUS:
        if (record->event.pressed) {
            send_string("+");
    }
        return false;
    case MINUS:
        if (record->event.pressed) {
            send_string("-");
    }
        return false;
    case DONE:
        if (record->event.pressed) {
            register_code(KC_LALT);
            tap_code(KC_V);
            unregister_code(KC_LALT);
    }
        return false;
    case BRL:
        if (record->event.pressed) {
            send_string("(");
    }
        return false;
    case BRR:
        if (record->event.pressed) {
            send_string(")");
    }
        return false;
    case BRB:
        if (record->event.pressed) {
            send_string("()");
            tap_code(KC_LEFT);
    }
        return false;
    case CBL:
        if (record->event.pressed) {
            send_string("{");
    }
        return false;
    case CBR:
        if (record->event.pressed) {
            send_string("}");
    }
        return false;
    case CBB:
        if (record->event.pressed) {
            send_string("{}");
            tap_code(KC_LEFT);
    }
        return false;
    case INF:
        if (record->event.pressed) {
            register_code(KC_LALT);
            tap_code(KC_5);
            unregister_code(KC_LALT);
    }
        return false;
    case PI:
        if (record->event.pressed) {
            register_code(KC_LALT);
            tap_code(KC_P);
            unregister_code(KC_LALT);
    }
        return false;
    case PER:
        if (record->event.pressed) {
            register_code(KC_LSFT);
            tap_code(KC_5);
            unregister_code(KC_LSFT);
    }
        return false;
    case DPIPE:
        if (record->event.pressed) {
            send_string("||");
    }
        return false;
    case DDOT:
        if (record->event.pressed) {
            send_string("::");
    }
        return false;
    case DSLASH:
        if (record->event.pressed) {
            send_string("//");
    }
        return false;
    case DLB:
        if (record->event.pressed) {
            send_string("<<");
    }
        return false;
    case DRB:
        if (record->event.pressed) {
            send_string(">>");
    }
        return false;
    case AST:
        if (record->event.pressed) {
            send_string("*");
    }
        return false;

    default:
        return true;
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Housekeeping Tasks
void housekeeping_task_user(void) {
  achordion_task();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tap Dance Array
tap_dance_action_t tap_dance_actions[] = {
    [TD_ALFRED] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_alfred_finished, dance_alfred_reset),
    [TD_HOOK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_hook_finished, dance_hook_reset),
    [TD_CLEANSHOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cleanshot_finished, dance_cleanshot_reset),
    [TD_DROP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_drop_finished, dance_drop_reset),
    [TD_SIDENOTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sidenote_finished, dance_sidenote_reset),
    [TD_ARC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_arc_finished, dance_arc_reset),
    [TD_SNIPLAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sniplab_finished, dance_sniplab_reset),
    [TD_PERP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_perp_finished, dance_perp_reset),
    [TD_CHAT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_chat_finished, dance_chat_reset),
    [TD_MUSE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_muse_finished, dance_muse_reset),
    [TD_TRELLO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_trello_finished, dance_trello_reset),
    [TD_OOUTLINER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_ooutliner_finished, dance_ooutliner_reset),
    [TD_DAYONE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dayone_finished, dance_dayone_reset),
    [TD_FANTASTICAL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_fantastical_finished, dance_fantastical_reset),
    [TD_SPARK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_spark_finished, dance_spark_reset),
    [TD_ANYBOX] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_anybox_finished, dance_anybox_reset),
    [TD_EAGLE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_eagle_finished, dance_eagle_reset),
    [TD_DEVONTHINK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_devonthink_finished, dance_devonthink_reset),
    [TD_FINDER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_finder_finished, dance_finder_reset),
    [TD_BEAR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_bear_finished, dance_bear_reset),
    [TD_OMNIFOCUS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_omnifocus_finished, dance_omnifocus_reset),
    [TD_DRAFTS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_drafts_finished, dance_drafts_reset),
    // Colemak Layer
    [TD_ESCAPE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_escape_finished, dance_escape_reset),
    [TD_TAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_tab_finished, dance_tab_reset),
    [TD_TEXHYPE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_texhype_finished, dance_texhype_reset),
    [TD_UNMEHZ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_unmehz_finished, dance_unmehz_reset),
    [TD_KEYCUE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_keycue_finished, dance_keycue_reset),
    [TD_QMACRO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_qmacro_finished, dance_qmacro_reset),
    [TD_UNIALF] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_unialf_finished, dance_unialf_reset),
    [TD_SPACE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_space_finished, dance_space_reset),
    [TD_CLIP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_clip_finished, dance_clip_reset),
    [TD_FILEFRED] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_filefred_finished, dance_filefred_reset),
    [TD_SCREEN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_screen_finished, dance_screen_reset),
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_caps_finished, dance_caps_reset),
    [TD_ALFMEH2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_alfmeh2_finished, dance_alfmeh2_reset),
    [TD_HASHAT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_hashat_finished, dance_hashat_reset),
    [TD_FORWARDDELETE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_forwarddelete_finished, dance_forwarddelete_reset),
    [TD_SMILE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_smile_finished, dance_smile_reset),
    [TD_SLASH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_slash_finished, dance_slash_reset),
    [TD_QUESTION] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_question_finished, dance_question_reset),
    [TD_QUICKY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_quicky_finished, dance_quicky_reset),
    [TD_PERIOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_period_finished, dance_period_reset),
    [TD_COMMA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_comma_finished, dance_comma_reset),
    [TD_DELWORD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_delword_finished, dance_delword_reset),
    [TD_OSSHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_osshift_finished, dance_osshift_reset),
    [TD_LEADOSTROPHE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_leadostrophe_finished, dance_leadostrophe_reset),
    [TD_USCR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_uscr_finished, dance_uscr_reset),
    [TD_VPASTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_vpaste_finished, dance_vpaste_reset),
    [TD_DDUPLICATE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dduplicate_finished, dance_dduplicate_reset),
    [TD_COPY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_copy_finished, dance_copy_reset),
    [TD_XCUT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_xcut_finished, dance_xcut_reset),
    [TD_QSELALL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_qselall_finished, dance_qselall_reset),
    [TD_ONE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_one_finished, dance_one_reset),
    [TD_TWO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_two_finished, dance_two_reset),
    [TD_THREE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_three_finished, dance_three_reset),
    // Extend Layer
    [TD_TIL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_til_finished, dance_til_reset),
    // Windows Layer
    [TD_FULL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_full_finished, dance_full_reset),
    // Fun Layer
    [TD_PORT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_port_finished, dance_port_reset),
    [TD_CLARITY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_clarity_finished, dance_clarity_reset),
    [TD_SLEEVE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sleeve_finished, dance_sleeve_reset),
    // Symbol Layer
    [TD_EQUALS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_equals_finished, dance_equals_reset),
    [TD_STAR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_star_finished, dance_star_reset),
    [TD_RB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_rb_finished, dance_rb_reset),
    [TD_SBL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sbl_finished, dance_sbl_reset),
    [TD_SBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sbr_finished, dance_sbr_reset),
    [TD_BACKT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_backt_finished, dance_backt_reset),
    [TD_UNSC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_unsc_finished, dance_unsc_reset),
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Leader key
void leader_start_user(void) {
}
void leader_end_user(void) {
    if (leader_sequence_one_key(KC_F)) {
        // Leader, f => Types the below string
        SEND_STRING("QMK is awesome.");
    } else if (leader_sequence_three_keys(KC_D, KC_D, KC_S)) {
        // Leader, d, d, s => Types the below string
        SEND_STRING("https://start.duckduckgo.com\n");
       // Codes
    } else if (leader_sequence_one_key(KC_P)) {
        // Leader, p => Types the below string
        SEND_STRING("gReatestEver9000\n");
    } else if (leader_sequence_two_keys(KC_P, KC_P)) {
        // Leader, p => Types the below string
        SEND_STRING("IruletheChaos9000\n");
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RGB Effects
#include "quantum.h"

// Define custom flags for specific keys
#define LED_FLAG_F  0x02  // F key
#define LED_FLAG_U  0x04  // U key
#define LED_FLAG_N  0x08  // N key
#define LED_FLAG_W  0x10  // W key
#define LED_FLAG_I  0x20  // I key

void keyboard_post_init_user(void) {
    // Enable RGB Matrix
    rgb_matrix_enable();

    // Set the default effect to Starlight
    rgb_matrix_mode(RGB_MATRIX_STARLIGHT);
    rgb_matrix_sethsv(11, 176, 255);
    eeconfig_update_rgb_matrix(); // Ensure it persists across power cycles
}

// Track the current mode
uint8_t current_mode = RGB_MATRIX_NONE;

// Set the layer effect only when mode changes
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);
    uint8_t default_layer = get_highest_layer(default_layer_state);
    uint8_t new_mode = current_mode;  // Keep previous mode by default

    // Handle active layers
    switch (layer) {
        case EXTEND:
            new_mode = RGB_MATRIX_DIGITAL_RAIN;  // Set effect for Extend
            break;

        default:
            // Return to the default layer RGB effect
            switch (default_layer) {
                case CMAK_BASE:
                    new_mode = RGB_MATRIX_STARLIGHT;  // Typing heatmap for Colemak
                    break;
                case MAC_BASE:
                    new_mode = RGB_MATRIX_STARLIGHT;
                    rgb_matrix_sethsv(128, 255, 128);
                    break;
                default:
                    break;
            }
            break;
    }

    // Apply the new mode if it has changed
    if (new_mode != current_mode) {
        current_mode = new_mode;
        rgb_matrix_mode_noeeprom(new_mode);
    }

    return state;
}

// Handle default layer changes dynamically
layer_state_t default_layer_state_set_user(layer_state_t state) {
    uint8_t default_layer = get_highest_layer(state);

    // Update RGB effects or colors based on default layer
    switch (default_layer) {
        case CMAK_BASE:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_STARLIGHT);
            break;
        case MAC_BASE:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_STARLIGHT);
            rgb_matrix_sethsv(132, 102, 180);
            break;
        default:
            break;
    }

    return state;
}

// Advanced user function for per-key RGB lighting
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    uint8_t default_layer = get_highest_layer(default_layer_state);

    // Force MAC_BASE to use its color
    if (default_layer == MAC_BASE) {
        //rgb_matrix_sethsv(132, 102, 255);  // 🔹 Explicitly reapply color
    }

    for (uint8_t i = led_min; i < led_max; i++) {
          // SYMBOL Layer: Only S, Y, M should light up
          if (layer == FUN) {
            rgb_matrix_set_color(36, RGB_RED); // Light up 'S'
            rgb_matrix_set_color(42, RGB_RED); // Light up 'Y'
            rgb_matrix_set_color(58, RGB_RED); // Light up 'M'
        }
        // WINDOWS Layer: Only W, I, N should light up
        if (layer == WINDOWS) {
            rgb_matrix_set_color(35, RGB_CYAN); // Light up 'S'
            rgb_matrix_set_color(60, RGB_CYAN); // Light up 'Y'
            rgb_matrix_set_color(58, RGB_CYAN); // Light up 'M'
        }
          // SYMBOL Layer: Only S, Y, M should light up
            if (layer == SYM) {
                rgb_matrix_set_color(53, RGB_GOLDENROD); // Light up 'S'
                rgb_matrix_set_color(43, RGB_GOLDENROD); // Light up 'Y'
                rgb_matrix_set_color(57, RGB_GOLDENROD); // Light up 'M'
            }
          // SYMBOL Layer: Only S, Y, M should light up
          if (layer == PIC) {
            rgb_matrix_set_color(37, RGB_RED); // Light up 'S'
            rgb_matrix_set_color(60, RGB_RED); // Light up 'Y'
            rgb_matrix_set_color(65, RGB_RED); // Light up 'M'
        }
        // CAPS LOCK Blinking
        if (i == CAPS_LED && is_caps_word_on()) {
            if (timer_elapsed32(caps_blink_timer) > 500) {
                caps_blink_timer = timer_read32();
                rgb_matrix_set_color(i, RGB_RED);
            }
        }
    }

    return false;  // Allow other matrix effects to run
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Keymap Layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_tkl_ansi(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    KC_MUTE,    KC_SNAP,  KC_SIRI,  RGB_MOD,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,    KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,    KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,              KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD, KC_ROPTN, MO(MAC_FN), KC_RCTL,    KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_tkl_ansi(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,              XXXXXXX,
        XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,              XXXXXXX,              XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX),

    [CMAK_BASE] = LAYOUT_tkl_ansi(
        ALFRED,   HOOK,     CLEANSHT, DROP,     SIDENOTE, ARC,      SNIP,     PERP,     CHAT,     MUSE,     TRELLO,   OOUT,     DAYONE,     KC_MUTE,    FANTAS,   SPARK,    ANYBOX,
        ESCAPE,   ONE,      TWO,      THREE,    KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  SMILE,      FORDEL,     EAGLE,    DEVON,    FINDER,
        TAB,      QSELALL,  KC_W,     KC_F,     KC_P,     KC_B,     USCR,     KC_J,     KC_L,     KC_U,     QUICKY,   QUESTION, SLASH,      HASHAT,     BEAR,     OFOCUS,   DRAFTS,
        TEXHYPE,  HOME_A,   HOME_R,   HOME_S,   HOME_T,   KC_G,     LEADPOST, KC_M,     HOME_N,   HOME_E,   HOME_I,   HOME_O,               ALFMEH2,
        UNMEHZ,             XCUT,     CCOPY,    DDUP,     VPASTE,   OSSHIFT,  DELWORD,  KC_K,     KC_H,     COMMA,    PERIOD,               CAPW,                KC_UP,
        KEYCUE,   QMACRO,   UNIALF,                                     SPACE,                              CLIP,     FILEFRED, KC_LALT,    SCREEN,    KC_LEFT,  KC_DOWN,  KC_RGHT),

    [EXTEND] = LAYOUT_tkl_ansi(
        SHTDWN,   SLEEP,    RSTART,   MCNTRL,   LNCHPAD,  _______,  _______,  _______,  _______,  REWIND,   PLAY,     NEXT,     SPOTIFY,    RGB_TOG,    RGB_RMOD, RGB_MOD,  BAT_LVL,
        TIL,      KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     RGB_SPI,    RGB_VAI,  RGB_HUI,  RGB_SAI,
        TEXHYPE,  MSEC1,    MSEWHLRI, MSEWHLDO, MSEWHLLE, _______,  MOUSEUP,  _______,  HOME,     KC_UP,    MOUSEUP,  _______,  _______,    RGB_SPD,    RGB_VAD,  RGB_HUD,  RGB_SAD,
        KC_LCTL,  KC_LALT,  KC_LGUI,  MSEWHLUP, KC_LSFT,  MOUSELT,  MOUSEDN,  MOUSERT,  KC_LEFT,  KC_DOWN,  KC_RGHT,  MSEC1,                _______,
        UNDO,               CUT,      COPY,     DUPLICA,  PASTE,    MSEC1,    MSEC4,    MSEC2,    MOUSELT,  MOUSERT,  MOUSEDN,              _______,              _______,
        KEYCUE,   QMACRO,   UNIALF,                                 _______,                                CLIP,     FILEFRED,  KC_LALT,   SCREEN,    _______,  _______,  _______),

    [WINDOWS] = LAYOUT_tkl_ansi(
        FULL,     WIN1_1,   WIN1_2,   WIN1_3,   XXXXXXX,  WIN4_1,   WIN4_2,   WIN4_3,   WIN4_4,   WIN5_1,   WIN5_2,   WIN5_3,   WIN5_4,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        _______,  WIN2_1,   WIN2_2,   WIN2_3,   WIN2_4,   WIN2_5,   WIN2_6,   WIN2_7,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        _______,  WIN3_1,   WIN3_2,   WIN3_3,   WIN3_4,   WIN3_5,   WIN3_6,   WIN3_7,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        WIN8_2,   WIN6_1,   WIN6_2,   WIN6_3,   WIN6_4,   WIN6_5,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,              XXXXXXX,
        WIN8_1,             WIN8_6,   WIN8_5,   WIN8_4,   WIN8_3,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,              XXXXXXX,              XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX),

    [FUN] = LAYOUT_tkl_ansi(
        SYSSET,   PASS,     PORT,     MSG,      WHATSAPP, ELGATO,   LDECK,    _______,  CLARITY,  SLVPREV,  SLVPP,    SLVNEXT,  SLEEVE,     SLVMUTE,    SLVLIKE,  _______,  SPEED,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    TERMIN,   ITERM,    WORK,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    KMESTRO,  VSCODE,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,              _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    _______,  _______,  _______),

    [SYM] = LAYOUT_tkl_ansi(
        XXXXXXX,  POUND,    DOLLAR,   EURO,     YEN,      OG,       TM,       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        TIL,      LB,       RB,       BB,       DLB,      BRB,      XXXXXXX,  XXXXXXX,  XXXXXXX,  LAARROW,  LARROW,   ARROW,    AARROW,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        DPIPE,    SBL,      SBR,      SBC,      SBTD,     TROSA,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  PLUS,     EQUALS,   STAR,       XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        DDOT,     BRL,      BRR,      BRB,      DONE,     INF,      PI,       PER,      XXXXXXX,  XXXXXXX,  MINUS,    UNSC,                 XXXXXXX,
        DSLASH,             CBL,      CBR,      CBB,      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  AND,                  XXXXXXX,              XXXXXXX,
        BACKT,    XXXXXXX,  XXXXXXX,                                XXXXXXX,                                AST,      XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX),

    [PIC] = LAYOUT_tkl_ansi(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,              XXXXXXX,
        XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,              XXXXXXX,              XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX),

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Encoder Map
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [CMAK_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [EXTEND]   = {ENCODER_CCW_CW(HAZEDN, HAZEUP)},
    [WINDOWS] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [FUN] = {ENCODER_CCW_CW(SLVVOLD, SLVVOLU)},
    [SYM] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [PIC] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
 };
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Auto Shift Definitions
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    // Handle Home Row Mods and Tap Dances for Auto Shift
    switch (keycode) {
        // Home Row Mods (Enable Auto Shift for single-tap behavior):
       // QWERTY Layout
        case LALT_T(KC_S):
        case LGUI_T(KC_D):
        case LSFT_T(KC_F):
        case RSFT_T(KC_J):
        case RGUI_T(KC_K):
        case LALT_T(KC_L):
        case RCTL_T(KC_SCLN):
        // COLEMAK Home Row Mods
        case LCTL_T(KC_A):
        case LALT_T(KC_R):
        case LGUI_T(KC_S):
        case LSFT_T(KC_T):
        case LSFT_T(KC_N):
        case RGUI_T(KC_E):
        case LALT_T(KC_I):
        case RCTL_T(KC_O):
        case LSFT_T(KC_Z):
            return true; // Allow Auto Shift for home row mods when tapped

        default:
            return false; // Auto Shift disabled for all other keys
    }
}
