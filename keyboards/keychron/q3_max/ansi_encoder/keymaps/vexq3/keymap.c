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
#include "unicode.h"
#include "features/autocorrection.h"
#include "features/repeat_key.h"
#include "features/sentence_case.h"
#include "features/achordion.h"
#include "features/select_word.h"
#include "features/select_word_back.h"

enum layers {
    MAC_BASE,    // Layer 0 - Base Layer
    MAC_FN,      // Layer 1 - Function Layer
    CMAK_BASE,   // Layer 2 - Colemak Base Layer
    EXTEND,      // Layer 3 - Extend Layer
    WINDOWS,     // Layer 4 - Windows Layer
    FUN,         // Layer 5 - Function Layer
    SYM,         // Layer 6 - Symbol Layer
    PIC,         // Layer 7 - Picto Layer
   ///  ADM,         // Layer 7 - Admin Layer
};

// Tap Dance Declarations
enum {
    TD_F15_ANYBOX,
    TD_PD_DRAFTS,
    TD_END_OMNIFOCUS,
    TD_PERIOD,
    TD_BRACKET,
    TD_QUESTION,
    TD_SLASH,
    TD_TILDE,
    TD_CAPS,
    TD_SPACE,
    TD_COMMA,
    TD_COMSH,
    TD_LEAD,
    TD_DEL,
    TD_DELFOR,
    TD_BSPACE,
    TD_ALFYHYPY,
    TD_CODE,
    TD_SELBC,
    TD_SELFC,
    TD_SLASH9,
    TD_BSLASH0,
    TD_FINDER,
    TD_DEVONTHINK,
    TD_SPARK,
    TD_FANTASTICAL,
    TD_DAYONE,
    TD_TRELLO,
    TD_OOUTLINER,
    TD_XMIND,
    TD_MUSE,
    TD_HOOK,
    TD_ALFRED,
    TD_DROP,
    TD_SNIP,
    TD_TEXTE,
    TD_PERP,
    TD_CHAT,
    TD_ARC,
    TD_OBSIDIAN,
    TD_EAGLE,
    TD_TEXTC,
    TD_CSPC_P,
    TD_CSPC_N,
    TD_CAPP_P,
    TD_CAPP_N,
    TD_CMOVE_N,
    TD_CMOVE_P,
    TD_SLEEVE,
    TD_CLEANSHOT,
    TD_APOSTROPHE,
    TD_BRACKET_L,
    TD_BRACKET_R,
    TD_ADM,
    TD_LEADY,
    TD_UNDERSCORE,
    REPEAT,
    TD_Z,
    TD_SYMPIC,
    TD_TIL,
    TD_RB,
    TD_SBL,
    TD_SBR,
    TD_USCR,
    TD_STAR,
    TD_BACKT,
    TD_EQUALS,
    TD_UNSC,
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

// Definitons

    #define PERIOD   TD(TD_PERIOD)
    #define BRACKET  TD(TD_BRACKET)
    #define QUESTION TD(TD_QUESTION)
    #define SLASH    TD(TD_SLASH)
    #define TILDE    TD(TD_TILDE)
    #define CAPW     TD(TD_CAPS)
    #define SPACE    TD(TD_SPACE)
    #define COMMA    TD(TD_COMMA)
    #define DELF     TD(TD_DELFOR)
    #define BSPACE   TD(TD_BSPACE)
    //#define LEADER   QK_LEAD
    #define ALFYHYPY TD(TD_ALFYHYPY)
    #define CODE     TD(TD_CODE)
    #define SELBC    TD(TD_SELBC)
    #define SELFC    TD(TD_SELFC)
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
    //#define PAGE_UP  KC_PAGE_UP
    //#define PAGE_DN  KC_PAGE_DOWN
    //#define HOME     KC_HOME
    //#define END      KC_END
    #define PLAY     KC_MEDIA_PLAY_PAUSE
    #define REWIND   KC_MEDIA_PREV_TRACK
    #define NEXT     KC_MEDIA_FAST_FORWARD
    #define MCNTRL   KC_MISSION_CONTROL
    #define LNCHPAD  KC_LAUNCHPAD
    //#define SLEEP    KC_SYSTEM_SLEEP
    //#define WAKE     KC_SYSTEM_WAKE
    #define POWER    KC_SYSTEM_POWER
    #define BBACK    KC_WWW_BACK
    #define BFORW    KC_WWW_FORWARD
    #define SLASH9   TD(TD_SLASH9)
    #define BSLASH0  TD(TD_BSLASH0)
    #define TEXTC    TD(TD_TEXTC)
    #define CSPACEP  TD(TD_CSPC_P)
    #define CSPACEN  TD(TD_CSPC_N)
    #define CAPP_N   TD(TD_CAPP_N)
    #define CAPP_P   TD(TD_CAPP_P)
    #define CMOVE_N  TD(TD_CMOVE_N)
    #define CMOVE_P  TD(TD_CMOVE_P)
    #define SLEEVE   TD(TD_SLEEVE)
    #define APOST    TD(TD_APOSTROPHE)
    #define TDOSS    TD(TD_BRACKET_L)
    #define TDDELW   TD(TD_BRACKET_R)
    #define ADM      TD(TD_ADM)
    #define LEADY    TD(TD_LEADY)
    #define RB       TD(TD_RB)

// QWERTY Layout
// Left-hand home row mods
    #define CTL_A LCTL_T(KC_A)
    #define ALT_S LALT_T(KC_S)
    #define GUI_D LGUI_T(KC_D)
    #define SFT_F LSFT_T(KC_F)
// Right-hand home row mods
    #define SFT_J RSFT_T(KC_J)
    #define GUI_K RGUI_T(KC_K)
    #define ALT_L LALT_T(KC_L)
    #define CTL_SCLN RCTL_T(KC_SCLN)

        #define SHIFTZ MT(MOD_LSFT, KC_Z)

// F keys
    #define ANYBOX    TD(TD_F15_ANYBOX)
    #define DRAFTS    TD(TD_PD_DRAFTS)
    #define OFOCUS    TD(TD_END_OMNIFOCUS)
    #define FINDER    TD(TD_FINDER)
    #define DEVON     TD(TD_DEVONTHINK)
    #define SPARK     TD(TD_SPARK)
    #define FANTAS    TD(TD_FANTASTICAL)
    #define DAYONE    TD(TD_DAYONE)
    #define TRELLO    TD(TD_TRELLO)
    #define OOUT      TD(TD_OOUTLINER)
    #define XMIND     TD(TD_XMIND)
    #define MUSE      TD(TD_MUSE)
    #define HOOK      TD(TD_HOOK)
    #define ALFRED    TD(TD_ALFRED)
    #define DROP      TD(TD_DROP)
    #define SNIP      TD(TD_SNIP)
    #define TEXTE     TD(TD_TEXTE)
    #define PERP      TD(TD_PERP)
    #define CHAT      TD(TD_CHAT)
    #define ARC       TD(TD_ARC)
    #define OBSIDIAN  TD(TD_OBSIDIAN)
    #define EAGLE     TD(TD_EAGLE)
    #define CLEANSHT  TD(TD_CLEANSHOT)
    #define UNDSCR    TD(TD_UNDERSCORE)
    #define ZED       TD(TD_Z)
    #define SYMPIC    TD(TD_SYMPIC)
    #define TIL       TD(TD_TIL)
    #define SBL       TD(TD_SBL)
    #define SBR       TD(TD_SBR)
    #define USCR      TD(TD_USCR)
    #define STAR      TD(TD_STAR)
    #define BACKT     TD(TD_BACKT)
    #define EQUALS    TD(TD_EQUALS)
    #define UNSC      TD(TD_UNSC)

    // Leds
    static bool is_caps_active_flag = false;  // Tracks Caps Word state
    static uint32_t caps_blink_timer = 0;    // Timer for CAPS blinking

    #define CAPS_LED 74  // Set this to the correct LED index for your CAPS key

    // Anybox
    void dance_f15_anybox_finished(tap_dance_state_t *state, void *user_data) {
    // Determine the number of taps or holds
    if (state->count == 1 && state->pressed) {
        // Single hold: Shift + Home
        register_code(KC_LSFT);
        tap_code(KC_F15);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        // Single tap: Option + Command + Shift + Home
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F15);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        // Double hold: Ctrl + Home
        register_code(KC_LCTL);
        register_code(KC_LGUI);
        tap_code(KC_F15);
        register_code(KC_LGUI);
        register_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: Alt + Home
        register_code(KC_LALT);
        tap_code(KC_F15);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        // Triple hold: Ctrl + Alt + Home
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F15);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        // Triple tap: Shift + Ctrl + Home
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F15);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        // Quad hold: Alt + Shift + Home
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F15);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        // Quad tap: Ctrl + Alt + Shift + Home
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F15);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}

void dance_f15_anybox_reset(tap_dance_state_t *state, void *user_data) {
    // Reset logic if needed
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}

    // CleanShot
    void dance_cleanshot_finished(tap_dance_state_t *state, void *user_data) {
    // Determine the number of taps or holds
    if (state->count == 1 && state->pressed) {
        // Single hold: Shift + Home
        register_code(KC_LSFT);
        tap_code(KC_F1);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        // Single tap: Option + Command + Shift + Home
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F1);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        // Double hold: Ctrl + Home
        register_code(KC_LCTL);
        register_code(KC_LGUI);
        tap_code(KC_F1);
        register_code(KC_LGUI);
        register_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: Alt + Home
        register_code(KC_LALT);
        register_code(KC_LGUI);
        tap_code(KC_F1);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        // Triple hold: Ctrl + Alt + Home
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F1);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        // Triple tap: Shift + Ctrl + Home
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F1);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        // Quad hold: Alt + Shift + Home
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F1);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        // Quad tap: Ctrl + Alt + Shift + Home
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
    // Reset logic if needed
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }

// Obsidian
void dance_eagle_finished(tap_dance_state_t *state, void *user_data) {
    // Determine the number of taps or holds
    if (state->count == 1 && state->pressed) {
        // Single hold: Shift + Home
        register_code(KC_LSFT);
        tap_code(KC_INS);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        // Single tap: Option + Command + Shift + Home
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_INS);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        // Double hold: Ctrl + Home
        register_code(KC_LCTL);
        tap_code(KC_INS);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: Alt + Home
        register_code(KC_LALT);
        tap_code(KC_INS);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        // Triple hold: Ctrl + Alt + Home
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_INS);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        // Triple tap: Shift + Ctrl + Home
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_INS);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        // Quad hold: Alt + Shift + Home
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_INS);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        // Quad tap: Ctrl + Alt + Shift + Home
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
    // Reset logic if needed
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}

// Anybox
void dance_obsidian_finished(tap_dance_state_t *state, void *user_data) {
    // Determine the number of taps or holds
    if (state->count == 1 && state->pressed) {
        // Single hold: Shift + Home
        register_code(KC_LSFT);
        tap_code(KC_DEL);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        // Single tap: Option + Command + Shift + Home
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_DEL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        // Double hold: Ctrl + Home
        register_code(KC_LCTL);
        tap_code(KC_DEL);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: Alt + Home
        register_code(KC_LALT);
        tap_code(KC_DEL);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        // Triple hold: Ctrl + Alt + Home
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_DEL);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        // Triple tap: Shift + Ctrl + Home
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_DEL);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        // Quad hold: Alt + Shift + Home
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_DEL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        // Quad tap: Ctrl + Alt + Shift + Home
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_DEL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}

