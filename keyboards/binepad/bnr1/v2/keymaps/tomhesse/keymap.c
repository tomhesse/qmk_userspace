/* Copyright 2025 Tom Hesse
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

bool         encoder_pressed     = false;
int8_t       encoder_accumulator = 0; // Track encoder step count
const int8_t encoder_threshold   = 2; // Only send key after 2 steps

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_1x1(
        LT(1, KC_MPLY) // Hold for layer 1, tap for Play/Pause
    ),

    [1] = LAYOUT_ortho_1x1(
        KC_TRNS
    )
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }, // Default layer: Volume control
    [1] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) }, // Layer 1: Track navigation
};
// clang-format on
#endif

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(1)) { // Check if we are on layer 1
        encoder_accumulator += (clockwise ? 1 : -1);

        if (abs(encoder_accumulator) >= encoder_threshold) {
            tap_code(clockwise ? KC_MNXT : KC_MPRV);
            encoder_accumulator -= encoder_threshold * (encoder_accumulator / abs(encoder_accumulator));
        }
        return false;
    }
    return true; // Allow QMK to handle it normally if layer 1 is not active
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == LT(1, KC_MPLY)) {
        encoder_pressed = record->event.pressed;
        if (!encoder_pressed) {
            encoder_accumulator = 0; // Reset accumulator when button is released
        }
    }
    return true;
}
