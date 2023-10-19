#ifndef __INC_LIB8TION_MATH_H
#define __INC_LIB8TION_MATH_H

#include "scale8.h"


/// @file math8.h
/// Fast, efficient 8-bit math functions specifically
/// designed for high-performance LED programming. 

/// @ingroup lib8tion
/// @{

/// @defgroup Math Basic Math Operations
/// Fast, efficient 8-bit math functions specifically
/// designed for high-performance LED programming.
///
/// Because of the AVR (Arduino) and ARM assembly language
/// implementations provided, using these functions often
/// results in smaller and faster code than the equivalent
/// program using plain "C" arithmetic and logic.
/// @{

/// Add one byte to another, saturating at 0xFF
/// @param i first byte to add
/// @param j second byte to add
/// @returns the sum of i + j, capped at 0xFF
LIB8STATIC_ALWAYS_INLINE uint8_t qadd8( uint8_t i, uint8_t j)
{
    unsigned int t = i + j;
    if( t > 255) t = 255;
    return t;
}

/// Add one byte to another, saturating at 0x7F and -0x80
/// @param i first byte to add
/// @param j second byte to add
/// @returns the sum of i + j, capped at 0x7F and -0x80
LIB8STATIC_ALWAYS_INLINE int8_t qadd7( int8_t i, int8_t j)
{
    int16_t t = i + j;
    if( t > 127) t = 127;
    else if( t < -128) t = -128;
    return t;
}

/// Subtract one byte from another, saturating at 0x00
/// @param i byte to subtract from
/// @param j byte to subtract
/// @returns i - j with a floor of 0
LIB8STATIC_ALWAYS_INLINE uint8_t qsub8( uint8_t i, uint8_t j)
{
    int t = i - j;
    if( t < 0) t = 0;
    return t;
}

/// Add one byte to another, with 8-bit result
/// @note This does not saturate and may overflow!
/// @param i first byte to add
/// @param j second byte to add
/// @returns the sum of i + j, 8-bit
LIB8STATIC_ALWAYS_INLINE uint8_t add8( uint8_t i, uint8_t j)
{
    int t = i + j;
    return t;
}

/// Add one byte to two bytes, with 16-bit result
/// @note This does not saturate and may overflow!
/// @param i first value to add, 8-bit
/// @param j second value to add, 16-bit
/// @returns the sum of i + j, 16-bit
LIB8STATIC_ALWAYS_INLINE uint16_t add8to16( uint8_t i, uint16_t j)
{
    uint16_t t = i + j;
    return t;
}


/// Subtract one byte from another, 8-bit result
/// @note This does not saturate and may overflow!
/// @param i byte to subtract from
/// @param j byte to subtract
/// @returns i - j
LIB8STATIC_ALWAYS_INLINE uint8_t sub8( uint8_t i, uint8_t j)
{
    int t = i - j;
    return t;
}

/// Calculate an integer average of two unsigned
/// 8-bit integer values (uint8_t), rounded down. 
/// Fractional results are rounded down, e.g. avg8(20,41) = 30
/// @param i first value to average
/// @param j second value to average
/// @returns mean average of i and j, rounded down
LIB8STATIC_ALWAYS_INLINE uint8_t avg8( uint8_t i, uint8_t j)
{
    return (i + j) >> 1;
}

/// Calculate an integer average of two unsigned
/// 16-bit integer values (uint16_t), rounded down. 
/// Fractional results are rounded down, e.g. avg16(20,41) = 30
/// @param i first value to average
/// @param j second value to average
/// @returns mean average of i and j, rounded down
LIB8STATIC_ALWAYS_INLINE uint16_t avg16( uint16_t i, uint16_t j)
{
    return (uint32_t)((uint32_t)(i) + (uint32_t)(j)) >> 1;
}

/// Calculate an integer average of two unsigned
/// 8-bit integer values (uint8_t), rounded up. 
/// Fractional results are rounded up, e.g. avg8r(20,41) = 31
/// @param i first value to average
/// @param j second value to average
/// @returns mean average of i and j, rounded up
LIB8STATIC_ALWAYS_INLINE uint8_t avg8r( uint8_t i, uint8_t j)
{
    return (i + j + 1) >> 1;
}

/// Calculate an integer average of two unsigned
/// 16-bit integer values (uint16_t), rounded up. 
/// Fractional results are rounded up, e.g. avg16r(20,41) = 31
/// @param i first value to average
/// @param j second value to average
/// @returns mean average of i and j, rounded up
LIB8STATIC_ALWAYS_INLINE uint16_t avg16r( uint16_t i, uint16_t j)
{
    return (uint32_t)((uint32_t)(i) + (uint32_t)(j) + 1) >> 1;
}


/// Calculate an integer average of two signed 7-bit
/// integers (int8_t). 
/// If the first argument is even, result is rounded down. 
/// If the first argument is odd, result is rounded up. 
/// @param i first value to average
/// @param j second value to average
/// @returns mean average of i and j, rounded
LIB8STATIC_ALWAYS_INLINE int8_t avg7( int8_t i, int8_t j)
{
    return (i>>1) + (j>>1) + (i & 0x1);
}

/// Calculate an integer average of two signed 15-bit
/// integers (int16_t). 
/// If the first argument is even, result is rounded down.
/// If the first argument is odd, result is rounded up.
/// @param i first value to average
/// @param j second value to average
/// @returns mean average of i and j, rounded
LIB8STATIC_ALWAYS_INLINE int16_t avg15( int16_t i, int16_t j)
{
    return (i>>1) + (j>>1) + (i & 0x1);
}