void dance_obsidian_reset(tap_dance_state_t *state, void *user_data) {
    // Reset logic if needed
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
// Tap Dance Actions for Page Down (PD) - Drafts
void dance_pd_drafts_finished(tap_dance_state_t *state, void *user_data) {
    // Determine the number of taps or holds
    if (state->count == 1 && state->pressed) {
        // Single hold: Shift + Home
        register_code(KC_LSFT);
        tap_code(KC_PGDN);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        // Single tap: Option + Command + Shift + Home
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_PGDN);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        // Double hold: Ctrl + Home
        register_code(KC_LCTL);
        tap_code(KC_PGDN);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: Alt + Home
        register_code(KC_LALT);
        tap_code(KC_PGDN);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        // Triple hold: Ctrl + Alt + Home
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_PGDN);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        // Triple tap: Shift + Ctrl + Home
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_PGDN);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        // Quad hold: Alt + Shift + Home
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_PGDN);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        // Quad tap: Ctrl + Alt + Shift + Home
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_PGDN);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}

void dance_pd_drafts_reset(tap_dance_state_t *state, void *user_data) {
    // Reset logic if needed
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}

// Tap Action for End - OmniFocus
void dance_end_omnifocus_finished(tap_dance_state_t *state, void *user_data) {
    // Determine the number of taps or holds
    if (state->count == 1 && state->pressed) {
        // Single hold: Shift + Home
        register_code(KC_LSFT);
        tap_code(KC_END);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        // Single tap: Option + Command + Shift + Home
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_END);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        // Double hold: Ctrl + Home
        register_code(KC_LCTL);
        tap_code(KC_END);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: Alt + Home
        register_code(KC_LALT);
        tap_code(KC_END);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        // Triple hold: Ctrl + Alt + Home
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_END);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        // Triple tap: Shift + Ctrl + Home
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_END);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        // Quad hold: Alt + Shift + Home
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_END);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        // Quad tap: Ctrl + Alt + Shift + Home
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_END);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}

void dance_end_omnifocus_reset(tap_dance_state_t *state, void *user_data) {
    // Reset logic if needed
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}

// Tap dance for Finder
void dance_finder_finished(tap_dance_state_t *state, void *user_data) {
    // Determine the number of taps or holds
    if (state->count == 1 && state->pressed) {
        // Single hold: Shift + F1
        register_code(KC_LSFT);
        tap_code(KC_PGUP);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        // Single tap: F1
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_PGUP);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        // Double hold: Ctrl + F1
        register_code(KC_LCTL);
        tap_code(KC_PGUP);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: Alt + F1
        register_code(KC_LALT);
        tap_code(KC_PGUP);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        // Triple hold: Ctrl + Alt + F1
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_PGUP);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        // Triple tap: Shift + Ctrl + F1
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_PGUP);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        // Quad hold: Alt + Shift + F1
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_PGUP);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        // Quad tap: Ctrl + Alt + Shift + F1
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
    // Reset logic if needed
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}

// Devonthink
void dance_devonthink_finished(tap_dance_state_t *state, void *user_data) {
    // Determine the number of taps or holds
    if (state->count == 1 && state->pressed) {
        // Single hold: Shift + Home
        register_code(KC_LSFT);
        tap_code(KC_HOME);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        // Single tap: Option + Command + Shift + Home
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_HOME);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        // Double hold: Ctrl + Home
        register_code(KC_LCTL);
        tap_code(KC_HOME);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: Alt + Home
        register_code(KC_LALT);
        tap_code(KC_HOME);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        // Triple hold: Ctrl + Alt + Home
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_HOME);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        // Triple tap: Shift + Ctrl + Home
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_HOME);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        // Quad hold: Alt + Shift + Home
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_HOME);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        // Quad tap: Ctrl + Alt + Shift + Home
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
    // Reset logic if needed
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}

// Spark
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

// Fantastical
void dance_fantastical_finished(tap_dance_state_t *state, void *user_data) {
    // Replace KC_F14 with KC_F13
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

// Dayone
void dance_dayone_finished(tap_dance_state_t *state, void *user_data) {
    // Replace KC_F14 with KC_F13
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

// Trello
void dance_trello_finished(tap_dance_state_t *state, void *user_data) {
    // Replace KC_F14 with KC_F13
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

// Ooutliner
void dance_ooutliner_finished(tap_dance_state_t *state, void *user_data) {
    // Replace KC_F14 with KC_F13
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

// Xmind
void dance_xmind_finished(tap_dance_state_t *state, void *user_data) {
    // Replace KC_F14 with KC_F13
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F9);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F9);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F9);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F9);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F9);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F9);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F9);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F9);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}

void dance_xmind_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}

// Muse
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

// Hook
void dance_hook_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F7);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LCTL); // Press Shift
        tap_code(KC_H);      // Backslash with Shift = Pipe
        unregister_code(KC_LCTL); // Release Shift
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LGUI);
        tap_code(KC_H);
        register_code(KC_LGUI);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_H);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_H);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_H);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        // Step 1: Control + H (Invoke Hookmark)
        register_code(KC_LCTL);
        tap_code(KC_H);
        unregister_code(KC_LCTL);

        // Step 2: Wait 500ms (0.5s)
        wait_ms(500);

        // Step 3: Control + M (Open Action Menu)
        register_code(KC_LCTL);
        tap_code(KC_M);
        unregister_code(KC_LCTL);

        // Step 4: Wait 500ms (0.5s)
        wait_ms(500);

        // Step 5: Control + Q (Execute Action)
        register_code(KC_LCTL);
        tap_code(KC_C);
        unregister_code(KC_LCTL);
    } else if (state->count == 4 && !state->pressed) {
        // Step 1: Control + H (Invoke Hookmark)
        register_code(KC_LCTL);
        tap_code(KC_H);
        unregister_code(KC_LCTL);

        // Step 2: Wait 500ms (0.5s)
        wait_ms(500);

        // Step 3: Control + M (Open Action Menu)
        register_code(KC_LCTL);
        tap_code(KC_M);
        unregister_code(KC_LCTL);

        // Step 4: Wait 500ms (0.5s)
        wait_ms(500);

        // Step 5: Control + Q (Execute Action)
        register_code(KC_LCTL);
        tap_code(KC_Q);
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

// Alfred
void dance_alfred_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F3);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        tap_code(KC_F3);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F3);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        tap_code(KC_F3);
         wait_ms(500);
        tap_code(KC_SPC);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F3);
        register_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LGUI);
        tap_code(KC_F3);
        unregister_code(KC_LGUI);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F3);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F3);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
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

// Drop
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

// Snip
void dance_snip_finished(tap_dance_state_t *state, void *user_data) {
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

void dance_snip_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}

// Textexpander
void dance_texte_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F19);
        unregister_code(KC_LSFT);
    } else if (state->count == 1 && !state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_F19);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        register_code(KC_LCTL);
        tap_code(KC_F19);
        unregister_code(KC_LCTL);
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F19);
        unregister_code(KC_LALT);
    } else if (state->count == 3 && state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_F19);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    } else if (state->count == 3 && !state->pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_F19);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    } else if (state->count == 4 && state->pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F19);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 4 && !state->pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_F19);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}

void dance_texte_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}

// Perp
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

// Chat
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

// Arc
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

// Tap Dance Actions for Period
void dance_period_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: . Space Capitalization
        SEND_STRING(". ");
        set_oneshot_mods(MOD_LSFT);  // Activate One-Shot Shift
    }else if (state->count == 1 && state->pressed) {
            // Single tap: . Space Capitalization
            SEND_STRING(".");
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: : Space Capitalization
        SEND_STRING(": ");
        set_oneshot_mods(MOD_LSFT);  // Activate One-Shot Shift
    }
}

void dance_period_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        clear_oneshot_mods();  // Clear One Shot Shift if hold is used
    }
}

// Tap Dance Actions for Question/Exclamation
void dance_question_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: ? followed by Space Capitalization
        SEND_STRING("? ");
        set_oneshot_mods(MOD_LSFT);  // Activate One-Shot Shift
    } else if (state->count == 1 && state->pressed) {
            // Single tap: ? followed by Space Capitalization
            SEND_STRING("!");
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: ! followed by Space Capitalization
        SEND_STRING("! ");
        set_oneshot_mods(MOD_LSFT);  // Activate One-Shot Shift
    }
}

void dance_question_reset(tap_dance_state_t *state, void *user_data) {
    // No need to clear the one-shot mods manually; timeout will handle it
    if (state->pressed) {
        clear_oneshot_mods();  // Clear One-Shot Shift if hold was used
    }
}

// Tap Dance Actions for Slash, Backslash, and Pipe
void dance_slash_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: /
        tap_code(KC_SLSH);
    } else if (state->count == 2 && !state->pressed) {
        // Double tap:
        tap_code(KC_BSLS);
    } else if (state->pressed) {
        // Hold: |
        register_code(KC_LSFT); // Press Shift
        tap_code(KC_BSLS);      // Backslash with Shift = Pipe
        unregister_code(KC_LSFT); // Release Shift
    }
}

// Optional: Reset Function
void dance_slash_reset(tap_dance_state_t *state, void *user_data) {
    // Add logic if needed for reset behavior
}

// Tap Dance Actions for Tilde
void dance_tilde_finished(tap_dance_state_t *state, void *user_data) {
    td_state_t dance_state = cur_dance(state);  // Use the tap dance state function

    switch (dance_state) {
        case TD_SINGLE_TAP:
            // Single tap sends 'Esc'
            tap_code(KC_ESC);
            break;

        case TD_DOUBLE_TAP:
            // Double tap sends '`' (Backtick)
            tap_code(KC_GRV);
            break;

        default:
            break;
    }
}

void dance_tilde_reset(tap_dance_state_t *state, void *user_data) {
    // Turn off MO(FUN) when the key is released
    layer_off(FUN);
}

// Tap dance function to activate/deactivate CAPS Word
void dance_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {  // Single tap activates CAPS Word
        caps_word_on();                         // Turn on CAPS Word
        is_caps_active_flag = true;             // Set flag for CAPS active
        caps_blink_timer = timer_read32();      // Initialize blinking timer
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: Sends '"'
        SEND_STRING(")");
    } else if (state->pressed) {                // Press and hold activates Shift
        register_code(KC_LSFT);
    }
}

void dance_caps_reset(tap_dance_state_t *state, void *user_data) {
    is_caps_active_flag = false;  // Directly reset CAPS blinking flag
    unregister_code(KC_LSFT);     // Release Shift key if pressed
}

// Tap Dance Functions for Space/Enter/Extend
void dance_space_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single Tap: Send Space
        tap_code(KC_SPC);
    } else if (state->count == 1 && state->pressed) {
        // Hold: Activate MO(EXTEND)
        layer_on(EXTEND);
    } else if (state->count == 2 && !state->pressed) {
        // Double Tap: Send Enter
        tap_code(KC_ENT);
    } else if (state->count == 2 && state->pressed) {
        // Hold: Activate MO(EXTEND)
        register_code(KC_LSFT);  // Hold Option
        tap_code(KC_ENT); // Fonard Delete
        unregister_code(KC_LSFT); // Release Conmand
    }
}

