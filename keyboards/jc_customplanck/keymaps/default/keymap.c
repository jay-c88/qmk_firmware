/* Copyright 2017 JC
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

#include "jc_customplanck.h"
#include "action_layer.h"
#include "keymap_extras/keymap_german.h"
#include "rgblight.h"
#include "led.h"
#include "avr/wdt.h"
#include "eeconfig.h"
#include <avr/eeprom.h>

const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {100, 50, 10};

enum jc_layers {
  _MAIN,    // Main Layer
  _COLE,    // Colemak Layer (Toggle)
  _NUMB,    // Number Layer (Momentary)
  _SYMB,    // Symbol Layer (Momentary)
  _NAVI,    // Navigation Layer (Momentary)
  _LHUB,    // Layer Hub (Momentary)
  _MEDI,    // Media Layer (Toggle)
  _NUMP,    // NumPad Layer (Toggle)
  _MOUS,    // Mouse Layer (Toggle)
  _QMKL,    // QMK Layer (Toggle)
  _DIA3,    // Diablo 3 Layer (Toggle)
  _D3FN,    // Diablo 3 FN Layer (Macros) (Momentary)
};

enum jc_customplanck_keycodes {
  MAIN = SAFE_RANGE,
  COLE,
  LHUB,
  MEDI,
  NUMP,
  MOUS,
  QMKL,
  DIA3,
  D3FN,
  DYNAMIC_MACRO_RANGE,  // has to be last entry!
};

#include "dynamic_macro.h"  // has to be after keycodes enum

enum jc_customplanck_functions {
  __LLUP,
  __LLDN,
};

enum jc_customplanck_macros {
  _M_D3_Clr,
  _M_D3_1L,
  _M_D3_2L,
  _M_D3_3L,
  _M_D3_4L,
  _M_D3_ClTn,
  _M_MicM,
};

#define __________  KC_TRNS
#define XXXXXXXXXX  KC_NO
#define DE_MICR     ALGR(KC_M)

#define DM_REC1     DYN_REC_START1
#define DM_REC2     DYN_REC_START2
#define DM_PLY1     DYN_MACRO_PLAY1
#define DM_PLY2     DYN_MACRO_PLAY2
#define DM_STOP     DYN_REC_STOP

#define D3_Clr      M(_M_D3_Clr)
#define D3_1L       M(_M_D3_1L)
#define D3_2L       M(_M_D3_2L)
#define D3_3L       M(_M_D3_3L)
#define D3_4L       M(_M_D3_4L)
#define D3_ClTn     M(_M_D3_ClTn)
#define M_MicM      M(_M_MicM)

uint8_t layer_led_val_step_max = 6;
uint8_t layer_led_val_step = 6;



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* _MAIN: Main Layer (QWERZ-DE)
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Z  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ö  |   Ä  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Y  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   Ü  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |_NAVI |_NUMB |_LHUB |_SYMB | SPC  |_NAVI | Del  |   ß  | Enter|
 * `-----------------------------------------------------------------------------------'
 */
[_MAIN] = KEYMAP(
    KC_TAB,      DE_Q,      DE_W,      DE_E,      DE_R,      DE_T,      DE_Z,      DE_U,      DE_I,      DE_O,      KC_P,   KC_BSPC,
   KC_CAPS,      DE_A,      DE_S,      DE_D,      DE_F,      DE_G,      DE_H,      DE_J,      DE_K,      DE_L,     DE_OE,     DE_AE,
   KC_LSFT,      DE_Y,      DE_X,      DE_C,      DE_V,      DE_B,      DE_N,      DE_M,   DE_COMM,    DE_DOT,     DE_UE,   KC_RSFT,
   KC_LCTL,   KC_LGUI,   KC_LALT, MO(_NAVI), MO(_NUMB),      LHUB, MO(_SYMB),    KC_SPC, MO(_NAVI),    KC_DEL,     DE_SS,    KC_ENT
),

