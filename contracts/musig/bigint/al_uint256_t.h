/*
al_uint256_t.h
An unsigned 256 bit integer library for C++

Copyright (c) 2013 - 2017 Jason Lee @ calccrypto at gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

With much help from Auston Sterling

Thanks to Fran�ois Dessenne for convincing me
to do a general rewrite of this class.
*/

#ifndef __AL_UINT256_T__
#define __AL_UINT256_T__

#include <eosiolib/system.h>
#include <cstdint>
// #include <ostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "al_uint128_t.h"

struct al_uint256_t;

// Give al_uint256_t type traits
namespace std
{ // This is probably not a good idea
template <>
struct is_arithmetic<al_uint256_t> : std::true_type
{
};
template <>
struct is_integral<al_uint256_t> : std::true_type
{
};
template <>
struct is_unsigned<al_uint256_t> : std::true_type
{
};
} // namespace std

struct al_uint256_t
{
    //   private:
    al_uint128_t UPPER, LOWER;

    //   public:
    // Constructors
    al_uint256_t();
    al_uint256_t(const al_uint256_t &rhs);
    al_uint256_t(al_uint256_t &&rhs);

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t(const T &rhs)
        : UPPER(al_uint128_0), LOWER(rhs)
    {
    }

    template <typename S, typename T, typename = typename std::enable_if<std::is_integral<S>::value && std::is_integral<T>::value, void>::type>
    al_uint256_t(const S &upper_rhs, const T &lower_rhs)
        : UPPER(upper_rhs), LOWER(lower_rhs)
    {
    }

    template <typename R, typename S, typename T, typename U,
              typename = typename std::enable_if<std::is_integral<R>::value && std::is_integral<S>::value && std::is_integral<T>::value && std::is_integral<U>::value, void>::type>
    al_uint256_t(const R &upper_lhs, const S &lower_lhs, const T &upper_rhs, const U &lower_rhs)
        : UPPER(upper_lhs, lower_lhs), LOWER(upper_rhs, lower_rhs)
    {
    }

    //  RHS input args only

    // Assignment Operator
    al_uint256_t &operator=(const al_uint256_t &rhs);
    al_uint256_t &operator=(al_uint256_t &&rhs);

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t &operator=(const T &rhs)
    {
        UPPER = al_uint128_0;
        LOWER = rhs;
        return *this;
    }

    // Typecast Operators
    operator bool() const;
    operator uint8_t() const;
    operator uint16_t() const;
    operator uint32_t() const;
    operator uint64_t() const;
    operator al_uint128_t() const;

