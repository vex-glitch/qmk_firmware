//////////////////////////////////////////////✨I N C L U D E S ✨//////////////////////////////////////////////
#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "quantum.h"
#include "features/autocorrection.h"
//////////////////////////////////////////////✨L A Y E R S ✨//////////////////////////////////////////////
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
//////////////////////////////////////////////✨C A P S  B L I N K ✨//////////////////////////////////////////////
    static bool is_caps_active_flag = false;
    static uint32_t caps_blink_timer = 0;
    #define CAPS_LED 0
//////////////////////////////////////////////✨T A P D A N C E S ✨//////////////////////////////////////////////
enum {
/////////////////////////////////////////////////✨F  K E Y S ✨/////////////////////////////////////////////////
    TD_ALFRED,
    TD_HOOK,
    TD_CLEANSHOT,
    TD_DROP,
    TD_ARC,
    TD_SNIPLAB,
    TD_PERP,
    TD_CHAT,
    TD_CLAUDE,
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
    TD_OBSIDIAN,
    TD_OMNIFOCUS,
    TD_BBEDIT,
/////////////////////////////////////✨C O L E M A K  L A Y E R  T A P D A N C E S ✨//////////////////////////////////////////
    TD_ESCAPE,
    TD_TAB,
    TD_HYPENATOR,
    TD_ZSETNOT,
    TD_QMACRO,
    TD_MIDKEY,
    TD_SPACE,
    TD_FILEFRED,
    TD_SCREEN,
    TD_CAPS,
    TD_ALFMEH2,
    TD_HASHAT,
    TD_SMILE,
    TD_SLASH,
    TD_QUESTION,
    TD_PERIOD,
    TD_COMMA,
    TD_DELWORD,
    TD_USCR,
    TD_LEADAPP,
    TD_DELIMIT,
    TD_KEYFORL,
    TD_KEYSNIP,
///////////////////////////////////////✨E X T E N D  L A Y E R  T A P D A N C E S ✨//////////////////////////////////////
    TD_TIL,
//////////////////////////////////////✨W I N D O W S  L A Y E R  T A P D A N C E S ✨////////////////////////////////////
    TD_FULL,
/////////////////////////////////////////✨F U N  L A Y E R  T A P D A N C E S ✨////////////////////////////////////////
    TD_PORT,
    TD_ENDEL,
    TD_SLEEVE,
///////////////////////////////////////✨S Y M B O L  L A Y E R  T A P D A N C E S ✨//////////////////////////////////////////
    TD_RB,
    TD_SBL,
    TD_SBR,
    TD_BACKT,
    TD_EQUALS,
    TD_STAR,
    TD_UNSC,
  };
////////////////////////////////////////✨T A P  H O L D  D E C L A R A T I O N S ✨//////////////////////////////////////////
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
////////////////////////////////////////////✨D E F I N I T I O N S ✨////////////////////////////////////////////////
//////////////////////////////////////////////✨F  K E Y  D E F S ✨//////////////////////////////////////////////
    #define ALFRED    TD(TD_ALFRED)
    #define HOOK      TD(TD_HOOK)
    #define CLEANSHT  TD(TD_CLEANSHOT)
    #define DROP      TD(TD_DROP)
    #define ARC       TD(TD_ARC)
    #define SNIP      TD(TD_SNIPLAB)
    #define PERP      TD(TD_PERP)
    #define CHAT      TD(TD_CHAT)
    #define CLAUDE	  TD(TD_CLAUDE)
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
    #define OBSIDIAN  TD(TD_OBSIDIAN)
    #define OFOCUS    TD(TD_OMNIFOCUS)
    #define BBEDIT	  TD(TD_BBEDIT)
//////////////////////////////////////////////✨C O L E M A K  D E F S ✨//////////////////////////////////////////////
    #define ESCAPE    TD(TD_ESCAPE)
    #define TAB       TD(TD_TAB)
    #define HYPENATOR TD(TD_HYPENATOR)
    #define ZSETNOT	  TD(TD_ZSETNOT)
    #define QMACRO    TD(TD_QMACRO)
    #define MIDKEY	  TD(TD_MIDKEY)
    #define SPACE     TD(TD_SPACE)
    #define FILEFRED  TD(TD_FILEFRED)
    #define SCREEN    TD(TD_SCREEN)
    #define CAPW      TD(TD_CAPS)
    #define ALFMEH2   TD(TD_ALFMEH2)
    #define HASHAT    TD(TD_HASHAT)
    #define SMILE     TD(TD_SMILE)
    #define SLASH     TD(TD_SLASH)
    #define QUESTION  TD(TD_QUESTION)
    #define PERIOD    TD(TD_PERIOD)
    #define COMMA     TD(TD_COMMA)
    #define DELWORD   TD(TD_DELWORD)
    #define USCR      TD(TD_USCR)
    #define LEADAPP	  TD(TD_LEADAPP)
    #define DELIMIT	  TD(TD_DELIMIT)
    #define KEYFORL	  TD(TD_KEYFORL)
    #define KEYSNIP	  TD(TD_KEYSNIP)
//////////////////////////////////////////////✨E X T E N D  D E F S ✨//////////////////////////////////////////////
    #define TIL       TD(TD_TIL)
/////////////////////////////////////////////✨W I N D O W S  D E F S ✨//////////////////////////////////////////////
    #define FULL      TD(TD_FULL)
//////////////////////////////////////////////✨F U N  D E F S ✨//////////////////////////////////////////////
    #define PORT      TD(TD_PORT)
    #define ENDEL	  TD(TD_ENDEL)
    #define SLEEVE    TD(TD_SLEEVE)
//////////////////////////////////////////////✨S Y M B O L  D E F S ✨//////////////////////////////////////////////
    #define RB        TD(TD_RB)
    #define SBL       TD(TD_SBL)
    #define SBR       TD(TD_SBR)
    #define BACKT     TD(TD_BACKT)
    #define EQUALS    TD(TD_EQUALS)
    #define STAR      TD(TD_STAR)
    #define UNSC      TD(TD_UNSC)
//////////////////////////////////////////////✨M I S C  D E F S ✨//////////////////////////////////////////////
    #define MOUSEUP   KC_MS_UP
    #define MOUSEDN   KC_MS_DOWN
    #define MOUSELT   KC_MS_LEFT
    #define MOUSERT   KC_MS_RIGHT
    #define MSEWHLUP  KC_MS_WH_UP
    #define MSEWHLDO  KC_MS_WH_DOWN
    #define MSEWHLLE  KC_MS_WH_LEFT
    #define MSEWHLRI  KC_MS_WH_RIGHT
    #define MSEC1     KC_MS_BTN1
    #define MSEC2     KC_MS_BTN2
    #define MSEC3     KC_MS_BTN3
    #define MSEC4     KC_MS_BTN4
    #define PAGEUP    KC_PGUP
    #define PAGEDN    KC_PGDN
    #define HOME      KC_HOME
    #define END       KC_END
    #define PLAY      KC_MEDIA_PLAY_PAUSE
    #define REWIND    KC_MEDIA_PREV_TRACK
    #define NEXT      KC_MEDIA_FAST_FORWARD
    #define MCNTRL    KC_MISSION_CONTROL
    #define LNCHPAD   KC_LAUNCHPAD
    #define POWER     KC_SYSTEM_POWER
    #define BBACK     KC_WWW_BACK
    #define BFORW     KC_WWW_FORWARD
////////////////////////////////////////✨F  K E Y  T A P  F U N C T I O N S ✨/////////////////////////////////////////
// ALFRED::TapDance 🪩
void dance_alfred_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F5));	// ⇧ F5 :: 2025.05.18-09:56
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F5));	// ⎈ F5 :: 2025.05.18-09:57
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F5));	// ⎇ F5 :: 2025.05.18-09:57
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F5)));	// ⎈⇧ F5 :: 2025.05.18-09:57
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F5)));	// ⇧⎇ F5 :: 2025.05.18-09:58
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F5)));	// ⎈⎇ F5 :: 2025.05.18-09:59
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F5));	// MEH F5 :: 2025.05.18-09:59
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F5)));	// ⎇⌘ F5 :: 2025.05.18-09:59
	}
}
void dance_alfred_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
    layer_clear();
}
 // HOOKMARK::TapDance 🪩
