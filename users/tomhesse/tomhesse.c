#include <stdlib.h>
#include "mouse_jiggler.h"

// Process user input
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Handle mouse jiggler key
    if (!process_mouse_jiggler(keycode, record)) {
        return false;
    }
    return true;
}

// Matrix scan function
void matrix_scan_user(void) {
    mouse_jiggler_matrix_scan(); // Run mouse jiggler logic
}

// Keyboard post init function
void keyboard_post_init_user(void) {
    // Seed the random number generator for the mouse jiggler
    srand(timer_read());
}
