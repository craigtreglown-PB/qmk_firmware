// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include <stdint.h>
#include QMK_KEYBOARD_H
#include g/keymap_combo.h

#define KC_COPY_UPDATED LCTL(KC_C)
#define KC_CUT_UPDATED LCTL(KC_X)
#define KC_PASTE_UPDATED LCTL(KC_V)
#define KC_UNDO_UPDATED LCTL(KC_Z)
#define KC_REDO_UPDATED LCTL(KC_Y)
#define KC_FOCUS_BROWSER_BAR LCTL(KC_L)




/*
Advanced tapdance stuff
*/

// tapdance keycodes
enum td_keycodes {
  ALT_LP // Our example key: `LALT` when held, `(` when tapped. Add additional keycodes for each tapdance.
};

// define a type containing as many tapdance states as you need
typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_SINGLE_TAP
} td_state_t;

// create a global instance of the tapdance state type
static td_state_t td_state;

// declare your tapdance functions:

// `finished` and `reset` functions for each tapdance keycode
void altlp_finished (tap_dance_state_t *state, void *user_data);
void altlp_reset (tap_dance_state_t *state, void *user_data);

/*
End advanced tapdance stuff
*/


//Tap Dance Declarations
enum {
 CT_CP,
 CT_PASTE,
 TD_APOSTROPHE,
 J_ESC_TD
};


//Tap Dance Definitions

//copy on double tap c
void dance_cp_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_C);
  } else {
    register_code (KC_RCTL);
    register_code (KC_C);
  }
}

void dance_cp_reset (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_C);
  } else {
    unregister_code (KC_RCTL);
    unregister_code (KC_C);
  }
}

//paste on double tap v
void dance_paste_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_V);
  } else {
    register_code (KC_RCTL);
    register_code (KC_V);
  }
}

void dance_paste_reset (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_V);
  } else {
    unregister_code (KC_RCTL);
    unregister_code (KC_V);
  }
}



// determine the tapdance state to return
int cur_dance_advanced (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) { return SINGLE_TAP; }
    else { return SINGLE_HOLD; }
  }
  if (state->count == 2) { return DOUBLE_SINGLE_TAP; }
  else { return 3; } // any number higher than the maximum state value you return above
}
 
// handle the possible states for each tapdance keycode you define:

void J_ESC_TD_finished (tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance_advanced(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_J);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RSFT)); // for a layer-tap key, use `layer_on(_MY_LAYER)` here
      break;
    case DOUBLE_SINGLE_TAP: // allow nesting of 2 parens `((` within tapping term
      tap_code16(KC_ESC);
      register_code16(KC_ESC);
  }
}

void J_ESC_TD_reset (tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_J);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_RSFT)); // for a layer-tap key, use `layer_off(_MY_LAYER)` here
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_ESC);
  }
}




//All tap dance functions would go here. Only showing this one.
tap_dance_action_t tap_dance_actions[] = {
 [CT_CP] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cp_finished, dance_cp_reset),
 [CT_PASTE] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_paste_finished, dance_paste_reset),
 [TD_APOSTROPHE] = ACTION_TAP_DANCE_DOUBLE (KC_I, KC_QUOT),
 [J_ESC_TD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, J_ESC_TD_finished, J_ESC_TD_reset)
};




// combos
const uint16_t PROGMEM esc_combo[]    = {LT(2, KC_TAB), LT(4, KC_SPC), COMBO_END};
const uint16_t PROGMEM delete_combo[] = {LT(3, KC_ENT), LT(1, KC_BSPC), COMBO_END};
const uint16_t PROGMEM esc_combo_jk[] = {MT(MOD_RSFT, KC_J), MT(MOD_RCTL, KC_K), COMBO_END};
const uint16_t PROGMEM right_hyper_combo[] = {TD(J_ESC_TD),    MT(MOD_RCTL, KC_K),    MT(MOD_RALT, KC_L), MT(MOD_RGUI, KC_SCLN), COMBO_END};