/* _COLE: Colemak Layer
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   Ö  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |   Ä  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   Ü  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |_NAVI |_NUMB |_LHUB |_SYMB | SPC  |_NAVI | Del  |   ß  | Enter|
 * `-----------------------------------------------------------------------------------'
 */
[_COLE] = KEYMAP(
    KC_TAB,      KC_Q,      KC_W,      KC_F,      KC_P,      KC_G,      KC_J,      KC_L,      KC_U,      KC_Y,     DE_OE,   KC_BSPC,
   KC_CAPS,      KC_A,      KC_R,      KC_S,      KC_T,      KC_D,      KC_H,      KC_N,      KC_E,      KC_I,      KC_O,     DE_AE,
   KC_LSFT,      KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_K,      KC_M,   KC_COMM,    KC_DOT,     DE_UE,   KC_RSFT,
   KC_LCTL,   KC_LGUI,   KC_LALT, MO(_NAVI), MO(_NUMB),      LHUB, MO(_SYMB),    KC_SPC, MO(_NAVI),    KC_DEL,     DE_SS,    KC_ENT
),

/* _NUMB: Number Layer (Momentary)
 * ,-----------------------------------------------------------------------------------.
 * |  Esc | Bksp |   7  |   8  |   9  |  Del |   %  |   7  |   8  |   9  |   +  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Enter|   4  |   5  |   6  | XXXX |   .  |   4  |   5  |   6  |   -  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | SPC  |   1  |   2  |   3  |   0  |   0  |   1  |   2  |   3  |   *  |   /  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |   0  |      | XXXX | XXXX |      |   0  |   ,  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMB] = KEYMAP(
    KC_ESC,   KC_BSPC,      DE_7,      DE_8,      DE_9,    KC_DEL,   DE_PERC,      DE_7,      DE_8,      DE_9,   DE_PLUS,__________,
__________,    KC_ENT,      DE_4,      DE_5,      DE_6,XXXXXXXXXX,    DE_DOT,      DE_4,      DE_5,      DE_6,   DE_MINS,    DE_EQL,
__________,    KC_SPC,      DE_1,      DE_2,      DE_3,      DE_0,      DE_0,      DE_1,      DE_2,      DE_3,   DE_ASTR,   DE_SLSH,
__________,__________,__________,      DE_0,__________,XXXXXXXXXX,XXXXXXXXXX,__________,      DE_0,   DE_COMM,__________,__________
),

/* _SYMB: Symbol Layer (UNICODE ONLY!) (Momentary)
 * ,-----------------------------------------------------------------------------------.
 * |   ^  |   @  |   "  |   €  |   $  |   %  |   §  |   <  |   >  |   =  |   +  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   °  |   [  |   ]  |   {  |   }  |   !  |   ?  |   (  |   )  |   -  |   :  |   '  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   `  |   ´  | XXXX |   ~  |   |  |   &  |   *  |   _  |   \  |   /  |   ;  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | XXXX | XXXX | XXXX |      |      | XXXX |      |   µ   |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMB] = KEYMAP(
   DE_CIRC,     DE_AT,   DE_DQOT,   DE_EURO,    DE_DLR,   DE_PERC,   DE_PARA,   DE_LESS,   DE_MORE,    DE_EQL,   DE_PLUS,   DE_HASH,
   DE_RING,   DE_LBRC,   DE_RBRC,   DE_LCBR,   DE_RCBR,   DE_EXLM,    DE_QST,   DE_LPRN,   DE_RPRN,   DE_MINS,   DE_COLN,   DE_QUOT,
__________,    DE_GRV,   DE_ACUT,XXXXXXXXXX,   DE_TILD,   DE_PIPE,   DE_AMPR,   DE_ASTR,   DE_UNDS,   DE_BSLS,   DE_SLSH,   DE_SCLN,
__________,__________,__________,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,__________,__________,XXXXXXXXXX,__________,   DE_MICR,__________
),

/* _NAVI: Navigation Layer (Momentary)
 * ,-----------------------------------------------------------------------------------.
 * |  Esc | PgUp | Home |  Up  |  End | NLock| XXXX | Home |  Up  |  End | PgUp |  ESC |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | PgDn | Left | Down | Right|  F6  |  F7  | Left | Down | Right| PgDn |  Ins |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F8  |  F9  |  F10 |  F11 |  F12 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | MMute|PrnScr|ScrLck| Pause|      |  Alt |  Win | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_NAVI] = KEYMAP(
    KC_ESC,   KC_PGUP,   KC_HOME,     KC_UP,    KC_END,   KC_NLCK,XXXXXXXXXX,   KC_HOME,     KC_UP,    KC_END,   KC_PGUP,    KC_ESC,
__________,   KC_PGDN,   KC_LEFT,   KC_DOWN,   KC_RGHT,     KC_F6,     KC_F7,   KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_PGDN,    KC_INS,
__________,     KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F8,     KC_F9,    KC_F10,    KC_F11,    KC_F12,__________,
__________,__________,__________,__________,    M_MicM,   KC_PSCR,   KC_SLCK,   KC_PAUS,__________,   KC_RALT,   KC_RGUI,   KC_RCTL
),

/* _LHUB: Layer Hub Layer(Momentary)
 * ,-----------------------------------------------------------------------------------.
 * |_QMKL | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX |_MOUS | XXXX |_DIA3 | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |_MEDI | XXXX | XXXX | XXXX | _NUMP|      |_MAIN |_COLE | XXXX | XXXX | XXXX |_MEDI |
 * `-----------------------------------------------------------------------------------'
 */
