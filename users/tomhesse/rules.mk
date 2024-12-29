BOOTMAGIC_ENABLE = yes		# Enable Bootmagic
MOUSEKEY_ENABLE = yes		# Enable mouse keys
EXTRAKEY_ENABLE = yes		# Enable audio and system controls
NKRO_ENABLE = yes			# Enable N-Key rollover
LTO_ENABLE = yes			# Enable link-time optimization

# Explicitly disabled
RGBLIGHT_ENABLE = no		# RGB underglow
BACKLIGHT_ENABLE = no		# Keyboard backlight

# Include custom source files
SRC += tomhesse.c
SRC += mouse_jiggler.c