void dance_hook_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F6));	// ⇧ F6 :: 2025.05.18-10:21
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F6));	// ⎈ F6 :: 2025.05.18-10:21
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F6));	// ⎇ F6 :: 2025.05.18-10:22
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F6)));	// ⎈⇧ F6 :: 2025.05.18-10:22
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F6)));	// ⇧⎇ F6 :: 2025.05.18-10:22
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F6)));	// ⎈⎇ F6 :: 2025.05.18-10:22
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F6));	// MEH F6 :: 2025.05.18-10:23
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F6)));	// ⎇⌘ F6 :: 2025.05.18-10:23
	}
}
void dance_hook_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
    layer_clear();
}
// CLEANSHOT::TapDance 🪩
void dance_cleanshot_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F7));	// ⇧ F7 :: 2025.05.18-10:27
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F7));	// ⎈ F7 :: 2025.05.18-10:27
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F7));	// ⎇ F7 :: 2025.05.18-10:28
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F7)));	// ⎈⇧ F7 :: 2025.05.18-10:28
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F7)));	// ⇧⎇ F7 :: 2025.05.18-10:28
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F7)));	// ⎈⎇ F7 :: 2025.05.18-10:28
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F7));	// MEH F7 :: 2025.05.18-10:29
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F7)));	// ⎇⌘ F7 :: 2025.05.18-10:29
	}
}
void dance_cleanshot_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// DROP::TapDance 🪩
void dance_drop_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F8));	// ⇧ F8 :: 2025.05.18-10:32
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F8));	// ⎈ F8 :: 2025.05.18-10:33
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F8));	// ⎇ F8 :: 2025.05.18-10:33
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F8)));	// ⎈⇧ F8 :: 2025.05.18-10:33
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F8)));	// ⇧⎇ F8 :: 2025.05.18-10:33
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F8)));	// ⎈⎇ F8 :: 2025.05.18-10:34
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F8));	// MEH F8 :: 2025.05.18-10:34
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F8)));	// ⎇⌘ F8 :: 2025.05.18-10:34
	}
}
void dance_drop_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// SNIPLAB::TapDance 🪩
void dance_sniplab_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F9));	// ⇧ F9 :: 2025.05.18-10:38
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F9));	// ⎈ F9 :: 2025.05.18-10:38
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F9));	// ⎇ F9 :: 2025.05.18-10:39
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F9)));	// ⎈⇧ F9 :: 2025.05.18-10:39
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F9)));	// ⇧⎇ F9 :: 2025.05.18-10:39
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F9)));	// ⎈⎇ F9 :: 2025.05.18-10:39
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F9));	// MEH F9 :: 2025.05.18-10:40
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F9)));	// ⎇⌘ F9 :: 2025.05.18-10:40
	}
}
void dance_sniplab_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// ARC::TapDance 🪩
void dance_arc_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F10));	// ⇧ F10 :: 2025.05.18-10:41
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F10));	// ⎈ F10 :: 2025.05.18-10:41
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F10));	// ⎇ F10 :: 2025.05.18-10:41
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F10)));	// ⎈⇧ F10 :: 2025.05.18-10:41
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F10)));	// ⇧⎇ F10 :: 2025.05.18-10:41
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F10)));	// ⎈⎇ F10 :: 2025.05.18-10:42
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F10));	// MEH F10 :: 2025.05.18-10:42
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F10)));	// ⎇⌘ F10 :: 2025.05.18-10:42
	}
}
void dance_arc_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// PERP::TapDance 🪩
void dance_perp_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F11));	// ⇧ F11 :: 2025.05.18-10:43
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F11));	// ⎈ F11 :: 2025.05.18-10:44
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F11));	// ⎇ F11 :: 2025.05.18-10:44
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F11)));	// ⎈⇧ F11 :: 2025.05.18-10:44
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F11)));	// ⇧⎇ F11 :: 2025.05.18-10:44
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F11)));	// ⎈⎇ F11 :: 2025.05.18-10:44
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F11));	// MEH F11 :: 2025.05.18-10:45
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F11)));	// ⎇⌘ F11 :: 2025.05.18-10:45
	}
}
void dance_perp_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// CHAT::TapDance 🪩
void dance_chat_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F12));	// ⇧ F12 :: 2025.05.18-10:46
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F12));	// ⎈ F12 :: 2025.05.18-10:46
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F12));	// ⎇ F12 :: 2025.05.18-10:46
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F12)));	// ⎈⇧ F12 :: 2025.05.18-10:46
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F12)));	// ⇧⎇ F12 :: 2025.05.18-10:46
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F12)));	// ⎈⎇ F12 :: 2025.05.18-10:47
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F12));	// MEH F12 :: 2025.05.18-10:47
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F12)));	// ⎇⌘ F12 :: 2025.05.18-10:47
	}
}
void dance_chat_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// CLAUDE::TapDance 🪩
void dance_claude_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F13));	// ⇧ F13 :: 2025.05.19-07:46
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F13));	// ⎈ F13 :: 2025.05.19-07:47
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F13));	// ⎇ F13 :: 2025.05.19-07:47
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F13)));	// ⎈⇧ F13 :: 2025.05.19-07:47
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F13)));	// ⇧⎇ F13 :: 2025.05.19-07:47
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F13)));	// ⎈⎇ F13 :: 2025.05.19-07:47
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F13));	// MEH F13 :: 2025.05.19-07:48
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F13)));	// ⎇⌘ F13 :: 2025.05.19-07:48
	}
}
void dance_claude_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// OOUTLINER::TapDance 🪩
void dance_ooutliner_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F14));	// ⇧ F14 :: 2025.05.19-07:46
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F14));	// ⎈ F14 :: 2025.05.19-07:47
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F14));	// ⎇ F14 :: 2025.05.19-07:47
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F14)));	// ⎈⇧ F14 :: 2025.05.19-07:47
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F14)));	// ⇧⎇ F14 :: 2025.05.19-07:47
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F14)));	// ⎈⎇ F14 :: 2025.05.19-07:47
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F14));	// MEH F14 :: 2025.05.19-07:48
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F14)));	// ⎇⌘ F14 :: 2025.05.19-07:48
	}
}
void dance_ooutliner_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// MUSE::TapDance 🪩
void dance_muse_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F15));	// ⇧ F15 :: 2025.05.19-07:56
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F15));	// ⎈ F15 :: 2025.05.19-07:57
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F15));	// ⎇ F15 :: 2025.05.19-07:57
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F15)));	// ⎈⇧ F15 :: 2025.05.19-07:57
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F15)));	// ⇧⎇ F15 :: 2025.05.19-07:57
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F15)));	// ⎈⎇ F15 :: 2025.05.19-07:57
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F15));	// MEH F15 :: 2025.05.19-07:58
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F15)));	// ⎇⌘ F15 :: 2025.05.19-07:58
	}
}
void dance_muse_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// TRELLO::TapDance 🪩
void dance_trello_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F16));	// ⇧ F16 :: 2025.05.19-08:19
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F16));	// ⎈ F16 :: 2025.05.19-08:19
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F16));	// ⎇ F16 :: 2025.05.19-08:19
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F16)));	// ⎈⇧ F16 :: 2025.05.19-08:19
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F16)));	// ⇧⎇ F16 :: 2025.05.19-08:19
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F16)));	// ⎈⎇ F16 :: 2025.05.19-08:19
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F16));	// MEH F16 ::2025.05.19-08:19
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F16)));	// ⎇⌘ F16 :: 2025.05.19-08:19
	}
}
void dance_trello_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// DAYONE::TapDance 🪩
void dance_dayone_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F17));	// ⇧ F17 :: 2025.05.19-08:19
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F17));	// ⎈ F17 :: 2025.05.19-08:19
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F17));	// ⎇ F17 :: 2025.05.19-08:19
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F17)));	// ⎈⇧ F17 :: 2025.05.19-08:19
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F17)));	// ⇧⎇ F17 :: 2025.05.19-08:19
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F17)));	// ⎈⎇ F17 :: 2025.05.19-08:19
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F17));	// MEH F17 ::2025.05.19-08:19
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F17)));	// ⎇⌘ F17 :: 2025.05.19-08:19
	}
}
void dance_dayone_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// FANTASTICAL::TapDance 🪩
void dance_fantastical_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F18));	// ⇧ F18 :: 2025.05.19-08:19
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F18));	// ⎈ F18 :: 2025.05.19-08:19
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F18));	// ⎇ F18 :: 2025.05.19-08:19
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F18)));	// ⎈⇧ F18 :: 2025.05.19-08:19
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F18)));	// ⇧⎇ F18 :: 2025.05.19-08:19
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F18)));	// ⎈⎇ F18 :: 2025.05.19-08:19
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F18));	// MEH F18 ::2025.05.19-08:19
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F18)));	// ⎇⌘ F18 :: 2025.05.19-08:19
	}
}
void dance_fantastical_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// SPARK::TapDance 🪩
void dance_spark_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F19));	// ⇧ F19 :: 2025.05.19-08:19
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F19));	// ⎈ F19 :: 2025.05.19-08:19
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F19));	// ⎇ F19 :: 2025.05.19-08:19
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F19)));	// ⎈⇧ F19 :: 2025.05.19-08:19
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F19)));	// ⇧⎇ F19 :: 2025.05.19-08:19
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F19)));	// ⎈⎇ F19 :: 2025.05.19-08:19
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F19));	// MEH F19 ::2025.05.19-08:19
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F19)));	// ⎇⌘ F19 :: 2025.05.19-08:19
	}
}
void dance_spark_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// ANYBOX::TapDance 🪩
void dance_anybox_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F20));	// ⇧ F20 :: 2025.05.19-08:19
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F20));	// ⎈ F20 :: 2025.05.19-08:19
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F20));	// ⎇ F20 :: 2025.05.19-08:19
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F20)));	// ⎈⇧ F20 :: 2025.05.19-08:19
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F20)));	// ⇧⎇ F20 :: 2025.05.19-08:19
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F20)));	// ⎈⎇ F20 :: 2025.05.19-08:19
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F20));	// MEH F20 ::2025.05.19-08:19
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F20)));	// ⎇⌘ F20 :: 2025.05.19-08:19
	}
}
void dance_anybox_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// EAGLE::TapDance 🪩
void dance_eagle_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_PGUP));	// ⇧ F21 :: 2025.05.19-08:19
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_PGUP));	// ⎈ F21 :: 2025.05.19-08:19
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_PGUP));	// ⎇ F21 :: 2025.05.19-08:19
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_PGUP)));	// ⎈⇧ F21 :: 2025.05.19-08:19
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_PGUP)));	// ⇧⎇ F21 :: 2025.05.19-08:19
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_PGUP)));	// ⎈⎇ F21 :: 2025.05.19-08:19
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_PGUP));	// MEH F21 ::2025.05.19-08:19
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_PGUP)));	// ⎇⌘ F21 :: 2025.05.19-08:19
	}
}
void dance_eagle_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// DEVONTHINK::TapDance 🪩
void dance_devonthink_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_PGDN));	// ⇧ F22 :: 2025.05.19-08:19
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_PGDN));	// ⎈ F22 :: 2025.05.19-08:19
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_PGDN));	// ⎇ F22 :: 2025.05.19-08:19
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_PGDN)));	// ⎈⇧ F22 :: 2025.05.19-08:19
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_PGDN)));	// ⇧⎇ F22 :: 2025.05.19-08:19
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_PGDN)));	// ⎈⎇ F22 :: 2025.05.19-08:19
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_PGDN));	// MEH F22 :: 2025.05.19-08:19
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_PGDN)));	// ⎇⌘ F22 :: 2025.05.19-08:19
	}
}
void dance_devonthink_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// FINDER::TapDance 🪩
void dance_finder_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_HOME));	// ⇧ F23 :: 2025.05.19-08:19
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_HOME));	// ⎈ F23 :: 2025.05.19-08:19
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_HOME));	// ⎇ F23 :: 2025.05.19-08:19
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_HOME)));	// ⎈⇧ F23 :: 2025.05.19-08:19
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_HOME)));	// ⇧⎇ F23 :: 2025.05.19-08:19
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_HOME)));	// ⎈⎇ F23 :: 2025.05.19-08:19
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_HOME));	// MEH F23 :: 2025.05.19-08:19
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_HOME)));	// ⎇⌘ F23 :: 2025.05.19-08:19
	}
}
void dance_finder_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// OMNIFOCUS::TapDance 🪩
void dance_omnifocus_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F4));   // ⇧ F4 :: 2025.05.19-08:26
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F4));   // ⎈ F4 :: 2025.05.19-08:27
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F4));   // ⎇ F4 :: 2025.05.19-08:27
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F4)));    // ⎈⇧ F4 :: 2025.05.19-08:27
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F4)));    // ⇧⎇ F4 :: 2025.05.19-08:27
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F4)));    // ⎈⎇ F4 :: 2025.05.19-08:27
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F4)); // MEH F4 :: 2025.05.19-08:28
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F4)));    // ⎇⌘ F4 :: 2025.05.19-08:28
	}
}
void dance_omnifocus_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// OBSIDIAN::TapDance 🪩
void dance_obsidian_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F3));	// ⇧ F3 :: 2025.05.19-08:19
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F3));	// ⎈ F3 :: 2025.05.19-08:19
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F3));	// ⎇ F3 :: 2025.05.19-08:19
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F3)));	// ⎈⇧ F3 :: 2025.05.19-08:19
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F3)));	// ⇧⎇ F3 :: 2025.05.19-08:19
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F3)));	// ⎈⎇ F3 :: 2025.05.19-08:19
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F3));	// MEH F3 :: 2025.05.19-08:19
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F3)));	// ⎇⌘ F3 :: 2025.05.19-08:19
    }
}
void dance_obsidian_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// BBEDIT::TapDance 🪩
void dance_bbedit_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(S(KC_F2));	// ⇧ F2 :: 2025.05.19-08:18
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F2));	// ⎈ F2 :: 2025.05.19-08:18
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F2));	// ⎇ F2 :: 2025.05.19-08:18
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F2)));	// ⎈⇧ F2 :: 2025.05.19-08:18
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F2)));	// ⇧⎇ F2 :: 2025.05.19-08:18
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F2)));	// ⎈⎇ F2 :: 2025.05.19-08:19
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F2));	// MEH F2 :: 2025.05.19-08:19
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F2)));	// ⎇⌘ F2 :: 2025.05.19-08:19
	}
}
void dance_bbedit_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
/////////////////////////////////////////✨C O L E M A K  T A P  F U N C T I O N S ✨//////////////////////////////////////////////
// ESCAPE::TapDance 🪩
void dance_escape_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(G(KC_H));	// ⌘ H :: 2025.05.19-09:01
	} else if (state->count == 1 && !state->pressed) {
		tap_code(KC_ESC);	// ⚫︎KC_ESC :: 2025.05.19-09:02
	} else if (state->count == 2 && state->pressed) {
		tap_code16(G(KC_Q));	// ⌘ Q :: 2025.05.19-09:02
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(G(KC_W));	// ⌘ W :: 2025.05.19-09:02
	}
}
void dance_escape_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// TAB::TapDance 🪩
void dance_tab_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		register_code(KC_LCTL);	// Send /⬇︎MEH :: 2025.05.19-09:11
        register_code(KC_LSFT); // Send /⬇︎LSFT :: 2025.05.19-09:42
        register_code(KC_LALT); // Send /⬇︎LALT :: 2025.05.19-09:42
	} else if (state->count == 1 && !state->pressed) {
		tap_code(KC_TAB);	// ⚫︎KC_TAB :: 2025.05.19-09:11
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(S(A(G(KC_TAB))));	// ⇧⎇⌘ TAB :: 2025.05.19-09:12
	}
}
void dance_tab_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// HYPENATOR::TapDance 🪩
void dance_hypenator_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		register_code(KC_LGUI);	// Send /⬇︎LGUI :: 2025.05.19-13:35
		register_code(KC_LSFT);	// Send /⬇︎LSFT :: 2025.05.19-13:35
		register_code(KC_LALT);	// Send /⬇︎LALT :: 2025.05.19-13:36
		register_code(KC_LCTL);	// Send /⬇︎LCTL :: 2025.05.19-13:36
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(KC_F1));	// ⎈ F1 :: 2025.05.19-13:36
	} else if (state->count == 2 && state->pressed) {
		tap_code16(A(KC_F1));	// ⎇ F1 :: 2025.05.19-13:37
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(KC_F1)));	// ⎈⇧ F1 :: 2025.05.19-13:37
	} else if (state->count == 3 && state->pressed) {
		tap_code16(S(A(KC_F1)));	// ⇧⎇ F1 :: 2025.05.19-13:37
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(A(KC_F1)));	// ⎈⎇ F1 :: 2025.05.19-13:37
	} else if (state->count == 4 && state->pressed) {
		tap_code16(MEH(KC_F1));	// MEH F1 :: 2025.05.19-13:38
	} else if (state->count == 4 && !state->pressed) {
		tap_code16(A(G(KC_F1)));	// ⎇⌘ F1 :: 2025.05.19-13:38
	}
}
void dance_hypenator_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// ZSETNOT::TapDance 🪩
void dance_zsetnot_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		tap_code16(G(KC_Z));	// ⌘ Z :: 2025.05.19-09:47
	} else if (state->count == 1 && !state->pressed) {
		tap_code(KC_Z);	// ⚫︎KC_Z :: 2025.05.19-09:47
	} else if (state->count == 2 && state->pressed) {
		tap_code16(G(KC_COMM));	// ⌘ , :: 2025.05.19-09:48
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(S(A(G(KC_MINS))));	// ⇧⎇⌘ − :: 2025.05.19-09:48
	}
}
void dance_zsetnot_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// QMACRO::TapDance 🪩
void dance_qmacro_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		layer_on(FUN);	//  :: 2025.05.19-10:28
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(HYPR(KC_F1));	// HYPR F1 :: 2025.05.19-10:29
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(A(KC_H)));	// ⎈⎇ H :: 2025.05.19-10:29
	}
}
void dance_qmacro_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// MIDKEY::TapDance 🪩
void dance_midkey_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {	// 💀 UNIVERSAL COMMAND PALETTE
		tap_code16(S(A(G(KC_K))));	// ⇧⎇⌘ K :: 2025.05.19-13:58
	} else if (state->count == 1 && !state->pressed) {	// 💀 CLIPBOARD HISTORY
		tap_code16(C(S(G(KC_X))));	// ⎈⇧⌘ X :: 2025.05.19-13:59
	} else if (state->count == 2 && state->pressed) {	// 💀 SCREENSHOT HISTORY
		tap_code16(MEH(KC_X));	// MEH X :: 2025.05.19-13:59
	} else if (state->count == 2 && !state->pressed) {	// 💀 UNIVERSAL ACTIONS
		tap_code16(MEH(KC_L));	// MEH L :: 2025.05.19-13:59
	}
}
void dance_midkey_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// SPACE::TapDance 🪩
void dance_space_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		layer_on(EXTEND);	//  :: 2025.05.19-11:06
	} else if (state->count == 1 && !state->pressed) {
		tap_code(KC_SPC);	// ⚫︎KC_SPC :: 2025.05.19-11:07
	} else if (state->count == 2 && state->pressed) {
		tap_code16(S(KC_ENT));	// ⇧ ↵ :: 2025.05.19-11:07
	} else if (state->count == 2 && !state->pressed) {
		tap_code(KC_ENT);	// ⚫︎KC_ENT :: 2025.05.19-11:08
	}
}
void dance_space_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// FILEFRED::TapDance 🪩
void dance_filefred_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {	// 💀 LAYER WINDOWS
		layer_on(WINDOWS);	//  :: 2025.05.19-14:39
	} else if (state->count == 1 && !state->pressed) {	// 💀 OPEN FILE
		SEND_STRING(SS_TAP(X_F3) SS_DELAY(50) "opfilen ");	// Send  (⚫︎F3 🕘50 "open") :: 2025.05.19-14:39
	} else if (state->count == 2 && state->pressed) {	// 💀 INSIDE FILE
		SEND_STRING(SS_TAP(X_F3) SS_DELAY(50) "ifilen ");	// Send  (⚫︎F3 🕘50 "in") :: 2025.05.19-14:40
	} else if (state->count == 2 && !state->pressed) {	// 💀 FIND FILE
		SEND_STRING(SS_TAP(X_F3) SS_DELAY(50) "fifilend ");	// Send  (⚫︎F3 🕘50 "find") :: 2025.05.19-14:41
	} else if (state->count == 3 && !state->pressed) {	// 💀 DYNAMIC FILE SEARCH
		SEND_STRING(SS_TAP(X_F3) SS_DELAY(50) "ff ");	// Send  (⚫︎F3 🕘50 "ff") :: 2025.05.19-14:41
	}
}
void dance_filefred_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// SCREEN::TapDance 🪩
void dance_screen_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		register_code(KC_LCTL);	// Send /⬇︎LCTL :: 2025.05.19-15:04
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(S(G(KC_1))));	// ⎈⇧⌘ 1 :: 2025.05.19-15:04
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(G(KC_2))));	// ⎈⇧⌘ 2 :: 2025.05.19-15:05
	} else if (state->count == 3 && !state->pressed) {
		tap_code16(C(S(G(KC_3))));	// ⎈⇧⌘ 3 :: 2025.05.19-15:05
	}
}
void dance_screen_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// CAPS::TapDance 🪩
void dance_caps_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {	// 💀 UNDO
		tap_code16(S(G(KC_Z)));	// ⇧⌘ Z :: 2025.05.19-15:24
	} else if (state->count == 1 && !state->pressed) {	// 💀 ONE SHOT SHIFT
		set_oneshot_mods(MOD_LSFT);	//  :: 2025.05.19-15:24
	} else if (state->count == 2 && !state->pressed) {	// 💀 CAPS WORD
		caps_word_on();
		is_caps_active_flag = true;
		caps_blink_timer = timer_read32();	//  :: 2025.05.19-15:24
	}
}
void dance_caps_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// ALFMEH2::TapDance 🪩
void dance_alfmeh2_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		register_code(KC_LGUI);	// Send /⬇︎LGUI :: 2025.05.19-15:55
		register_code(KC_LSFT);	// Send /⬇︎LSFT :: 2025.05.19-15:55
		register_code(KC_LCTL);	// Send /⬇︎LCTL :: 2025.05.19-15:55
	} else if (state->count == 1 && !state->pressed) {
		tap_code(KC_F3);	// ⚫︎KC_F3 :: 2025.05.19-15:55
	} else if (state->count == 2 && !state->pressed) {
		SEND_STRING(SS_TAP(X_F3) SS_DELAY(50) "! ");	// Send  (⚫︎F3 🕘50 "! ") :: 2025.05.19-15:56
		set_oneshot_mods(MOD_LSFT);	//  :: 2025.05.19-15:56
	}
}
void dance_alfmeh2_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// HASHAT::TapDance 🪩
void dance_hashat_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		layer_on(SYM);	//  :: 2025.05.19-16:27
	} else if (state->count == 1 && !state->pressed) {
		SEND_STRING("#");	// Send  ("#") :: 2025.05.19-16:28
	} else if (state->count == 2 && state->pressed) {
		SEND_STRING("&");	// Send  ("&") :: 2025.05.19-16:28
	} else if (state->count == 2 && !state->pressed) {
		SEND_STRING("@");	// Send  ("@") :: 2025.05.19-16:28
	}
}
void dance_hashat_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// SMILE::TapDance 🪩
void dance_smile_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		SEND_STRING("+");	// Send  ("+") :: 2025.05.19-16:30
	} else if (state->count == 1 && !state->pressed) {
		SEND_STRING("=");	// Send  ("=") :: 2025.05.19-16:30
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(G(KC_SPC)));	// ⎈⌘ ␣ :: 2025.05.19-16:30
	}
}
void dance_smile_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// SLASH::TapDance 🪩
void dance_slash_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		SEND_STRING("|");	// Send  ("|") :: 2025.05.19-16:35
	} else if (state->count == 1 && !state->pressed) {
		tap_code(KC_SLSH);	// ⚫︎KC_SLSH :: 2025.05.19-16:35
	} else if (state->count == 2 && !state->pressed) {
		tap_code(KC_BSLS);	// ⚫︎KC_BSLS :: 2025.05.19-16:35
	}
}
void dance_slash_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// QUESTION::TapDance 🪩
void dance_question_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		SEND_STRING("?");	// Send  ("?") :: 2025.05.19-16:37
	} else if (state->count == 1 && !state->pressed) {
		SEND_STRING("? ");	// Send  ("? ") :: 2025.05.19-16:37
		set_oneshot_mods(MOD_LSFT);    //   :: 2025.05.22-13:21
	} else if (state->count == 2 && state->pressed) {
		SEND_STRING("!");	// Send  ("!") :: 2025.05.19-16:38
	} else if (state->count == 2 && !state->pressed) {
		SEND_STRING("! ");	// Send  ("! ") :: 2025.05.19-16:38
		set_oneshot_mods(MOD_LSFT);    //   :: 2025.05.22-13:20
	}
}
void dance_question_reset(tap_dance_state_t *state, void *user_data) {
	layer_clear();
}
// PERIOD::TapDance 🪩
void dance_period_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		SEND_STRING(".");	// Send  (".") :: 2025.05.19-16:39
	} else if (state->count == 1 && !state->pressed) {
		SEND_STRING(". ");	// Send  (". ") :: 2025.05.19-16:40
        set_oneshot_mods(MOD_LSFT);    //   :: 2025.05.22-13:19
    } else if (state->count == 2 && state->pressed) {
		SEND_STRING(":");	// Send  (":") :: 2025.05.19-16:40
	} else if (state->count == 2 && !state->pressed) {
		SEND_STRING(": ");	// Send  (": ") :: 2025.05.19-16:40
		set_oneshot_mods(MOD_LSFT);    //   :: 2025.05.22-13:20
	}
}
void dance_period_reset(tap_dance_state_t *state, void *user_data) {
	layer_clear();
}
// COMMA::TapDance 🪩
void dance_comma_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		SEND_STRING(",");	// Send  (",") :: 2025.05.19-16:42
	} else if (state->count == 1 && !state->pressed) {
		SEND_STRING(", ");	// Send  (", ") :: 2025.05.19-16:42
	} else if (state->count == 2 && state->pressed) {
		SEND_STRING(";");	// Send  (";") :: 2025.05.19-16:42
	} else if (state->count == 2 && !state->pressed) {
		SEND_STRING("; ");	// Send  ("; ") :: 2025.05.19-16:42
	}
}
void dance_comma_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// DELWORD::TapDance 🪩
void dance_delword_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {	// 💀 DELETE WORD
		tap_code16(A(KC_BSPC));	// ⎇ BSPC :: 2025.05.19-16:45
	} else if (state->count == 1 && !state->pressed) {	// 💀 BACKSPACE
		tap_code(KC_BSPC);	// ⚫︎KC_BSPC :: 2025.05.19-16:46
	} else if (state->count == 2 && state->pressed) {	// 💀 DELETE LINE
		tap_code16(G(KC_BSPC));	// ⌘ BSPC :: 2025.05.19-16:46
	}
}
void dance_delword_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// USCR::TapDance 🪩
void dance_uscr_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		SEND_STRING("_");	// Send  ("_") :: 2025.05.19-18:20w
	} else if (state->count == 1 && !state->pressed) {
		SEND_STRING(" - ");	// Send  (" - ") :: 2025.05.19-18:20
        set_oneshot_mods(MOD_LSFT); //  :: 2025.05.19-18:51
	} else if (state->count == 2 && state->pressed) {
		SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_QUOT) SS_TAP(X_QUOT) SS_UP(X_LSFT) SS_TAP(X_LEFT));	// Send  (⬇︎SFT ⚫︎QUOT ⚫︎QUOT ⬆︎SFT ⚫︎LEFT) :: 2025.05.19-18:20
	} else if (state->count == 2 && !state->pressed) {
		SEND_STRING(SS_TAP(X_QUOT));	// Send  (⚫︎QUOT) :: 2025.05.19-18:21
	}
}
void dance_uscr_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// LEADAPP::TapDance 🪩
void dance_leadapp_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {	// 💀 TAP CONTROL
		tap_code(KC_LCTL);	// ⚫︎KC_LCTL :: 2025.05.19-18:39
	} else if (state->count == 1 && !state->pressed) {	// 💀 LEADER START
		leader_start();	//  :: 2025.05.19-18:40
	} else if (state->count == 2 && !state->pressed) {	// 💀 ACTIVATE LAST APPLICATION
		tap_code16(C(S(G(KC_P))));	// ⎈⇧⌘ P :: 2025.05.19-18:40
	}
}
void dance_leadapp_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// DELIMIT::TapDance 🪩
void dance_delimit_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		SEND_STRING(" ][");	// Send  (" ££") :: 2025.05.19-18:56
	} else if (state->count == 1 && !state->pressed) {
		SEND_STRING(" ^^");	// Send  (" ^^") :: 2025.05.19-18:57
	} else if (state->count == 2 && state->pressed) {
		SEND_STRING(" ><");	// Send  (" ><") :: 2025.05.19-18:57
	} else if (state->count == 2 && !state->pressed) {
		SEND_STRING(" :;");	// Send  (" /\") :: 2025.05.19-18:57
	} else if (state->count == 3 && state->pressed) {
		SEND_STRING(" `~");	// Send  (" :;") :: 2025.05.19-18:57
	} else if (state->count == 3 && !state->pressed) {
		SEND_STRING(" ;:");	// Send  (" ;:") :: 2025.05.19-18:57
	}
}
void dance_delimit_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// KEYFORL::TapDance 🪩
void dance_keyforl_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {	// 💀 KEYBOARD MAP
		register_code(KC_LALT);
		register_code(KC_LCTL);
		wait_ms(1000);
		unregister_code(KC_LCTL);
		unregister_code(KC_LALT);    // ⬇⎇⎈ 🕙1000 ⬆⎈⎇ :: 2025.05.22-12:47
	} else if (state->count == 1 && !state->pressed) {	// 💀 URL
		register_code(KC_LGUI);
		register_code(KC_LCTL);
		wait_ms(1000);
		unregister_code(KC_LCTL);
		unregister_code(KC_LGUI);    // ⬇⌘⎈ 🕙1000 ⬆⎈⌘ :: 2025.05.22-12:47
	} else if (state->count == 2 && state->pressed) {	// 💀 INCLUDES
		register_code(KC_LGUI);
		register_code(KC_LSFT);
		wait_ms(1000);
		unregister_code(KC_LSFT);
		unregister_code(KC_LGUI);    // ⬇⌘⇧ 🕙1000 ⬆⇧⌘ :: 2025.05.22-12:47
	} else if (state->count == 2 && !state->pressed) {	// 💀 ICLOUD
		register_code(KC_LCTL);
		register_code(KC_LGUI);
		register_code(KC_LSFT);
		wait_ms(1000);
		unregister_code(KC_LCTL);
		unregister_code(KC_LSFT);
		unregister_code(KC_LGUI);    // ⬇⎈⌘⇧ 🕙1000 ⬆⎈⇧⌘ :: 2025.05.22-12:48
	} else if (state->count == 3 && !state->pressed) {	// 💀 DOWNLOADS
		register_code(KC_LCTL);
		register_code(KC_LALT);
		register_code(KC_LSFT);
		wait_ms(1000);
		unregister_code(KC_LSFT);
		unregister_code(KC_LALT);
		unregister_code(KC_LCTL);    // ⬇⎈⎇⇧ 🕙1000 ⬆⇧⎇⎈ :: 2025.05.22-12:48
	} else if (state->count == 4 && !state->pressed) {
		register_code(KC_LALT);
		register_code(KC_LGUI);
		register_code(KC_LSFT);
		wait_ms(1000);
		unregister_code(KC_LALT);
		unregister_code(KC_LSFT);
		unregister_code(KC_LGUI);    // ⬇⎇⌘⇧ 🕙1000 ⬆⎇⇧⌘ :: 2025.05.22-12:49
	}
}
void dance_keyforl_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// KEYSNIP::TapDance 🪩
void dance_keysnip_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {	// 💀 GLOBAL
		register_code(KC_LCTL);
		register_code(KC_LALT);
		register_code(KC_LGUI);
		wait_ms(1000);
		unregister_code(KC_LGUI);
		unregister_code(KC_LALT);
		unregister_code(KC_LCTL);    // ⬇⎈⎇⌘ 🕙1000 ⬆⌘⎇⎈ :: 2025.05.22-12:40
	} else if (state->count == 1 && !state->pressed) {
		register_code(KC_LSFT);
		wait_ms(150);
		unregister_code(KC_LSFT);
		wait_ms(150);    // ⬇⇧ 🕙150 ⬆⇧ 🕙150 :: 2025.05.22-12:40
		register_code(KC_LSFT);
		wait_ms(150);
		unregister_code(KC_LSFT);    // ⬇⇧ 🕙150 ⬆⇧ :: 2025.05.22-12:40
	} else if (state->count == 2 && !state->pressed) {
		register_code(KC_LCTL);
		wait_ms(150);
		unregister_code(KC_LCTL);
		wait_ms(150);    // ⬇⎈ 🕙150 ⬆⎈ 🕙150 :: 2025.05.22-12:40
		register_code(KC_LCTL);
		wait_ms(150);
		unregister_code(KC_LCTL);    // ⬇⎈ 🕙150 ⬆⎈ :: 2025.05.22-12:41
	} else if (state->count == 3 && !state->pressed) {
		register_code(KC_LALT);
		wait_ms(150);
		unregister_code(KC_LALT);
		wait_ms(150);    // ⬇⎇ 🕙150 ⬆⎇ 🕙150 :: 2025.05.22-12:41
		register_code(KC_LALT);
		wait_ms(150);
		unregister_code(KC_LALT);    // ⬇⎇ 🕙150 ⬆⎇ :: 2025.05.22-12:41
	} else if (state->count == 4 && !state->pressed) {
		register_code(KC_LGUI);
		wait_ms(150);
		unregister_code(KC_LGUI);
		wait_ms(150);    // ⬇⌘ 🕙150 ⬆⌘ 🕙150 :: 2025.05.22-12:42
		register_code(KC_LGUI);
		wait_ms(150);
		unregister_code(KC_LGUI);    // ⬇⌘ 🕙150 ⬆⌘ :: 2025.05.22-12:42
	}
}
void dance_keysnip_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
/////////////////////////////////////✨E X T E N D  T A P  F U N C T I O N S ✨//////////////////////////////////////////////
// TIL::TapDance 🪩
void dance_til_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		SEND_STRING("~~~~" SS_TAP(X_LEFT) SS_TAP(X_LEFT));	// Send  ("~~~~" ⚫︎LEFT ⚫︎LEFT) :: 2025.05.19-19:28
	} else if (state->count == 1 && !state->pressed) {
		SEND_STRING("~");	// Send  ("~") :: 2025.05.19-19:29
	} else if (state->count == 2 && !state->pressed) {
		SEND_STRING("~~" SS_TAP(X_LEFT));	// Send  ("~~" ⚫︎LEFT) :: 2025.05.19-19:29
	}
}
void dance_til_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
/////////////////////////////////////✨W I N D O W S  T A P  F U N C T I O N S ✨//////////////////////////////////////////////
// FULL::TapDance 🪩
void dance_full_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		// 💀 DO NOTHING :: 2025.05.22-13:50
	} else if (state->count == 1 && !state->pressed) {	// 💀 FULLSCREEN :: 2025.05.22-13:52
		tap_code16(C(G(KC_F))); // ⎈⌘ F :: 2025.05.22-13:50
	} else if (state->count == 2 && !state->pressed) {	// 💀 FILL :: 2025.05.22-13:53
		tap_code16(C(KC_F));    // ⎈ F :: 2025.05.22-13:51
	}
}
void dance_full_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
///////////////////////////////////////✨F U N  T A P  F U N C T I O N S ✨//////////////////////////////////////////////
// PORT::TapDance 🪩
void dance_port_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		// 💀 DO NOTHING :: 2025.05.22-13:57
	} else if (state->count == 1 && !state->pressed) {	// 💀 INVOKE PORTAL :: 2025.05.22-13:59
		tap_code16(C(S(G(KC_F6)))); // ⎈⇧⌘ F6 :: 2025.05.22-13:57
	} else if (state->count == 2 && !state->pressed) {	// 💀 KM::PLAY/PAUSE PORTAL :: 2025.05.22-13:59
		tap_code16(HYPR(KC_F4));    // HYPR F4 :: 2025.05.22-13:58
	}
}
void dance_port_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// ENDEL::TapDance 🪩
void dance_endel_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		// 💀 DO NOTHING :: 2025.05.22-14:00
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(A(G(KC_E))));  // ⎈⎇⌘ E :: 2025.05.22-14:01
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(C(S(G(KC_E))));  // ⎈⇧⌘ E :: 2025.05.22-14:01
	}
}
void dance_endel_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// SLEEVE::TapDance 🪩
void dance_sleeve_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		// 💀 DO NOTHING :: 2025.05.22-14:12
	} else if (state->count == 1 && !state->pressed) {
		tap_code16(C(S(G(KC_F5)))); // ⎈⇧⌘ F5 :: 2025.05.22-14:13
	} else if (state->count == 2 && !state->pressed) {
		tap_code16(S(G(KC_9))); // ⇧⌘ 9 :: 2025.05.22-14:13
	}
}
void dance_sleeve_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
///////////////////////////////////////✨S Y M B O L  T A P  F U N C T I O N S ✨//////////////////////////////////////////////
// RB::TapDance 🪩
void dance_rb_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		SEND_STRING(">" SS_DELAY(50) SS_TAP(X_SPC));    // Send  (">" 🕘50 ⚫︎SPC) :: 2025.05.22-15:19
	} else if (state->count == 1 && !state->pressed) {
		SEND_STRING(">");   // Send  (">") :: 2025.05.22-15:20
	}
}
void dance_rb_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// SBL::TapDance 🪩
void dance_sbl_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		SEND_STRING("[[");  // Send  ("[[") :: 2025.05.22-15:40
	} else if (state->count == 1 && !state->pressed) {
		SEND_STRING("[");   // Send  ("[") :: 2025.05.22-15:40
	}
}
void dance_sbl_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// SBR::TapDance 🪩
void dance_sbr_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		SEND_STRING("- [ ] ");  // Send  ("- [ ] ") :: 2025.05.22-15:22
	} else if (state->count == 1 && !state->pressed) {
		SEND_STRING("]");   // Send  ("]") :: 2025.05.22-15:23
	}
}
void dance_sbr_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// BACKT::TapDance 🪩
void dance_backt_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		SEND_STRING("``" SS_DELAY(50) SS_TAP(X_LEFT));  // Send  ("``" 🕘50 ⚫︎LEFT) :: 2025.05.22-15:24
	} else if (state->count == 1 && !state->pressed) {
		SEND_STRING("`");   // Send  ("`") :: 2025.05.22-15:24
	}
}
void dance_backt_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// EQUALS::TapDance 🪩
void dance_equals_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		SEND_STRING("====" SS_DELAY(50) SS_TAP(X_LEFT) SS_TAP(X_LEFT)); // Send  ("====" 🕘50 ⚫︎LEFT ⚫︎LEFT) :: 2025.05.22-15:34
	} else if (state->count == 1 && !state->pressed) {
		SEND_STRING("=");   // Send  ("=") :: 2025.05.22-15:34
	}
}
void dance_equals_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// STAR::TapDance 🪩
void dance_star_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		SEND_STRING("****" SS_DELAY(50) SS_TAP(X_LEFT) SS_TAP(X_LEFT)); // Send  ("****" 🕘50 ⚫︎LEFT ⚫︎LEFT) :: 2025.05.22-15:41
	} else if (state->count == 1 && !state->pressed) {
		SEND_STRING("*");   // Send  ("*") :: 2025.05.22-15:41
	}
}
void dance_star_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
// UNSC::TapDance 🪩
void dance_unsc_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1 && state->pressed) {
		SEND_STRING("____" SS_DELAY(50) SS_TAP(X_LEFT) SS_TAP(X_LEFT)); // Send  ("____" 🕘50 ⚫︎LEFT ⚫︎LEFT) :: 2025.05.22-15:42
	} else if (state->count == 1 && !state->pressed) {
		SEND_STRING("___"); // Send  ("___") :: 2025.05.22-15:42
	}
}
void dance_unsc_reset(tap_dance_state_t *state, void *user_data) {
	clear_keyboard();
	layer_clear();
}
//////////////////////////////////////////////✨P E R  K E Y  T A P  T E R M ✨//////////////////////////////////////////////
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
        case TD(TD_ARC):
            return TAPPING_TERM + 100;
        case TD(TD_SNIPLAB):
            return TAPPING_TERM + 100;
        case TD(TD_PERP):
            return TAPPING_TERM + 100;
        case TD(TD_CHAT):
            return TAPPING_TERM + 100;
        case TD(TD_CLAUDE):
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
        case TD(TD_OBSIDIAN):
			return TAPPING_TERM + 100;
        case TD(TD_OMNIFOCUS):
            return TAPPING_TERM + 100;
        case TD(TD_BBEDIT):
			return TAPPING_TERM + 100;