[_LHUB] = KEYMAP(
      QMKL,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
XXXXXXXXXX,      MOUS,XXXXXXXXXX,      DIA3,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
      MEDI,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,      NUMP,__________,      MAIN,      COLE,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,      MEDI
),

/* _MEDI: Media Layer (Toggle)
 * ,-----------------------------------------------------------------------------------.
 * |  Esc | MStop| Vol- | Mute | Vol+ | XXXX |MAccl0| MScrL|  MUp | MScrR| MScrU| Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Enter| MRwd | MPrev| MPlay| MNext| MFfd |MAccl1| MLeft| MDown| MRght| MScrD| Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Del | WStop| WBak | WRef | WFwd | XXXX |MAccl2|  M3  |  M4  |  M5  |  Up  | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ,  |   .  | XXXX | XXXX | Space| TGOFF| Space|  M1  |  M2  | Left | Down | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_MEDI] = KEYMAP(
    KC_ESC,   KC_MSTP,   KC_VOLD,   KC_MUTE,   KC_VOLU,XXXXXXXXXX,   KC_ACL0,   KC_WH_L,   KC_MS_U,   KC_WH_R,   KC_WH_U,   KC_BSPC,
    KC_ENT,   KC_MRWD,   KC_MPRV,   KC_MPLY,   KC_MNXT,   KC_MFFD,   KC_ACL1,   KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_WH_D,    KC_ENT,
    KC_DEL,   KC_WSTP,   KC_WBAK,   KC_WREF,   KC_WFWD,XXXXXXXXXX,   KC_ACL2,   KC_BTN3,   KC_BTN4,   KC_BTN5,     KC_UP,XXXXXXXXXX,
   KC_COMM,    KC_DOT,XXXXXXXXXX,XXXXXXXXXX,    KC_SPC,      MEDI,    KC_SPC,   KC_BTN1,   KC_BTN2,   KC_LEFT,   KC_DOWN,   KC_RGHT
),

/* _NUMP: NumPad Layer (Toggle)
 * ,-----------------------------------------------------------------------------------.
 * | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | NmLk |   7  |   8  |   9  |   +  |   /  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |   4  |   5  |   6  |   -  | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |   1  |   2  |   3  |   *  | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | XXXX | XXXX | XXXX | XXXX | TGOFF| Space|   0  |   0  |   .  | XXXX | Enter|
 * `-----------------------------------------------------------------------------------'
 */
