#include "al_uint128_t.h"

const al_uint128_t al_uint128_0(0);
const al_uint128_t al_uint128_1(1);
const al_uint128_t al_uint128_max((uint64_t)-1, (uint64_t)-1);

al_uint128_t::al_uint128_t()
    : UPPER(0), LOWER(0)
{
}

al_uint128_t::al_uint128_t(const al_uint128_t &rhs)
    : UPPER(rhs.UPPER), LOWER(rhs.LOWER)
{
}

al_uint128_t::al_uint128_t(al_uint128_t &&rhs)
    : UPPER(std::move(rhs.UPPER)), LOWER(std::move(rhs.LOWER))
{
    if (this != &rhs)
    {
        rhs.UPPER = 0;
        rhs.LOWER = 0;
    }
}

al_uint128_t &al_uint128_t::operator=(const al_uint128_t &rhs)
{
    UPPER = rhs.UPPER;
    LOWER = rhs.LOWER;
    return *this;
}

al_uint128_t &al_uint128_t::operator=(al_uint128_t &&rhs)
{
    if (this != &rhs)
    {
        UPPER = std::move(rhs.UPPER);
        LOWER = std::move(rhs.LOWER);
        rhs.UPPER = 0;
        rhs.LOWER = 0;
    }
    return *this;
}

al_uint128_t::operator bool() const
{
    return (bool)(UPPER | LOWER);
}

al_uint128_t::operator uint8_t() const
{
    return (uint8_t)LOWER;
}

al_uint128_t::operator uint16_t() const
{
    return (uint16_t)LOWER;
}

al_uint128_t::operator uint32_t() const
{
    return (uint32_t)LOWER;
}

al_uint128_t::operator uint64_t() const
{
    return (uint64_t)LOWER;
}

al_uint128_t al_uint128_t::operator&(const al_uint128_t &rhs) const
{
    return al_uint128_t(UPPER & rhs.UPPER, LOWER & rhs.LOWER);
}

al_uint128_t &al_uint128_t::operator&=(const al_uint128_t &rhs)
{
    UPPER &= rhs.UPPER;
    LOWER &= rhs.LOWER;
    return *this;
}

al_uint128_t al_uint128_t::operator|(const al_uint128_t &rhs) const
{
    return al_uint128_t(UPPER | rhs.UPPER, LOWER | rhs.LOWER);
}

al_uint128_t &al_uint128_t::operator|=(const al_uint128_t &rhs)
{
    UPPER |= rhs.UPPER;
    LOWER |= rhs.LOWER;
    return *this;
}

al_uint128_t al_uint128_t::operator^(const al_uint128_t &rhs) const
{
    return al_uint128_t(UPPER ^ rhs.UPPER, LOWER ^ rhs.LOWER);
}

al_uint128_t &al_uint128_t::operator^=(const al_uint128_t &rhs)
{
    UPPER ^= rhs.UPPER;
    LOWER ^= rhs.LOWER;
    return *this;
}

al_uint128_t al_uint128_t::operator~() const
{
    return al_uint128_t(~UPPER, ~LOWER);
}

al_uint128_t al_uint128_t::operator<<(const al_uint128_t &rhs) const
{
    const uint64_t shift = rhs.LOWER;
    if (((bool)rhs.UPPER) || (shift >= 128))
    {
        return al_uint128_0;
    }
    else if (shift == 64)
    {
        return al_uint128_t(LOWER, 0);
    }
    else if (shift == 0)
    {
        return *this;
    }
    else if (shift < 64)
    {
        return al_uint128_t((UPPER << shift) + (LOWER >> (64 - shift)), LOWER << shift);
    }
    else if ((128 > shift) && (shift > 64))
    {
        return al_uint128_t(LOWER << (shift - 64), 0);
    }
    else
    {
        return al_uint128_0;
    }
}

al_uint128_t &al_uint128_t::operator<<=(const al_uint128_t &rhs)
{
    *this = *this << rhs;
    return *this;
}

al_uint128_t al_uint128_t::operator>>(const al_uint128_t &rhs) const
{
    const uint64_t shift = rhs.LOWER;
    if (((bool)rhs.UPPER) || (shift >= 128))
    {
        return al_uint128_0;
    }
    else if (shift == 64)
    {
        return al_uint128_t(0, UPPER);
    }
    else if (shift == 0)
    {
        return *this;
    }
    else if (shift < 64)
    {
        return al_uint128_t(UPPER >> shift, (UPPER << (64 - shift)) + (LOWER >> shift));
    }
    else if ((128 > shift) && (shift > 64))
    {
        return al_uint128_t(0, (UPPER >> (shift - 64)));
    }
    else
    {
        return al_uint128_0;
    }
}

al_uint128_t &al_uint128_t::operator>>=(const al_uint128_t &rhs)
{
    *this = *this >> rhs;
    return *this;
}

