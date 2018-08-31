/** 
 * This source adapted from https://mattmccutchen.net/bigint/ by Mithrilcoin.io for EOS.IO smart contract.
 */
#include "BigIntegerUtils.hpp"
#include "BigUnsignedInABase.hpp"

std::string bigUnsignedToString(const BigUnsigned &x)
{
	return std::string(BigUnsignedInABase(x, BigUnsignedInABase::Base(10)));
}

std::string bigIntegerToString(const BigInteger &x)
{
	return (x.getSign() == BigInteger::negative)
						 ? (std::string("-") + bigUnsignedToString(x.getMagnitude()))
						 : (bigUnsignedToString(x.getMagnitude()));
}

BigUnsigned stringToBigUnsigned(const std::string &s)
{
	return BigUnsigned(BigUnsignedInABase(s, BigUnsignedInABase::Base(10)));
}

class ext_string : public std::string
{
public:
	ext_string(const std::string &cstr) : std::string(cstr) {}

	const std::string substr(size_t offset, size_t substr_size, bool copy)
	{
		return (const std::string)(std::string::substr(offset, substr_size));
	}
};

BigInteger stringToBigInteger(const std::string &s)
{
	// Recognize a sign followed by a BigUnsigned.
	const char signChar = s.c_str()[0];
	ext_string childStr(s);

	return (signChar == '-') ? BigInteger(stringToBigUnsigned(childStr.substr(1, s.size() - 2, false)), BigInteger::negative)
													 : (signChar == '+') ? BigInteger(stringToBigUnsigned(childStr.substr(1, s.size() - 2, false)))
																							 : BigInteger(stringToBigUnsigned(s));
}

// commented by swapnibble
/*
eosio::ostream &operator <<(eosio::ostream &os, const BigUnsigned &x) {
	BigUnsignedInABase::Base base;
	long osFlags = os.flags();
	if (osFlags & os.dec)
		base = 10;
	else if (osFlags & os.hex) {
		base = 16;
		if (osFlags & os.showbase)
			os << "0x";
	} else if (osFlags & os.oct) {
		base = 8;
		if (osFlags & os.showbase)
			os << '0';
	} else {
		throw "eosio::ostream << BigUnsigned: Could not determine the desired base from output-stream flags";
	}
	std::string s = std::string(BigUnsignedInABase(x, base));
	os << s;
	return os;
}

eosio::ostream &operator <<(eosio::ostream &os, const BigInteger &x) {
	if (x.getSign() == BigInteger::negative)
		os << '-';
	os << x.getMagnitude();
	return os;
}
*/