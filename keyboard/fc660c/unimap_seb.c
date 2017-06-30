#include "action.h"
#include "actionmap.h"
#include "hook.h"
#include "fc660c.h"
#include "debug.h"


/* id for user defined functions */
enum function_id {
    LSHIFT_LPAREN,
    LSHIFT_LPAREN_L2,
    RSHIFT_RPAREN,
    RSHIFT_RPAREN_L2,
};

#define AC_L3       ACTION_LAYER_MOMENTARY(3)
#define AC_L4       ACTION_LAYER_MOMENTARY(4)
#define AC_LS_2     ACTION_LAYER_MODS(2, MOD_LSFT)
#define AC_RS_2     ACTION_LAYER_MODS(2, MOD_RSFT)
#define AC_TGL1     ACTION_LAYER_TOGGLE(1)

#define AC_LPRN     ACTION_FUNCTION_TAP(LSHIFT_LPAREN)
#define AC_LP_2     ACTION_FUNCTION_TAP(LSHIFT_LPAREN_L2)
#define AC_RPRN     ACTION_FUNCTION_TAP(RSHIFT_RPAREN)
#define AC_RP_2     ACTION_FUNCTION_TAP(RSHIFT_RPAREN_L2)

#define AC_SP_3     ACTION_LAYER_TAP_KEY(3, KC_SPACE)
#define AC_SP_4     ACTION_LAYER_TAP_KEY(4, KC_SPACE)

// emulates FC660C default keymap
#ifdef KEYMAP_SECTION_ENABLE
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] PROGMEM = {
#endif
    [0] = KMAP(
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS,
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL,
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,
        //LS_2,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RS_2,UP,
        LP_2,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RP_2,UP,
        LCTL,LGUI,LALT,          SP_3,                     RALT,RCTL,L3,  LEFT,DOWN,RGHT
    ),
    [1] = KMAP(
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS,
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL,
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,
        //LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT,UP,
        LPRN,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RPRN,UP,
        LCTL,LGUI,LALT,          SP_4,                     RALT,RCTL,L4,  LEFT,DOWN,RGHT
    ),
    [2] = KMAP(
        GRV, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,TRNS,
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS
    ),
    [3] = KMAP(
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,     TRNS,
        CAPS,TGL1,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS,TRNS,TRNS,TRNS,     TRNS,
        TRNS,VOLD,VOLU,MUTE,TRNS,TRNS,TRNS,TRNS,HOME,PGUP,TRNS,TRNS,     TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,END, PGDN,TRNS,          TRNS,PGUP,
        TRNS,TRNS,TRNS,          SP_3,                    TRNS,APP, L3,  HOME,PGDN,END
    ),
    [4] = KMAP(
        ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,     TRNS,
        CAPS,TGL1,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS,TRNS,TRNS,TRNS,     TRNS,
        TRNS,VOLD,VOLU,MUTE,TRNS,TRNS,TRNS,TRNS,HOME,PGUP,TRNS,TRNS,     TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,END, PGDN,TRNS,          TRNS,PGUP,
        TRNS,TRNS,TRNS,          SP_4,                    TRNS,APP, L4,  HOME,PGDN,END
    ),
};

/*
 * user defined action function
 */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (record->event.pressed) dprint("P"); else dprint("R");
    dprintf("%d", record->tap.count);
    if (record->tap.interrupted) dprint("i");
    dprint("\n");

    switch (id) {
        case LSHIFT_LPAREN:
        case LSHIFT_LPAREN_L2:
            // Shift parentheses example: LShft + tap '('
            // http://stevelosh.com/blog/2012/10/a-modern-space-cadet/#shift-parentheses
            // http://geekhack.org/index.php?topic=41989.msg1304899#msg1304899
            if (record->event.pressed) {
                if (record->tap.count > 0 && !record->tap.interrupted) {
                    if (record->tap.interrupted) {
                        dprint("tap interrupted\n");
                        register_mods(MOD_BIT(KC_LSHIFT));
                        if (id == LSHIFT_LPAREN_L2) layer_on(2);
                    }
                } else {
                    register_mods(MOD_BIT(KC_LSHIFT));
                    if (id == LSHIFT_LPAREN_L2) layer_on(2);
                }
            } else {
                if (record->tap.count > 0 && !(record->tap.interrupted)) {
                    add_weak_mods(MOD_BIT(KC_LSHIFT));
                    send_keyboard_report();
                    register_code(KC_9);
                    unregister_code(KC_9);
                    del_weak_mods(MOD_BIT(KC_LSHIFT));
                    send_keyboard_report();
                    record->tap.count = 0;  // ad hoc: cancel tap
                } else {
                    unregister_mods(MOD_BIT(KC_LSHIFT));
                    if (id == LSHIFT_LPAREN_L2) layer_off(2);
                }
            }
            break;
        case RSHIFT_RPAREN:
        case RSHIFT_RPAREN_L2:
            // Shift parentheses example: LShft + tap '('
            // http://stevelosh.com/blog/2012/10/a-modern-space-cadet/#shift-parentheses
            // http://geekhack.org/index.php?topic=41989.msg1304899#msg1304899
            if (record->event.pressed) {
                if (record->tap.count > 0 && !record->tap.interrupted) {
                    if (record->tap.interrupted) {
                        dprint("tap interrupted\n");
                        register_mods(MOD_BIT(KC_RSHIFT));
                        if (id == RSHIFT_RPAREN_L2) layer_on(2);
                    }
                } else {
                    register_mods(MOD_BIT(KC_RSHIFT));
                    if (id == RSHIFT_RPAREN_L2) layer_on(2);
                }
            } else {
                if (record->tap.count > 0 && !(record->tap.interrupted)) {
                    add_weak_mods(MOD_BIT(KC_RSHIFT));
                    send_keyboard_report();
                    register_code(KC_0);
                    unregister_code(KC_0);
                    del_weak_mods(MOD_BIT(KC_RSHIFT));
                    send_keyboard_report();
                    record->tap.count = 0;  // ad hoc: cancel tap
                } else {
                    unregister_mods(MOD_BIT(KC_RSHIFT));
                    if (id == RSHIFT_RPAREN_L2) layer_off(2);
                }
            }
            break;

    }
}

void hook_layer_change(uint32_t layer_state)
{
    // lights LED on Insert when layer 1 is enabled
    if (layer_state & (1L<<1)) {
        PORTB &= ~(1<<5);
    } else {
        PORTB |=  (1<<5);
    }
}