void dance_space_reset(tap_dance_state_t *state, void *user_data) {
        // Release MO(EXTEND) when key is released
        layer_off(EXTEND);
}

// Tap Dance Actions for Comma
void dance_comma_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: , followed by Space
        SEND_STRING(", ");
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: '
        SEND_STRING("; ");
    }
}

void dance_comma_reset(tap_dance_state_t *state, void *user_data) {
    // No additional reset logic needed
}

// Tap Dance Actions for Comma
void dance_apostrophe_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: , followed by Space
        SEND_STRING("'");
    } else if (state->count == 1 && state->pressed) {
            // Single tap: , followed by Space
            SEND_STRING(",");
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: '
        SEND_STRING("\"\"");
        tap_code(KC_LEFT); // Move cursor between the double quotes
    }
}

void dance_apostrophe_reset(tap_dance_state_t *state, void *user_data) {
    // No additional reset logic needed
}

// Tap Dance Actions for Bracket
void dance_bracket_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Inserts < > with the cursor between
        SEND_STRING("()");
        tap_code(KC_LEFT);
    } else if (state->count == 1 && state->pressed) {
        // Hold: Inserts { } with the cursor between
        SEND_STRING("[[]]");
        tap_code(KC_LEFT);
        tap_code(KC_LEFT);
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: '
        SEND_STRING("[]");
        tap_code(KC_LEFT);
    }
}

void dance_bracket_reset(tap_dance_state_t *state, void *user_data) {
    // No reset logic needed
}

// Tap Dance Actions for Bracket
void dance_bracketr_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Activate One Shot Shift
        register_code(KC_LALT);  // Hold Option
        tap_code(KC_BSPC); // Fonard Delete
        unregister_code(KC_LALT); // Release Conmand
    } else if (state->count == 1 && state->pressed) {
        // Single hold: Inserts "{"
        SEND_STRING("}");
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LGUI);  // Hold Option
        tap_code(KC_BSPC); // Fonard Delete
        unregister_code(KC_LGUI); // Release Conmand
    } else if (state->count == 2 && state->pressed) {
        // Double tap: Inserts "<"
        SEND_STRING(">");

    } else if (state->count == 3 && !state->pressed) {
        tap_code(KC_BSPC); // Fonard Delete
    }
}

void dance_bracketr_reset(tap_dance_state_t *state, void *user_data) {
    // No reset logic needed
}

// Tap Dance Actions for Bracket
void dance_bracketl_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Activate One Shot Shift
        set_oneshot_mods(MOD_LSFT);
    } else if (state->count == 1 && state->pressed) {
        // Single hold: Inserts "{"
        SEND_STRING("{");
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: Inserts "<"
        SEND_STRING("<");
    }
}

void dance_bracketl_reset(tap_dance_state_t *state, void *user_data) {
    // No reset logic needed
}

// Tap Dance Actions for Delete Forward
void dance_delfor_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Delete forward
        tap_code(KC_DEL);       // Forward Delete
    } else if (state->count == 1 && state->pressed) {
        register_code(KC_LALT);  // Hold Option
        tap_code(KC_DEL); // Fonard Delete
        unregister_code(KC_LALT); // Release Conmand
    } else if (state->count == 2 && state->pressed) {
        // Double Hold: Select word forward and delete
        register_code(KC_LSFT); // Hold Shift
        register_code(KC_LGUI); // Hold Command
        tap_code(KC_RGHT);      // Arrow Right
        unregister_code(KC_LGUI); // Release Command
        unregister_code(KC_LSFT); // Release Shift
        tap_code(KC_BSPC);      // Delete (Backspace)
    }
}

void dance_delfor_reset(tap_dance_state_t *state, void *user_data) {
    // Reset logic: Release any held keys
    unregister_code(KC_LALT);  // Release Option if it was held
    unregister_code(KC_LSFT);  // Release Shift if it was held
    unregister_code(KC_LGUI);  // Release Command if it was held
}

// Tap Dance Actions for Backspace
void dance_bspace_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Backspace
        tap_code(KC_BSPC);
    } else if (state->count == 1 && state->pressed) {
        // Hold: Option + Backspace (delete previous word)
        register_code(KC_LALT);
        tap_code(KC_BSPC);
        unregister_code(KC_LALT);
    } else if (state->count == 2 && state->pressed) {
        // Tap Hold: Command + Backspace (delete current line backward)
        register_code(KC_LGUI);
        tap_code(KC_BSPC);
        unregister_code(KC_LGUI);
    }
}

void dance_bspace_reset(tap_dance_state_t *state, void *user_data) {
    // Reset logic: Ensure all held modifiers are released
    unregister_code(KC_LALT);  // Release Option
    unregister_code(KC_LGUI);  // Release Command
}


// Tap Dance Actions for Leader/Hyper Key
void dance_alfyhypy_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single Tap: Activate Leader Key
        tap_code(KC_F3);
    } else if (state->count == 1 && state->pressed) {
        register_mods(MOD_HYPR);  // Properly register Hyper modifiers
    } else if (state->count == 2 && !state->pressed) {
        // Hold: Activate Hyper Key
        SEND_STRING("\"");
    }
}

void dance_alfyhypy_reset(tap_dance_state_t *state, void *user_data) {
        // Release Hyper modifiers
        unregister_mods(MOD_HYPR);
}

void dance_code_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single Tap: Inserts <> with the cursor between
        SEND_STRING("<>");
        tap_code(KC_LEFT);
    } else if (state->count == 2 && !state->pressed) {
        // Double Tap: Inserts {}
        SEND_STRING("{}");
        tap_code(KC_LEFT);
    } else if (state->pressed) {
        // Hold: Activate MO(WINDOWS) (Momentary Layer Switch)
        layer_on(WINDOWS);
    }
}

void dance_code_reset(tap_dance_state_t *state, void *user_data) {
        // Turn off MO(WINDOWS) when the key is released
        layer_off(WINDOWS);
}

void dance_selfc_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single Tap: Send Tab Key
        tap_code(KC_TAB);
    } else if (state->count == 1 && state->pressed) {
        // Single Hold: Activate WINDOWS Layer
        layer_on(WINDOWS);
    } else if (state->count == 2 && !state->pressed) {
        // Double Tap: Select Word Forward
        select_word_tap('W');
    } else if (state->count == 2 && state->pressed) {
        // Double Hold: Select Line Forward
        select_word_register('L');
    }
}

void dance_selfc_reset(tap_dance_state_t *state, void *user_data) {
    if (layer_state_is(WINDOWS)) {
        layer_off(WINDOWS);
    }
    select_word_unregister(); // Ensure selection is released
}

void dance_selbc_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single Tap: Send Alt + Shift + Tab
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_TAB);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
    } else if (state->count == 1 && state->pressed) {
        // Single Hold: Activate WINDOWS Layer
        layer_on(FUN);
    } else if (state->count == 2 && !state->pressed) {
        // Double Tap: Select Word Backward
        select_word_tap('B');
    } else if (state->count == 2 && state->pressed) {
        // Double Hold: Select Line Backward (Shift + Up Arrow)
        register_mods(MOD_BIT(KC_LSFT));  // Hold Shift
        tap_code(KC_UP);                   // Tap Up Arrow
        unregister_mods(MOD_BIT(KC_LSFT)); // Release Shift
    }
}

void dance_selbc_reset(tap_dance_state_t *state, void *user_data) {
    if (layer_state_is(FUN)) {
        layer_off(FUN);
    }
    select_word_unregister(); // Ensure selection is released
}

// Tap dance for slash 0
void dance_slash9_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Send '9'
        tap_code(KC_9);
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: Send '//'
        tap_code(KC_SLSH); // Send '/'
        tap_code(KC_SLSH); // Send another '/'
    } else if (state->pressed) {
        // Hold: Send '/'
        register_code(KC_SLSH);
        unregister_code(KC_SLSH); // Release '/' immediately
    }
}

void dance_slash9_reset(tap_dance_state_t *state, void *user_data) {
        // Release '/'
        unregister_code(KC_SLSH);
        unregister_code(KC_LSFT);
    }

// Tap dance for Bslash
void dance_bslash0_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Send '0'
        tap_code(KC_0);
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: Send '|'
        register_code(KC_LSFT); // Hold Shift
        tap_code(KC_BSLS);      // Send Backslash (| with Shift)
        unregister_code(KC_LSFT);
    } else if (state->pressed) {
        // Hold: Send '\'
        register_code(KC_BSLS);
        unregister_code(KC_BSLS); // Release '\' immediately
    }
}

void dance_bslash0_reset(tap_dance_state_t *state, void *user_data) {
        // Release '\'
        unregister_code(KC_BSLS);
        unregister_code(KC_LSFT);
    }

// Tap Dance for Textc
void dance_textc_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        // Single Tap Hold: Activate FUN Layer
        layer_on(SYM);
    } else if (state->count == 1 && !state->pressed) {
        // Single Tap: Send " ///"
        SEND_STRING(" ///");
    } else if (state->count == 2 && !state->pressed) {
        register_code(KC_LALT);
        tap_code(KC_F19);
        unregister_code(KC_LALT);
}
}

void dance_textc_reset(tap_dance_state_t *state, void *user_data) {
    // Ensure layer is turned off when tap dance ends
    layer_off(SYM);
    unregister_code(KC_LALT);   // Release Option
}

// Space_p Colemak
void dance_cspc_p_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single Tap: Send Control + Left
        register_code(KC_LCTL);  // Hold Control
        tap_code(KC_LEFT);       // Tap Left Arrow
        unregister_code(KC_LCTL); // Release Control
    } else if (state->count == 2 && !state->pressed) {
        // Double Tap: Send Command + Left
        register_code(KC_LGUI);  // Hold Command
        tap_code(KC_LEFT);       // Tap Left Arrow
        unregister_code(KC_LGUI); // Release Command
    } else if (state->pressed) {
        // Hold: Send Option
        register_code(KC_LALT);  // Hold Option
    }
}

void dance_cspc_p_reset(tap_dance_state_t *state, void *user_data) {
    // Release any keys if held
    unregister_code(KC_LALT);   // Release Option
    unregister_code(KC_LGUI);   // Release Command
}

// Space_n Colemak
void dance_cspc_n_finished(tap_dance_state_t *state, void *user_data) {
    td_state_t dance_state = cur_dance(state); // Get the tap dance state

    switch (dance_state) {
        case TD_SINGLE_TAP:
            // Single Tap: Control + Right Arrow (Move one word right)
            register_code(KC_LCTL);
            tap_code(KC_RGHT);
            unregister_code(KC_LCTL);
            break;

        case TD_SINGLE_HOLD:
            // Hold: Option (Alt)
            register_code(KC_LALT);
            break;

        case TD_DOUBLE_TAP:
            // Double Tap: Command + Right Arrow (Move to end of line)
            register_code(KC_LGUI);
            tap_code(KC_RGHT);
            unregister_code(KC_LGUI);
            break;

        default:
            break;
    }
}

void dance_cspc_n_reset(tap_dance_state_t *state, void *user_data) {
    // Reset logic for Hold or Double Hold
    unregister_code(KC_LALT); // Release Option
    unregister_code(KC_LGUI); // Release Command
}

