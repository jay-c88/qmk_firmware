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

#include "jc_customplanck.h"
#include "action_layer.h"
#include "keymap_extras/keymap_german.h"
#include "led.h"
#include "avr/wdt.h"

enum jc_layers {
  _MAIN,    // Main Layer
  _COLE,    // Colemak Layer (Toggle)
  _NUMB,    // Number Layer (Momentary)
  _SYMB,    // Symbol Layer (Momentary)
  _NAVI,    // Navigation Layer (Momentary)
  _LHUB,    // Layer Hub (Momentary)
  _MEDI,    // Media Layer (Toggle)
  _NUMP,    // NumPad Layer (Toggle)
  _QMKL     // QMK Layer (Toggle)
};

enum jc_customplanck_keycodes {
  DEFAULT = SAFE_RANGE,
  LHUB,
  MEDI,
  NUMP,
  QMKL,
}

enum jc_customplanck_functions {
  __RST,
};

#define __________  KC_TRNS
#define XXXXXXXXXX  KC_NO
#define DE_MICR     ALGR(KC_M)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* _MAIN: Main Layer
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Z  |   U  |   I  |   O  |   P  |   Ü  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ö  |   Ä  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Y  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   ß  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |_NAVI |_LHUB |_NUMB | SPC  |_SYMB |_NAVI | Del  | Bksp | Enter|
 * `-----------------------------------------------------------------------------------'
 */
[_MAIN] = KEYMAP(
    KC_TAB,      DE_Q,      DE_W,      DE_E,      DE_R,      DE_T,      DE_Z,      DE_U,      DE_I,      DE_O,      KC_P,     DE_UE,
   KC_CAPS,      DE_A,      DE_S,      DE_D,      DE_F,      DE_G,      DE_H,      DE_J,      DE_K,      DE_L,     DE_OE,     DE_AE,
   KC_LSFT,      DE_Y,      DE_X,      DE_C,      DE_V,      DE_B,      DE_N,      DE_M,   DE_COMM,    DE_DOT,     DE_SS,   KC_RSFT,
   KC_LCTL,   KC_LGUI,   KC_LALT, MO(_NAVI),      LHUB, MO(_NUMB),    KC_SPC, MO(_SYMB), MO(_NAVI),    KC_DEL,   KC_BSPC,    KC_ENT
),

/* _COLE: Colemak Layer (Toggle)
 * ,-----------------------------------------------------------------------------------.
 * |      |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   Ö  |   Ü  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |   Ä  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   V  |   B  |   K  |   M  |      |      |   ß  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_COLE] = KEYMAP(
__________,      KC_Q,      KC_W,      KC_F,      KC_P,      KC_G,      KC_J,      KC_L,      KC_U,      KC_Y,     DE_OE,     DE_UE,
__________,      KC_A,      KC_R,      KC_S,      KC_T,      KC_D,      KC_H,      KC_N,      KC_E,      KC_I,      KC_O,     DE_AE,
__________,      KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_K,      KC_M,__________,__________,     DE_SS,__________,
__________,__________,__________,__________,__________,__________,__________,__________,__________,__________,__________,__________
),

/* _NUMB: Number Layer (Momentary)
 * ,-----------------------------------------------------------------------------------.
 * |  Esc | XXXX |   7  |   8  |   9  | Bksp |   %  |   7  |   8  |   9  |   +  |   /  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Enter|   4  |   5  |   6  |  Del |   .  |   4  |   5  |   6  |   -  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | XXXX |   1  |   2  |   3  |   0  |   0  |   1  |   2  |   3  |   *  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |   0  |   ,  |      |      |      |   0  |   ,  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMB] = KEYMAP(
    KC_ESC,XXXXXXXXXX,      DE_7,      DE_8,      DE_9,   KC_BSPC,   DE_PERC,      DE_7,      DE_8,      DE_9,   DE_PLUS,   DE_SLSH,
__________,    KC_ENT,      DE_4,      DE_5,      DE_6,    KC_DEL,    DE_DOT,      DE_4,      DE_5,      DE_6,   DE_MINS,    DE_EQL,
__________,XXXXXXXXXX,      DE_1,      DE_2,      DE_3,      DE_0,      DE_0,      DE_1,      DE_2,      DE_3,   DE_ASTR,__________,
__________,__________,      DE_0,   DE_COMM,__________,__________,__________,      DE_0,   DE_COMM,__________,__________,__________
),

/* _SYMB: Symbol Layer (UNICODE ONLY!) (Momentary)
 * ,-----------------------------------------------------------------------------------.
 * |   ^  |   @  |   "  |   €  |   $  |   %  |   §  |   <  |   >  |   =  |   +  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   °  |   [  |   ]  |   {  |   }  |   !  |   ?  |   (  |   )  |   -  |   :  |   '  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   `  |   ´  | XXXX |   _  |   |  |   &  |   µ  |   ~  |   \  |   /  |   ;  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | XXXX | XXXX | XXXX |      |      | XXXX |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMB] = KEYMAP(
   DE_CIRC,     DE_AT,   DE_DQOT,   DE_EURO,    DE_DLR,   DE_PERC,   DE_PARA,   DE_LESS,   DE_MORE,    DE_EQL,   DE_PLUS,   DE_HASH,
   DE_RING,   DE_LBRC,   DE_RBRC,   DE_LCBR,   DE_RCBR,   DE_EXLM,    DE_QST,   DE_LPRN,   DE_RPRN,   DE_MINS,   DE_COLN,   DE_QUOT,
__________,    DE_GRV,   DE_ACUT,XXXXXXXXXX,   DE_UNDS,   DE_PIPE,   DE_AMPR,   DE_MICR,   DE_TILD,   DE_BSLS,   DE_SLSH,   DE_SCLN,
__________,__________,__________,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,__________,__________,XXXXXXXXXX,__________,__________,__________
),

