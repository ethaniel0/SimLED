#ifndef __INC_LIB8TION_TRIG_H
#define __INC_LIB8TION_TRIG_H

/// @file trig8.h
/// Fast, efficient 8-bit trigonometry functions specifically
/// designed for high-performance LED programming. 

/// @ingroup lib8tion
/// @{

/// @defgroup Trig Fast Trigonometry Functions
/// Fast 8-bit and 16-bit approximations of sin(x) and cos(x). 
///
/// Don't use these approximations for calculating the
/// trajectory of a rocket to Mars, but they're great
/// for art projects and LED displays.
///
/// On Arduino/AVR, the 16-bit approximation is more than
/// 10X faster than floating point sin(x) and cos(x), while
/// the 8-bit approximation is more than 20X faster.
/// @{

/// Platform-independent alias of the fast sin implementation
#define sin16 sin16_C

/// Fast 16-bit approximation of sin(x). This approximation never varies more than
/// 0.69% from the floating point value you'd get by doing
///    @code{.cpp}
///    float s = sin(x) * 32767.0;
///    @endcode
///
/// @param theta input angle from 0-65535
/// @returns sin of theta, value between -32767 to 32767.
LIB8STATIC int16_t sin16_C( uint16_t theta )
{
    static const uint16_t base[] =
    { 0, 6393, 12539, 18204, 23170, 27245, 30273, 32137 };
    static const uint8_t slope[] =
    { 49, 48, 44, 38, 31, 23, 14, 4 };

    uint16_t offset = (theta & 0x3FFF) >> 3; // 0..2047
    if( theta & 0x4000 ) offset = 2047 - offset;

    uint8_t section = offset / 256; // 0..7
    uint16_t b   = base[section];
    uint8_t  m   = slope[section];

    uint8_t secoffset8 = (uint8_t)(offset) / 2;

    uint16_t mx = m * secoffset8;
    int16_t  y  = mx + b;

    if( theta & 0x8000 ) y = -y;

    return y;
}

/// Fast 16-bit approximation of cos(x). This approximation never varies more than
/// 0.69% from the floating point value you'd get by doing
///    @code{.cpp}
///    float s = cos(x) * 32767.0;
///    @endcode
///
/// @param theta input angle from 0-65535
/// @returns cos of theta, value between -32767 to 32767.
LIB8STATIC int16_t cos16( uint16_t theta)
{
    return sin16( theta + 16384);
}

///////////////////////////////////////////////////////////////////////
// sin8() and cos8() 
// Fast 8-bit approximations of sin(x) & cos(x).

/// Pre-calculated lookup table used in sin8() and cos8() functions
const uint8_t b_m16_interleave[] = { 0, 49, 49, 41, 90, 27, 117, 10 };

/// Platform-independent alias of the fast sin implementation
#define sin8 sin8_C

/// Fast 8-bit approximation of sin(x). This approximation never varies more than
/// 2% from the floating point value you'd get by doing
///   @code{.cpp}
///   float s = (sin(x) * 128.0) + 128;
///   @endcode
///
/// @param theta input angle from 0-255
/// @returns sin of theta, value between 0 and 255
LIB8STATIC uint8_t sin8_C( uint8_t theta)
{
    uint8_t offset = theta;
    if( theta & 0x40 ) {
        offset = (uint8_t)255 - offset;
    }
    offset &= 0x3F; // 0..63

    uint8_t secoffset  = offset & 0x0F; // 0..15
    if( theta & 0x40) ++secoffset;

    uint8_t section = offset >> 4; // 0..3
    uint8_t s2 = section * 2;
    const uint8_t* p = b_m16_interleave;
    p += s2;
    uint8_t b   =  *p;
    ++p;
    uint8_t m16 =  *p;

    uint8_t mx = (m16 * secoffset) >> 4;

    int8_t y = mx + b;
    if( theta & 0x80 ) y = -y;

    y += 128;

    return y;
}

/// Fast 8-bit approximation of cos(x). This approximation never varies more than
/// 2% from the floating point value you'd get by doing
///   @code{.cpp}
///   float s = (cos(x) * 128.0) + 128;
///   @endcode
///
/// @param theta input angle from 0-255
/// @returns cos of theta, value between 0 and 255
LIB8STATIC uint8_t cos8( uint8_t theta)
{
    return sin8( theta + 64);
}

/// @} Trig
/// @} lib8tion

#endif
