// #include "./ecurve.hpp";

// namespace EC
// {
// al_uint256_t ECurve::submod(al_uint256_t a, al_uint256_t b) const
// {
//   al_uint256_t a_nn;

//   if (a > b)
//   {
//     a_nn = a;
//   }
//   else
//   {
//     a_nn = a + GEN_ORDER;
//   }

//   return ECurve::addmod(a_nn - b, 0, GEN_ORDER);
// }

// al_uint256_t ECurve::addmod(al_uint256_t a, al_uint256_t b, al_uint256_t module) const
// {
//   eosio_assert(module != 0, "Zero devision isn't allowed");
//   return (a + b) % module;
// }

// function expMod(uint256 _base, uint256 _exponent, uint256 _modulus)
//         internal constant returns (uint256 retval)
//     {
//         bool success;
//         uint256[1] memory output;
//         uint[6] memory input;
//         input[0] = 0x20;        // baseLen = new(big.Int).SetBytes(getData(input, 0, 32))
//         input[1] = 0x20;        // expLen  = new(big.Int).SetBytes(getData(input, 32, 32))
//         input[2] = 0x20;        // modLen  = new(big.Int).SetBytes(getData(input, 64, 32))
//         input[3] = _base;
//         input[4] = _exponent;
//         input[5] = _modulus;
//         assembly {
//             success := staticcall(sub(gas, 2000), 5, input, 0xc0, output, 0x20)
//             // Use "invalid" to make gas estimation work
//             switch success case 0 { invalid }
//         }
//         require(success);
//         return output[0];
//     }

// } // namespace EC