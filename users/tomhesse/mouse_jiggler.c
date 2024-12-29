#include "mouse_jiggler.h"
#include <stdlib.h>

// Mouse jiggler state structure
typedef struct {
    bool active;           // Is the jiggler active?
    uint16_t frequency;    // Frequency of jiggle (in milliseconds)
    uint16_t timer;        // Timer for the next jiggle
} mouse_jiggler_state_t;

// Instantiate the mouse jiggler state
static mouse_jiggler_state_t mouse_jiggler = {
    .active = false,
    .frequency = DEFAULT_JIGGLE_FREQUENCY, // Use constant from header
    .timer = 0
};


// Perform a randomized mouse movement
void perform_random_mouse_jiggle(void) {
    uint8_t direction = rand() % 4; // Generate a random number between 0 and 3
    switch (direction) {
        case 0: tap_code(KC_MS_LEFT); break;
        case 1: tap_code(KC_MS_RIGHT); break;
        case 2: tap_code(KC_MS_UP); break;
        case 3: tap_code(KC_MS_DOWN); break;
    }
}

// Process the custom key for toggling mouse jiggler
bool process_mouse_jiggler(uint16_t keycode, keyrecord_t *record) {
    if (keycode == MA_JIGL) {
        if (record->event.pressed) {
            mouse_jiggler.active = !mouse_jiggler.active; // Toggle the jiggler
        }
        return false; // Skip further processing for this key
    }
    // Disable jiggler on other keypresses
    if (record->event.pressed && mouse_jiggler.active) {
        mouse_jiggler.active = false;
    }
    return true; // Continue processing other keys
}

// Run the mouse jiggler logic in the matrix scan
void mouse_jiggler_matrix_scan(void) {
    if (mouse_jiggler.active && timer_elapsed(mouse_jiggler.timer) > mouse_jiggler.frequency) {
        mouse_jiggler.timer = timer_read(); // Reset timer
        perform_random_mouse_jiggle();    // Execute jiggle
    }
}