//////////////////////////////////////////////✨C O L E M A K  P E R  K E Y ✨//////////////////////////////////////////////
        case TD(TD_ESCAPE):
            return TAPPING_TERM + 50;
        case TD(TD_TAB):
            return TAPPING_TERM + 25;
        case TD(TD_HYPENATOR):
            return TAPPING_TERM + 75;
        case TD(TD_QMACRO):
            return TAPPING_TERM + 50;
        case TD(TD_MIDKEY):
			return TAPPING_TERM + 50;
        case TD(TD_SPACE):
            return TAPPING_TERM + 50;
        case TD(TD_FILEFRED):
            return TAPPING_TERM + 75;
        case TD(TD_SCREEN):
            return TAPPING_TERM + 50;
        case TD(TD_CAPS):
            return TAPPING_TERM + 25;
        case TD(TD_ALFMEH2):
            return TAPPING_TERM + 50;
        case TD(TD_HASHAT):
            return TAPPING_TERM + 50;
        case TD(TD_SMILE):
            return TAPPING_TERM + 25;
        case TD(TD_SLASH):
            return TAPPING_TERM + 50;
        case TD(TD_QUESTION):
            return TAPPING_TERM + 50;
        case TD(TD_PERIOD):
            return TAPPING_TERM + 50;
        case TD(TD_COMMA):
            return TAPPING_TERM + 50;
        case TD(TD_DELWORD):
            return TAPPING_TERM + 25;
        case TD(TD_USCR):
            return TAPPING_TERM + 50;
        case TD(TD_DELIMIT):
			return TAPPING_TERM + 50;
        case TD(TD_KEYFORL):
			return TAPPING_TERM + 100;
        case TD(TD_KEYSNIP):
			return TAPPING_TERM + 100;