// Space_n Colemak
void dance_underscore_finished(tap_dance_state_t *state, void *user_data) {
    td_state_t dance_state = cur_dance(state); // Get the tap dance state

    switch (dance_state) {
        case TD_SINGLE_TAP:
            // Single Tap: Control + Right Arrow (Move one word right)
            SEND_STRING("-");
            break;

        case TD_SINGLE_HOLD:
            // Hold: Option (Alt)
            SEND_STRING("_");
            break;

        case TD_DOUBLE_TAP:
            // Double Tap: Command + Right Arrow (Move to end of line)
            register_code(KC_LALT);
            tap_code(KC_3);
            unregister_code(KC_LALT);
            break;

            case TD_DOUBLE_HOLD:
            // Double Tap: Command + Right Arrow (Move to end of line)
            SEND_STRING("@");
            break;

        default:
            break;
    }
}

void dance_underscore_reset(tap_dance_state_t *state, void *user_data) {
    // Reset logic for Hold or Double Hold
    unregister_code(KC_LALT); // Release Option
    unregister_code(KC_LGUI); // Release Command
}

// Tap Dance Actions for App Next Colemak
void dance_capp_n_finished(tap_dance_state_t *state, void *user_data) {
    td_state_t dance_state = cur_dance(state); // Get the tap dance state

    switch (dance_state) {
        case TD_SINGLE_TAP:
            // Single Tap: Ctrl + Cmd + Right Arrow
            register_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LCTL));
            tap_code(KC_RGHT);
            unregister_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LCTL));
            break;

        case TD_DOUBLE_TAP:
            // Double Tap: Move forward a word (Option + Right Arrow)
            register_mods(MOD_BIT(KC_LALT)); // Hold Option
            tap_code(KC_RGHT);               // Tap Right Arrow
            unregister_mods(MOD_BIT(KC_LALT)); // Release Option
            break;

        case TD_SINGLE_HOLD:
            // Hold: Command
            register_code(KC_LGUI);
            break;

        default:
            break;
    }
}

void dance_capp_n_reset(tap_dance_state_t *state, void *user_data) {
    // Reset logic for Hold or Double Hold
    unregister_code(KC_LGUI); // Release Command
    unregister_code(KC_LALT); // Release Option
    unregister_code(KC_LCTL); // Release Control
}

// Tap Dance Actions for App Previous Colemak
void dance_capp_p_finished(tap_dance_state_t *state, void *user_data) {
    td_state_t dance_state = cur_dance(state); // Get the tap dance state

    switch (dance_state) {
        case TD_SINGLE_TAP:
        register_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LCTL));
        tap_code(KC_LEFT);
        unregister_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LCTL));
            break;

        case TD_DOUBLE_TAP:
            // Double Tap: Move forward a word (Option + Right Arrow)
            register_mods(MOD_BIT(KC_LALT)); // Hold Option
            tap_code(KC_LEFT);               // Tap Right Arrow
            unregister_mods(MOD_BIT(KC_LALT)); // Release Option
            break;

        case TD_SINGLE_HOLD:
            // Hold: Command
            register_code(KC_LGUI);
            break;

        default:
            break;
    }
}

void dance_capp_p_reset(tap_dance_state_t *state, void *user_data) {
    // Reset logic for Hold or Double Hold
    unregister_code(KC_LGUI); // Release Command
    unregister_code(KC_LALT); // Release Option
    unregister_code(KC_LCTL); // Release Option
}

// Colemak move by word/line
void dance_cmove_n_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single Tap: Command + Right
        register_mods(MOD_BIT(KC_LALT));
        tap_code(KC_RGHT);
        unregister_mods(MOD_BIT(KC_LALT));
    } else if (state->count == 1 && state->pressed) {
        // Double Tap: Control + Right
        register_mods(MOD_BIT(KC_LGUI));
        tap_code(KC_RGHT);
        unregister_mods(MOD_BIT(KC_LGUI));
    }
}

void dance_cmove_n_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        // Unregister any held mods on reset
        unregister_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI));
    }
}

// Colemak move by word/line p
void dance_cmove_p_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single Tap: Command + Right
        register_mods(MOD_BIT(KC_LALT));
        tap_code(KC_LEFT);
        unregister_mods(MOD_BIT(KC_LALT));
    } else if (state->count == 1 && state->pressed) {
        // Double Tap: Control + Right
        register_mods(MOD_BIT(KC_LGUI));
        tap_code(KC_LEFT);
        unregister_mods(MOD_BIT(KC_LGUI));
    }
}

void dance_cmove_p_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        // Unregister any held mods on reset
        unregister_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI));
    }
}

// Sleeve
void dance_sleeve_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        // Single tap: Ctrl + Shift + Cmd + F5
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_F5);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
    } else if (state->count == 2) {
        // Double tap: Shift + Cmd + 9
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_9);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
    }
}

void dance_sleeve_reset(tap_dance_state_t *state, void *user_data) {
    // Reset logic if needed (not required in this case)
}

void dance_leady_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {

        // Single Tap: Activate Leader Key

        leader_start();
    } else if (state->count == 1 && state->pressed) {
        // Hold: Send F3
        register_code(KC_F3);
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: Send F3
        tap_code(KC_F3);
    }
}

void dance_leady_reset(tap_dance_state_t *state, void *user_data) {
    // Release F3 when key is released
    unregister_code(KC_F3);
}

void dance_z_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Sends 'Z'
        tap_code(KC_Z);
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: Sends '"'
        SEND_STRING("(");
    } else if (state->pressed) {
        // Hold: Acts as Shift
        register_code(KC_LSFT); // Press Shift
    }
}

// Reset function to release Shift when key is released
void dance_z_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_LSFT); // Release Shift
}

void dance_sympic_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Activate one-shot SYM layer
        send_string("#");
    } else if (state->count == 1 && state->pressed) {
        // Hold: Activate momentary PIC layer
        layer_on(SYM);
    } else if (state->count == 2 && !state->pressed) {
        send_string("@");
    }
}

void dance_sympic_reset(tap_dance_state_t *state, void *user_data) {
    // Always turn off the PIC layer when the key is released (no need to check state->pressed)
    layer_off(SYM);
}

// Tap Dance Actions for Bracket
void dance_til_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Inserts < > with the cursor between
        SEND_STRING("~");
    } else if (state->count == 1 && state->pressed) {
        // Hold: Inserts { } with the cursor between
        SEND_STRING("~~~~");
        tap_code(KC_LEFT);
        tap_code(KC_LEFT);
    } else if (state->count == 2 && !state->pressed) {
        // Double tap: '
        SEND_STRING("~~");
        tap_code(KC_LEFT);
    }
}

void dance_til_reset(tap_dance_state_t *state, void *user_data) {
    // No reset logic needed
}

// Tap Dance Actions for Bracket
void dance_rb_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Inserts < > with the cursor between
        SEND_STRING(">");
    } else if (state->count == 1 && state->pressed) {
        // Hold: Inserts { } with the cursor between
        SEND_STRING(">");
        tap_code(KC_SPACE);
    }
}

void dance_rb_reset(tap_dance_state_t *state, void *user_data) {
    // No reset logic needed
}

// Tap Dance Actions for Bracket
void dance_sbl_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Inserts < > with the cursor between
        SEND_STRING("[");
    } else if (state->count == 2 && !state->pressed) {
        // Hold: Inserts { } with the cursor between
        SEND_STRING("[[");
        tap_code(KC_SPACE);
    }
}

void dance_sbl_reset(tap_dance_state_t *state, void *user_data) {
    // No reset logic needed
}

// Tap Dance Actions for Bracket
void dance_sbr_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Inserts < > with the cursor between
        SEND_STRING("]");
    } else if (state->count == 2 && !state->pressed) {
        // Hold: Inserts { } with the cursor between
        SEND_STRING("- [ ]");
        tap_code(KC_SPACE);
    }
}

void dance_sbr_reset(tap_dance_state_t *state, void *user_data) {
    // No reset logic needed
}

void dance_uscr_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Inserts < > with the cursor between
        SEND_STRING("-");
    } else if (state->count == 2 && !state->pressed) {
        // Hold: Inserts { } with the cursor between
        SEND_STRING("_");
    } else if (state->count == 1 && state->pressed) {
        // Hold: Inserts { } with the cursor between
        SEND_STRING("_");
    }
}

void dance_uscr_reset(tap_dance_state_t *state, void *user_data) {
    // No reset logic needed
}

void dance_star_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Inserts < > with the cursor between
        SEND_STRING("*");
    } else if (state->count == 2 && !state->pressed) {
        // Hold: Inserts { } with the cursor between
        SEND_STRING("****");
        tap_code(KC_LEFT);
        tap_code(KC_LEFT);
    }
}

void dance_star_reset(tap_dance_state_t *state, void *user_data) {
    // No reset logic needed
}

void dance_backt_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Inserts < > with the cursor between
        SEND_STRING("`");
    } else if (state->count == 2 && !state->pressed) {
        // Hold: Inserts { } with the cursor between
        SEND_STRING("``");
        tap_code(KC_LEFT);
    }
}

void dance_backt_reset(tap_dance_state_t *state, void *user_data) {
    // No reset logic needed
}

void dance_equals_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // Single tap: Inserts < > with the cursor between
        SEND_STRING("=");
    } else if (state->count == 2 && !state->pressed) {
        // Hold: Inserts { } with the cursor between
        SEND_STRING("====");
        tap_code(KC_LEFT);
        tap_code(KC_LEFT);
    }
}

void dance_equals_reset(tap_dance_state_t *state, void *user_data) {
    // No reset logic needed
}

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

// Tap Dance for TD_ADM (OSL(ADM) on tap, RCTL on hold)
 ///void dance_adm_finished(tap_dance_state_t *state, void *user_data) {
   ///  if (state->count == 1 && !state->pressed) {
        // Single Tap: Activate One Shot Layer ADM
    ///     tap_code16(OSL(ADM));
     ///} else if (state->pressed) {
        // Hold: Act as Right Control
      ///   register_code(KC_RCTL);
    /// }
 ///}

 ///void dance_adm_reset(tap_dance_state_t *state, void *user_data) {
    // Reset Right Control when released
    /// unregister_code(KC_RCTL);
 ///}