/* _NAVI: Navigation Layer (Momentary)
 * ,-----------------------------------------------------------------------------------.
 * |  Esc | PgUp | Home |  Up  |  End | NLock| XXXX | Home |  Up  |  End | PgUp |  ESC |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | PgDn | Left | Down | Right|  F6  |  F7  | Left | Down | Right| PgDn |  Ins |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F8  |  F9  |  F10 |  F11 |  F12 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | XXXX |PrnScr|ScrLck| Pause|      |  Alt |  Win | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_NAVI] = KEYMAP(
    KC_ESC,   KC_PGUP,   KC_HOME,     KC_UP,    KC_END,   KC_NLCK,XXXXXXXXXX,   KC_HOME,     KC_UP,    KC_END,   KC_PGUP,    KC_ESC,
__________,   KC_PGDN,   KC_LEFT,   KC_DOWN,   KC_RGHT,     KC_F6,     KC_F7,   KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_PGDN,    KC_INS,
__________,     KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F8,     KC_F9,    KC_F10,    KC_F11,    KC_F12,__________,
__________,__________,__________,__________,XXXXXXXXXX,   KC_PSCR,   KC_SLCK,   KC_PAUS,__________,   KC_RALT,   KC_RGUI,   KC_RCTL
),

/* _LHUB: Layer Hub Layer(Momentary)
 * ,-----------------------------------------------------------------------------------.
 * |_QMKL | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |_MEDI | XXXX | XXXX |_NUMP |      |_COLE | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * `-----------------------------------------------------------------------------------'
 */
[_LHUB] = KEYMAP(
      QMKL,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
      MEDI,XXXXXXXXXX,XXXXXXXXXX,      NUMP,__________,      COLE,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX
),

/* _MEDI: Media Layer (Toggle)
 * ,-----------------------------------------------------------------------------------.
 * |  Esc | Mute | Vol- | Vol+ | WRefr| WStop|MAccl0| MScrL|  MUp | MScrR| MScrU| Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Enter| MPly | MPrev| MNext| WBack| WFwd |MAccl1| MLeft| MDown| MRght| MScrD| Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Del | MStop| MRew | MFwd | XXXX | XXXX |MAccl2|  M3  |  M4  |  M5  |  Up  | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ,  |   .  | XXXX | XXXX | TGOFF| Space| Space|  M1  |  M2  | Left | Down | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_MEDI] = KEYMAP(
    KC_ESC,   KC_MUTE,   KC_VOLD,   KC_VOLU,   KC_WREF,   KC_WSTP,   KC_ACL0,   KC_WH_L,   KC_MS_U,   KC_WH_R,   KC_WH_U,   KC_BSPC,
    KC_ENT,   KC_MPLY,   KC_MPRV,   KC_MNXT,   KC_WBAK,   KC_WFWD,   KC_ACL1,   KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_WH_D,    KC_ENT,
    KC_DEL,   KC_MSTP,   KC_MRWD,   KC_MFFD,XXXXXXXXXX,XXXXXXXXXX,   KC_ACL2,   KC_BTN3,   KC_BTN4,   KC_BTN5,     KC_UP,XXXXXXXXXX,
   KC_COMM,    KC_DOT,XXXXXXXXXX,XXXXXXXXXX,      MEDI,    KC_SPC,    KC_SPC,   KC_BTN1,   KC_BTN2,   KC_LEFT,   KC_DOWN,   KC_RGHT
),

/* _NUMP: NumPad Layer (Toggle)
 * ,-----------------------------------------------------------------------------------.
 * | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | NmLk |   7  |   8  |   9  |   +  |   /  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |   4  |   5  |   6  |   -  | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |   1  |   2  |   3  |   *  | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | XXXX | XXXX | XXXX | TGOFF| XXXX | Space|   0  |   0  |   .  | XXXX | Enter|
 * `-----------------------------------------------------------------------------------'
 */