//////////////////////////////////////////////✨E X T E N D  P E R  K E Y ✨//////////////////////////////////////////////
        case TD(TD_TIL):
            return TAPPING_TERM + 25;
//////////////////////////////////////////////✨W I N D O W S  P E R  K E Y ✨//////////////////////////////////////////////
        case TD(TD_FULL):
            return TAPPING_TERM + 50;
//////////////////////////////////////////////✨F U N  P E R  K E Y ✨//////////////////////////////////////////////
        case TD(TD_PORT):
            return TAPPING_TERM + 50;
        case TD(TD_ENDEL):
			return TAPPING_TERM + 50;
        case TD(TD_SLEEVE):
            return TAPPING_TERM + 50;
//////////////////////////////////////////////✨S Y M B O L  P E R  K E Y ✨//////////////////////////////////////////////
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
////////////////////////////////////////✨C A P S  W O R D  P R O C E S S I N G ✨//////////////////////////////////////////////
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
        case HOME_A:
        case HOME_R:
        case HOME_S:
        case HOME_T:
        case HOME_N:
        case HOME_E:
        case HOME_I:
        case HOME_O:
        case ZSETNOT:
    add_weak_mods(MOD_BIT(KC_LSFT));        // Apply shift
return true;                                // Keep Caps Word active
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
        case DELWORD:
        case QUESTION:
        case SLASH:
        case COMMA:
        case PERIOD:
        case HASHAT:
        case USCR:
return true;
    default:
return false; // End Caps Word for other keys
    }
}
/////////////////////////////////////////✨M A C R O  D E C L A R A T I O N S ✨//////////////////////////////////////////////
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
//////////////////////////////////////////////✨E X T E N D  M A C R O  D E C ✨//////////////////////////////////////////////
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
//////////////////////////////////////////////✨F U N  M A C R O  D E C ✨//////////////////////////////////////////////
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
//////////////////////////////////////////////✨S Y M B O L  M A C R O  D E C ✨//////////////////////////////////////////////
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
    TROSA,
};
/////////////////////////////////////////✨P R O C E S S  R E C O R D  U S E R ✨//////////////////////////////////////////////
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_autocorrection(keycode, record)) { return false; }
    switch (keycode) {
////////////////////////////////////////////////✨M O O M  M A C R O S ✨//////////////////////////////////////////////
    case WIN1_1:
        if (record->event.pressed) {
    	    tap_code16(S(A(G(KC_1))));  // ⇧⎇⌘ 1 :: 2025.05.22-16:14
	    } return false;
    case WIN1_2:
        if (record->event.pressed) {
    	    tap_code16(S(A(G(KC_2))));  // ⇧⎇⌘ 2 :: 2025.05.22-16:15
	    } return false;
    case WIN1_3:
        if (record->event.pressed) {
    	    tap_code16(S(A(G(KC_3))));  // ⇧⎇⌘ 3 :: 2025.05.22-16:15
	    } return false;
    case WIN2_1:
        if (record->event.pressed) {
    	    tap_code16(S(A(G(KC_4))));  // ⇧⎇⌘ 4 :: 2025.05.22-16:16
	    } return false;
    case WIN2_2:
        if (record->event.pressed) {
    	    tap_code16(S(A(G(KC_5))));  // ⇧⎇⌘ 5 :: 2025.05.22-16:16
	    } return false;
    case WIN2_3:
        if (record->event.pressed) {
    	    tap_code16(S(A(G(KC_6))));  // ⇧⎇⌘ 6 :: 2025.05.22-16:17
	    } return false;
    case WIN2_4:
        if (record->event.pressed) {
    	    tap_code16(S(A(G(KC_7))));  // ⇧⎇⌘ 7 :: 2025.05.22-16:17
	    } return false;
    case WIN2_5:
        if (record->event.pressed) {
    	    tap_code16(S(A(G(KC_8))));  // ⇧⎇⌘ 8 :: 2025.05.22-16:17
	    } return false;
    case WIN2_6:
        if (record->event.pressed) {
    	    tap_code16(S(A(G(KC_9))));  // ⇧⎇⌘ 9 :: 2025.05.22-16:18
	    } return false;
    case WIN2_7:
        if (record->event.pressed) {
    	    tap_code16(S(A(G(KC_0))));  // ⇧⎇⌘ 0 :: 2025.05.22-16:18
	    } return false;
    case WIN3_1:
        if (record->event.pressed) {
    	    tap_code16(A(G(KC_1))); // ⎇⌘ 1 :: 2025.05.22-16:19
	    } return false;
    case WIN3_2:
        if (record->event.pressed) {
    	    tap_code16(A(G(KC_2))); // ⎇⌘ 2 :: 2025.05.22-16:19
	    } return false;
    case WIN3_3:
        if (record->event.pressed) {
    	    tap_code16(A(G(KC_3))); // ⎇⌘ 3 :: 2025.05.22-16:20
	    } return false;
    case WIN3_4:
        if (record->event.pressed) {
    	    tap_code16(A(G(KC_4))); // ⎇⌘ 4 :: 2025.05.22-16:20
	    } return false;
    case WIN3_5:
        if (record->event.pressed) {
    	    tap_code16(A(G(KC_5))); // ⎇⌘ 5 :: 2025.05.22-16:20
	    } return false;
    case WIN3_6:
        if (record->event.pressed) {
    	    tap_code16(A(G(KC_6))); // ⎇⌘ 6 :: 2025.05.22-16:21
	    } return false;
    case WIN3_7:
        if (record->event.pressed) {
    	    tap_code16(A(G(KC_7))); // ⎇⌘ 7 :: 2025.05.22-16:21
	    } return false;
    case WIN4_1:
        if (record->event.pressed) {
    	    tap_code16(A(G(KC_8))); // ⎇⌘ 8 :: 2025.05.22-16:22
	    } return false;
    case WIN4_2:
        if (record->event.pressed) {
    	    tap_code16(A(G(KC_9))); // ⎇⌘ 9 :: 2025.05.22-16:22
	    } return false;
    case WIN4_3:
        if (record->event.pressed) {
    	    tap_code16(A(G(KC_0))); // ⎇⌘ 0 :: 2025.05.22-16:23
	    } return false;
    case WIN4_4:
        if (record->event.pressed) {
    	    tap_code16(C(A(G(KC_1))));  // ⎈⎇⌘ 1 :: 2025.05.22-16:23
	    } return false;
    case WIN5_1:
        if (record->event.pressed) {
    	    tap_code16(C(A(KC_2))); // ⎈⎇ 2 :: 2025.05.22-16:24
	    } return false;
    case WIN5_2:
        if (record->event.pressed) {
    	    tap_code16(C(A(KC_3))); // ⎈⎇ 3 :: 2025.05.22-16:24
	    } return false;
    case WIN5_3:
        if (record->event.pressed) {
    	    tap_code16(C(A(KC_4))); // ⎈⎇ 4 :: 2025.05.22-16:25
	    } return false;
    case WIN5_4:
        if (record->event.pressed) {
    	    tap_code16(C(A(KC_5))); // ⎈⎇ 5 :: 2025.05.22-16:25
	    } return false;
    case WIN6_1:
        if (record->event.pressed) {
    	    tap_code16(C(A(KC_7))); // ⎈⎇ 7 :: 2025.05.22-16:26
	    } return false;
    case WIN6_2:
        if (record->event.pressed) {
    	    tap_code16(C(A(KC_6))); // ⎈⎇ 7 :: 2025.05.22-16:26
	    } return false;
    case WIN6_3:
        if (record->event.pressed) {
    	    tap_code16(C(A(KC_8))); // ⎈⎇ 8 :: 2025.05.22-16:27
	    } return false;
    case WIN6_4:
        if (record->event.pressed) {
    	    tap_code16(C(A(KC_9))); // ⎈⎇ 9 :: 2025.05.22-16:27
	    } return false;
    case WIN6_5:
        if (record->event.pressed) {
    	    tap_code16(C(A(KC_0))); // ⎈⎇ 0 :: 2025.05.22-16:27
	    } return false;
    case WIN7_1:
        if (record->event.pressed) {
    	    tap_code16(C(A(G(KC_2))));  // ⎈⎇⌘ 2 :: 2025.05.22-16:28
	    } return false;
    case WIN7_2:
        if (record->event.pressed) {
    	    tap_code16(C(A(G(KC_3))));  // ⎈⎇⌘ 3 :: 2025.05.22-16:28
	    } return false;
    case WIN8_1:
        if (record->event.pressed) {
    	    tap_code16(MEH(KC_7));  // MEH 6 :: 2025.05.22-16:29
	    } return false;
    case WIN8_2:
        if (record->event.pressed) {
    	    tap_code16(MEH(KC_6));  // MEH 6 :: 2025.05.22-16:30
	    } return false;
    case WIN8_3:
        if (record->event.pressed) {
    	    tap_code16(MEH(KC_5));  // MEH 5 :: 2025.05.22-16:30
	    } return false;
    case WIN8_4:
        if (record->event.pressed) {
    	    tap_code16(MEH(KC_4));  // MEH 4 :: 2025.05.22-16:31
	    } return false;
    case WIN8_5:
        if (record->event.pressed) {
    	    tap_code16(MEH(KC_3));  // MEH 3 :: 2025.05.22-16:31
	    } return false;
    case WIN8_6:
        if (record->event.pressed) {
    	    tap_code16(MEH(KC_2));  // MEH 2 :: 2025.05.22-16:32
	    } return false;
//////////////////////////////////////////////✨E X T E N D  M A C R O S ✨//////////////////////////////////////////////
    case HAZEDN:	// 💀 EXTEND ENCODER :: 2025.05.22-17:27
        if (record->event.pressed) {
    	    tap_code16(MEH(KC_J));  // MEH J :: 2025.05.22-17:20
	    } return false;
    case HAZEUP:	// 💀 EXTEND ENCODER :: 2025.05.22-17:27
        if (record->event.pressed) {
    	    tap_code16(MEH(KC_G));  // MEH G :: 2025.05.22-17:21
	    } return false;
    case SHTDWN:
        if (record->event.pressed) {
    	    tap_code16(HYPR(KC_1)); // HYPR 1 :: 2025.05.22-17:21
	    } return false;
    case SLEEP:
        if (record->event.pressed) {
    	    tap_code16(HYPR(KC_2)); // HYPR 2 :: 2025.05.22-17:21
	    } return false;
    case RSTART:
        if (record->event.pressed) {
    	    tap_code16(HYPR(KC_3)); // HYPR 3 :: 2025.05.22-17:22
	    } return false;
    case UNDO:
        if (record->event.pressed) {
    	    tap_code16(G(KC_Z));    // ⌘ Z :: 2025.05.22-17:22
	    } return false;
    case COPY:
        if (record->event.pressed) {
    	    tap_code16(G(KC_C));    // ⌘ C :: 2025.05.22-17:23
	    } return false;
    case PASTE:
        if (record->event.pressed) {
    	    tap_code16(G(KC_V));    // ⌘ V :: 2025.05.22-17:23
	    } return false;
    case DUPLICA:
        if (record->event.pressed) {
    	    tap_code16(G(KC_D));    // ⌘ D :: 2025.05.22-17:24
	    } return false;
    case CUT:
        if (record->event.pressed) {
    	    tap_code16(G(KC_X));    // ⌘ X :: 2025.05.22-17:24
	    } return false;
    case SPOTIFY:
        if (record->event.pressed) {
    	    tap_code16(C(S(G(KC_F4)))); // ⎈⇧⌘ F4 :: 2025.05.22-17:24
	    } return false;
//////////////////////////////////////////////✨F U N  M A C R O S ✨//////////////////////////////////////////////
    case ZOOMIN:                                // Encoder::Fun
        if (record->event.pressed) {
            register_code(KC_LALT);
            tap_code(MSEWHLDO);
            unregister_code(KC_LALT);
        } return false;
    case ZOOMOUT:                                // Encoder::Fun
        if (record->event.pressed) {
            register_code(KC_LALT);
            tap_code(MSEWHLUP);
            unregister_code(KC_LALT);
        } return false;
    case KMESTRO:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F1)))));
        } return false;
    case SYSSET:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F4)))));
        } return false;
    case PASS:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F3)))));
        } return false;
    case PORTAL:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F6)))));
        } return false;
    case SPEED:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F7)))));
        } return false;
    case MSG:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F8)))));
        } return false;
    case WHATSAPP:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_PGUP)))));
        } return false;
    case ELGATO:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F9)))));
        } return false;
    case LDECK:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_L)))));
        } return false;
    case ITERM:
        if (record->event.pressed) {
    	    tap_code16(C(S(G(KC_T))));  // ⎈⇧⌘ T :: 2025.05.22-17:28
	    } return false;
    case SLVPP:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_0)))));
        } return false;
    case SLVNEXT:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_TAP(X_0))));
        } return false;
    case SLVPREV:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_9))));
        } return false;
    case SLVVOLU:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_7))));
        } return false;
    case SLVVOLD:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_TAP(X_8)))));
        } return false;
    case SLVMUTE:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LGUI(SS_TAP(X_6))));
        } return false;
    case SLVLIKE:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LALT(SS_LGUI(SS_TAP(X_0)))));
        } return false;
    case VSCODE:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT(SS_LGUI(SS_LSFT(SS_TAP(X_C)))));
        } return false;
    case WORK:
        if (record->event.pressed) {
    	    tap_code16(S(A(G(KC_DOWN))));   // ⇧⎇⌘ ↓ :: 2025.05.22-17:29
	    } return false;
    case TERMIN:
        if (record->event.pressed) {
    	    tap_code16(MEH(KC_9));  // MEH 9 :: 2025.05.22-17:32
	    } return false;