[_NUMP] = KEYMAP(
XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,   KC_NLCK,     KC_P7,     KC_P8,     KC_P9,   KC_PPLS,   KC_PSLS,
XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,     KC_P4,     KC_P5,     KC_P6,   KC_PMNS,XXXXXXXXXX,
XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,     KC_P1,     KC_P2,     KC_P3,   KC_PAST,XXXXXXXXXX,
XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,      NUMP,    KC_SPC,     KC_P0,     KC_P0,   KC_PDOT,XXXXXXXXXX,   KC_PENT
),

/* _MOUS: Mouse Layer (Toggle)
 * ,-----------------------------------------------------------------------------------.
 * |  Esc | Bksp |  M4  |  MUp |  M5  | MScrU|MAccl0| XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Tab | Enter| MLeft| MDown| MRght| MScrD|MAccl1| XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift| Space|  Del | WRef | MScrL| MScrR|MAccl2| XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  Alt |  M3  |  M2  |  M1  | TGOFF| XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUS] = KEYMAP(
    KC_ESC,   KC_BSPC,   KC_BTN4,   KC_MS_U,   KC_BTN5,   KC_WH_U,   KC_ACL0,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
    KC_TAB,    KC_ENT,   KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_WH_D,   KC_ACL1,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
   KC_LSFT,    KC_SPC,    KC_DEL,   KC_WREF,   KC_WH_L,   KC_WH_R,   KC_ACL2,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
   KC_LCTL,   KC_LALT,   KC_BTN3,   KC_BTN2,   KC_BTN1,      MOUS,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX
),

/* _QMKL: QMK Layer (Toggle)
 * ,-----------------------------------------------------------------------------------.
 * | XXXX | Hue- | Hue+ | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | Reset|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | Sat- | Sat+ |LEDCyc|LEDTog| XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | Debug|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | Val- | Val+ | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | DRec1| DRec2|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | XXXX | XXXX | XXXX | XXXX | TGOFF| XXXX | XXXX | XXXX | DStpR| DPly1| DPly2|
 * `-----------------------------------------------------------------------------------'
 */
[_QMKL] = KEYMAP(
XXXXXXXXXX,   RGB_HUD,   RGB_HUI, F(__LLDN), F(__LLUP),XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,     RESET,
XXXXXXXXXX,   RGB_SAD,   RGB_SAI,   RGB_MOD,   RGB_TOG,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,     DEBUG,
XXXXXXXXXX,   RGB_VAD,   RGB_VAI,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,   DM_REC1,   DM_REC2,
XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,      QMKL,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,   DM_STOP,   DM_PLY1,   DM_PLY2
),

/* _DIA3: 
 * ,-----------------------------------------------------------------------------------.
 * |||||||||||||
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |||||||||||||
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |||||||||||||
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |||||||||||||
 * `-----------------------------------------------------------------------------------'
 */
[_DIA3] = KEYMAP(
    KC_ESC,      DE_1,      DE_2,      DE_3,      DE_4,      DE_5,   KC_PGUP,XXXXXXXXXX,XXXXXXXXXX,      DE_9,      DE_0,   KC_BSPC,
    KC_TAB,      DE_Q,      DE_S,      DE_D,      DE_F,      DE_T,   KC_PGDN,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,    KC_ENT,
   KC_LSFT,      DE_M,      DE_X,      DE_C,      DE_V,      DE_G,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
   KC_LCTL,     KC_F5,   KC_LALT,      D3FN,   KC_LSFT,    KC_SPC,   KC_LALT,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,      DIA3
),

/* _D3FN: 
 * ,-----------------------------------------------------------------------------------.
 * |||||||||||||
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |||||||||||||
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |||||||||||||
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |||||||||||||
 * `-----------------------------------------------------------------------------------'
 */