bool al_uint128_t::operator!() const
{
    return !(bool)(UPPER | LOWER);
}

bool al_uint128_t::operator&&(const al_uint128_t &rhs) const
{
    return ((bool)*this && rhs);
}

bool al_uint128_t::operator||(const al_uint128_t &rhs) const
{
    return ((bool)*this || rhs);
}

bool al_uint128_t::operator==(const al_uint128_t &rhs) const
{
    return ((UPPER == rhs.UPPER) && (LOWER == rhs.LOWER));
}

bool al_uint128_t::operator!=(const al_uint128_t &rhs) const
{
    return ((UPPER != rhs.UPPER) | (LOWER != rhs.LOWER));
}

bool al_uint128_t::operator>(const al_uint128_t &rhs) const
{
    if (UPPER == rhs.UPPER)
    {
        return (LOWER > rhs.LOWER);
    }
    return (UPPER > rhs.UPPER);
}

bool al_uint128_t::operator<(const al_uint128_t &rhs) const
{
    if (UPPER == rhs.UPPER)
    {
        return (LOWER < rhs.LOWER);
    }
    return (UPPER < rhs.UPPER);
}

bool al_uint128_t::operator>=(const al_uint128_t &rhs) const
{
    return ((*this > rhs) | (*this == rhs));
}

bool al_uint128_t::operator<=(const al_uint128_t &rhs) const
{
    return ((*this < rhs) | (*this == rhs));
}

al_uint128_t al_uint128_t::operator+(const al_uint128_t &rhs) const
{
    return al_uint128_t(UPPER + rhs.UPPER + ((LOWER + rhs.LOWER) < LOWER), LOWER + rhs.LOWER);
}

al_uint128_t &al_uint128_t::operator+=(const al_uint128_t &rhs)
{
    UPPER += rhs.UPPER + ((LOWER + rhs.LOWER) < LOWER);
    LOWER += rhs.LOWER;
    return *this;
}

al_uint128_t al_uint128_t::operator-(const al_uint128_t &rhs) const
{
    return al_uint128_t(UPPER - rhs.UPPER - ((LOWER - rhs.LOWER) > LOWER), LOWER - rhs.LOWER);
}

al_uint128_t &al_uint128_t::operator-=(const al_uint128_t &rhs)
{
    *this = *this - rhs;
    return *this;
}

al_uint128_t al_uint128_t::operator*(const al_uint128_t &rhs) const
{
    // split values into 4 32-bit parts
    uint64_t top[4] = {UPPER >> 32, UPPER & 0xffffffff, LOWER >> 32, LOWER & 0xffffffff};
    uint64_t bottom[4] = {rhs.UPPER >> 32, rhs.UPPER & 0xffffffff, rhs.LOWER >> 32, rhs.LOWER & 0xffffffff};
    uint64_t products[4][4];

    // multiply each component of the values
    for (int y = 3; y > -1; y--)
    {
        for (int x = 3; x > -1; x--)
        {
            products[3 - x][y] = top[x] * bottom[y];
        }
    }

    // first row
    uint64_t fourth32 = (products[0][3] & 0xffffffff);
    uint64_t third32 = (products[0][2] & 0xffffffff) + (products[0][3] >> 32);
    uint64_t second32 = (products[0][1] & 0xffffffff) + (products[0][2] >> 32);
    uint64_t first32 = (products[0][0] & 0xffffffff) + (products[0][1] >> 32);

    // second row
    third32 += (products[1][3] & 0xffffffff);
    second32 += (products[1][2] & 0xffffffff) + (products[1][3] >> 32);
    first32 += (products[1][1] & 0xffffffff) + (products[1][2] >> 32);

    // third row
    second32 += (products[2][3] & 0xffffffff);
    first32 += (products[2][2] & 0xffffffff) + (products[2][3] >> 32);

    // fourth row
    first32 += (products[3][3] & 0xffffffff);

    // move carry to next digit
    third32 += fourth32 >> 32;
    second32 += third32 >> 32;
    first32 += second32 >> 32;

    // remove carry from current digit
    fourth32 &= 0xffffffff;
    third32 &= 0xffffffff;
    second32 &= 0xffffffff;
    first32 &= 0xffffffff;

    // combine components
    return al_uint128_t((first32 << 32) | second32, (third32 << 32) | fourth32);
}

al_uint128_t &al_uint128_t::operator*=(const al_uint128_t &rhs)
{
    *this = *this * rhs;
    return *this;
}