//////////////////////////////////////////////✨S Y M B O L  M A C R O S ✨//////////////////////////////////////////////
    case POUND:
        if (record->event.pressed) {
    	    tap_code16(A(KC_3));    // ⎇ 3 :: 2025.05.22-17:34
	    } return false;
    case DOLLAR:
        if (record->event.pressed) {
    	    SEND_STRING("$");   // Send  ("$") :: 2025.05.22-17:34
	    } return false;
    case EURO:
        if (record->event.pressed) {
    	    tap_code16(A(KC_4));    // ⎇ 4 :: 2025.05.22-17:35
	    } return false;
    case YEN:
        if (record->event.pressed) {
    	    tap_code16(A(KC_Y));    // ⎇ Y :: 2025.05.22-17:35
	    } return false;
    case OG:
        if (record->event.pressed) {
    	    tap_code16(A(KC_R));    // ⎇ R :: 2025.05.22-17:35
	    } return false;
    case TM:
        if (record->event.pressed) {
    	    tap_code16(A(KC_2));    // ⎇ 2 :: 2025.05.22-17:36
	    } return false;
    case LB:
        if (record->event.pressed) {
    	    SEND_STRING("<");   // Send  ("<") :: 2025.05.22-17:36
	    } return false;
    case BB:
        if (record->event.pressed) {
    	    SEND_STRING("<>" SS_DELAY(50) SS_TAP(X_LEFT));  // Send  ("<>" 🕘50 ⚫︎LEFT) :: 2025.05.22-17:36
	    } return false;
    case AND:
        if (record->event.pressed) {
    	    SEND_STRING("&");   // Send  ("&") :: 2025.05.22-17:37
	    } return false;
    case BTICK:
        if (record->event.pressed) {
    	    SEND_STRING("`");   // Send  ("`") :: 2025.05.22-17:37
	    } return false;
    case ARROW:
        if (record->event.pressed) {
    	    SEND_STRING("->");  // Send  ("->") :: 2025.05.22-17:37
	    } return false;
    case LARROW:
        if (record->event.pressed) {
    	    SEND_STRING("<-");  // Send  ("<-") :: 2025.05.22-17:38
	    } return false;
    case AARROW:
        if (record->event.pressed) {
    	    SEND_STRING("=>");  // Send  ("=>") :: 2025.05.22-17:38
	    } return false;
    case LAARROW:
        if (record->event.pressed) {
    	    SEND_STRING("<=");  // Send  ("<=") :: 2025.05.22-17:38
	    } return false;
    case SBC:
        if (record->event.pressed) {
    	    SEND_STRING("[]" SS_DELAY(50) SS_TAP(X_LEFT));  // Send  ("[]" 🕘50 ⚫︎LEFT) :: 2025.05.22-17:39
	    } return false;
    case SBTD:
        if (record->event.pressed) {
    	    SEND_STRING("[ ]"); // Send  ("[ ]") :: 2025.05.22-17:39
	    } return false;
    case PLUS:
        if (record->event.pressed) {
    	    SEND_STRING("+");   // Send  ("+") :: 2025.05.22-17:40
	    } return false;
    case MINUS:
        if (record->event.pressed) {
    	    SEND_STRING("-");   // Send  ("-") :: 2025.05.22-17:40
	    } return false;
    case DONE:
        if (record->event.pressed) {
    	    SEND_STRING(SS_LALT("v"));  // Send ⎇ ("v") :: 2025.05.22-17:40
	    } return false;
    case BRL:
        if (record->event.pressed) {
    	    SEND_STRING("(");   // Send  ("(") :: 2025.05.22-17:41
	    } return false;
    case BRR:
        if (record->event.pressed) {
    	    SEND_STRING(")");   // Send  ("") :: 2025.05.22-17:41
	    } return false;
    case BRB:
        if (record->event.pressed) {
    	    SEND_STRING("( " SS_DELAY(50) SS_TAP(X_LEFT));  // Send  ("(" 🕘50 ⚫︎LEFT) :: 2025.05.22-17:42
	    } return false;
    case CBL:
        if (record->event.pressed) {
    	    SEND_STRING("{");   // Send  ("{") :: 2025.05.22-17:42
	    } return false;
    case CBR:
        if (record->event.pressed) {
    	    SEND_STRING("}");   // Send  ("}") :: 2025.05.22-17:42
	    } return false;
    case CBB:
        if (record->event.pressed) {
    	    SEND_STRING("{}" SS_DELAY(50) SS_TAP(X_LEFT));  // Send  ("{}" 🕘50 ⚫︎LEFT) :: 2025.05.22-17:43
	    } return false;
    case INF:
        if (record->event.pressed) {
    	    tap_code16(A(KC_5));    // ⎇ 5 :: 2025.05.22-17:44
	    } return false;
    case PI:
        if (record->event.pressed) {
    	    tap_code16(A(KC_P));    // ⎇ P :: 2025.05.22-17:44
	    } return false;
    case PER:
        if (record->event.pressed) {
    	    tap_code16(S(KC_5));    // ⇧ 5 :: 2025.05.22-17:45
	    } return false;
    case DPIPE:
        if (record->event.pressed) {
    	    SEND_STRING("||");  // Send  ("||") :: 2025.05.22-17:45
	    } return false;
    case DDOT:
        if (record->event.pressed) {
    	    SEND_STRING("::");  // Send  ("::") :: 2025.05.22-17:45
	    } return false;
    case DSLASH:
        if (record->event.pressed) {
    	    SEND_STRING("//");  // Send  ("//") :: 2025.05.22-17:46
	    } return false;
    case DLB:
        if (record->event.pressed) {
    	    SEND_STRING("<<");  // Send  ("<<") :: 2025.05.22-17:46
	    } return false;
    case DRB:
        if (record->event.pressed) {
    	    SEND_STRING(">>");  // Send  (">>") :: 2025.05.22-17:46
	    } return false;
    case AST:
        if (record->event.pressed) {
    	    SEND_STRING("*");   // Send  ("*") :: 2025.05.22-17:46
	    } return false;
    case TROSA:
        if (record->event.pressed) {
    	    tap_code16(S(KC_6));    // ⇧ 6 :: 2025.05.22-17:47
	    } return false;
    default:
        return true;
    } return true;
}
////////////////////////////////////////✨T A P  D A N C E  A R R A Y ✨//////////////////////////////////////////////
tap_dance_action_t tap_dance_actions[] = {
    [TD_ALFRED] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_alfred_finished, dance_alfred_reset),
    [TD_HOOK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_hook_finished, dance_hook_reset),
    [TD_CLEANSHOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cleanshot_finished, dance_cleanshot_reset),
    [TD_DROP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_drop_finished, dance_drop_reset),
    [TD_ARC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_arc_finished, dance_arc_reset),
    [TD_SNIPLAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sniplab_finished, dance_sniplab_reset),
    [TD_PERP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_perp_finished, dance_perp_reset),
    [TD_CHAT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_chat_finished, dance_chat_reset),
    [TD_CLAUDE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_claude_finished, dance_claude_reset),
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
    [TD_OBSIDIAN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_obsidian_finished, dance_obsidian_reset),
    [TD_OMNIFOCUS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_omnifocus_finished, dance_omnifocus_reset),
    [TD_BBEDIT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_bbedit_finished, dance_bbedit_reset),