[_D3FN] = KEYMAP(
    D3_Clr,     D3_1L,     D3_2L,     D3_3L,     D3_4L,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
     KC_F9,      DE_L,      DE_J,      DE_O,      DE_P,   D3_ClTn,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
   KC_PSCR,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
    KC_ENT,XXXXXXXXXX,XXXXXXXXXX,__________,    M_MicM,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX
),

};

/* id for user defined functions */
enum function_id {
    LAYERLED_DOWN,
    LAYERLED_UP,
};

/*
* user defined action function
*/
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case LAYERLED_DOWN:
            if (record->event.pressed) {
              if (layer_led_val_step - 1 < 1) {
                layer_led_val_step = 1;
              }
              else {
                layer_led_val_step = layer_led_val_step - 1;
              }
              eeprom_update_byte(EECONFIG_LAYERLEDSTATUS, layer_led_val_step);
            }
            break;
        case LAYERLED_UP:
            if (record->event.pressed) {
              if (layer_led_val_step + 1 > layer_led_val_step_max) {
                layer_led_val_step = layer_led_val_step_max;
              }
              else {
                layer_led_val_step = layer_led_val_step + 1;
              }
              eeprom_update_byte(EECONFIG_LAYERLEDSTATUS, layer_led_val_step);
            }
            break;
        default:
            break;
    }
}


/*
*   fn_actions
*/
const uint16_t PROGMEM fn_actions[] = {
  [__LLDN] = ACTION_FUNCTION(LAYERLED_DOWN),
  [__LLUP] = ACTION_FUNCTION(LAYERLED_UP),
};



