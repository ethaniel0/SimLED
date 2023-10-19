#define FASTLED_INTERNAL
#include "FastLED.h"
#include <chrono>
#include "arduinoFunctions.h"



/// @file FastLED.cpp
/// Central source file for FastLED, implements the CFastLED class/object

FASTLED_NAMESPACE_BEGIN

/// Pointer to the matrix object when using the Smart Matrix Library
/// @see https://github.com/pixelmatix/SmartMatrix
void *pSmartMatrix = NULL;

CLEDController *CLEDController::m_pHead = NULL;
CLEDController *CLEDController::m_pTail = NULL;
static uint32_t lastshow = 0;

/// Global frame counter, used for debugging ESP implementations
/// @todo Include in FASTLED_DEBUG_COUNT_FRAME_RETRIES block?
uint32_t _frame_cnt=0;

/// Global frame retry counter, used for debugging ESP implementations
/// @todo Include in FASTLED_DEBUG_COUNT_FRAME_RETRIES block?
uint32_t _retry_cnt=0;

// uint32_t CRGB::Squant = ((uint32_t)((__TIME__[4]-'0') * 28))<<16 | ((__TIME__[6]-'0')*50)<<8 | ((__TIME__[7]-'0')*28);


/// Called at program exit when run in a desktop environment. 
/// Extra C definition that some environments may need. 
/// @returns 0 to indicate success
extern "C" int atexit(void (* /*func*/ )()) { return 0; }

FASTLED_NAMESPACE_END