// Per key tapping term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_PD_DRAFTS):  // Use the keycode TD(...) for the tap dance
            return TAPPING_TERM + 100;  // Adjust this value as needed
        case TD(TD_F15_ANYBOX):
            return TAPPING_TERM + 100;
        case TD(TD_END_OMNIFOCUS):
            return TAPPING_TERM + 100;
        case TD(TD_CLEANSHOT):
            return TAPPING_TERM + 100;
        case TD(TD_FINDER):
            return TAPPING_TERM + 100;
        case TD(TD_DEVONTHINK):
            return TAPPING_TERM + 100;
        case TD(TD_SPARK):
            return TAPPING_TERM + 100;
        case TD(TD_FANTASTICAL):
            return TAPPING_TERM + 100;
        case TD(TD_DAYONE):
            return TAPPING_TERM + 100;
        case TD(TD_TRELLO):
            return TAPPING_TERM + 100;
        case TD(TD_OOUTLINER):
            return TAPPING_TERM + 100;
        case TD(TD_XMIND):
            return TAPPING_TERM + 100;
        case TD(TD_MUSE):
            return TAPPING_TERM + 100;
        case TD(TD_HOOK):
            return TAPPING_TERM + 100;
        case TD(TD_ALFRED):
            return TAPPING_TERM + 100;
        case TD(TD_DROP):
            return TAPPING_TERM + 100;
        case TD(TD_SNIP):
            return TAPPING_TERM + 100;
        case TD(TD_TEXTE):
            return TAPPING_TERM + 100;
        case TD(TD_TEXTC):
            return TAPPING_TERM + 50;
        case TD(TD_PERP):
            return TAPPING_TERM + 100;
        case TD(TD_CHAT):
            return TAPPING_TERM + 100;
        case TD(TD_ARC):
            return TAPPING_TERM + 100;
        case TD(TD_OBSIDIAN):
            return TAPPING_TERM + 100;
        case TD(TD_EAGLE):
            return TAPPING_TERM + 100;
        case TD(TD_SLEEVE):
            return TAPPING_TERM + 100;
        case TD(TD_APOSTROPHE):
            return TAPPING_TERM + 50;
        case TD(TD_SPACE):
            return TAPPING_TERM + 50;
        case TD(TD_CSPC_P):
            return TAPPING_TERM + 100;
            case TD(TD_CSPC_N):
            return TAPPING_TERM + 100;
            case TD(TD_CAPP_P):
            return TAPPING_TERM + 100;
            case TD(TD_CAPP_N):
            return TAPPING_TERM + 100;
            case TD(TD_SELBC):
            return TAPPING_TERM + 100;
            case TD(TD_SELFC):
            return TAPPING_TERM + 100;
            case TD(TD_BRACKET_L):
            return TAPPING_TERM + 75;
            case TD(TD_BRACKET_R):
            return TAPPING_TERM + 75;
            case TD(TD_PERIOD):
            return TAPPING_TERM + 50;
            case TD(TD_QUESTION):
            return TAPPING_TERM + 75;
            case TD(TD_BRACKET):
            return TAPPING_TERM + 75;
            case TD(TD_SLASH):
            return TAPPING_TERM + 75;
            case TD(TD_DELFOR):
            return TAPPING_TERM + 75;
            case TD(TD_UNDERSCORE):
            return TAPPING_TERM + 75;
            case TD(TD_Z):
            return TAPPING_TERM + 75;
            case TD(TD_CAPS):
            return TAPPING_TERM + 75;
            case TD(TD_ALFYHYPY):
            return TAPPING_TERM + 75;
            case TD(TD_LEADY):
            return TAPPING_TERM + 75;
            case TD(TD_TIL):
            return TAPPING_TERM + 50;
            default:
            return TAPPING_TERM;  // Default tapping term
    }
}

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
        case ALT_S:
        case GUI_D:
        case SFT_F:
        case SFT_J:
        case GUI_K:
        case ALT_L:
        case CTL_SCLN:
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
        case KC_BACKSLASH:
        case KC_NONUS_HASH:
        case KC_SEMICOLON:
        case KC_GRAVE:
        case BSPACE:
        case DELF:
        case BRACKET:
            return true;
        default:
            return false; // End Caps Word for other keys
    }
}
// Cap word indicator
void caps_word_set_user(bool active) {
    if (active) {
        // Do something when Caps Word activates.
    } else {
        // Do something when Caps Word deactivates.
    }
}

combo_t key_combos[] = {};
uint16_t COMBO_LEN = 0;

// Macros
enum custom_keycodes {
    SELWORD = SAFE_RANGE,
    SWORD_B,
    DELWORD,
    SLINE,
    SLINE_P,
    UNDO,
    COPY,
    CUT,
    PASTE,
    DUPLICA,
    DELWB,
    DELWF,
    ARC_B,
    ARC_F,
    WIN1_1,
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
    WIN_EXT,
    WIN_CEN,
    FULLSCR,
    KC_TITLE,
    KMESTRO,  // Keyboard Maestro
    SYSSET,               // System Settings
    PASS,                 // 1Password
    SPOTIFY,              // Spotify
    PORTAL,               // Portal
    SPEED,            // Speedtest
    MSG,                  // Messages
    WHATSAPP,             // WhatsApp
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
    ZOOMIN,
    ZOOMOUT,

    SELWFWD,  // Select Word Forward
    SELWBAK,              // Select Word Backward
    SELLINE,              // Select Line Forward
    SELLINE_B,            // Select Line Backward
    HAZEDN,
    HAZEUP,
    BTICK,
    POUND,
    DOLLAR,
    EURO,
    YEN,
    OG,
    LB,
    BB,
    AND,
    MT,
    ARROW,
    LARROW,
    AARROW,
    LAARROW,
    SBC,
    SBTD,
    TM,
    TROSA,
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
};