std::pair<al_uint128_t, al_uint128_t> al_uint128_t::divmod(const al_uint128_t &lhs, const al_uint128_t &rhs) const
{
    // Save some calculations /////////////////////
    if (rhs == al_uint128_0)
    {
        throw std::domain_error("Error: division or modulus by 0");
    }
    else if (rhs == al_uint128_1)
    {
        return std::pair<al_uint128_t, al_uint128_t>(lhs, al_uint128_0);
    }
    else if (lhs == rhs)
    {
        return std::pair<al_uint128_t, al_uint128_t>(al_uint128_1, al_uint128_0);
    }
    else if ((lhs == al_uint128_0) || (lhs < rhs))
    {
        return std::pair<al_uint128_t, al_uint128_t>(al_uint128_0, lhs);
    }

    std::pair<al_uint128_t, al_uint128_t> qr(al_uint128_0, al_uint128_0);
    for (uint8_t x = lhs.bits(); x > 0; x--)
    {
        qr.first <<= al_uint128_1;
        qr.second <<= al_uint128_1;

        if ((lhs >> (x - 1U)) & 1)
        {
            qr.second++;
        }

        if (qr.second >= rhs)
        {
            qr.second -= rhs;
            qr.first++;
        }
    }
    return qr;
}

al_uint128_t al_uint128_t::operator/(const al_uint128_t &rhs) const
{
    return divmod(*this, rhs).first;
}

al_uint128_t &al_uint128_t::operator/=(const al_uint128_t &rhs)
{
    *this = *this / rhs;
    return *this;
}

al_uint128_t al_uint128_t::operator%(const al_uint128_t &rhs) const
{
    return divmod(*this, rhs).second;
}

al_uint128_t &al_uint128_t::operator%=(const al_uint128_t &rhs)
{
    *this = *this % rhs;
    return *this;
}

al_uint128_t &al_uint128_t::operator++()
{
    return *this += al_uint128_1;
}

al_uint128_t al_uint128_t::operator++(int)
{
    al_uint128_t temp(*this);
    ++*this;
    return temp;
}

al_uint128_t &al_uint128_t::operator--()
{
    return *this -= al_uint128_1;
}

al_uint128_t al_uint128_t::operator--(int)
{
    al_uint128_t temp(*this);
    --*this;
    return temp;
}

al_uint128_t al_uint128_t::operator+() const
{
    return *this;
}

al_uint128_t al_uint128_t::operator-() const
{
    return ~*this + al_uint128_1;
}

const uint64_t &al_uint128_t::upper() const
{
    return UPPER;
}

const uint64_t &al_uint128_t::lower() const
{
    return LOWER;
}

uint8_t al_uint128_t::bits() const
{
    uint8_t out = 0;
    if (UPPER)
    {
        out = 64;
        uint64_t up = UPPER;
        while (up)
        {
            up >>= 1;
            out++;
        }
    }
    else
    {
        uint64_t low = LOWER;
        while (low)
        {
            low >>= 1;
            out++;
        }
    }
    return out;
}

std::string al_uint128_t::str(uint8_t base, const unsigned int &len) const
{
    if ((base < 2) || (base > 16))
    {
        throw std::invalid_argument("Base must be in the range [2, 16]");
    }
    std::string out = "";
    if (!(*this))
    {
        out = "0";
    }
    else
    {
        std::pair<al_uint128_t, al_uint128_t> qr(*this, al_uint128_0);
        do
        {
            qr = divmod(qr.first, base);
            out = "0123456789abcdef"[(uint8_t)qr.second] + out;
        } while (qr.first);
    }
    if (out.size() < len)
    {
        out = std::string(len - out.size(), '0') + out;
    }
    return out;
}

al_uint128_t operator<<(const bool &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) << rhs;
}

al_uint128_t operator<<(const uint8_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) << rhs;
}

al_uint128_t operator<<(const uint16_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) << rhs;
}

al_uint128_t operator<<(const uint32_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) << rhs;
}

al_uint128_t operator<<(const uint64_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) << rhs;
}

al_uint128_t operator<<(const int8_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) << rhs;
}

al_uint128_t operator<<(const int16_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) << rhs;
}

al_uint128_t operator<<(const int32_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) << rhs;
}

al_uint128_t operator<<(const int64_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) << rhs;
}

al_uint128_t operator>>(const bool &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) >> rhs;
}

al_uint128_t operator>>(const uint8_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) >> rhs;
}

al_uint128_t operator>>(const uint16_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) >> rhs;
}

al_uint128_t operator>>(const uint32_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) >> rhs;
}

al_uint128_t operator>>(const uint64_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) >> rhs;
}

al_uint128_t operator>>(const int8_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) >> rhs;
}

al_uint128_t operator>>(const int16_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) >> rhs;
}

al_uint128_t operator>>(const int32_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) >> rhs;
}

al_uint128_t operator>>(const int64_t &lhs, const al_uint128_t &rhs)
{
    return al_uint128_t(lhs) >> rhs;
}

std::ostream &operator<<(std::ostream &stream, const al_uint128_t &rhs)
{
    if (stream.flags() & stream.oct)
    {
        stream << rhs.str(8);
    }
    else if (stream.flags() & stream.dec)
    {
        stream << rhs.str(10);
    }
    else if (stream.flags() & stream.hex)
    {
        stream << rhs.str(16);
    }
    return stream;
}
