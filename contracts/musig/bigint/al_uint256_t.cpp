#include "al_uint256_t.h"

const al_uint128_t al_uint128_64(64);
const al_uint128_t al_uint128_128(128);
const al_uint128_t al_uint128_256(256);
const al_uint256_t al_uint256_0(0);
const al_uint256_t al_uint256_1(1);
const al_uint256_t al_uint256_max(al_uint128_t((uint64_t)-1, (uint64_t)-1), al_uint128_t((uint64_t)-1, (uint64_t)-1));

al_uint256_t::al_uint256_t()
    : UPPER(al_uint128_0), LOWER(al_uint128_0)
{
}

al_uint256_t::al_uint256_t(const al_uint256_t &rhs)
    : UPPER(rhs.UPPER), LOWER(rhs.LOWER)
{
}

al_uint256_t::al_uint256_t(al_uint256_t &&rhs)
    : UPPER(std::move(rhs.UPPER)), LOWER(std::move(rhs.LOWER))
{
    if (this != &rhs)
    {
        rhs.UPPER = al_uint128_0;
        rhs.LOWER = al_uint128_0;
    }
}

al_uint256_t &al_uint256_t::operator=(const al_uint256_t &rhs)
{
    UPPER = rhs.UPPER;
    LOWER = rhs.LOWER;
    return *this;
}

al_uint256_t &al_uint256_t::operator=(al_uint256_t &&rhs)
{
    if (this != &rhs)
    {
        UPPER = std::move(rhs.UPPER);
        LOWER = std::move(rhs.LOWER);
        rhs.UPPER = al_uint128_0;
        rhs.LOWER = al_uint128_0;
    }
    return *this;
}

al_uint256_t::operator bool() const
{
    return (bool)(UPPER | LOWER);
}

al_uint256_t::operator uint8_t() const
{
    return (uint8_t)LOWER;
}

al_uint256_t::operator uint16_t() const
{
    return (uint16_t)LOWER;
}

al_uint256_t::operator uint32_t() const
{
    return (uint32_t)LOWER;
}

al_uint256_t::operator uint64_t() const
{
    return (uint64_t)LOWER;
}

al_uint256_t::operator al_uint128_t() const
{
    return LOWER;
}

al_uint256_t al_uint256_t::operator&(const al_uint128_t &rhs) const
{
    return al_uint256_t(al_uint128_0, LOWER & rhs);
}

al_uint256_t al_uint256_t::operator&(const al_uint256_t &rhs) const
{
    return al_uint256_t(UPPER & rhs.UPPER, LOWER & rhs.LOWER);
}

al_uint256_t &al_uint256_t::operator&=(const al_uint128_t &rhs)
{
    UPPER = al_uint128_0;
    LOWER &= rhs;
    return *this;
}

al_uint256_t &al_uint256_t::operator&=(const al_uint256_t &rhs)
{
    UPPER &= rhs.UPPER;
    LOWER &= rhs.LOWER;
    return *this;
}

al_uint256_t al_uint256_t::operator|(const al_uint128_t &rhs) const
{
    return al_uint256_t(UPPER, LOWER | rhs);
}

al_uint256_t al_uint256_t::operator|(const al_uint256_t &rhs) const
{
    return al_uint256_t(UPPER | rhs.UPPER, LOWER | rhs.LOWER);
}

al_uint256_t &al_uint256_t::operator|=(const al_uint128_t &rhs)
{
    LOWER |= rhs;
    return *this;
}

al_uint256_t &al_uint256_t::operator|=(const al_uint256_t &rhs)
{
    UPPER |= rhs.UPPER;
    LOWER |= rhs.LOWER;
    return *this;
}

al_uint256_t al_uint256_t::operator^(const al_uint128_t &rhs) const
{
    return al_uint256_t(UPPER, LOWER ^ rhs);
}

al_uint256_t al_uint256_t::operator^(const al_uint256_t &rhs) const
{
    return al_uint256_t(UPPER ^ rhs.UPPER, LOWER ^ rhs.LOWER);
}

al_uint256_t &al_uint256_t::operator^=(const al_uint128_t &rhs)
{
    LOWER ^= rhs;
    return *this;
}

al_uint256_t &al_uint256_t::operator^=(const al_uint256_t &rhs)
{
    UPPER ^= rhs.UPPER;
    LOWER ^= rhs.LOWER;
    return *this;
}

al_uint256_t al_uint256_t::operator~() const
{
    return al_uint256_t(~UPPER, ~LOWER);
}