uint16_t SELECT_WORD_KEYCODE = SELWORD;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Process existing macros
    if (!process_sentence_case(keycode, record)) { return false; }
    if (!process_repeat_key(keycode, record, REPEAT)) { return false; }
    if (!process_select_word_back(keycode, record, SWORD_B)) return false;
    if (!process_autocorrection(keycode, record)) { return false; }
    if (!process_achordion(keycode, record)) { return false; }
    if (!process_select_word(keycode, record, SELWORD)) { return false; }

    switch (keycode) {
        // WORD SELECTION MACROS
        case SELWFWD:  // Forward Word Selection
            if (record->event.pressed) {
                select_word_register('W');
            } else {
                select_word_unregister();
            }
            break;

        case SELWBAK:  // Backward Word Selection
            if (record->event.pressed) {
                select_word_register('B');
            } else {
                select_word_unregister();
            }
            break;

        case SELLINE:  // Select Entire Line Forward
            if (record->event.pressed) {
                select_word_register('L');
            } else {
                select_word_unregister();
            }
            break;

        case SELLINE_B:  // Select Entire Line Backward
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LSFT));  // Hold Shift
                tap_code(KC_UP);                  // Tap Up Arrow
                unregister_mods(MOD_BIT(KC_LSFT)); // Release Shift
            }
            break;

        // DELETE WORD MACROS
        case DELWB:  // Delete Word Backward
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_BSPC);
                unregister_code(KC_LALT);
            }
            return false;

            case REPEAT:
            if (record->event.pressed) {
                tap_code16(REPEAT);  // Ensure it triggers repeat
            }
            return false;

        case DELWF:  // Delete Word Forward
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_DEL);
                unregister_code(KC_LALT);
            }
            return false;

        // LINE SELECTION MACROS
        case SLINE:  // Select Line Forward
            if (record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_LCMD);
                tap_code(KC_RGHT);
                unregister_code(KC_LCMD);
                unregister_code(KC_LSFT);
            }
            return false;

        case SLINE_P:  // Select Line Backward
            if (record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_LCMD);
                tap_code(KC_LEFT);
                unregister_code(KC_LCMD);
                unregister_code(KC_LSFT);
            }
            return false;

        // STANDARD MACROS
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

        // HYPER KEY MACROS (ARC)
        case ARC_B:  // Hyper + Left
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LALT);
                register_code(KC_LCMD);
                register_code(KC_LSFT);
                tap_code(KC_LEFT);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCMD);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
            }
            return false;

        case ARC_F:  // Hyper + Right
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LALT);
                register_code(KC_LCMD);
                register_code(KC_LSFT);
                tap_code(KC_RIGHT);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCMD);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
            }
            return false;

        // APPLICATION SHORTCUTS

        case FULLSCR:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LCMD);
                tap_code(KC_F);
                unregister_code(KC_LCMD);
                unregister_code(KC_LCTL);
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

        case SPOTIFY:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F4)))));
            }
            return false;

        case ELGATO:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F9)))));
            }
            return false;

        case WHATSAPP:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_PGUP)))));
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
        case LDECK:
                if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_L))))); // Ctrl + Opt + Cmd + F10
        }

            //Window management
                case WIN1_1:
                    if (record->event.pressed) {
                        // Send Opt + Shift + Cmd + 1
                        register_code(KC_LALT);   // Hold Option
                        register_code(KC_LSFT);  // Hold Shift
                        register_code(KC_LCMD);  // Hold Command
                        tap_code(KC_1);          // Press 1
                        unregister_code(KC_LCMD);  // Release Command
                        unregister_code(KC_LSFT);  // Release Shift
                        unregister_code(KC_LALT);  // Release Option
                    }
                    return false;  // Skip further processing
                case WIN1_2:
                    if (record->event.pressed) {
                        // Send Opt + Shift + Cmd + 2
                        register_code(KC_LALT);   // Hold Option
                        register_code(KC_LSFT);  // Hold Shift
                        register_code(KC_LCMD);  // Hold Command
                        tap_code(KC_2);          // Press 2
                        unregister_code(KC_LCMD);  // Release Command
                        unregister_code(KC_LSFT);  // Release Shift
                        unregister_code(KC_LALT);  // Release Option
                    }
                    return false;  // Skip further processing
                case WIN1_3:
                    if (record->event.pressed) {
                        // Send Opt + Shift + Cmd + 3
                        register_code(KC_LALT);   // Hold Option
                        register_code(KC_LSFT);  // Hold Shift
                        register_code(KC_LCMD);  // Hold Command
                        tap_code(KC_3);          // Press 3
                        unregister_code(KC_LCMD);  // Release Command
                        unregister_code(KC_LSFT);  // Release Shift
                        unregister_code(KC_LALT);  // Release Option
                    }
                    return false;  // Skip further processing
                    // Windows 2
                case WIN2_1:
                    if (record->event.pressed) {
                        register_code(KC_LALT);   // Hold Option
                        register_code(KC_LSFT);  // Hold Shift
                        register_code(KC_LCMD);  // Hold Command
                        tap_code(KC_4);          // Press 4
                        unregister_code(KC_LCMD);  // Release Command
                        unregister_code(KC_LSFT);  // Release Shift
                        unregister_code(KC_LALT);  // Release Option
                    }
                    return false;
                case WIN2_2:
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
                    // 3
                case WIN3_1:
                    if (record->event.pressed) {
                        // Option + Command + 1
                        register_code(KC_LALT);   // Hold Option
                        register_code(KC_LCMD);  // Hold Command
                        tap_code(KC_1);          // Press 1
                        unregister_code(KC_LCMD);  // Release Command
                        unregister_code(KC_LALT);  // Release Option
                    }
                    return false;
                case WIN3_2:
                    if (record->event.pressed) {
                        // Option + Command + 2
                        register_code(KC_LALT);
                        register_code(KC_LCMD);
                        tap_code(KC_2);
                        unregister_code(KC_LCMD);
                        unregister_code(KC_LALT);
                    }
                    return false;
                case WIN3_3:
                    if (record->event.pressed) {
                        // Option + Command + 3
                        register_code(KC_LALT);
                        register_code(KC_LCMD);
                        tap_code(KC_3);
                        unregister_code(KC_LCMD);
                        unregister_code(KC_LALT);
                    }
                    return false;
                case WIN3_4:
                    if (record->event.pressed) {
                        // Option + Command + 4
                        register_code(KC_LALT);
                        register_code(KC_LCMD);
                        tap_code(KC_4);
                        unregister_code(KC_LCMD);
                        unregister_code(KC_LALT);
                    }
                    return false;
                case WIN3_5:
                    if (record->event.pressed) {
                        // Option + Command + 5
                        register_code(KC_LALT);
                        register_code(KC_LCMD);
                        tap_code(KC_5);
                        unregister_code(KC_LCMD);
                        unregister_code(KC_LALT);
                    }
                    return false;
                case WIN3_6:
                    if (record->event.pressed) {
                        // Option + Command + 6
                        register_code(KC_LALT);
                        register_code(KC_LCMD);
                        tap_code(KC_6);
                        unregister_code(KC_LCMD);
                        unregister_code(KC_LALT);
                    }
                    return false;
                case WIN3_7:
                    if (record->event.pressed) {
                        // Option + Command + 7
                        register_code(KC_LALT);
                        register_code(KC_LCMD);
                        tap_code(KC_7);
                        unregister_code(KC_LCMD);
                        unregister_code(KC_LALT);
                    }
                    return false;
                 case WIN4_1:
                    if (record->event.pressed) {
                        // Shift + Command + 8
                        register_code(KC_LALT);  // Hold Shift
                        register_code(KC_LCMD); // Hold Command
                        tap_code(KC_8);         // Press 8
                        unregister_code(KC_LCMD); // Release Command
                        unregister_code(KC_LALT); // Release Shift
                    }
                    return false;
                case WIN4_2:
                    if (record->event.pressed) {
                        // Shift + Command + 9
                        register_code(KC_LCTL);
                        register_code(KC_LCMD);
                        tap_code(KC_9);
                        unregister_code(KC_LCTL);
                        unregister_code(KC_LALT);
                    }
                    return false;
                case WIN4_3:
                    if (record->event.pressed) {
                        // Shift + Command + 0
                        register_code(KC_LALT);
                        register_code(KC_LCMD);
                        tap_code(KC_0);
                        unregister_code(KC_LALT);
                        unregister_code(KC_LCTL);
                    }
                    return false;
                case WIN4_4:
                    if (record->event.pressed) {
                        // Control + Shift + 1
                        register_code(KC_LCTL);  // Hold Control
                        register_code(KC_LALT);
                        register_code(KC_LCMD);  // Hold Shift
                        tap_code(KC_1);
                        unregister_code(KC_LCMD);          // Press 1
                        unregister_code(KC_LALT); // Release Shift
                        unregister_code(KC_LCTL); // Release Control
                    }
                    return false;
                    // 5
                 case WIN5_1:
                    if (record->event.pressed) {
                        // Control + Option + 2
                        register_code(KC_LCTL);  // Hold Control
                        register_code(KC_LALT);  // Hold Option
                        tap_code(KC_2);          // Press 2
                        unregister_code(KC_LALT);  // Release Option
                        unregister_code(KC_LCTL);  // Release Control
                    }
                    return false;
                case WIN5_2:
                    if (record->event.pressed) {
                        // Control + Option + 3
                        register_code(KC_LCTL);
                        register_code(KC_LALT);
                        tap_code(KC_3);
                        unregister_code(KC_LALT);
                        unregister_code(KC_LCTL);
                    }
                    return false;
                case WIN5_3:
                    if (record->event.pressed) {
                        // Control + Option + 4
                        register_code(KC_LCTL);
                        register_code(KC_LALT);
                        tap_code(KC_4);
                        unregister_code(KC_LALT);
                        unregister_code(KC_LCTL);
                    }
                    return false;
                case WIN5_4:
                    if (record->event.pressed) {
                        // Control + Option + 5
                        register_code(KC_LCTL);
                        register_code(KC_LALT);
                        tap_code(KC_5);
                        unregister_code(KC_LALT);
                        unregister_code(KC_LCTL);
                    }
                    return false;
                    // 6
                case WIN6_1:
                    if (record->event.pressed) {
                        // Control + Option + 6
                        register_code(KC_LCTL);  // Hold Control
                        register_code(KC_LALT);  // Hold Option
                        tap_code(KC_6);          // Press 6
                        unregister_code(KC_LALT);  // Release Option
                        unregister_code(KC_LCTL);  // Release Control
                    }
                    return false;
                case WIN6_2:
                    if (record->event.pressed) {
                        // Control + Option + 7
                        register_code(KC_LCTL);
                        register_code(KC_LALT);
                        tap_code(KC_7);
                        unregister_code(KC_LALT);
                        unregister_code(KC_LCTL);
                    }
                    return false;
                case WIN6_3:
                    if (record->event.pressed) {
                        // Control + Option + 8
                        register_code(KC_LCTL);
                        register_code(KC_LALT);
                        tap_code(KC_8);
                        unregister_code(KC_LALT);
                        unregister_code(KC_LCTL);
                    }
                    return false;
                case ZOOMIN:
                    if (record->event.pressed) {
                        // Control + Option + 8
                        register_code(KC_LALT);
                        tap_code(MSEWHLDO);
                        unregister_code(KC_LALT);
                    }
                    return false;
                            case ZOOMOUT:
                    if (record->event.pressed) {
                        // Control + Option + 8
                        register_code(KC_LALT);
                        tap_code(MSEWHLUP);
                        unregister_code(KC_LALT);
                    }
                    return false;
                case WIN6_4:
                    if (record->event.pressed) {
                        // Control + Option + 9
                        register_code(KC_LCTL);
                        register_code(KC_LALT);
                        tap_code(KC_9);
                        unregister_code(KC_LALT);
                        unregister_code(KC_LCTL);
                    }
                    return false;
                case WIN6_5:
                    if (record->event.pressed) {
                        // Control + Option + 0
                        register_code(KC_LCTL);
                        register_code(KC_LALT);
                        tap_code(KC_0);
                        unregister_code(KC_LALT);
                        unregister_code(KC_LCTL);
                    }
                    return false;
                    // 7
                case WIN7_1:
                    if (record->event.pressed) {
                        // Ctrl + Option + Command + 2
                        register_code(KC_LCTL);  // Hold Control
                        register_code(KC_LALT);  // Hold Option
                        register_code(KC_LCMD);  // Hold Command
                        tap_code(KC_2);          // Press 2
                        unregister_code(KC_LCMD);  // Release Command
                        unregister_code(KC_LALT);  // Release Option
                        unregister_code(KC_LCTL);  // Release Control
                    }
                    return false;
                case WIN7_2:
                    if (record->event.pressed) {
                        // Ctrl + Option + Command + 3
                        register_code(KC_LCTL);
                        register_code(KC_LALT);
                        register_code(KC_LCMD);
                        tap_code(KC_3);
                        unregister_code(KC_LCMD);
                        unregister_code(KC_LALT);
                        unregister_code(KC_LCTL);
                    }
                    return false;
                case WIN_EXT:
                    if (record->event.pressed) {
                        // Ctrl + Option + Command + 3
                        register_code(KC_LALT);
                        register_code(KC_LSFT);
                        tap_code(KC_5);
                        unregister_code(KC_LSFT);
                        unregister_code(KC_LALT);                  }
                    return false;
                case WIN_CEN:
                    if (record->event.pressed) {
                        // Ctrl + Option + Command + 3
                        register_code(KC_LALT);
                        register_code(KC_LSFT);
                        tap_code(KC_6);
                        unregister_code(KC_LSFT);
                        unregister_code(KC_LALT);                  }
                    return false;
                case HAZEDN:
                    if (record->event.pressed) {
                        // Ctrl + Option + Command + 3
                        register_code(KC_LCTL);
                        register_code(KC_LALT);
                        register_code(KC_LSFT);
                        tap_code(KC_J);
                        unregister_code(KC_LSFT);
                        unregister_code(KC_LALT);
                        unregister_code(KC_LCTL);
                    }
                    return false;
                case HAZEUP:
                    if (record->event.pressed) {
                        // Ctrl + Option + Command + 3
                        register_code(KC_LCTL);
                        register_code(KC_LALT);
                        register_code(KC_LSFT);
                        tap_code(KC_G);
                        unregister_code(KC_LSFT);
                        unregister_code(KC_LALT);
                        unregister_code(KC_LCTL);
                    }
                    return false;

                    ///Symbol layer
                case BTICK:
                    if (record->event.pressed) {
                        // Ctrl + Option + Command + 3
                        SEND_STRING("`");
                    }
                    return false;
                case POUND:
                    if (record->event.pressed) {
                        register_code(KC_LALT);
                        tap_code(KC_3);
                        unregister_code(KC_LALT);
                    }
                    return false;
                case DOLLAR:
                    if (record->event.pressed) {
                        // Ctrl + Option + Command + 3
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
                case TROSA:
                    if (record->event.pressed) {
                        register_code(KC_LSFT);
                        tap_code(KC_6);
                        unregister_code(KC_LSFT);
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


         default:
            return true;  // Process all other keycodes normally
    }

    return true;
}

enum unicode_names {
    CR,  // Define a name for the © symbol

};

const uint32_t PROGMEM unicode_map[] = {
    [CR] = 0x00A9,  // Assign © (Unicode U+00A9)
    [TM] = 0x2122, // Unicode for ™
};

void housekeeping_task_user(void) {
  select_word_task();
  achordion_task();
  // move_cursor_task();
  // Other tasks...
}