/// Calculate the remainder of one unsigned 8-bit
/// value divided by anoter, aka A % M. 
/// Implemented by repeated subtraction, which is
/// very compact, and very fast if A is "probably"
/// less than M.  If A is a large multiple of M,
/// the loop has to execute multiple times.  However,
/// even in that case, the loop is only two
/// instructions long on AVR, i.e., quick.
/// @param a dividend byte
/// @param m divisor byte
/// @returns remainder of a / m (i.e. a % m)
LIB8STATIC_ALWAYS_INLINE uint8_t mod8( uint8_t a, uint8_t m)
{
    while( a >= m) a -= m;
    return a;
}

/// Add two numbers, and calculate the modulo
/// of the sum and a third number, M. 
/// In other words, it returns (A+B) % M.
/// It is designed as a compact mechanism for
/// incrementing a "mode" switch and wrapping
/// around back to "mode 0" when the switch
/// goes past the end of the available range.
/// e.g. if you have seven modes, this switches
/// to the next one and wraps around if needed:
///   @code{.cpp}
///   mode = addmod8( mode, 1, 7);
///   @endcode
/// @param a dividend byte
/// @param b value to add to the dividend
/// @param m divisor byte
/// @returns remainder of (a + b) / m
/// @see mod8() for notes on performance.
LIB8STATIC uint8_t addmod8( uint8_t a, uint8_t b, uint8_t m)
{
    a += b;
    while( a >= m) a -= m;
    return a;
}

/// Subtract two numbers, and calculate the modulo
/// of the difference and a third number, M. 
/// In other words, it returns (A-B) % M.
/// It is designed as a compact mechanism for
/// decrementing a "mode" switch and wrapping
/// around back to "mode 0" when the switch
/// goes past the start of the available range.
/// e.g. if you have seven modes, this switches
/// to the previous one and wraps around if needed:
///   @code{.cpp}
///   mode = submod8( mode, 1, 7);
///   @endcode
/// @param a dividend byte
/// @param b value to subtract from the dividend
/// @param m divisor byte
/// @returns remainder of (a - b) / m
/// @see mod8() for notes on performance.
LIB8STATIC uint8_t submod8( uint8_t a, uint8_t b, uint8_t m)
{
    a -= b;
    while( a >= m) a -= m;
    return a;
}

/// 8x8 bit multiplication, with 8-bit result. 
/// @param i first byte to multiply
/// @param j second byte to multiply
/// @returns the product of i * j
/// @note This does not saturate and may overflow!
LIB8STATIC_ALWAYS_INLINE uint8_t mul8( uint8_t i, uint8_t j)
{
    return ((int)i * (int)(j) ) & 0xFF;
}


/// 8x8 bit multiplication with 8-bit result, saturating at 0xFF. 
/// @param i first byte to multiply
/// @param j second byte to multiply
/// @returns the product of i * j, capping at 0xFF
LIB8STATIC_ALWAYS_INLINE uint8_t qmul8( uint8_t i, uint8_t j)
{
    unsigned p = (unsigned)i * (unsigned)j;
    if( p > 255) p = 255;
    return p;
}


/// Take the absolute value of a signed 8-bit uint8_t. 
LIB8STATIC_ALWAYS_INLINE int8_t abs8( int8_t i)
{
    if( i < 0) i = -i;
    return i;
}

/// Square root for 16-bit integers. 
/// About three times faster and five times smaller
/// than Arduino's general `sqrt` on AVR.
LIB8STATIC uint8_t sqrt16(uint16_t x)
{
    if( x <= 1) {
        return x;
    }

    uint8_t low = 1; // lower bound
    uint8_t hi, mid;

    if( x > 7904) {
        hi = 255;
    } else {
        hi = (x >> 5) + 8; // initial estimate for upper bound
    }

    do {
        mid = (low + hi) >> 1;
        if ((uint16_t)(mid * mid) > x) {
            hi = mid - 1;
        } else {
            if( mid == 255) {
                return 255;
            }
            low = mid + 1;
        }
    } while (hi >= low);

    return low - 1;
}

/// Blend a variable proportion (0-255) of one byte to another. 
/// @param a the starting byte value
/// @param b the byte value to blend toward
/// @param amountOfB the proportion (0-255) of b to blend
/// @returns a byte value between a and b, inclusive
LIB8STATIC uint8_t blend8( uint8_t a, uint8_t b, uint8_t amountOfB)
{

    // The BLEND_FIXED formula is
    //
    //   result = (  A*(amountOfA) + B*(amountOfB)              )/ 256
    //
    // …where amountOfA = 255-amountOfB.
    //
    // This formula will never return 255, which is why the BLEND_FIXED + SCALE8_FIXED version is
    //
    //   result = (  A*(amountOfA) + A + B*(amountOfB) + B      ) / 256
    //
    // We can rearrange this formula for some great optimisations.
    //
    //   result = (  A*(amountOfA) + A + B*(amountOfB) + B      ) / 256
    //          = (  A*(255-amountOfB) + A + B*(amountOfB) + B  ) / 256
    //          = (  A*(256-amountOfB) + B*(amountOfB) + B      ) / 256
    //          = (  A*256 + B + B*(amountOfB) - A*(amountOfB)  ) / 256  // this is the version used in SCALE8_FIXED AVR below
    //          = (  A*256 + B + (B-A)*(amountOfB)              ) / 256  // this is the version used in SCALE8_FIXED C below

    uint16_t partial;
    uint8_t result;

    partial = (a << 8) | b; // A*256 + B

    // on many platforms this compiles to a single multiply of (B-A) * amountOfB
    partial += (b * amountOfB);
    partial -= (a * amountOfB);
    
    result = partial >> 8;
    
    return result;
}

#endif