/////////////////////////////////////////✨C O L E M A K  A R R A Y ✨//////////////////////////////////////////////
    [TD_ESCAPE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_escape_finished, dance_escape_reset),
    [TD_TAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_tab_finished, dance_tab_reset),
    [TD_HYPENATOR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_hypenator_finished, dance_hypenator_reset),
    [TD_ZSETNOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_zsetnot_finished, dance_zsetnot_reset),
    [TD_QMACRO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_qmacro_finished, dance_qmacro_reset),
    [TD_MIDKEY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_midkey_finished, dance_midkey_reset),
    [TD_SPACE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_space_finished, dance_space_reset),
    [TD_FILEFRED] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_filefred_finished, dance_filefred_reset),
    [TD_SCREEN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_screen_finished, dance_screen_reset),
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_caps_finished, dance_caps_reset),
    [TD_ALFMEH2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_alfmeh2_finished, dance_alfmeh2_reset),
    [TD_HASHAT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_hashat_finished, dance_hashat_reset),
    [TD_SMILE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_smile_finished, dance_smile_reset),
    [TD_SLASH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_slash_finished, dance_slash_reset),
    [TD_QUESTION] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_question_finished, dance_question_reset),
    [TD_PERIOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_period_finished, dance_period_reset),
    [TD_COMMA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_comma_finished, dance_comma_reset),
    [TD_DELWORD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_delword_finished, dance_delword_reset),
    [TD_USCR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_uscr_finished, dance_uscr_reset),
    [TD_LEADAPP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_leadapp_finished, dance_leadapp_reset),
    [TD_DELIMIT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_delimit_finished, dance_delimit_reset),
    [TD_KEYFORL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_keyforl_finished, dance_keyforl_reset),
    [TD_KEYSNIP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_keysnip_finished, dance_keysnip_reset),
/////////////////////////////////////////////✨E X T E N D  A R R A Y ✨//////////////////////////////////////////////
    [TD_TIL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_til_finished, dance_til_reset),
////////////////////////////////////////////✨W I N D O W S  A R R A Y ✨//////////////////////////////////////////////
    [TD_FULL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_full_finished, dance_full_reset),
//////////////////////////////////////////////✨F U N  A R R A Y ✨//////////////////////////////////////////////
    [TD_PORT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_port_finished, dance_port_reset),
    [TD_ENDEL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_endel_finished, dance_endel_reset),
    [TD_SLEEVE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sleeve_finished, dance_sleeve_reset),