al_uint256_t al_uint256_t::operator<<(const al_uint128_t &rhs) const
{
    return *this << al_uint256_t(rhs);
}

al_uint256_t al_uint256_t::operator<<(const al_uint256_t &rhs) const
{
    const al_uint128_t shift = rhs.LOWER;
    if (((bool)rhs.UPPER) || (shift >= al_uint128_256))
    {
        return al_uint256_0;
    }
    else if (shift == al_uint128_128)
    {
        return al_uint256_t(LOWER, al_uint128_0);
    }
    else if (shift == al_uint128_0)
    {
        return *this;
    }
    else if (shift < al_uint128_128)
    {
        return al_uint256_t((UPPER << shift) + (LOWER >> (al_uint128_128 - shift)), LOWER << shift);
    }
    else if ((al_uint128_256 > shift) && (shift > al_uint128_128))
    {
        return al_uint256_t(LOWER << (shift - al_uint128_128), al_uint128_0);
    }
    else
    {
        return al_uint256_0;
    }
}

al_uint256_t &al_uint256_t::operator<<=(const al_uint128_t &shift)
{
    return *this <<= al_uint256_t(shift);
}

al_uint256_t &al_uint256_t::operator<<=(const al_uint256_t &shift)
{
    *this = *this << shift;
    return *this;
}

al_uint256_t al_uint256_t::operator>>(const al_uint128_t &rhs) const
{
    return *this >> al_uint256_t(rhs);
}

al_uint256_t al_uint256_t::operator>>(const al_uint256_t &rhs) const
{
    const al_uint128_t shift = rhs.LOWER;
    if (((bool)rhs.UPPER) | (shift >= al_uint128_256))
    {
        return al_uint256_0;
    }
    else if (shift == al_uint128_128)
    {
        return al_uint256_t(UPPER);
    }
    else if (shift == al_uint128_0)
    {
        return *this;
    }
    else if (shift < al_uint128_128)
    {
        return al_uint256_t(UPPER >> shift, (UPPER << (al_uint128_128 - shift)) + (LOWER >> shift));
    }
    else if ((al_uint128_256 > shift) && (shift > al_uint128_128))
    {
        return al_uint256_t(UPPER >> (shift - al_uint128_128));
    }
    else
    {
        return al_uint256_0;
    }
}

al_uint256_t &al_uint256_t::operator>>=(const al_uint128_t &shift)
{
    return *this >>= al_uint256_t(shift);
}

al_uint256_t &al_uint256_t::operator>>=(const al_uint256_t &shift)
{
    *this = *this >> shift;
    return *this;
}

bool al_uint256_t::operator!() const
{
    return !(bool)*this;
}

bool al_uint256_t::operator&&(const al_uint128_t &rhs) const
{
    return (*this && al_uint256_t(rhs));
}

bool al_uint256_t::operator&&(const al_uint256_t &rhs) const
{
    return ((bool)*this && (bool)rhs);
}

bool al_uint256_t::operator||(const al_uint128_t &rhs) const
{
    return (*this || al_uint256_t(rhs));
}

bool al_uint256_t::operator||(const al_uint256_t &rhs) const
{
    return ((bool)*this || (bool)rhs);
}

bool al_uint256_t::operator==(const al_uint128_t &rhs) const
{
    return (*this == al_uint256_t(rhs));
}

bool al_uint256_t::operator==(const al_uint256_t &rhs) const
{
    return ((UPPER == rhs.UPPER) && (LOWER == rhs.LOWER));
}

bool al_uint256_t::operator!=(const al_uint128_t &rhs) const
{
    return (*this != al_uint256_t(rhs));
}

bool al_uint256_t::operator!=(const al_uint256_t &rhs) const
{
    return ((UPPER != rhs.UPPER) | (LOWER != rhs.LOWER));
}

bool al_uint256_t::operator>(const al_uint128_t &rhs) const
{
    return (*this > al_uint256_t(rhs));
}

bool al_uint256_t::operator>(const al_uint256_t &rhs) const
{
    if (UPPER == rhs.UPPER)
    {
        return (LOWER > rhs.LOWER);
    }
    if (UPPER > rhs.UPPER)
    {
        return true;
    }
    return false;
}

bool al_uint256_t::operator<(const al_uint128_t &rhs) const
{
    return (*this < al_uint256_t(rhs));
}

bool al_uint256_t::operator<(const al_uint256_t &rhs) const
{
    if (UPPER == rhs.UPPER)
    {
        return (LOWER < rhs.LOWER);
    }
    if (UPPER < rhs.UPPER)
    {
        return true;
    }
    return false;
}