    // Bitwise Operators
    al_uint256_t operator&(const al_uint128_t &rhs) const;
    al_uint256_t operator&(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t operator&(const T &rhs) const
    {
        return al_uint256_t(al_uint128_0, LOWER & (al_uint128_t)rhs);
    }

    al_uint256_t &operator&=(const al_uint128_t &rhs);
    al_uint256_t &operator&=(const al_uint256_t &rhs);

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t &operator&=(const T &rhs)
    {
        UPPER = al_uint128_0;
        LOWER &= rhs;
        return *this;
    }

    al_uint256_t operator|(const al_uint128_t &rhs) const;
    al_uint256_t operator|(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t operator|(const T &rhs) const
    {
        return al_uint256_t(UPPER, LOWER | al_uint128_t(rhs));
    }

    al_uint256_t &operator|=(const al_uint128_t &rhs);
    al_uint256_t &operator|=(const al_uint256_t &rhs);

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t &operator|=(const T &rhs)
    {
        LOWER |= (al_uint128_t)rhs;
        return *this;
    }

    al_uint256_t operator^(const al_uint128_t &rhs) const;
    al_uint256_t operator^(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t operator^(const T &rhs) const
    {
        return al_uint256_t(UPPER, LOWER ^ (al_uint128_t)rhs);
    }

    al_uint256_t &operator^=(const al_uint128_t &rhs);
    al_uint256_t &operator^=(const al_uint256_t &rhs);

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t &operator^=(const T &rhs)
    {
        LOWER ^= (al_uint128_t)rhs;
        return *this;
    }

    al_uint256_t operator~() const;

    // Bit Shift Operators
    al_uint256_t operator<<(const al_uint128_t &shift) const;
    al_uint256_t operator<<(const al_uint256_t &shift) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t operator<<(const T &rhs) const
    {
        return *this << al_uint256_t(rhs);
    }

    al_uint256_t &operator<<=(const al_uint128_t &shift);
    al_uint256_t &operator<<=(const al_uint256_t &shift);

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t &operator<<=(const T &rhs)
    {
        *this = *this << al_uint256_t(rhs);
        return *this;
    }

    al_uint256_t operator>>(const al_uint128_t &shift) const;
    al_uint256_t operator>>(const al_uint256_t &shift) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t operator>>(const T &rhs) const
    {
        return *this >> al_uint256_t(rhs);
    }

    al_uint256_t &operator>>=(const al_uint128_t &shift);
    al_uint256_t &operator>>=(const al_uint256_t &shift);

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t &operator>>=(const T &rhs)
    {
        *this = *this >> al_uint256_t(rhs);
        return *this;
    }

    // Logical Operators
    bool operator!() const;

    bool operator&&(const al_uint128_t &rhs) const;
    bool operator&&(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    bool operator&&(const T &rhs) const
    {
        return ((bool)*this && rhs);
    }

    bool operator||(const al_uint128_t &rhs) const;
    bool operator||(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    bool operator||(const T &rhs) const
    {
        return ((bool)*this || rhs);
    }

    // Comparison Operators
    bool operator==(const al_uint128_t &rhs) const;
    bool operator==(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    bool operator==(const T &rhs) const
    {
        return (!UPPER && (LOWER == al_uint128_t(rhs)));
    }

    bool operator!=(const al_uint128_t &rhs) const;
    bool operator!=(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    bool operator!=(const T &rhs) const
    {
        return ((bool)UPPER | (LOWER != al_uint128_t(rhs)));
    }

    bool operator>(const al_uint128_t &rhs) const;
    bool operator>(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    bool operator>(const T &rhs) const
    {
        return ((bool)UPPER | (LOWER > al_uint128_t(rhs)));
    }

    bool operator<(const al_uint128_t &rhs) const;
    bool operator<(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    bool operator<(const T &rhs) const
    {
        return (!UPPER) ? (LOWER < al_uint128_t(rhs)) : false;
    }

    bool operator>=(const al_uint128_t &rhs) const;
    bool operator>=(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    bool operator>=(const T &rhs) const
    {
        return ((*this > rhs) | (*this == rhs));
    }

    bool operator<=(const al_uint128_t &rhs) const;
    bool operator<=(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    bool operator<=(const T &rhs) const
    {
        return ((*this < rhs) | (*this == rhs));
    }

    // Arithmetic Operators
    al_uint256_t operator+(const al_uint128_t &rhs) const;
    al_uint256_t operator+(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t operator+(const T &rhs) const
    {
        return al_uint256_t(UPPER + ((LOWER + (al_uint128_t)rhs) < LOWER), LOWER + (al_uint128_t)rhs);
    }

    al_uint256_t &operator+=(const al_uint128_t &rhs);
    al_uint256_t &operator+=(const al_uint256_t &rhs);

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t &operator+=(const T &rhs)
    {
        UPPER = UPPER + ((LOWER + rhs) < LOWER);
        LOWER = LOWER + rhs;
        return *this;
    }

    al_uint256_t operator-(const al_uint128_t &rhs) const;
    al_uint256_t operator-(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t operator-(const T &rhs) const
    {
        return al_uint256_t(UPPER - ((LOWER - rhs) > LOWER), LOWER - rhs);
    }

    al_uint256_t &operator-=(const al_uint128_t &rhs);
    al_uint256_t &operator-=(const al_uint256_t &rhs);

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t &operator-=(const T &rhs)
    {
        *this = *this - rhs;
        return *this;
    }

    al_uint256_t operator*(const al_uint128_t &rhs) const;
    al_uint256_t operator*(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t operator*(const T &rhs) const
    {
        return *this * al_uint256_t(rhs);
    }

    al_uint256_t &operator*=(const al_uint128_t &rhs);
    al_uint256_t &operator*=(const al_uint256_t &rhs);

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t &operator*=(const T &rhs)
    {
        *this = *this * al_uint256_t(rhs);
        return *this;
    }

  private:
    std::pair<al_uint256_t, al_uint256_t> divmod(const al_uint256_t &lhs, const al_uint256_t &rhs) const;

  public:
    al_uint256_t operator/(const al_uint128_t &rhs) const;
    al_uint256_t operator/(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t operator/(const T &rhs) const
    {
        return *this / al_uint256_t(rhs);
    }

    al_uint256_t &operator/=(const al_uint128_t &rhs);
    al_uint256_t &operator/=(const al_uint256_t &rhs);

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t &operator/=(const T &rhs)
    {
        *this = *this / al_uint256_t(rhs);
        return *this;
    }

    al_uint256_t operator%(const al_uint128_t &rhs) const;
    al_uint256_t operator%(const al_uint256_t &rhs) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t operator%(const T &rhs) const
    {
        return *this % al_uint256_t(rhs);
    }

    al_uint256_t &operator%=(const al_uint128_t &rhs);
    al_uint256_t &operator%=(const al_uint256_t &rhs);

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    al_uint256_t &operator%=(const T &rhs)
    {
        *this = *this % al_uint256_t(rhs);
        return *this;
    }

    // Increment Operators
    al_uint256_t &operator++();
    al_uint256_t operator++(int);

    // Decrement Operators
    al_uint256_t &operator--();
    al_uint256_t operator--(int);

    // Nothing done since promotion doesn't work here
    al_uint256_t operator+() const;

    // two's complement
    al_uint256_t operator-() const;

    // Get private values
    const al_uint128_t &upper() const;
    const al_uint128_t &lower() const;

    // Get bitsize of value
    uint16_t bits() const;

    // Get string representation of value
    void str(uint8_t base, char *out, const unsigned int &len) const;
};

// useful values
extern const al_uint128_t al_uint128_64;
extern const al_uint128_t al_uint128_128;
extern const al_uint128_t al_uint128_256;
extern const al_uint256_t al_uint256_0;
extern const al_uint256_t al_uint256_1;
extern const al_uint256_t al_uint256_max;

// Bitwise Operators
al_uint256_t operator&(const al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
al_uint256_t operator&(const T &lhs, const al_uint256_t &rhs)
{
    return rhs & lhs;
}

al_uint128_t &operator&=(al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
T &operator&=(T &lhs, const al_uint256_t &rhs)
{
    return lhs = static_cast<T>(rhs & lhs);
}

al_uint256_t operator|(const al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
al_uint256_t operator|(const T &lhs, const al_uint256_t &rhs)
{
    return rhs | lhs;
}

al_uint128_t &operator|=(al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
T &operator|=(T &lhs, const al_uint256_t &rhs)
{
    return lhs = static_cast<T>(rhs | lhs);
}

al_uint256_t operator^(const al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
al_uint256_t operator^(const T &lhs, const al_uint256_t &rhs)
{
    return rhs ^ lhs;
}

al_uint128_t &operator^=(al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
T &operator^=(T &lhs, const al_uint256_t &rhs)
{
    return lhs = static_cast<T>(rhs ^ lhs);
}

// Bitshift operators
al_uint256_t operator<<(const bool &lhs, const al_uint256_t &rhs);
al_uint256_t operator<<(const uint8_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator<<(const uint16_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator<<(const uint32_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator<<(const uint64_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator<<(const al_uint128_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator<<(const int8_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator<<(const int16_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator<<(const int32_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator<<(const int64_t &lhs, const al_uint256_t &rhs);

al_uint128_t &operator<<=(al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
T &operator<<=(T &lhs, const al_uint256_t &rhs)
{
    lhs = static_cast<T>(al_uint256_t(lhs) << rhs);
    return lhs;
}

al_uint256_t operator>>(const bool &lhs, const al_uint256_t &rhs);
al_uint256_t operator>>(const uint8_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator>>(const uint16_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator>>(const uint32_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator>>(const uint64_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator>>(const al_uint128_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator>>(const int8_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator>>(const int16_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator>>(const int32_t &lhs, const al_uint256_t &rhs);
al_uint256_t operator>>(const int64_t &lhs, const al_uint256_t &rhs);

al_uint128_t &operator>>=(al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
T &operator>>=(T &lhs, const al_uint256_t &rhs)
{
    return lhs = static_cast<T>(al_uint256_t(lhs) >> rhs);
}

// Comparison Operators
bool operator==(const al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
bool operator==(const T &lhs, const al_uint256_t &rhs)
{
    return (!rhs.upper() && ((uint64_t)lhs == rhs.lower()));
}

bool operator!=(const al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
bool operator!=(const T &lhs, const al_uint256_t &rhs)
{
    return (rhs.upper() | ((uint64_t)lhs != rhs.lower()));
}

bool operator>(const al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
bool operator>(const T &lhs, const al_uint256_t &rhs)
{
    return rhs.upper() ? false : ((al_uint128_t)lhs > rhs.lower());
}

bool operator<(const al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
bool operator<(const T &lhs, const al_uint256_t &rhs)
{
    return rhs.upper() ? true : ((al_uint128_t)lhs < rhs.lower());
}

bool operator>=(const al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
bool operator>=(const T &lhs, const al_uint256_t &rhs)
{
    return rhs.upper() ? false : ((al_uint128_t)lhs >= rhs.lower());
}

bool operator<=(const al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
bool operator<=(const T &lhs, const al_uint256_t &rhs)
{
    return rhs.upper() ? true : ((al_uint128_t)lhs <= rhs.lower());
}

// Arithmetic Operators
al_uint256_t operator+(const al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
al_uint256_t operator+(const T &lhs, const al_uint256_t &rhs)
{
    return rhs + lhs;
}

al_uint128_t &operator+=(al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
T &operator+=(T &lhs, const al_uint256_t &rhs)
{
    lhs = static_cast<T>(rhs + lhs);
    return lhs;
}

al_uint256_t operator-(const al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
al_uint256_t operator-(const T &lhs, const al_uint256_t &rhs)
{
    return -(rhs - lhs);
}

al_uint128_t &operator-=(al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
T &operator-=(T &lhs, const al_uint256_t &rhs)
{
    return lhs = static_cast<T>(-(rhs - lhs));
}

al_uint256_t operator*(const al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
al_uint256_t operator*(const T &lhs, const al_uint256_t &rhs)
{
    return rhs * lhs;
}

al_uint128_t &operator*=(al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
T &operator*=(T &lhs, const al_uint256_t &rhs)
{
    return lhs = static_cast<T>(rhs * lhs);
}

al_uint256_t operator/(const al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
al_uint256_t operator/(const T &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) / rhs;
}

al_uint128_t &operator/=(al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
T &operator/=(T &lhs, const al_uint256_t &rhs)
{
    return lhs = static_cast<T>(al_uint256_t(lhs) / rhs);
}

al_uint256_t operator%(const al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
al_uint256_t operator%(const T &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) % rhs;
}

al_uint128_t &operator%=(al_uint128_t &lhs, const al_uint256_t &rhs);

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
T &operator%=(T &lhs, const al_uint256_t &rhs)
{
    return lhs = static_cast<T>(al_uint256_t(lhs) % rhs);
}

// IO Operator
// std::ostream &operator<<(std::ostream &stream, const al_uint256_t &rhs);
#endif
