#include <stdlib.h>
#include "mouse_jiggler.h"

// Mouse jiggler state structure
typedef struct {
    bool     active;    // Is the jiggler active?
    uint16_t frequency; // Frequency of jiggle (in milliseconds)
    uint16_t timer;     // Timer for the next jiggle
} mouse_jiggler_state_t;

// Instantiate the mouse jiggler state
static mouse_jiggler_state_t mouse_jiggler = {.active    = false,
                                              .frequency = DEFAULT_JIGGLE_FREQUENCY, // Use constant from header
                                              .timer     = 0};

// Perform a randomized mouse movement
static inline void perform_random_mouse_jiggle(void) {
    static const uint8_t directions[4] = {KC_MS_LEFT, KC_MS_RIGHT, KC_MS_UP, KC_MS_DOWN};
    tap_code(directions[rand() % 4]);
}

// Process the custom key for toggling mouse jiggler
bool process_mouse_jiggler(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (keycode == MA_JIGL) {
            mouse_jiggler.active = !mouse_jiggler.active; // Toggle jiggler
            return false;
        } else if (mouse_jiggler.active) {
            mouse_jiggler.active = false; // Disable jiggler on any other key press
        }
    }
    return true; // Continue processing other keys
}

// Run the mouse jiggler logic in the matrix scan
void mouse_jiggler_matrix_scan(void) {
    if (mouse_jiggler.active && timer_elapsed(mouse_jiggler.timer) > mouse_jiggler.frequency) {
        mouse_jiggler.timer = timer_read(); // Reset timer
        perform_random_mouse_jiggle();      // Execute jiggle
    }
}
