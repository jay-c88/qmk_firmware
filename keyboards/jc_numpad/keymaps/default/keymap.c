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
#include "jc_numpad.h"
#include "avr/wdt.h"
#include "keymap_extras/keymap_german.h"

enum jc_numpad_layers {
  _MAIN,    // Main Layer (Switch)
  _MEDI,    // Media Layer (from _MAIN) (Momentary)
  _FUNC,    // F1-F12 Layer (Switch)
  _QMKL,    // QMK Layer (from _FUNC) (Momentary)
  _TEST,    // Testing Layer (Switch)
  _TES1,    // Testing 1 Layer (Toggle)
  _DUMM,    // DUMMY Layer (from _TEST) (Toggle)
};

enum jc_numpad_functions {
  __RST,
};

#define __________ KC_TRNS
#define XXXXXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* _MAIN: Main Layer (Switch)
 * ,---------------------------.
 * | XXXX | _FUNC| _TEST| Bksp |
 * |------+------+------+------+
 * | NLCK |   /  |   *  |   -  |
 * |------+------+------+------+
 * |   7  |   8  |   9  |   +  |
 * |------+------+------+------+
 * |   4  |   5  |   6  |_MEDI |
 * |------+------+------+------|
 * |   1  |   2  |   3  |      |
 * |------+------+------+ Enter|
 * |      0      | PDOT |      |
 * `---------------------------'
 */
[_MAIN] = KEYMAP(
  XXXXXXXXXX, TO(_FUNC), TO(_TEST),   KC_BSPC,
     KC_NLCK,   KC_PSLS,   KC_PAST,   KC_PMNS,
       KC_P7,     KC_P8,     KC_P9,   KC_PPLS,
       KC_P4,     KC_P5,     KC_P6, MO(_MEDI),
       KC_P1,     KC_P2,     KC_P3,
                  KC_P0,   KC_PDOT,   KC_PENT
),

/* _MEDI: Media Layer (Momentary from _MAIN)
 * ,---------------------------.
 * |  Esc | XXXX | XXXX | XXXX |
 * |------+------+------+------+
 * | Play | Prev | Next | Vol+ |
 * |------+------+------+------+
 * | XXXX | XXXX | XXXX | Vol- |
 * |------+------+------+------+
 * | WBack| WRefr| WFwd |      |
 * |------+------+------+------|
 * | XXXX | XXXX | XXXX |      |
 * |------+------+------+ XXXX |
 * |    Space    | XXXX |      |
 * `---------------------------'
 */
[_MEDI] = KEYMAP(
      KC_ESC,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
     KC_MPLY,   KC_MPRV,   KC_MNXT,   KC_VOLU,
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,   KC_VOLD,
     KC_WBAK,   KC_WREF,   KC_WFWD,__________,
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
                 KC_SPC,XXXXXXXXXX,XXXXXXXXXX
),

/* _FUNC: F1-F12 Layer (Switch)
 * ,---------------------------.
 * | _MAIN| XXXX | _TEST| XXXX |
 * |------+------+------+------+
 * |  F10 |  F11 |  F12 | PSCR |
 * |------+------+------+------+
 * |  F7  |  F8  |  F9  | SCLCK|
 * |------+------+------+------+
 * |  F4  |  F5  |  F6  | PAUS |
 * |------+------+------+------|
 * |  F1  |  F2  |  F3  |      |
 * |------+------+------+ Enter|
 * |     LGUI    |_QMKL |      |
 * `---------------------------'
 */
[_FUNC] = KEYMAP(
   TO(_MAIN),XXXXXXXXXX, TO(_TEST),XXXXXXXXXX,
      KC_F10,    KC_F11,    KC_F12,   KC_PSCR,
       KC_F7,     KC_F8,     KC_F9,   KC_SLCK,
       KC_F4,     KC_F5,     KC_F6,   KC_PAUS,
       KC_F1,     KC_F2,     KC_F3,
                KC_LGUI, MO(_QMKL),    KC_ENT
),

/* _QMKL: QMK Layer (Momentary from _FUNC)
 * ,---------------------------.
 * | XXXX | XXXX | XXXX |  Fn0 |
 * |------+------+------+------+
 * | XXXX | XXXX | XXXX | RESET|
 * |------+------+------+------+
 * | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+
 * | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------|
 * | XXXX | XXXX | XXXX |      |
 * |------+------+------+ XXXX |
 * |     XXXX    |      |      |
 * `---------------------------'
 */
[_QMKL] = KEYMAP(
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,      F(__RST),
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
        XXXXXXXXXX     ,__________,XXXXXXXXXX
),

/* _TEST: Test Layer (Switch)
 * ,---------------------------.
 * | _MAIN| _FUNC| XXXX |_DUMM |
 * |------+------+------+------+
 * | XXXX | XXXX | XXXX | _TES1|
 * |------+------+------+------+
 * | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+
 * | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------|
 * | XXXX | XXXX | XXXX |      |
 * |------+------+------+ XXXX |
 * |     XXXX    | XXXX |      |
 * `---------------------------'
 */
[_TEST] = KEYMAP(
   TO(_MAIN), TO(_FUNC),XXXXXXXXXX, TG(_DUMM),
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX, TG(_TES1),
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
        XXXXXXXXXX     ,XXXXXXXXXX,XXXXXXXXXX
),

/* _TES1: Test Layer (Switch)
 * ,---------------------------.
 * | XXXX | XXXX | XXXX |LayOFF|
 * |------+------+------+------+
 * | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+
 * | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+
 * | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------|
 * | XXXX | XXXX | XXXX |      |
 * |------+------+------+ XXXX |
 * |     XXXX    | XXXX |      |
 * `---------------------------'
 */
[_TES1] = KEYMAP(
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX, TG(_TES1),
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
     DE_EXLM,     DE_AT,XXXXXXXXXX,XXXXXXXXXX,
     KC_LEFT,XXXXXXXXXX,   KC_RGHT,XXXXXXXXXX,
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
        XXXXXXXXXX     ,XXXXXXXXXX,XXXXXXXXXX
),

/* _DUMM: Dummy layer (Toggle from _TEST)
 * ,---------------------------.
 * | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+
 * | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+
 * | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+
 * | XXXX | XXXX | XXXX |      |
 * |------+------+------+------|
 * | XXXX | XXXX | XXXX |      |
 * |------+------+------+ XXXX |
 * |     XXXX    |      |      |
 * `---------------------------'
 */
[_DUMM] = KEYMAP(
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,__________,
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
  XXXXXXXXXX,XXXXXXXXXX,XXXXXXXXXX,
        XXXXXXXXXX     ,XXXXXXXXXX,XXXXXXXXXX
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

const uint16_t PROGMEM fn_actions[] = {
  [__RST] = ACTION_FUNCTION(PROMICRO_PROGRAM),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        default:
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        // output low
        DDRD |= (1<<3);
        PORTD |= (1<<3);
    } else {
        // Hi-Z
        DDRD &= ~(1<<3);
        PORTD &= ~(1<<3);
    }
}
