#pragma once

#include "action.h"
#include "quantum_keycodes.h"

// Mouse Jiggler: Prevents idle detection by simulating random mouse movements.
// Add `MA_JIGL` to your keymap to toggle this functionality.

// Default frequency of mouse jiggle (in milliseconds)
#define DEFAULT_JIGGLE_FREQUENCY 15000

// Custom keycode for mouse jiggler
enum custom_keycodes {
    MA_JIGL = SAFE_RANGE
};

// Function prototypes
bool process_mouse_jiggler(uint16_t keycode, keyrecord_t *record);
void mouse_jiggler_matrix_scan(void);
void perform_random_mouse_jiggle(void);