const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case _M_D3_Clr:
          if (record->event.pressed) {
            unregister_code(KC_P1);
            unregister_code(KC_P2);
            unregister_code(KC_P3);
            unregister_code(KC_P4);
          }
          return false;
          break;
        case _M_D3_1L:
          if (record->event.pressed) {
            register_code(KC_P1);
          }
          return false;
          break;
        case _M_D3_2L:
          if (record->event.pressed) {
            register_code(KC_P2);
          }
          return false;
          break;
        case _M_D3_3L:
          if (record->event.pressed) {
            register_code(KC_P3);
          }
          return false;
          break;
        case _M_D3_4L:
          if (record->event.pressed) {
            register_code(KC_P4);
          }
          return false;
          break;
        case _M_D3_ClTn:
          if (record->event.pressed) {
            unregister_code(KC_P1);
            unregister_code(KC_P2);
            unregister_code(KC_P3);
            unregister_code(KC_P4);
            register_code(KC_T);
          } else {
            unregister_code(KC_T);
          }
          return false;
          break;
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
    case NUMP:
        if (record->event.pressed) {
            if(IS_LAYER_OFF(_NUMP)) {
              layer_on(_NUMP);
              layer_off(_LHUB);
            }
            else if(IS_LAYER_ON(_NUMP)) {
              layer_off(_NUMP);
              layer_on(_LHUB);
            }
        }
        return false;
        break;
    case MOUS:
        if (record->event.pressed) {
            if(IS_LAYER_OFF(_MOUS)) {
              layer_on(_MOUS);
              layer_off(_LHUB);
            }
            else if(IS_LAYER_ON(_MOUS)) {
              layer_off(_MOUS);
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
    case DIA3:
        if (record->event.pressed) {
            if(IS_LAYER_OFF(_DIA3)) {
              layer_on(_DIA3);
              layer_off(_LHUB);
            }
            else if(IS_LAYER_ON(_DIA3)) {
              layer_off(_DIA3);
            }
        }
        return false;
        break;
    case D3FN:
        if (record->event.pressed) {
            layer_on(_D3FN);
        }
        else {
            layer_off(_D3FN);
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
  layer_led_val_step = eeprom_read_byte(EECONFIG_LAYERLEDSTATUS);
}

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    switch (layer) {
        case _NUMB:
            led[6].r = 255 * layer_led_val_step / layer_led_val_step_max;
            led[6].g = 127 * layer_led_val_step / layer_led_val_step_max;
            led[6].b = 0 * layer_led_val_step / layer_led_val_step_max;
            ws2812_setleds(led, 8);
            break;
        case _SYMB:
            led[6].r = 255 * layer_led_val_step / layer_led_val_step_max;
            led[6].g = 255 * layer_led_val_step / layer_led_val_step_max;
            led[6].b = 0 * layer_led_val_step / layer_led_val_step_max;
            ws2812_setleds(led, 8);
            break;
        case _NAVI:
            led[6].r = 0 * layer_led_val_step / layer_led_val_step_max;
            led[6].g = 255 * layer_led_val_step / layer_led_val_step_max;
            led[6].b = 0 * layer_led_val_step / layer_led_val_step_max;
            ws2812_setleds(led, 8);
            break;
        case _LHUB:
            led[6].r = 120 * layer_led_val_step / layer_led_val_step_max;
            led[6].g = 120 * layer_led_val_step / layer_led_val_step_max;
            led[6].b = 220 * layer_led_val_step / layer_led_val_step_max;
            ws2812_setleds(led, 8);
            break;
        case _MEDI:
            led[6].r = 70 * layer_led_val_step / layer_led_val_step_max;
            led[6].g = 230 * layer_led_val_step / layer_led_val_step_max;
            led[6].b = 230 * layer_led_val_step / layer_led_val_step_max;
            ws2812_setleds(led, 8);
            break;
        case _NUMP:
            led[6].r = 190 * layer_led_val_step / layer_led_val_step_max;
            led[6].g = 41 * layer_led_val_step / layer_led_val_step_max;
            led[6].b = 255 * layer_led_val_step / layer_led_val_step_max;
            ws2812_setleds(led, 8);
            break;
        case _MOUS:
            led[6].r = 0 * layer_led_val_step / layer_led_val_step_max;
            led[6].g = 0 * layer_led_val_step / layer_led_val_step_max;
            led[6].b = 255 * layer_led_val_step / layer_led_val_step_max;
            ws2812_setleds(led, 8);
            break;
        case _QMKL:
            led[6].r = 255 * layer_led_val_step / layer_led_val_step_max;
            led[6].g = 0 * layer_led_val_step / layer_led_val_step_max;
            led[6].b = 0 * layer_led_val_step / layer_led_val_step_max;
            ws2812_setleds(led, 8);
            break;
        case _DIA3:
            led[6].r = 130 * layer_led_val_step / layer_led_val_step_max;
            led[6].g = 20 * layer_led_val_step / layer_led_val_step_max;
            led[6].b = 30 * layer_led_val_step / layer_led_val_step_max;
            ws2812_setleds(led, 8);
            break;
        case _D3FN:
            led[6].r = 180 * layer_led_val_step / layer_led_val_step_max;
            led[6].g = 70 * layer_led_val_step / layer_led_val_step_max;
            led[6].b = 70 * layer_led_val_step / layer_led_val_step_max;
            ws2812_setleds(led, 8);
            break;
        default: 
            led[6].r = 0;
            led[6].g = 0;
            led[6].b = 0;
            ws2812_setleds(led, 8);
            break;
    }
}

void led_set_user(uint8_t usb_led) {
    led_init_ports();

    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // Turn capslock on
        // PORTB &= ~(1<<2);
        led[7].r = 255;
        ws2812_setleds(led, 8);
    } else {
        // Turn capslock off
        // PORTB |= (1<<2);
        led[7].r = 0;
        ws2812_setleds(led, 8);
    }

    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        led[7].g = 255;
        ws2812_setleds(led, 8);
    } else {
        led[7].g = 0;
        ws2812_setleds(led, 8);
    }

    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        led[7].b = 150;
        ws2812_setleds(led, 8);
    } else {
        led[7].b = 0;
        ws2812_setleds(led, 8);
    }
}

void led_init_ports(void) {
    // * Set our LED pins as output
  // DDRE |= (1<<6);
  // PORTE |= (1<<6);
}