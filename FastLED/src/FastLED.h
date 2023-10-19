#ifndef __INC_FASTSPI_LED2_H
#define __INC_FASTSPI_LED2_H

/// @file FastLED.h
/// central include file for FastLED, defines the CFastLED class/object

/// Current FastLED version number, as an integer.
/// E.g. 3006000 for version "3.6.0", with:
/// * 1 digit for the major version
/// * 3 digits for the minor version
/// * 3 digits for the patch version
#define FASTLED_VERSION 3006000
#ifndef FASTLED_INTERNAL
#  ifdef  FASTLED_SHOW_VERSION
#    ifdef FASTLED_HAS_PRAGMA_MESSAGE
#      pragma message "FastLED version 3.006.000"
#    else
#      warning FastLED version 3.006.000  (Not really a warning, just telling you here.)
#    endif
#  endif
#endif

#ifndef __PROG_TYPES_COMPAT__
/// avr-libc define to expose __progmem__ typedefs.
/// @note These typedefs are now deprecated!
/// @see https://www.nongnu.org/avr-libc/user-manual/group__avr__pgmspace.html
#define __PROG_TYPES_COMPAT__
#endif


#include <cstdint>

#include "cpp_compat.h"

#include "fastled_config.h"
#include "led_sysdefs.h"

// Utility functions
#include "bitswap.h"

#include "controller.h"
#include "dmx.h"

#include "lib8tion.h"
#include "pixeltypes.h"
#include "hsv2rgb.h"
#include "colorutils.h"
#include "pixelset.h"
#include "colorpalettes.h"
#include "noise.h"

FASTLED_NAMESPACE_BEGIN

/// @} ClocklessChipsets
/// @} Chipsets

#if defined(LIB8_ATTINY)
#define NUM_CONTROLLERS 2
#else
/// Unknown NUM_CONTROLLERS definition. Unused elsewhere in the library?
/// @todo Remove?
#define NUM_CONTROLLERS 8
#endif

/// Alias of the FastLED instance for legacy purposes
#define FastSPI_LED FastLED
/// Alias of the FastLED instance for legacy purposes
#define FastSPI_LED2 FastLED
#ifndef LEDS
/// Alias of the FastLED instance for legacy purposes
#define LEDS FastLED
#endif

FASTLED_NAMESPACE_END

#endif