///////////////////////////////////////////✨S Y M B O L  A R R A Y ✨//////////////////////////////////////////////
    [TD_EQUALS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_equals_finished, dance_equals_reset),
    [TD_STAR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_star_finished, dance_star_reset),
    [TD_RB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_rb_finished, dance_rb_reset),
    [TD_SBL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sbl_finished, dance_sbl_reset),
    [TD_SBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sbr_finished, dance_sbr_reset),
    [TD_BACKT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_backt_finished, dance_backt_reset),
    [TD_UNSC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_unsc_finished, dance_unsc_reset),
};
//////////////////////////////////////////////✨L E A D E R  K E Y ✨//////////////////////////////////////////////
void leader_start_user(void) {
}
void leader_end_user(void) {
    if (leader_sequence_one_key(KC_F)) {
        // Leader, f => Types the below string
        SEND_STRING("QMK is awesome.");
//////////////////////////////////////////////✨T E X T   A C T I O N S ✨//////////////////////////////////////////////
//////////////////////////////////////////////✨W O R D   A C T I O N S ✨//////////////////////////////////////////////
    } else if (leader_sequence_one_key(KC_W)) {
        SEND_STRING(SS_LALT(SS_TAP(X_LEFT)));   // Send ⎇ (⚫︎LEFT) :: 2025.05.17-15:55
        clear_keyboard();
    } else if (leader_sequence_two_keys(KC_W, KC_W)) {
        SEND_STRING(SS_LALT(SS_TAP(X_LEFT) SS_TAP(X_LEFT)));    // Send ⎇ (⚫︎LEFT ⚫︎LEFT) :: 2025.05.17-16:41
        clear_keyboard();
///////////////////////////////////////////✨R O W S  & P A R A G R A P H S ✨//////////////////////////////////////////////
    } else if (leader_sequence_one_key(KC_R)) {
        tap_code16(S(KC_ENT));  // ⇧ ENT :: 2025.05.17-16:19
        clear_keyboard();
    } else if (leader_sequence_one_key(KC_P)) {
        tap_code16(S(KC_ENT));  // ⇧ ENT :: 2025.05.17-16:24
        tap_code16(S(KC_ENT));  // ⇧ ENT :: 2025.05.17-16:24
        clear_keyboard();
//////////////////////////////////////////////////✨C O D E S ✨//////////////////////////////////////////////
    } else if (leader_sequence_one_key(KC_P)) {
        // Leader, p => Types the below string
        SEND_STRING("gReatestEver9000\n");
    } else if (leader_sequence_two_keys(KC_P, KC_P)) {
        // Leader, p => Types the below string
        SEND_STRING("IruletheChaos9000\n");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    } else if (leader_sequence_two_keys(KC_T, KC_C)) {
        SEND_STRING("open kmtrigger://macro=A626AB28-DFE7-4D1C-BA1F-6BC28C8EFCD0\n");
    }
}
////////////////////////////////////////////////////✨R G B ✨//////////////////////////////////////////////////
// Define custom flags for specific keys
#define LED_FLAG_F  0x02  // F key
#define LED_FLAG_U  0x04  // U key
#define LED_FLAG_N  0x08  // N key
#define LED_FLAG_W  0x10  // W key
#define LED_FLAG_I  0x20  // I key
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void keyboard_post_init_user(void) {
    rgb_matrix_enable();                                                     // Enable RGB matrix
    rgb_matrix_mode(RGB_MATRIX_STARLIGHT);                                   // Set the default effect to Starlight
    rgb_matrix_sethsv(11, 176, 255);                                         // Set the default color to Coral
    eeconfig_update_rgb_matrix();                                            // Ensure it persists across power cycles
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    uint8_t current_mode = RGB_MATRIX_NONE;                                  // Track the current mode
layer_state_t layer_state_set_user(layer_state_t state) {                    // Set the layer effect only when mode changes
    uint8_t layer = get_highest_layer(state);
    uint8_t default_layer = get_highest_layer(default_layer_state);
    uint8_t new_mode = current_mode;                                         // Keep previous mode by default
    switch (layer) {                                                         // Handle active layers
        case EXTEND:
            new_mode = RGB_MATRIX_DIGITAL_RAIN;                              // Set Extend to Digital Rain
            break;
        default:                                                             // Return to the default layer RGB effect
    switch (default_layer) {
        case CMAK_BASE:
            new_mode = RGB_MATRIX_STARLIGHT;                                 // Starlight for Colemak
            break;
        case MAC_BASE:
            new_mode = RGB_MATRIX_STARLIGHT;                                 // Starlight for MacBase
            rgb_matrix_sethsv(128, 255, 128);                                // Set color to Teal
            break;
        default:
            break;
        }
        break;
    }
    if (new_mode != current_mode) {                                          // Apply the new mode if it has changed
        current_mode = new_mode;
        rgb_matrix_mode_noeeprom(new_mode);
    }
    return state;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
layer_state_t default_layer_state_set_user(layer_state_t state) {            // Handle default layer changes dynamically
    uint8_t default_layer = get_highest_layer(state);
    switch (default_layer) {                                                 // Update RGB effects based on default layer
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {  // Advanced user function for per-key RGB lighting
    uint8_t layer = get_highest_layer(layer_state);
    uint8_t default_layer = get_highest_layer(default_layer_state);
    if (default_layer == MAC_BASE) {                                          // Force MAC_BASE to use its color
            rgb_matrix_sethsv(128, 255, 128);
    }
    for (uint8_t i = led_min; i < led_max; i++) {
        if (layer == FUN) {
            rgb_matrix_set_color(36, RGB_RED);                                // Light up 'F'
            rgb_matrix_set_color(42, RGB_RED);                                // Light up 'U'
            rgb_matrix_set_color(58, RGB_RED);                                // Light up 'N'
        }
        if (layer == WINDOWS) {
            rgb_matrix_set_color(35, RGB_CYAN);                               // Light up 'W'
            rgb_matrix_set_color(60, RGB_CYAN);                               // Light up 'I'
            rgb_matrix_set_color(58, RGB_CYAN);                               // Light up 'N'
        }
        if (layer == SYM) {
            rgb_matrix_set_color(53, RGB_GOLDENROD);                          // Light up 'S'
            rgb_matrix_set_color(43, RGB_GOLDENROD);                          // Light up 'Y'
            rgb_matrix_set_color(57, RGB_GOLDENROD);                          // Light up 'M'
            }
        if (layer == PIC) {
            rgb_matrix_set_color(37, RGB_RED);                                // Light up 'P'
            rgb_matrix_set_color(65, RGB_RED);                                // Light up 'C'
            rgb_matrix_set_color(60, RGB_RED);                                // Light up 'I'
        }
        // CAPS LOCK Blinking
        if (i == CAPS_LED && is_caps_word_on()) {
            if (timer_elapsed32(caps_blink_timer) > 500) {
                caps_blink_timer = timer_read32();
                rgb_matrix_set_color(i, RGB_RED);
            }
        }
    }
    return false;
}
//////////////////////////////////////////////✨K E Y M A P  L A Y O U T ✨//////////////////////////////////////////////
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_tkl_ansi(
        KC_ESC,    KC_BRID,   KC_BRIU,   KC_MCTRL,  KC_LNPAD,  RGB_VAD,   RGB_VAI,   KC_MPRV,   KC_MPLY,   KC_MNXT,   KC_MUTE,    KC_VOLD,     KC_VOLU,     KC_MUTE,    KC_SNAP,   KC_SIRI,  RGB_MOD,
        KC_GRV,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,       KC_MINS,     KC_EQL,      KC_BSPC,    KC_INS,    KC_HOME,  KC_PGUP,
        KC_TAB,    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,       KC_LBRC,     KC_RBRC,     KC_BSLS,    KC_DEL,    KC_END,   KC_PGDN,
        KC_CAPS,   KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,    KC_QUOT,                  KC_ENT,
        KC_LSFT,              KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,     KC_SLSH,                  KC_RSFT,              KC_UP,
        KC_LCTL,   KC_LOPTN,  KC_LCMMD,                                   KC_SPC,                                     KC_RCMMD,   KC_ROPTN,    MO(MAC_FN),  KC_RCTL,    KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_tkl_ansi(
        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,                  XXXXXXX,
        XXXXXXX,              XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,                  XXXXXXX,              XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,                                    XXXXXXX,                                    XXXXXXX,    XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX),

    [CMAK_BASE] = LAYOUT_tkl_ansi(
        ALFRED,    HOOK,      CLEANSHT,  DROP,      SNIP,      ARC,       PERP,      CHAT,      CLAUDE,    OOUT,      MUSE,       TRELLO,      DAYONE,      KC_MUTE,    FANTAS,   SPARK,    ANYBOX,
        ESCAPE,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,       KC_MINS,     SMILE,       DELWORD,    EAGLE,    DEVON,    FINDER,
        TAB,       KC_Q,      KC_W,      KC_F,      KC_P,      KC_B,      USCR,      KC_J,      KC_L,      KC_U,      KC_Y,       QUESTION,    SLASH,       HASHAT,     OBSIDIAN, OFOCUS,   BBEDIT,
        HYPENATOR, HOME_A,    HOME_R,    HOME_S,    HOME_T,    KC_G,      MIDKEY,    KC_M,      HOME_N,    HOME_E,    HOME_I,     HOME_O,                   ALFMEH2,
        ZSETNOT,              KC_X,      KC_C,      KC_D,      KC_V,      LEADAPP,   DELIMIT,   KC_K,      KC_H,      COMMA,      PERIOD,                   CAPW,                 KC_UP,
        KEYFORL,   KEYSNIP,   QMACRO,                                      SPACE,                                     FILEFRED,   XXXXXXX,     XXXXXXX,     SCREEN,     KC_LEFT,  KC_DOWN,  KC_RGHT),

    [EXTEND] = LAYOUT_tkl_ansi(
        SHTDWN,    SLEEP,     RSTART,    MCNTRL,    LNCHPAD,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   REWIND,    PLAY,       NEXT,        SPOTIFY,     RGB_TOG,    RGB_RMOD, RGB_MOD,  BAT_LVL,
        TIL,       KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,     KC_F11,      KC_F12,      RGB_SPI,    RGB_VAI,  RGB_HUI,  RGB_SAI,
        HYPENATOR, MSEC1,     MSEWHLRI,  MSEWHLDO,  MSEWHLLE,  XXXXXXX,   MOUSEUP,   XXXXXXX,   HOME,      KC_UP,     MOUSEUP,    XXXXXXX,     XXXXXXX,     RGB_SPD,    RGB_VAD,  RGB_HUD,  RGB_SAD,
        KC_LCTL,   KC_LALT,   KC_LGUI,   MSEWHLUP,  KC_LSFT,   MOUSELT,   MOUSEDN,   MOUSERT,   KC_LEFT,   KC_DOWN,   KC_RGHT,    MSEC1,                    _______ ,
        UNDO,                 CUT,       COPY,      DUPLICA,   PASTE,     MSEC1,     MSEC4,     MSEC2,     MOUSELT,   MOUSERT,    MOUSEDN,                  _______ ,              _______,
        XXXXXXX,   XXXXXXX,   QMACRO,                                     _______,                                    XXXXXXX,    FILEFRED,    KC_LALT,     SCREEN,     _______,   _______,  _______),

    [WINDOWS] = LAYOUT_tkl_ansi(
        FULL,      WIN1_1,    WIN1_2,    WIN1_3,    XXXXXXX,   WIN4_1,    WIN4_2,    WIN4_3,    WIN4_4,    WIN5_1,    WIN5_2,     WIN5_3,      WIN5_4,      XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,   WIN2_1,    WIN2_2,    WIN2_3,    WIN2_4,    WIN2_5,    WIN2_6,    WIN2_7,    XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,   WIN3_1,    WIN3_2,    WIN3_3,    WIN3_4,    WIN3_5,    WIN3_6,    WIN3_7,    XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        WIN8_2,    WIN6_1,    WIN6_2,    WIN6_3,    WIN6_4,    WIN6_5,    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,                  XXXXXXX,
        WIN8_1,               WIN8_6,    WIN8_5,    WIN8_4,    WIN8_3,    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,                  XXXXXXX,              XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,                                    XXXXXXX,                                    XXXXXXX,    XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX),

    [FUN] = LAYOUT_tkl_ansi(
        SYSSET,    PASS,      PORT,      MSG,       WHATSAPP,  ELGATO,    LDECK,     _______,   ENDEL,     SLVPREV,   SLVPP,      SLVNEXT,     SLEEVE,      SLVMUTE,    SLVLIKE,  _______,  SPEED,
        _______,   BT_HST1,   BT_HST2,   BT_HST3,   P2P4G,     _______,   _______,   _______,   _______,   _______,   _______,    _______,     _______,     _______,    XXXXXXX,  XXXXXXX,  TERMIN,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,     _______,     _______,    KMESTRO,  VSCODE,   ITERM,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,                  _______,
        _______,              _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,                  _______,              _______,
        _______,   _______,   _______,                                    _______,                                    _______,    _______,     _______,     _______,    _______,  _______,  _______),

    [SYM] = LAYOUT_tkl_ansi(
        XXXXXXX,   POUND,     DOLLAR,    EURO,      YEN,       OG,        TM,        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        TIL,       LB,        RB,        BB,        DLB,       BRB,       XXXXXXX,   XXXXXXX,   XXXXXXX,   LAARROW,   LARROW,     ARROW,       AARROW,      XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        DPIPE,     SBL,       SBR,       SBC,       SBTD,      TROSA,     XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   PLUS,       EQUALS,      STAR,        XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        DDOT,      BRL,       BRR,       BRB,       DONE,      INF,       PI,        PER,       XXXXXXX,   XXXXXXX,   MINUS,      UNSC,                     XXXXXXX,
        DSLASH,               CBL,       CBR,       CBB,       XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    AND,                      XXXXXXX,              XXXXXXX,
        BACKT,     XXXXXXX,   XXXXXXX,                                    XXXXXXX,                                    AST,        XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX),

    [PIC] = LAYOUT_tkl_ansi(
        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,                  XXXXXXX,
        XXXXXXX,              XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,                  XXXXXXX,              XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,                                    XXXXXXX,                                    XXXXXXX,    XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX),

};
//////////////////////////////////////////////✨E N C O D E R ✨//////////////////////////////////////////////
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
///////////////////////////////////////////////////✨E N D ✨//////////////////////////////////////////////