bool al_uint256_t::operator>=(const al_uint128_t &rhs) const
{
    return (*this >= al_uint256_t(rhs));
}

bool al_uint256_t::operator>=(const al_uint256_t &rhs) const
{
    return ((*this > rhs) | (*this == rhs));
}

bool al_uint256_t::operator<=(const al_uint128_t &rhs) const
{
    return (*this <= al_uint256_t(rhs));
}

bool al_uint256_t::operator<=(const al_uint256_t &rhs) const
{
    return ((*this < rhs) | (*this == rhs));
}

al_uint256_t al_uint256_t::operator+(const al_uint128_t &rhs) const
{
    return *this + al_uint256_t(rhs);
}

al_uint256_t al_uint256_t::operator+(const al_uint256_t &rhs) const
{
    return al_uint256_t(UPPER + rhs.UPPER + (((LOWER + rhs.LOWER) < LOWER) ? al_uint128_1 : al_uint128_0), LOWER + rhs.LOWER);
}

al_uint256_t &al_uint256_t::operator+=(const al_uint128_t &rhs)
{
    return *this += al_uint256_t(rhs);
}

al_uint256_t &al_uint256_t::operator+=(const al_uint256_t &rhs)
{
    UPPER = rhs.UPPER + UPPER + ((LOWER + rhs.LOWER) < LOWER);
    LOWER = LOWER + rhs.LOWER;
    return *this;
}

al_uint256_t al_uint256_t::operator-(const al_uint128_t &rhs) const
{
    return *this - al_uint256_t(rhs);
}

al_uint256_t al_uint256_t::operator-(const al_uint256_t &rhs) const
{
    return al_uint256_t(UPPER - rhs.UPPER - ((LOWER - rhs.LOWER) > LOWER), LOWER - rhs.LOWER);
}

al_uint256_t &al_uint256_t::operator-=(const al_uint128_t &rhs)
{
    return *this -= al_uint256_t(rhs);
}

al_uint256_t &al_uint256_t::operator-=(const al_uint256_t &rhs)
{
    *this = *this - rhs;
    return *this;
}

al_uint256_t al_uint256_t::operator*(const al_uint128_t &rhs) const
{
    return *this * al_uint256_t(rhs);
}

al_uint256_t al_uint256_t::operator*(const al_uint256_t &rhs) const
{
    // split values into 4 64-bit parts
    al_uint128_t top[4] = {UPPER.upper(), UPPER.lower(), LOWER.upper(), LOWER.lower()};
    al_uint128_t bottom[4] = {rhs.upper().upper(), rhs.upper().lower(), rhs.lower().upper(), rhs.lower().lower()};
    al_uint128_t products[4][4];

    // multiply each component of the values
    for (int y = 3; y > -1; y--)
    {
        for (int x = 3; x > -1; x--)
        {
            products[3 - y][x] = top[x] * bottom[y];
        }
    }

    // first row
    al_uint128_t fourth64 = al_uint128_t(products[0][3].lower());
    al_uint128_t third64 = al_uint128_t(products[0][2].lower()) + al_uint128_t(products[0][3].upper());
    al_uint128_t second64 = al_uint128_t(products[0][1].lower()) + al_uint128_t(products[0][2].upper());
    al_uint128_t first64 = al_uint128_t(products[0][0].lower()) + al_uint128_t(products[0][1].upper());

    // second row
    third64 += al_uint128_t(products[1][3].lower());
    second64 += al_uint128_t(products[1][2].lower()) + al_uint128_t(products[1][3].upper());
    first64 += al_uint128_t(products[1][1].lower()) + al_uint128_t(products[1][2].upper());

    // third row
    second64 += al_uint128_t(products[2][3].lower());
    first64 += al_uint128_t(products[2][2].lower()) + al_uint128_t(products[2][3].upper());

    // fourth row
    first64 += al_uint128_t(products[3][3].lower());

    // combines the values, taking care of carry over
    return al_uint256_t(first64 << al_uint128_64, al_uint128_0) +
           al_uint256_t(third64.upper(), third64 << al_uint128_64) +
           al_uint256_t(second64, al_uint128_0) +
           al_uint256_t(fourth64);
}

al_uint256_t &al_uint256_t::operator*=(const al_uint128_t &rhs)
{
    return *this *= al_uint256_t(rhs);
}

al_uint256_t &al_uint256_t::operator*=(const al_uint256_t &rhs)
{
    *this = *this * rhs;
    return *this;
}

