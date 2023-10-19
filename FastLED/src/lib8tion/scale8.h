#ifndef __INC_LIB8TION_SCALE_H
#define __INC_LIB8TION_SCALE_H

/// @file scale8.h
/// Fast, efficient 8-bit scaling functions specifically
/// designed for high-performance LED programming. 

/// @addtogroup lib8tion
/// @{

/// @defgroup Scaling Scaling Functions
/// Fast, efficient 8-bit scaling functions specifically
/// designed for high-performance LED programming.
///
/// Because of the AVR(Arduino) and ARM assembly language
/// implementations provided, using these functions often
/// results in smaller and faster code than the equivalent
/// program using plain "C" arithmetic and logic.
/// @{


/// Scale one byte by a second one, which is treated as
/// the numerator of a fraction whose denominator is 256. 
///
/// In other words, it computes i * (scale / 256)
/// @param i input value to scale
/// @param scale scale factor, in n/256 units
/// @returns scaled value
/// @note Takes 4 clocks on AVR with MUL, 2 clocks on ARM
LIB8STATIC_ALWAYS_INLINE uint8_t scale8( uint8_t i, fract8 scale)
{
    return (((uint16_t)i) * (1+(uint16_t)(scale))) >> 8;
}


/// The "video" version of scale8() guarantees that the output will
/// be only be zero if one or both of the inputs are zero. 
/// If both inputs are non-zero, the output is guaranteed to be non-zero.  
/// This makes for better "video"/LED dimming, at the cost of
/// several additional cycles.
/// @param i input value to scale
/// @param scale scale factor, in n/256 units
/// @returns scaled value
/// @see scale8()
LIB8STATIC_ALWAYS_INLINE uint8_t scale8_video( uint8_t i, fract8 scale)
{
    uint8_t j = (((int)i * (int)scale) >> 8) + ((i&&scale)?1:0);
    // uint8_t nonzeroscale = (scale != 0) ? 1 : 0;
    // uint8_t j = (i == 0) ? 0 : (((int)i * (int)(scale) ) >> 8) + nonzeroscale;
    return j;
}


/// @defgroup ScalingDirty Scaling Functions that Leave R1 Dirty
/// These functions are more efficient for scaling multiple
/// bytes at once, but require calling cleanup_R1() afterwards.
/// @{


/// This version of scale8() does not clean up the R1 register on AVR. 
/// If you are doing several "scale8()'s" in a row, use this, and
/// then explicitly call cleanup_R1().
/// @warning You **MUST** call cleanup_R1() after using this function!
/// @param i input value to scale
/// @param scale scale factor, in n/256 units
/// @returns scaled value
/// @see scale8()
LIB8STATIC_ALWAYS_INLINE uint8_t scale8_LEAVING_R1_DIRTY( uint8_t i, fract8 scale)
{
    return (((uint16_t)i) * ((uint16_t)(scale)+1)) >> 8;
}

/// In place modifying version of scale8() that does not clean up the R1 register on AVR. 
/// If you are doing several "scale8()'s" in a row, use this, and
/// then explicitly call cleanup_R1().
/// @warning You **MUST** call cleanup_R1() after using this function!
/// @par
/// @warning This function always modifies its arguments in place!
/// @param i input value to scale
/// @param scale scale factor, in n/256 units
/// @see scale8()
LIB8STATIC_ALWAYS_INLINE void nscale8_LEAVING_R1_DIRTY( uint8_t& i, fract8 scale)
{
    i = (((uint16_t)i) * ((uint16_t)(scale)+1)) >> 8;
}


/// This version of scale8_video() does not clean up the R1 register on AVR. 
/// If you are doing several "scale8_video()'s" in a row, use this, and
/// then explicitly call cleanup_R1().
/// @warning You **MUST** call cleanup_R1() after using this function!
/// @param i input value to scale
/// @param scale scale factor, in n/256 units
/// @returns scaled value
/// @see scale8_video()
LIB8STATIC_ALWAYS_INLINE uint8_t scale8_video_LEAVING_R1_DIRTY( uint8_t i, fract8 scale)
{
    uint8_t j = (((int)i * (int)scale) >> 8) + ((i&&scale)?1:0);
    // uint8_t nonzeroscale = (scale != 0) ? 1 : 0;
    // uint8_t j = (i == 0) ? 0 : (((int)i * (int)(scale) ) >> 8) + nonzeroscale;
    return j;
}

/// In place modifying version of scale8_video() that does not clean up the R1 register on AVR. 
/// If you are doing several "scale8_video()'s" in a row, use this, and
/// then explicitly call cleanup_R1().
/// @warning You **MUST** call cleanup_R1() after using this function!
/// @par
/// @warning This function always modifies its arguments in place!
/// @param i input value to scale
/// @param scale scale factor, in n/256 units
/// @see scale8_video()
LIB8STATIC_ALWAYS_INLINE void nscale8_video_LEAVING_R1_DIRTY( uint8_t & i, fract8 scale)
{
    i = (((int)i * (int)scale) >> 8) + ((i&&scale)?1:0);
}

/// Clean up the r1 register after a series of *LEAVING_R1_DIRTY calls
/// @ingroup ScalingDirty
LIB8STATIC_ALWAYS_INLINE void cleanup_R1()
{
}

/// @} ScalingDirty


/// Scale three one-byte values by a fourth one, which is treated as
/// the numerator of a fraction whose demominator is 256. 
///
/// In other words, it computes r,g,b * (scale / 256)
///
/// @warning This function always modifies its arguments in place!
/// @param r first value to scale
/// @param g second value to scale
/// @param b third value to scale
/// @param scale scale factor, in n/256 units
LIB8STATIC void nscale8x3( uint8_t& r, uint8_t& g, uint8_t& b, fract8 scale)
{
    uint16_t scale_fixed = scale + 1;
    r = (((uint16_t)r) * scale_fixed) >> 8;
    g = (((uint16_t)g) * scale_fixed) >> 8;
    b = (((uint16_t)b) * scale_fixed) >> 8;
}