// Tap Dance Array
tap_dance_action_t tap_dance_actions[] = {
    [TD_F15_ANYBOX] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_f15_anybox_finished, dance_f15_anybox_reset),
    [TD_PD_DRAFTS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_pd_drafts_finished, dance_pd_drafts_reset),
    [TD_END_OMNIFOCUS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_end_omnifocus_finished, dance_end_omnifocus_reset),
    [TD_PERIOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_period_finished, dance_period_reset),
    [TD_BRACKET] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_bracket_finished, dance_bracket_reset),
    [TD_QUESTION] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_question_finished, dance_question_reset),
    [TD_SLASH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_slash_finished, dance_slash_reset),
    [TD_TILDE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_tilde_finished, dance_tilde_reset),
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_caps_finished, dance_caps_reset),
    [TD_SPACE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_space_finished, dance_space_reset),
    [TD_COMMA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_comma_finished, dance_comma_reset),
    [TD_DELFOR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_delfor_finished, dance_delfor_reset),
    [TD_BSPACE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_bspace_finished, dance_bspace_reset),
    [TD_ALFYHYPY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_alfyhypy_finished, dance_alfyhypy_reset),
    [TD_CODE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_code_finished, dance_code_reset),
    [TD_SELBC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_selbc_finished, dance_selbc_reset),
    [TD_SELFC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_selfc_finished, dance_selfc_reset),
    [TD_SLASH9] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_slash9_finished, dance_slash9_reset),
    [TD_BSLASH0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_bslash0_finished, dance_bslash0_reset),
    [TD_FINDER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_finder_finished, dance_finder_reset),
    [TD_DEVONTHINK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_devonthink_finished, dance_devonthink_reset),
    [TD_SPARK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_spark_finished, dance_spark_reset),
    [TD_FANTASTICAL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_fantastical_finished, dance_fantastical_reset),
    [TD_DAYONE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dayone_finished, dance_dayone_reset),
    [TD_TRELLO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_trello_finished, dance_trello_reset),
    [TD_OOUTLINER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_ooutliner_finished, dance_ooutliner_reset),
    [TD_XMIND] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_xmind_finished, dance_xmind_reset),
    [TD_MUSE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_muse_finished, dance_muse_reset),
    [TD_HOOK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_hook_finished, dance_hook_reset),
    [TD_ALFRED] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_alfred_finished, dance_alfred_reset),
    [TD_DROP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_drop_finished, dance_drop_reset),
    [TD_SNIP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_snip_finished, dance_snip_reset),
    [TD_TEXTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_texte_finished, dance_texte_reset),
    [TD_PERP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_perp_finished, dance_perp_reset),
    [TD_CHAT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_chat_finished, dance_chat_reset),
    [TD_ARC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_arc_finished, dance_arc_reset),
    [TD_OBSIDIAN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_obsidian_finished, dance_obsidian_reset),
    [TD_EAGLE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_eagle_finished, dance_eagle_reset),
    [TD_TEXTC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_textc_finished, dance_textc_reset),
    [TD_CSPC_N] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cspc_n_finished, dance_cspc_n_reset),
    [TD_CSPC_P] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cspc_p_finished, dance_cspc_p_reset),
    [TD_CAPP_N] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_capp_n_finished, dance_capp_n_reset),
    [TD_CAPP_P] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_capp_p_finished, dance_capp_p_reset),
    [TD_CMOVE_N] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cmove_n_finished, dance_cmove_n_reset),
    [TD_CMOVE_P] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cmove_p_finished, dance_cmove_p_reset),
    [TD_SLEEVE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sleeve_finished, dance_sleeve_reset),
    [TD_CLEANSHOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cleanshot_finished, dance_cleanshot_reset),
    [TD_APOSTROPHE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_apostrophe_finished, dance_apostrophe_reset),
    [TD_BRACKET_R] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_bracketr_finished, dance_bracketr_reset),
    [TD_BRACKET_L] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_bracketl_finished, dance_bracketl_reset),
    [TD_LEADY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_leady_finished, dance_leady_reset),
    [TD_UNDERSCORE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_underscore_finished, dance_underscore_reset),
   ///  [TD_ADM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_adm_finished, dance_adm_reset),
    [TD_Z] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_z_finished, dance_z_reset),
    [TD_SYMPIC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sympic_finished, dance_sympic_reset),
    [TD_TIL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_til_finished, dance_til_reset),
    [TD_RB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_rb_finished, dance_rb_reset),
    [TD_SBL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sbl_finished, dance_sbl_reset),
    [TD_SBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sbr_finished, dance_sbr_reset),
    [TD_USCR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_uscr_finished, dance_uscr_reset),
    [TD_STAR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_star_finished, dance_star_reset),
    [TD_BACKT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_backt_finished, dance_backt_reset),
    [TD_EQUALS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_equals_finished, dance_equals_reset),
    [TD_UNSC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_unsc_finished, dance_unsc_reset),

};