std::pair<al_uint256_t, al_uint256_t> al_uint256_t::divmod(const al_uint256_t &lhs, const al_uint256_t &rhs) const
{
    // Save some calculations /////////////////////
    if (rhs == al_uint256_0)
    {
        eosio_assert(true, "Error: division or modulus by 0");
    }
    else if (rhs == al_uint256_1)
    {
        return std::pair<al_uint256_t, al_uint256_t>(lhs, al_uint256_0);
    }
    else if (lhs == rhs)
    {
        return std::pair<al_uint256_t, al_uint256_t>(al_uint256_1, al_uint256_0);
    }
    else if ((lhs == al_uint256_0) || (lhs < rhs))
    {
        return std::pair<al_uint256_t, al_uint256_t>(al_uint256_0, lhs);
    }

    std::pair<al_uint256_t, al_uint256_t> qr(al_uint256_0, lhs);
    al_uint256_t copyd = rhs << (lhs.bits() - rhs.bits());
    al_uint256_t adder = al_uint256_1 << (lhs.bits() - rhs.bits());
    if (copyd > qr.second)
    {
        copyd >>= al_uint256_1;
        adder >>= al_uint256_1;
    }
    while (qr.second >= rhs)
    {
        if (qr.second >= copyd)
        {
            qr.second -= copyd;
            qr.first |= adder;
        }
        copyd >>= al_uint256_1;
        adder >>= al_uint256_1;
    }
    return qr;
}

al_uint256_t al_uint256_t::operator/(const al_uint128_t &rhs) const
{
    return *this / al_uint256_t(rhs);
}

al_uint256_t al_uint256_t::operator/(const al_uint256_t &rhs) const
{
    return divmod(*this, rhs).first;
}

al_uint256_t &al_uint256_t::operator/=(const al_uint128_t &rhs)
{
    return *this /= al_uint256_t(rhs);
}

al_uint256_t &al_uint256_t::operator/=(const al_uint256_t &rhs)
{
    *this = *this / rhs;
    return *this;
}

al_uint256_t al_uint256_t::operator%(const al_uint128_t &rhs) const
{
    return *this % al_uint256_t(rhs);
}

al_uint256_t al_uint256_t::operator%(const al_uint256_t &rhs) const
{
    return *this - (rhs * (*this / rhs));
}

al_uint256_t &al_uint256_t::operator%=(const al_uint128_t &rhs)
{
    return *this %= al_uint256_t(rhs);
}

al_uint256_t &al_uint256_t::operator%=(const al_uint256_t &rhs)
{
    *this = *this % rhs;
    return *this;
}

al_uint256_t &al_uint256_t::operator++()
{
    *this += al_uint256_1;
    return *this;
}

al_uint256_t al_uint256_t::operator++(int)
{
    al_uint256_t temp(*this);
    ++*this;
    return temp;
}

al_uint256_t &al_uint256_t::operator--()
{
    *this -= al_uint256_1;
    return *this;
}

al_uint256_t al_uint256_t::operator--(int)
{
    al_uint256_t temp(*this);
    --*this;
    return temp;
}

al_uint256_t al_uint256_t::operator+() const
{
    return *this;
}

al_uint256_t al_uint256_t::operator-() const
{
    return ~*this + al_uint256_1;
}

const al_uint128_t &al_uint256_t::upper() const
{
    return UPPER;
}

const al_uint128_t &al_uint256_t::lower() const
{
    return LOWER;
}

uint16_t al_uint256_t::bits() const
{
    uint16_t out = 0;
    if (UPPER)
    {
        out = 128;
        al_uint128_t up = UPPER;
        while (up)
        {
            up >>= al_uint128_1;
            out++;
        }
    }
    else
    {
        al_uint128_t low = LOWER;
        while (low)
        {
            low >>= al_uint128_1;
            out++;
        }
    }
    return out;
}

void al_uint256_t::str(uint8_t base, char *out, const unsigned int &len) const
{
    if ((base < 2) || (base > 16))
    {
        eosio_assert(true, "Base must be in the range [2, 16]");
    }

    for (size_t index = 0; index < len; index++)
    {
        out[index] = '0';
    }
    std::pair<al_uint256_t, al_uint256_t> qr(*this, al_uint128_0);
    size_t index = len;
    do
    {
        qr = divmod(qr.first, base);
        out[index--] = "0123456789abcdef"[(uint8_t)qr.second];
    } while (qr.first && index >= 0);
}

