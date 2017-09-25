/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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
#include "jc_icarus.h"
#include "keymap_extras/keymap_german.h"
#include "led.h"


enum jc_layers {
  _MAIN,    // Main Layer
  _COLE,    // Colemak Layer (Toggle)
  _SYMB,    // Symbol Layer (Momentary)
  _NAVI,    // Navigation Layer (Momentary)
  _NUMP,    // Numpad Layer (Momentary)
  _MIRR,    // Mirror Layer (Momentary)
  _CMIR,    // Colemak Mirror Layer (Momentary)
  _LHUB,    // Layer Hub (Momentary)
  _QMKL,    // QMK Layer (Toggle)
  _MEDI,    // Media Layer (Toggle)
};

enum jc_customplanck_keycodes {
  MAIN = SAFE_RANGE,
  COLE,
  SYMB,
  NAVI,
  NUMP,
  MIRR,
  CMIR,
  LHUB,
  QMKL,
  MEDI,
  DYNAMIC_MACRO_RANGE,  // has to be last entry!
};

#include "dynamic_macro.h"  // has to be after keycodes enum


enum jc_customplanck_macros {
  _M_MicM,
};

#define ________    KC_TRNS
#define XXXXXXXX    KC_NO
#define DE_MICR     ALGR(KC_M)

#define DM_REC1     DYN_REC_START1
#define DM_REC2     DYN_REC_START2
#define DM_PLY1     DYN_MACRO_PLAY1
#define DM_PLY2     DYN_MACRO_PLAY2
#define DM_STOP     DYN_REC_STOP

#define M_MicM      M(_M_MicM)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// _MAIN: Main Layer (QWERZ-DE)
[_MAIN] = KEYMAP(
    KC_ESC,    DE_1,    DE_2,    DE_3,    DE_4,    DE_5,                                            DE_6,    DE_7,    DE_8,    DE_9,    DE_0, KC_BSPC,
    KC_TAB,    DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,                                            DE_Z,    DE_U,    DE_I,    DE_O,    DE_P,   DE_SS,
   KC_CAPS,    DE_A,    DE_S,    DE_D,    DE_F,    DE_G,  KC_ENT,    LHUB,    XXXXXXXX,  KC_ENT,    DE_H,    DE_J,    DE_K,    DE_L,   DE_OE,   DE_AE,
   KC_LSFT,    DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,  KC_DEL, KC_BSPC,        MIRR,  KC_DEL,    DE_N,    DE_M, DE_COMM,  DE_DOT,   DE_UE, KC_RSFT,
   KC_LCTL, KC_LGUI, KC_LALT,    NAVI,           KC_SPC,    MIRR,    NUMP,        NUMP,    SYMB,           KC_SPC,    NAVI, KC_RALT, KC_RGUI, KC_RCTL
),

// _COLE: Colemak Layer (Custom-DE)
[_COLE] = KEYMAP(
    KC_ESC,    DE_1,    DE_2,    DE_3,    DE_4,    DE_5,                                            DE_6,    DE_7,    DE_8,    DE_9,    DE_0, KC_BSPC,
    KC_TAB,    DE_Q,    DE_W,    DE_F,    DE_P,    DE_G,                                            DE_J,    DE_L,    DE_U,    DE_Z,   DE_OE,   DE_SS,
   KC_CAPS,    DE_A,    DE_R,    DE_S,    DE_T,    DE_D,  KC_ENT,    LHUB,    XXXXXXXX,  KC_ENT,    DE_H,    DE_N,    DE_E,    DE_I,    DE_O,   DE_AE,
   KC_LSFT,    DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,  KC_DEL, KC_BSPC,        CMIR,  KC_DEL,    DE_K,    DE_M, DE_COMM,  DE_DOT,   DE_UE, KC_RSFT,
   KC_LCTL, KC_LGUI, KC_LALT,    NAVI,           KC_SPC,    CMIR,    NUMP,        NUMP,    SYMB,           KC_SPC,    NAVI, KC_RALT, KC_RGUI, KC_RCTL
),



// [_PLACEHOLDER] = KEYMAP(
//   XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,                                       ,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,
//   XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,                                       ,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,
//   XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,    XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,
//   XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,    XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,
//   XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,         XXXXXXXX,XXXXXXXX,XXXXXXXX,    XXXXXXXX,XXXXXXXX,         XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX
// ),

};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case _M_MicM:
          return MACRODOWN(D(CAPS), T(GRAVE), U(CAPS), END);
          break;
      }
    return MACRO_NONE;
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MAIN:
        if (record->event.pressed) {
          persistant_default_layer_set(1UL<<_MAIN);
        }
        return false;
        break;
    case COLE:
        if (record->event.pressed) {
          persistant_default_layer_set(1UL<<_COLE);
        }
        return false;
        break;
    case SYMB:
        if (record->event.pressed) {
            layer_on(_SYMB);
        }
        else {
            layer_off(_SYMB);
        }
        return false;
        break;
    case NAVI:
        if (record->event.pressed) {
            layer_on(_NAVI);
        }
        else {
            layer_off(_NAVI);
        }
        return false;
        break;
    case NUMP:
        if (record->event.pressed) {
            layer_on(_NUMP);
        }
        else {
            layer_off(_NUMP);
        }
        return false;
        break;
    case MIRR:
        if (record->event.pressed) {
            layer_on(_MIRR);
        }
        else {
            layer_off(_MIRR);
        }
        return false;
        break;
    case CMIR:
        if (record->event.pressed) {
            layer_on(_CMIR);
        }
        else {
            layer_off(_CMIR);
        }
        return false;
        break;
    case LHUB:
        if (record->event.pressed) {
            layer_on(_LHUB);
        }
        else {
            layer_off(_LHUB);
        }
        return false;
        break;
    case MEDI:
        if (record->event.pressed) {
            if(IS_LAYER_OFF(_MEDI)) {
              layer_on(_MEDI);
              layer_off(_LHUB);
            }
            else if(IS_LAYER_ON(_MEDI)) {
              layer_off(_MEDI);
              layer_on(_LHUB);
            }
        }
        return false;
        break;
    case QMKL:
        if (record->event.pressed) {
            if(IS_LAYER_OFF(_QMKL)) {
              layer_on(_QMKL);
              layer_off(_LHUB);
            }
            else if(IS_LAYER_ON(_QMKL)) {
              layer_off(_QMKL);
              layer_on(_LHUB);
            }
        }
        return false;
        break;
  }

  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }
  
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
