#ifndef __INC_LED_SYSDEFS_H
#define __INC_LED_SYSDEFS_H

#include "FastLED.h"
#include "fastled_config.h"

#ifndef FASTLED_NAMESPACE_BEGIN
/// Start of the FastLED namespace
#define FASTLED_NAMESPACE_BEGIN
/// End of the FastLED namespace
#define FASTLED_NAMESPACE_END
/// "Using" directive for the namespace
#define FASTLED_USING_NAMESPACE
#endif

/// Clock cycles per microsecond. 
/// Calculated using the F_CPU preprocessor define
#define CLKS_PER_US (F_CPU/1000000)

#endif
