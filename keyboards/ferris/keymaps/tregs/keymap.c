// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include <stdint.h>
#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

#define KC_COPY_UPDATED LCTL(KC_C)
#define KC_CUT_UPDATED LCTL(KC_X)
#define KC_PASTE_UPDATED LCTL(KC_V)
#define KC_UNDO_UPDATED LCTL(KC_Z)
#define KC_REDO_UPDATED LCTL(KC_Y)
#define KC_FOCUS_BROWSER_BAR LCTL(KC_L)

#ifdef TAPPING_TERM_PER_KEY                                                                                                                                                              
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_A:
            return TAPPING_TERM + 100;
        case KC_F:
        case KC_J:
        case KC_C:
        case KC_V:
        case KC_I:
            return TAPPING_TERM - 100;
        default:
            return TAPPING_TERM;
    }   
}       
#endif  


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_2(
  //,----------------------------------------.                    ,-----------------------------------------------------.
     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
  //|----+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     MT(MOD_LGUI, KC_A),    MT(MOD_LALT, KC_S),    MT(MOD_LCTL, KC_D),    MT(MOD_LSFT, KC_F),    KC_G,            KC_H,    MT(MOD_RSFT, KC_J),    MT(MOD_RCTL, KC_K),    MT(MOD_RALT, KC_L), MT(MOD_RGUI, KC_SCLN),
  //|----+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
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
      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,
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