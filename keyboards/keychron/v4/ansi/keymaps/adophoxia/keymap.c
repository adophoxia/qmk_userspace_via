/* Copyright 2025 @ Keychron (https://www.keychron.com)
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
#include "lib/lib8tion/lib8tion.h"

#define ARRAYSIZE(arr) sizeof(arr)/sizeof(arr[0])

// clang-format off

enum layers {
    BASE,
    _FN1,
    _FN2
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_60_ansi(
        KC_ESC,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_CAPS, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            MO(_FN1),
        KC_LCTL, KC_LWIN,  KC_LALT,                            KC_SPC,                             KC_RALT,  KC_NO,    KC_RCTL,  TG(_FN2)),

    [_FN1] = LAYOUT_60_ansi(
        KC_GRV,  KC_BRID,  KC_BRIU, KC_TASK, KC_FLXP, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  RGB_MOD,
        RGB_TOG, RGB_MOD,  RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, KC_APP,  KC_SCRL, KC_INS,   KC_PGUP,  KC_HOME,  _______,
        _______, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, KC_PSCR, KC_PGDN,  KC_END,             _______,
        _______,           _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______,  KC_DEL,             _______,
        _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______),

    [_FN2] = LAYOUT_60_ansi(
        KC_TILD, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,
        RGB_TOG, RGB_MOD,  RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______,  _______,  _______,  _______,
        _______, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______,  _______,            _______,
        _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_UP,              _______,
        _______, _______,  _______,                            _______,                            KC_LEFT,  KC_DOWN,  KC_RIGHT, TO(BASE))
};


void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

bool shutdown_user(bool jump_to_bootloader) {
    if (jump_to_bootloader) {
        // turn off LEDs for bootloader
        rgb_matrix_set_color_all(RGB_OFF);
    }
    void rgb_matrix_update_pwm_buffers(void);
    // force flushing -- otherwise will never happen
    rgb_matrix_update_pwm_buffers();
    // false to not process kb level
    return false;
}

void f_row_leds(void);
void caps_lock_alphabets(void);
void fn2_arrows(void);


uint8_t multimedia_f_row[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
};

uint8_t alphabets[] = {
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
    29, 30, 31, 32, 33, 34, 35, 36, 37,
    41, 42, 43, 44, 45, 46, 47, 48,
};

uint8_t arrows[] = {
    51, 57, 58, 59,
};

void f_row_leds() {
    for (uint8_t i = 0; i < ARRAYSIZE(multimedia_f_row); i++) {
        rgb_matrix_set_color(multimedia_f_row[0], RGB_RED);
        rgb_matrix_set_color(multimedia_f_row[1], RGB_RED);

        rgb_matrix_set_color(multimedia_f_row[2], RGB_ORANGE);
        rgb_matrix_set_color(multimedia_f_row[3], RGB_ORANGE);

        rgb_matrix_set_color(multimedia_f_row[4], RGB_YELLOW);
        rgb_matrix_set_color(multimedia_f_row[5], RGB_YELLOW);

        rgb_matrix_set_color(multimedia_f_row[6], RGB_GREEN);
        rgb_matrix_set_color(multimedia_f_row[7], RGB_GREEN);
        rgb_matrix_set_color(multimedia_f_row[8], RGB_GREEN);

        rgb_matrix_set_color(multimedia_f_row[9], RGB_BLUE);
        rgb_matrix_set_color(multimedia_f_row[10], RGB_BLUE);
        rgb_matrix_set_color(multimedia_f_row[11], RGB_BLUE);
    }
}

void fn2_arrows() {
    for (uint8_t i = 0; i < ARRAYSIZE(arrows); i++) {
        rgb_matrix_set_color(arrows[i], RGB_WHITE);
    }
}

void caps_lock_alphabets() {
    if (host_keyboard_led_state().caps_lock) { // Sets a breathing LED effect on caps locks and KC_A - KC_Z
        //RGB const rgb = hsv_to_rgb_glow((HSV){HSV_WHITE});
        for (uint8_t i = 0; i < ARRAYSIZE(alphabets); i++) {
            //rgb_matrix_set_color(alphabets[i], rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(alphabets[i], 255, 255, 255);
        }
        rgb_matrix_set_color(30, RGB_WHITE);
    }
}

bool rgb_matrix_indicators_user(void) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case BASE:
            caps_lock_alphabets();
            rgb_matrix_set_color(0, RGB_RED);
        break;
        case _FN1:
            f_row_leds();
            rgb_matrix_set_color(0, RGB_GREEN);
        break;
        case _FN2:
            fn2_arrows();
            rgb_matrix_set_color(0, RGB_BLUE);
        break;
        default:
            break;
        }
        return false;
    return true;
}