/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include QMK_KEYBOARD_H

#define KC_COPY_UPDATED LCTL(KC_C)
#define KC_CUT_UPDATED LCTL(KC_X)
#define KC_PASTE_UPDATED LCTL(KC_V)
#define KC_UNDO_UPDATED LCTL(KC_Z)
#define KC_REDO_UPDATED LCTL(KC_Y)
#define KC_FOCUS_BROWSER_BAR LCTL(KC_L)

// combos
const uint16_t PROGMEM esc_combo[]    = {LT(2, KC_TAB), LT(4, KC_SPC), COMBO_END};
const uint16_t PROGMEM delete_combo[] = {LT(3, KC_ENT), LT(1, KC_BSPC), COMBO_END};


combo_t key_combos[] = {
    COMBO(esc_combo, LT(6, KC_ESC)),
    COMBO(delete_combo, LT(5, KC_DEL)) // keycodes with modifiers are possible too!
};

//Tap Dance Declarations
enum {
 CT_CP,
 CT_PASTE,
 TD_APOSTROPHE
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

//All tap dance functions would go here. Only showing this one.
tap_dance_action_t tap_dance_actions[] = {
 [CT_CP] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cp_finished, dance_cp_reset),
 [CT_PASTE] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_paste_finished, dance_paste_reset),
 [TD_APOSTROPHE] = ACTION_TAP_DANCE_DOUBLE (KC_I, KC_QUOT)
};





const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    TD(TD_APOSTROPHE),    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    MT(MOD_LGUI, KC_A),    MT(MOD_LALT, KC_S),    MT(MOD_LCTL, KC_D),    MT(MOD_LSFT, KC_F),    KC_G,            KC_H,    MT(MOD_RSFT, KC_J),    MT(MOD_RCTL, KC_K),    MT(MOD_RALT, KC_L), MT(MOD_RGUI, KC_SCLN), KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    TD(CT_CP),    TD(CT_PASTE),    MT(KC_FOCUS_BROWSER_BAR, KC_B),                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          LT(6, KC_ESC),   LT(2, KC_TAB),  LT(4, KC_SPC),     LT(3, KC_ENT),   LT(1, KC_BSPC), LT(5, KC_DEL)
                                      //`--------------------------'  `--------------------------'

  ),

// numbers
    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,    KC_LBRC,    KC_7,    KC_8,    KC_9,    KC_RBRC,                KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   KC_QUOT,   KC_4,    KC_5,    KC_6, KC_EQL,                      KC_LEFT, MT(MOD_RSFT, KC_J),    MT(MOD_RCTL, KC_K),    MT(MOD_RALT, KC_L), MT(MOD_RGUI, KC_SCLN), XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_GRV,    KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_DOT, KC_0,  KC_PMNS,     KC_ENT,   MO(3), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

// navigation
    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_REDO_UPDATED, KC_PASTE_UPDATED, KC_COPY_UPDATED, KC_CUT_UPDATED,   KC_UNDO_UPDATED, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LGUI, KC_LALT,    KC_LCTL,    KC_LSFT, XXXXXXX,                KC_LEFT,  KC_DOWN,  KC_UP,   KC_RIGHT, KC_RIGHT,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HOME,  KC_PGDN,  KC_PGUP, KC_END, KC_END, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX,   XXXXXXX,  XXXXXXX,     KC_ENT, KC_WBAK, KC_WFWD
                                      //`--------------------------'  `--------------------------'
  ),

// symbols
    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, KC_DQT, KC_DLR, KC_PERC, KC_CIRC, KC_PLUS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_PIPE,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LPRN, KC_RPRN,  KC_UNDS,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

// mouse
    [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, KC_DLR, KC_PERC, KC_CIRC, KC_PLUS,                      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_PIPE,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_RPRN,  KC_SPC,     KC_BTN1, KC_BTN2, KC_BTN3
                                      //`--------------------------'  `--------------------------'
  ),

// function
    [5] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, KC_F11, KC_F4, KC_F5, KC_F6, KC_LSFT,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, KC_F10, KC_F1, KC_F2, KC_F3, KC_PAUS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_RPRN,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  // media
    [6] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MSEL, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_RPRN,  KC_SPC,     KC_MSTP, KC_MPLY, KC_MUTE
                                      //`--------------------------'  `--------------------------'
  ),

// gaming
    [7] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};

// const uint16_t PROGMEM test_combo1[] = {KC_A, KC_B, COMBO_END};
// const uint16_t PROGMEM test_combo2[] = {KC_C, KC_D, COMBO_END};
// combo_t key_combos[] = {
//     COMBO(test_combo1, KC_ESC),
//     COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too!
// };


#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }
    return rotation;
}

static void print_status_narrow(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("Numbers"), false);
            break;
        case 2:
            oled_write("Navigation", false);
            break;
        case 3:
            oled_write("Symbols", false);
            break;
        case 4:
            oled_write("Mouse", false);
            break;
        case 5:
            oled_write("Function  ", false);
            break;
        case 6:
            oled_write("Media  ", false);
            break;
        default:
            oled_write("Undef", false);
    }
}

__attribute__((weak)) void oled_render_logo(void) {
    // clang-format off
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    // clang-format on
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    // if (!oled_task_user()) {
    //     return false;
    // }
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        oled_render_logo();
    }
    return false;
}

#endif

//  bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
// }

// return true;
// }


// layer_state_t layer_state_set_user(layer_state_t state) {
//     switch (get_highest_layer(state)) {
//     case 0:
//         rgb_matrix_reload_from_eeprom();
//         break;
//     case 1: //numbers
//         rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
//         rgb_matrix_sethsv_noeeprom(HSV_BLUE);
//         break;
//     case 2: //nav
//         rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
//         rgb_matrix_sethsv_noeeprom(HSV_TEAL);
//         break;
//     case 3: //symbols
//         rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
//         rgb_matrix_sethsv_noeeprom(HSV_GREEN);
//         break;
//     case 4: //mouse
//         rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
//         rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
//         break;
//     case 5: //function
//         rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
//         rgb_matrix_sethsv_noeeprom(HSV_RED);
//         break;
//     case 6: //media
//         rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
//         rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
//         break;
//     }
//   return state;
// }