[_NUMP] = KEYMAP(
XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,   KC_NLCK,     KC_P7,     KC_P8,     KC_P9,   KC_PPLS,   KC_PSLS,
XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,     KC_P4,     KC_P5,     KC_P6,   KC_PMNS,XXXXXXXXXX,
XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,     KC_P1,     KC_P2,     KC_P3,   KC_PAST,XXXXXXXXXX,
XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,      NUMP,XXXXXXXXXX,    KC_SPC,     KC_P0,     KC_P0,   KC_PDOT,XXXXXXXXXX,   KC_PENT
),


/* _PH: 
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
// [_PH] = {
//   {,,,,,,,,,,,},
//   {,,,,,,,,,,,},
//   {,,,,,,,,,,,},
//   {,,,,,,,,,,,}
// },


/* _QMKL: QMK Layer (Toggle)
 * ,-----------------------------------------------------------------------------------.
 * | XXXX | Hue- | Hue+ | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | Reset|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | Sat- | Sat+ |LEDCyc|LEDTog| XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | Debug|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | Val- | Val+ | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | BL + | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | XXXX | XXXX | XXXX | TGOFF| XXXX | XXXX | XXXX | XXXX |BLStep| BL - |BLTogg|
 * `-----------------------------------------------------------------------------------'
 */
[_QMKL] = KEYMAP(
XXXXXXXXXX,   RGB_HUD,   RGB_HUI,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,  F(__RST),
XXXXXXXXXX,   RGB_SAD,   RGB_SAI,   RGB_MOD,   RGB_TOG,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,     DEBUG,
XXXXXXXXXX,   RGB_VAD,   RGB_VAI,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,    BL_INC,XXXXXXXXXX,
XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,      QMKL,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,   BL_STEP,    BL_DEC,   BL_TOGG
),

};

/* id for user defined functions */
enum function_id {
    PROMICRO_PROGRAM,
};

void promicro_bootloader_jmp(bool program) {
    uint16_t *const bootKeyPtr = (uint16_t *)0x0800;

    // Value used by Caterina bootloader use to determine whether to run the
    // sketch or the bootloader programmer.
    uint16_t bootKey = program ? 0x7777 : 0;

    *bootKeyPtr = bootKey;

    // setup watchdog timeout
    wdt_enable(WDTO_60MS);

    while(1) {} // wait for watchdog timer to trigger
}

/*
* user defined action function
*/
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case PROMICRO_PROGRAM:
            promicro_bootloader_jmp(true);
            break;
        default:
            break;
    }
}


/*
*   fn_actions
*/
const uint16_t PROGMEM fn_actions[] = {
  [__RST] = ACTION_FUNCTION(PROMICRO_PROGRAM),
};



const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
            }
        }
        else {
            
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
            }
        }
        else {
            
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
            }
        }
        else {
            
        }
        return false;
        break;
  }
  return true;
}


void matrix_init_user(void) {

}

void matrix_scan_user(void) {
    // uint8_t layer = biton32(layer_state);
    // switch (layer) {
    //     case 1:
    //         led[7].r = 0;
    //         led[7].g = 0;
    //         led[7].b = 0;
    //         ws2812_setleds(led, 8);
    //         break;
    //     default:
    //         led[7].r = 0;
    //         led[7].g = 0;
    //         led[7].b = 0;
    //         ws2812_setleds(led, 8);
    //         break;
    // }
}

void led_set_user(uint8_t usb_led) {
    led_init_ports();

    // if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    //     // Turn capslock on
    //     PORTB &= ~(1<<2);
    //     led[0].r = 255;
    //     ws2812_setleds(led, 8)
    // } else {
    //     // Turn capslock off
    //     PORTB |= (1<<2);
    //     led[0].r = 0;
    //     ws2812_setleds(led, 8)
    // }

    // if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
    //     led[0].g = 255;
    //     ws2812_setleds(led, 8)
    // } else {
    //     led[0].g = 0;
    //     ws2812_setleds(led, 8)
    // }

    // if (usb_led & (1<<USB_LED_NUM_LOCK)) {
    //     led[0].b = 255;
    //     ws2812_setleds(led, 8)
    // } else {
    //     led[0].b = 0;
    //     ws2812_setleds(led, 8)
    // }
}

void led_init_ports(void) {
    // * Set our LED pins as output
  DDRE |= (1<<6);
  PORTE |= (1<<6);
}