/// Scale three one-byte values by a fourth one, which is treated as
/// the numerator of a fraction whose demominator is 256. 
///
/// In other words, it computes r,g,b * (scale / 256), ensuring
/// that non-zero values passed in remain non-zero, no matter how low the scale
/// argument.
///
/// @warning This function always modifies its arguments in place!
/// @param r first value to scale
/// @param g second value to scale
/// @param b third value to scale
/// @param scale scale factor, in n/256 units
LIB8STATIC void nscale8x3_video( uint8_t& r, uint8_t& g, uint8_t& b, fract8 scale)
{
    uint8_t nonzeroscale = (scale != 0) ? 1 : 0;
    r = (r == 0) ? 0 : (((int)r * (int)(scale) ) >> 8) + nonzeroscale;
    g = (g == 0) ? 0 : (((int)g * (int)(scale) ) >> 8) + nonzeroscale;
    b = (b == 0) ? 0 : (((int)b * (int)(scale) ) >> 8) + nonzeroscale;
}

/// Scale two one-byte values by a third one, which is treated as
/// the numerator of a fraction whose demominator is 256.
///
/// In other words, it computes i,j * (scale / 256).
///
/// @warning This function always modifies its arguments in place!
/// @param i first value to scale
/// @param j second value to scale
/// @param scale scale factor, in n/256 units
LIB8STATIC void nscale8x2( uint8_t& i, uint8_t& j, fract8 scale)
{
    uint16_t scale_fixed = scale + 1;
    i = (((uint16_t)i) * scale_fixed ) >> 8;
    j = (((uint16_t)j) * scale_fixed ) >> 8;
}

/// Scale two one-byte values by a third one, which is treated as
/// the numerator of a fraction whose demominator is 256. 
///
/// In other words, it computes i,j * (scale / 256), ensuring
/// that non-zero values passed in remain non zero, no matter how low the scale
/// argument.
///
/// @warning This function always modifies its arguments in place!
/// @param i first value to scale
/// @param j second value to scale
/// @param scale scale factor, in n/256 units
LIB8STATIC void nscale8x2_video( uint8_t& i, uint8_t& j, fract8 scale)
{
    uint8_t nonzeroscale = (scale != 0) ? 1 : 0;
    i = (i == 0) ? 0 : (((int)i * (int)(scale) ) >> 8) + nonzeroscale;
    j = (j == 0) ? 0 : (((int)j * (int)(scale) ) >> 8) + nonzeroscale;
}


/// Scale a 16-bit unsigned value by an 8-bit value, which is treated
/// as the numerator of a fraction whose denominator is 256.
///
/// In other words, it computes i * (scale / 256)
/// @param i input value to scale
/// @param scale scale factor, in n/256 units
/// @returns scaled value
LIB8STATIC_ALWAYS_INLINE uint16_t scale16by8( uint16_t i, fract8 scale )
{
    uint16_t result;
    result = (i * (1+((uint16_t)scale))) >> 8;

    return result;
}

/// Scale a 16-bit unsigned value by an 16-bit value, which is treated
/// as the numerator of a fraction whose denominator is 65536. 
/// In other words, it computes i * (scale / 65536)
/// @param i input value to scale
/// @param scale scale factor, in n/65536 units
/// @returns scaled value
LIB8STATIC uint16_t scale16( uint16_t i, fract16 scale )
{
    uint16_t result;
    result = ((uint32_t)(i) * (1+(uint32_t)(scale))) / 65536;
    return result;
}
/// @} Scaling


/// @defgroup Dimming Dimming and Brightening Functions
/// Functions to dim or brighten data.
///
/// The eye does not respond in a linear way to light.
/// High speed PWM'd LEDs at 50% duty cycle appear far
/// brighter then the "half as bright" you might expect.
///
/// If you want your midpoint brightness LEDs (128) to
/// appear half as bright as "full" brightness (255), you
/// have to apply a "dimming function".
///
/// @note These are approximations of gamma correction with
///       a gamma value of 2.0. 
/// @see @ref GammaFuncs
/// @{

/// Adjust a scaling value for dimming. 
/// @see scale8()
LIB8STATIC uint8_t dim8_raw( uint8_t x)
{
    return scale8( x, x);
}

/// Adjust a scaling value for dimming for video (value will never go below 1)
/// @see scale8_video()
LIB8STATIC uint8_t dim8_video( uint8_t x)
{
    return scale8_video( x, x);
}

/// Linear version of the dimming function that halves for values < 128
LIB8STATIC uint8_t dim8_lin( uint8_t x )
{
    if( x & 0x80 ) {
        x = scale8( x, x);
    } else {
        x += 1;
        x /= 2;
    }
    return x;
}

/// Brighten a value (inverse of dim8_raw())
LIB8STATIC uint8_t brighten8_raw( uint8_t x)
{
    uint8_t ix = 255 - x;
    return 255 - scale8( ix, ix);
}

/// Brighten a value (inverse of dim8_video())
LIB8STATIC uint8_t brighten8_video( uint8_t x)
{
    uint8_t ix = 255 - x;
    return 255 - scale8_video( ix, ix);
}

/// Brighten a value (inverse of dim8_lin())
LIB8STATIC uint8_t brighten8_lin( uint8_t x )
{
    uint8_t ix = 255 - x;
    if( ix & 0x80 ) {
        ix = scale8( ix, ix);
    } else {
        ix += 1;
        ix /= 2;
    }
    return 255 - ix;
}

/// @} Dimming
/// @} lib8tion

#endif