// Leader key
void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_F)) {
        // Leader, f => Types the below string
        SEND_STRING("QMK is awesome.");
    } else if (leader_sequence_three_keys(KC_D, KC_D, KC_S)) {
        // Leader, d, d, s => Types the below string
        SEND_STRING("https://start.duckduckgo.com\n");
    // Global
    } else if (leader_sequence_two_keys(KC_A, KC_Z)) {
        // Leader, a, z => GUI+Z (Undo)
        tap_code16(LGUI(KC_Z));
    } else if (leader_sequence_three_keys(KC_A, KC_Z, KC_Z)) {
        // Leader, a, z, z => GUI+SHIFT+Z (Redo)
        tap_code16(SCMD(KC_Z));
    } else if (leader_sequence_two_keys(KC_A, KC_Q)) {
        // Leader, a, q => GUI+Q (Quit)
        tap_code16(LGUI(KC_Q));
    } else if (leader_sequence_two_keys(KC_A, KC_W)) {
        // Leader, a, w => GUI+W (Close)
        tap_code16(LGUI(KC_Q));
    } else if (leader_sequence_two_keys(KC_A, KC_H)) {
        // Leader, a, h => GUI+H (Hide)
        tap_code16(LGUI(KC_H));
    } else if (leader_sequence_two_keys(KC_A, KC_X)) {
        // Leader, a, x => GUI+X (Cut)
        tap_code16(LGUI(KC_X));
    } else if (leader_sequence_two_keys(KC_A, KC_C)) {
        // Leader, a, c => GUI+C (Copy)
        tap_code16(LGUI(KC_C));
    } else if (leader_sequence_two_keys(KC_A, KC_V)) {
        // Leader, a, v => GUI+V (Paste)
        tap_code16(LGUI(KC_V));
    } else if (leader_sequence_two_keys(KC_A, KC_M)) {
        // Leader, a, v => GUI+V (Minimize)
        tap_code16(LGUI(KC_M));
    } else if (leader_sequence_three_keys(KC_A, KC_C, KC_A)) {
        // Leader, a, c, a => Cmnd+A, Cmnd+C (Copy All)
        SEND_STRING(SS_LGUI("a") SS_LGUI("c"));
    } else if (leader_sequence_three_keys(KC_A, KC_S, KC_A)) {
        // Leader, a, s, a => Cmnd+A, (Select All)
        SEND_STRING(SS_LGUI("a") SS_LGUI("c"));
    } else if (leader_sequence_two_keys(KC_A, KC_S)) {
        // Leader, a, s => GUI+S (Save)
        tap_code16(LGUI(KC_S));
    } else if (leader_sequence_two_keys(KC_A, KC_D)) {
        // Leader, a, d => GUI+D (Duplicate)
        tap_code16(LGUI(KC_D));
    }else if (leader_sequence_three_keys(KC_A, KC_S, KC_S)) {
        // Leader, b => Types the below string
        register_code(KC_LCMD);   // Hold Command
        tap_code(KC_COMMA);           // Tap B
        unregister_code(KC_LCMD); // Release Command
    // Surf
    } else if (leader_sequence_two_keys(KC_S, KC_T)) {
        // Leader, s, t => GUI+T (New Tab)
        tap_code16(LGUI(KC_T));
    } else if (leader_sequence_three_keys(KC_S, KC_T, KC_T)) {
        // Leader, s, t, t => OPT+T (Split Tab)
        tap_code16(LALT(KC_T));
    } else if (leader_sequence_two_keys(KC_S, KC_N)) {
        // Leader, s, n => GUI+N (New Window)
        tap_code16(LGUI(KC_N));
    } else if (leader_sequence_three_keys(KC_A, KC_D, KC_D)) {
        // Leader, a, d, d => GUI+Backspace (Delete)
        tap_code16(LGUI(KC_BSPC));
    } else if (leader_sequence_three_keys(KC_S, KC_W, KC_W)) {
        // Leader, a, z, z => GUI+SHIFT+Z (Incognito)
        tap_code16(SCMD(KC_N));
    } else if (leader_sequence_two_keys(KC_S, KC_W)) {
        // Leader, s, t => GUI+T (New window)
        tap_code16(LGUI(KC_N));
    } else if (leader_sequence_three_keys(KC_S, KC_T, KC_R)) {
        // Leader, a, z, z => GUI+SHIFT+Z (Retore Tab)
        tap_code16(SCMD(KC_T));
    } else if (leader_sequence_two_keys(KC_S, KC_C)) {
        // Leader, s, t => GUI+T (Copy link)
        register_code(KC_LCTL);   // Hold Control
        register_code(KC_LALT);   // Hold Option
        tap_code(KC_C);           // Tap B
        unregister_code(KC_LALT); // Release Option
        unregister_code(KC_LCTL);
    // Codes
    } else if (leader_sequence_one_key(KC_P)) {
        // Leader, p => Types the below string
        SEND_STRING("gReatestEver9000\n");
    } else if (leader_sequence_two_keys(KC_P, KC_P)) {
        // Leader, p => Types the below string
        SEND_STRING("IruletheChaos9000\n");
    } else if (leader_sequence_three_keys(KC_S, KC_C, KC_C)) {
    // Leader, S, C => ⌃+⇧+⌥+⌘+C (Copy URL)
        register_code(KC_LCTL);   // Hold Control
        register_code(KC_LALT);   // Hold Option
        register_code(KC_LCMD);   // Hold Command
        register_code(KC_LSFT);   // Hold Shift
        tap_code(KC_C);           // Tap B
        unregister_code(KC_LSFT); // Release Shift
        unregister_code(KC_LCMD); // Release Command
        unregister_code(KC_LALT); // Release Option
        unregister_code(KC_LCTL);
        // Surf
    } else if (leader_sequence_two_keys(KC_S, KC_B)) {
        // Leader, b => Types the below string
        register_code(KC_LCTL);   // Hold Control
        register_code(KC_LALT);   // Hold Option
        register_code(KC_LCMD);   // Hold Command
        register_code(KC_LSFT);   // Hold Shift
        tap_code(KC_LEFT);           // Tap B
        unregister_code(KC_LSFT); // Release Shift
        unregister_code(KC_LCMD); // Release Command
        unregister_code(KC_LALT); // Release Option
        unregister_code(KC_LCTL);
    }else if (leader_sequence_two_keys(KC_S, KC_F)) {
        // Leader, b => Types the below string
        register_code(KC_LCTL);   // Hold Control
        register_code(KC_LALT);   // Hold Option
        register_code(KC_LCMD);   // Hold Command
        register_code(KC_LSFT);   // Hold Shift
        tap_code(KC_RIGHT);           // Tap B
        unregister_code(KC_LSFT); // Release Shift
        unregister_code(KC_LCMD); // Release Command
        unregister_code(KC_LALT); // Release Option
        unregister_code(KC_LCTL);
    }else if (leader_sequence_three_keys(KC_S, KC_T, KC_W)) {
        // Leader, b => Close Browser Window
        register_code(KC_LCMD);   // Hold Command
        register_code(KC_LSFT);   // Hold Shift
        tap_code(KC_W);           // Tap B
        unregister_code(KC_LSFT); // Release Shift
        unregister_code(KC_LCMD); // Release Command
         ///omnifocus
    }else if (leader_sequence_two_keys(KC_O, KC_I)) {
        // Leader, b => Close Browser Window
        register_code(KC_LCMD);   // Hold Command
        register_code(KC_LSFT);   // Hold Shift
        SEND_STRING("]");
        unregister_code(KC_LSFT); // Release Shift
        unregister_code(KC_LCMD); // Release Command
    }else if (leader_sequence_two_keys(KC_O, KC_O)) {
        // Leader, b => Close Browser Window
        register_code(KC_LCMD);   // Hold Command
        register_code(KC_LSFT);   // Hold Shift
        SEND_STRING("[");
        unregister_code(KC_LSFT); // Release Shift
        unregister_code(KC_LCMD); // Release Command
     ///Bear
    }else if (leader_sequence_two_keys(KC_B, KC_B)) {
        // Leader, b => Bear - Bold
        register_code(KC_LCMD);   // Hold Command
        tap_code(KC_B);
        unregister_code(KC_LCMD); // Release Command
    }else if (leader_sequence_two_keys(KC_B, KC_I)) {
        // Leader, b => Bear - Italic
        register_code(KC_LCMD);   // Hold Command
        tap_code(KC_I);
        unregister_code(KC_LCMD); // Release Command
    }else if (leader_sequence_two_keys(KC_B, KC_U)) {
        // Leader, b => Bear - Underline
        register_code(KC_LCMD);   // Hold Command
        tap_code(KC_U);
        unregister_code(KC_LCMD); // Release Command
    }else if (leader_sequence_two_keys(KC_B, KC_S)) {
        // Leader, b => Bear - Strikethrough
        register_code(KC_LCMD);   // Hold Command
        register_code(KC_LSFT);   // Hold Command
        tap_code(KC_U);
        unregister_code(KC_LSFT); // Release Command
        unregister_code(KC_LCMD);   // Hold Command
    }else if (leader_sequence_two_keys(KC_B, KC_H)) {
        // Leader, b => Bear - Highlights
        register_code(KC_LCMD);   // Hold Command
        register_code(KC_LSFT);   // Hold Command
        tap_code(KC_M);
        unregister_code(KC_LSFT); // Release Command
        unregister_code(KC_LCMD);   // Hold Command
    }else if (leader_sequence_three_keys(KC_B, KC_B, KC_Q)) {
        // Leader, b => Bear - Underline
        send_string(">");
        tap_code(KC_SPACE);
    }else if (leader_sequence_three_keys(KC_B, KC_B, KC_T)) {
        // Leader, b => Bear - Underline
        send_string("- [ ]");
    }else if (leader_sequence_three_keys(KC_B, KC_B, KC_L)) {
        // Leader, b => Bear - Underline
        send_string("---");
    }else if (leader_sequence_three_keys(KC_B, KC_B, KC_C)) {
        // Leader, b => Bear - Underline
        send_string("``");
        tap_code(KC_LEFT);
    }else if (leader_sequence_three_keys(KC_B, KC_B, KC_B)) {
        // Leader, b => Bear - Bold
       send_string("####");
       tap_code(KC_LEFT);
       tap_code(KC_LEFT);
    }else if (leader_sequence_three_keys(KC_B, KC_B, KC_I)) {
        // Leader, b => Bear - Italic
        send_string("__");
        tap_code(KC_LEFT);
    }else if (leader_sequence_three_keys(KC_B, KC_B, KC_U)) {
        // Leader, b => Bear - Underline
        send_string("~~");
        tap_code(KC_LEFT);
    }else if (leader_sequence_three_keys(KC_B, KC_B, KC_S)) {
        // Leader, b => Bear - Strikethrough
        send_string("~~~~");
        tap_code(KC_LEFT);
        tap_code(KC_LEFT);
    }else if (leader_sequence_three_keys(KC_B, KC_B, KC_H)) {
        // Leader, b => Bear - Highlights
        send_string("====");
        tap_code(KC_LEFT);
        tap_code(KC_LEFT);
    }else if (leader_sequence_four_keys(KC_B, KC_B, KC_C, KC_B)) {
        // Leader, b => Bear - Underline
        tap_code(KC_RETURN);
        send_string("```");
        tap_code(KC_RETURN);
        send_string("```");
        tap_code(KC_RETURN);
        tap_code(KC_UP);
        tap_code(KC_UP);

    }
}


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
                    new_mode = RGB_MATRIX_TYPING_HEATMAP;  // Typing heatmap for Colemak
                    break;
                case MAC_BASE:
                    new_mode = RGB_MATRIX_TYPING_HEATMAP;
                   // rgb_matrix_sethsv(132, 102, 180);   // 🔹 Temporarily disable STARLIGHT
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
            rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
            break;
        case MAC_BASE:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
           // rgb_matrix_sethsv(132, 102, 180);   // 🔹 Disable STARLIGHT
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
        // FUN Layer: Only F, U, N should light up
        if (layer == FUN) {
            if (g_led_config.flags[i] & LED_FLAG_F) {
                rgb_matrix_set_color(i, RGB_RED);
            }
            if (g_led_config.flags[i] & LED_FLAG_U) {
                rgb_matrix_set_color(i, RGB_RED);
            }
            if (g_led_config.flags[i] & LED_FLAG_N) {
                rgb_matrix_set_color(i, RGB_RED);
            }
        }

        // WINDOWS Layer: Only W, I, N should light up
        if (layer == WINDOWS) {
            if (g_led_config.flags[i] & LED_FLAG_W) {
                rgb_matrix_set_color(i, RGB_RED);
            }
            if (g_led_config.flags[i] & LED_FLAG_I) {
                rgb_matrix_set_color(i, RGB_RED);
            }
            if (g_led_config.flags[i] & LED_FLAG_N) {
                rgb_matrix_set_color(i, RGB_RED);
            }
        }

          // SYMBOL Layer: Only S, Y, M should light up
            if (layer == SYM) {
                rgb_matrix_set_color(52, RGB_RED); // Light up 'S'
                rgb_matrix_set_color(39, RGB_RED); // Light up 'Y'
                rgb_matrix_set_color(70, RGB_RED); // Light up 'M'
            }

          // SYMBOL Layer: Only S, Y, M should light up
          if (layer == PIC) {
            rgb_matrix_set_color(43, RGB_RED); // Light up 'S'
            rgb_matrix_set_color(41, RGB_RED); // Light up 'Y'
            rgb_matrix_set_color(66, RGB_RED); // Light up 'M'
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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_tkl_ansi(
        ARC,      CHAT,     PERP,     TEXTE,    SNIP,     DROP,     ALFRED,   HOOK,     MUSE,     XMIND,    OOUT,     TRELLO,   DAYONE,     KC_MUTE,    FANTAS,   SPARK,    KC_F15,
        TILDE,    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     SLASH9,   BSLASH0,  KC_MINS,  KC_EQL,     BSPACE,     EAGLE,    DEVON,    FINDER,
        TEXTC,    KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     BRACKET,  CODE,       DELF,       OBSIDIAN, OFOCUS,   DRAFTS,
        ALFYHYPY, HOME_A,   ALT_S,    GUI_D,    SFT_F,    KC_G,     KC_H,     SFT_J,    GUI_K,    ALT_L,    KC_RSFT,  REPEAT,               KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     COMMA,    PERIOD,   QUESTION,             CAPW,                 KC_UP,
        CSPACEP,  CAPP_P,   XXXXXXX,                           SPACE,                                       XXXXXXX,  CAPP_N,   CSPACEN,    KC_RCTL,    KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_tkl_ansi(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,              XXXXXXX,
        XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,              XXXXXXX,              XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX),

    [CMAK_BASE] = LAYOUT_tkl_ansi(
        ALFRED,   HOOK,     CLEANSHT, DROP,     ARC,      TEXTE,    SNIP,     PERP,     CHAT,     MUSE,     TRELLO,   OOUT,     DAYONE,     KC_MUTE,    FANTAS,   SPARK,    ANYBOX,
        TILDE,    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     DELF,       EAGLE,    DEVON,    FINDER,
        ALFYHYPY, KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     USCR,     KC_J,     KC_L,     KC_U,     KC_Y,     PERIOD,   SLASH,      SYMPIC,    OBSIDIAN, OFOCUS,   DRAFTS,
        LEADY,    HOME_A,   HOME_R,   HOME_S,   HOME_T,   KC_G,     APOST,    KC_M,     HOME_N,   HOME_E,   HOME_I,   HOME_O,               TEXTC,
        ZED,                KC_X,     KC_C,     KC_D,     KC_V,     TDOSS,    TDDELW,   KC_K,     KC_H,     QUESTION, COMMA,                CAPW,                KC_UP,
        CSPACEP,  CAPP_P,   SELBC,                                     SPACE,                               SELFC,    CAPP_N,   CSPACEN,    KC_LCTL,    KC_LEFT,  KC_DOWN,  KC_RGHT),

    [EXTEND] = LAYOUT_tkl_ansi(
        POWER,    MCNTRL,   LNCHPAD,  KC_PGUP,  _______,  _______,  _______,  ARC_B,    ARC_F,    REWIND,   PLAY,     NEXT,     SPOTIFY,    RGB_TOG,    RGB_RMOD, RGB_MOD,  BAT_LVL,
        TILDE,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    PAGEUP,   KC_F9,    KC_F10,   KC_F11,     RGB_SPI,    RGB_VAI,  RGB_HUI,  RGB_SAI,
        KC_LCTL,  MSEWHLRI, MSEWHLDO, MSEWHLLE, MSEWHLLE, _______,  MOUSEUP,  _______,  HOME,     KC_UP,    END,      _______,  _______,    RGB_SPD,    RGB_VAD,  RGB_HUD,  RGB_SAD,
        ALFYHYPY, KC_LALT,  MSEWHLUP, KC_LGUI,  KC_LSFT,  MOUSELT,  MOUSEDN,  MOUSERT,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,              _______,
        UNDO,               CUT,      COPY,     DUPLICA,  PASTE,    MSEC1,    MSEC4,    MSEC2,    DELWF,    PAGEDN,   DELWB,                _______,              _______,
        SLINE_P,  SWORD_B,  CMOVE_P,                                 _______,                               CMOVE_N,  SELWORD,  SLINE,      _______,    _______,  _______,  _______),

    [WINDOWS] = LAYOUT_tkl_ansi(
        FULLSCR,  WIN1_1,   WIN1_2,   WIN1_3,   _______,  WIN4_1,   WIN4_2,   WIN4_3,   WIN4_4,   WIN5_1,   WIN5_2,   WIN5_3,   WIN5_4,     _______,    _______,  _______,  _______,
        WIN_CEN,  WIN2_1,   WIN2_2,   WIN2_3,   WIN2_4,   WIN2_5,   WIN2_6,   WIN2_7,   _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        WIN_EXT,  WIN3_1,   WIN3_2,   WIN3_3,   WIN3_4,   WIN3_5,   WIN3_6,   WIN3_7,   _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  WIN6_1,   WIN6_2,   WIN6_3,   WIN6_4,   WIN6_5,   _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            WIN7_1,   WIN7_2,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,              _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    _______,  _______,  _______),

    [FUN] = LAYOUT_tkl_ansi(
        SYSSET,   PASS,     PORTAL,   MSG,      WHATSAPP, ELGATO,   LDECK,    _______,  _______,  SLVPREV,  SLVPP,    SLVNEXT,  SLEEVE,     SLVMUTE,    SLVLIKE,  _______,  SPEED,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    KMESTRO,  VSCODE,   ITERM,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,              _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    _______,  _______,  _______),

    [SYM] = LAYOUT_tkl_ansi(
        XXXXXXX,  POUND,    DOLLAR,   EURO,     YEN,      OG,       TM,       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        BACKT,    LB,       RB,       BB,       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  LAARROW,  LARROW,   ARROW,    AARROW,   AND,        XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        TIL,      SBL,      SBR,      SBC,      SBTD,     TROSA,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  PLUS,     EQUALS,   STAR,       XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  BRL,      BRR,      BRB,      DONE,     INF,      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  MINUS,    UNSC,                 XXXXXXX,
        XXXXXXX,            CBL,      CBR,      CBB,      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,              XXXXXXX,              XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX),

    [PIC] = LAYOUT_tkl_ansi(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,              XXXXXXX,
        XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,              XXXXXXX,              XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX),

};

// clang-format on
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
   ///  [ADM] = {ENCODER_CCW_CW(SLVVOLD, SLVVOLU)},
};
#endif // ENCODER_MAP_ENABLE

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