combo_t key_combos[] = {
    COMBO(esc_combo, LT(6, KC_ESC)),
    COMBO(delete_combo, LT(5, KC_DEL)),
    COMBO(esc_combo_jk, KC_ESC),
    COMBO(right_hyper_combo, KC_HYPR)
};     






const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_2(
  //,----------------------------------------.                    ,-----------------------------------------------------.
     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    TD(TD_APOSTROPHE),    KC_O,   KC_P,
  //|----+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     MT(MOD_LGUI, KC_A),    MT(MOD_LALT, KC_S),    MT(MOD_LCTL, KC_D),    MT(MOD_LSFT, KC_F),    KC_G,            KC_H,    TD(J_ESC_TD),    MT(MOD_RCTL, KC_K),    MT(MOD_RALT, KC_L), MT(MOD_RGUI, KC_SCLN),
  //|----+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_Z,    KC_X,    TD(CT_CP),    TD(CT_PASTE),    MT(KC_FOCUS_BROWSER_BAR, KC_B),                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
  //|----+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          LT(2, KC_TAB),  LT(4, KC_SPC),     LT(3, KC_ENT),   LT(1, KC_BSPC)
                                      //`--------------------------'  `--------------------------'

  ),

// numbers
    [1] = LAYOUT_split_3x5_2(
  //,------------------------------------------.                    ,-----------------------------------------------------.
      KC_LBRC,    KC_7,    KC_8,    KC_9,    KC_RBRC,                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  //|------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_QUOT,   KC_4,    KC_5,    KC_6, KC_EQL,                      KC_LEFT, MT(MOD_RSFT, KC_J),    MT(MOD_RCTL, KC_K),    MT(MOD_RALT, KC_L), MT(MOD_RGUI, KC_SCLN),
  //|------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_0,  KC_PMNS,     KC_ENT,   MO(3)
                                      //`--------------------------'  `--------------------------'
  ),

// navigation
    [2] = LAYOUT_split_3x5_2(
  //,---------------------------------------------.                    ,-----------------------------------------------------.
      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_REDO_UPDATED, KC_PASTE_UPDATED, KC_COPY_UPDATED, KC_CUT_UPDATED,   KC_UNDO_UPDATED,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI, KC_LALT,    KC_LCTL,    KC_LSFT, XXXXXXX,                KC_LEFT,  KC_DOWN,  KC_UP,   KC_RIGHT, KC_RIGHT,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HOME,  KC_PGDN,  KC_PGUP, KC_END, KC_END,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX,  XXXXXXX,     KC_ENT, KC_WBAK
                                      //`--------------------------'  `--------------------------'
  ),

// symbols
    [3] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,---------------------------------------------
      KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      KC_DQT, KC_DLR, KC_PERC, KC_CIRC, KC_PLUS,                      XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX,  
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_PIPE,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                          KC_RPRN,  KC_UNDS,     KC_ENT, _______
                                      //`--------------------------'  `--------------------------'
  ),

// mouse
    [4] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,---------------------------------------------
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, 
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                          KC_RPRN,  KC_SPC,     KC_BTN1, KC_BTN2
                                      //`--------------------------'  `--------------------------'
  ),

// function
    [5] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,-----------------------------------------------.
      KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--|
      KC_F11, KC_F4, KC_F5, KC_F6, KC_LSFT,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--|
      KC_F10, KC_F1, KC_F2, KC_F3, KC_PAUS,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--|
                                          KC_RPRN,  KC_SPC,     KC_ENT, _______
                                      //`--------------------------'  `--------------------------'
  ),

  // media
    [6] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,----------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+-|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MSEL, 
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+-|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+-|
                                          KC_RPRN,  KC_SPC,     KC_MUTE, KC_MPLY
                                      //`--------------------------'  `--------------------------'
  ),

// gaming
    [7] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,---------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                          _______,  KC_SPC,     KC_ENT, _______
                                      //`--------------------------'  `--------------------------'
  )
};