al_uint256_t operator&(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return rhs & lhs;
}

al_uint128_t &operator&=(al_uint128_t &lhs, const al_uint256_t &rhs)
{
    lhs = (rhs & lhs).lower();
    return lhs;
}

al_uint256_t operator|(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return rhs | lhs;
}

al_uint128_t &operator|=(al_uint128_t &lhs, const al_uint256_t &rhs)
{
    lhs = (rhs | lhs).lower();
    return lhs;
}

al_uint256_t operator^(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return rhs ^ lhs;
}

al_uint128_t &operator^=(al_uint128_t &lhs, const al_uint256_t &rhs)
{
    lhs = (rhs ^ lhs).lower();
    return lhs;
}

al_uint256_t operator<<(const bool &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) << rhs;
}

al_uint256_t operator<<(const uint8_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) << rhs;
}

al_uint256_t operator<<(const uint16_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) << rhs;
}

al_uint256_t operator<<(const uint32_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) << rhs;
}

al_uint256_t operator<<(const uint64_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) << rhs;
}

al_uint256_t operator<<(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) << rhs;
}

al_uint256_t operator<<(const int8_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) << rhs;
}

al_uint256_t operator<<(const int16_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) << rhs;
}

al_uint256_t operator<<(const int32_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) << rhs;
}

al_uint256_t operator<<(const int64_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) << rhs;
}

al_uint128_t &operator<<=(al_uint128_t &lhs, const al_uint256_t &rhs)
{
    lhs = (al_uint256_t(lhs) << rhs).lower();
    return lhs;
}

al_uint256_t operator>>(const bool &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) >> rhs;
}

al_uint256_t operator>>(const uint8_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) >> rhs;
}

al_uint256_t operator>>(const uint16_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) >> rhs;
}

al_uint256_t operator>>(const uint32_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) >> rhs;
}

al_uint256_t operator>>(const uint64_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) >> rhs;
}

al_uint256_t operator>>(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) >> rhs;
}

al_uint256_t operator>>(const int8_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) >> rhs;
}

al_uint256_t operator>>(const int16_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) >> rhs;
}

al_uint256_t operator>>(const int32_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) >> rhs;
}

al_uint256_t operator>>(const int64_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) >> rhs;
}

al_uint128_t &operator>>=(al_uint128_t &lhs, const al_uint256_t &rhs)
{
    lhs = (al_uint256_t(lhs) >> rhs).lower();
    return lhs;
}

// Comparison Operators
bool operator==(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return rhs == lhs;
}

bool operator!=(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return rhs != lhs;
}

bool operator>(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return rhs < lhs;
}

bool operator<(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return rhs > lhs;
}

bool operator>=(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return rhs <= lhs;
}

bool operator<=(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return rhs >= lhs;
}

// Arithmetic Operators
al_uint256_t operator+(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return rhs + lhs;
}

al_uint128_t &operator+=(al_uint128_t &lhs, const al_uint256_t &rhs)
{
    lhs = (rhs + lhs).lower();
    return lhs;
}

al_uint256_t operator-(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return -(rhs - lhs);
}

al_uint128_t &operator-=(al_uint128_t &lhs, const al_uint256_t &rhs)
{
    lhs = (-(rhs - lhs)).lower();
    return lhs;
}

al_uint256_t operator*(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return rhs * lhs;
}

al_uint128_t &operator*=(al_uint128_t &lhs, const al_uint256_t &rhs)
{
    lhs = (rhs * lhs).lower();
    return lhs;
}

al_uint256_t operator/(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) / rhs;
}

al_uint128_t &operator/=(al_uint128_t &lhs, const al_uint256_t &rhs)
{
    lhs = (al_uint256_t(lhs) / rhs).lower();
    return lhs;
}

al_uint256_t operator%(const al_uint128_t &lhs, const al_uint256_t &rhs)
{
    return al_uint256_t(lhs) % rhs;
}

al_uint128_t &operator%=(al_uint128_t &lhs, const al_uint256_t &rhs)
{
    lhs = (al_uint256_t(lhs) % rhs).lower();
    return lhs;
}

// std::ostream &operator<<(std::ostream &stream, const al_uint256_t &rhs)
// {
//     if (stream.flags() & stream.oct)
//     {
//         stream << rhs.str(8);
//     }
//     else if (stream.flags() & stream.dec)
//     {
//         stream << rhs.str(10);
//     }
//     else if (stream.flags() & stream.hex)
//     {
//         stream << rhs.str(16);
//     }
//     return stream;
// }
