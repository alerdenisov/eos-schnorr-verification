#include <eosiolib/eosio.hpp>
#include <eosiolib/system.h>
// #include "./ecurve/ecurve.hpp"
#include <eosiolib/crypto.h>
#include <secp256k1.h>

using namespace eosio;

class musig : public eosio::contract
{
public:
  using contract::contract;

  // @abi action
  void exec(checksum256 hash, signature sig)
  {
    // auto ctx = secp256k1_context_create(SECP256K1_CONTEXT_VERIFY | SECP256K1_CONTEXT_RANGEPROOF);
    // SECP256K1_WARN_UNUSED_RESULT int secp256k1_point_multiply(
    //   unsigned char *point,
    //   int *pointlen,
    //   const unsigned char *scalar
    // ) SECP256K1_ARG_NONNULL(1) SECP256K1_ARG_NONNULL(2) SECP256K1_ARG_NONNULL(3);
    unsigned char *point = (unsigned char *)malloc(sizeof(char) * 65);
    unsigned char *scalar = (unsigned char *)malloc(sizeof(char) * 32);
    int l = 65;
    secp256k1_point_multiply(point, &l, scalar);

    // public_key pk;
    // recover_key(&hash, (const char *)&sig, sizeof(sig), pk.data, sizeof(pk));
    // auto n = EC::big((uint64_t)0x30644e72e131a029ULL,
    //                  (uint64_t)0xb85045b68181585dULL,
    //                  (uint64_t)0x2833e84879b97091ULL,
    //                  (uint64_t)0x43e1f593f0000001ULL);
    // auto g = EC::G1Point(EC::big(1) % n, EC::big(2) % n);
    // auto a = EC::big(0);
    // auto b = EC::big(3);
    // auto curve = EC::ECurve(g, n, a, b);
    // // //
    // // // auto p = curve.ecmul(curve.g, EC::big(
    // // //                                   (uint64_t)0xcba5c4709e7f493ULL,
    // // //                                   (uint64_t)0x2a51b26d21254780ULL,
    // // //                                   (uint64_t)0x94e1bd7260c03c20ULL,
    // // //                                   (uint64_t)0xf6dac9385ce744d0ULL));
    // auto p = curve.ecadd(curve.g, curve.g);
    // eosio::print("PUBKEY :\n");
    // eosio::print("\nuu: ", p.X.upper().upper());
    // eosio::print("\nul: ", p.X.upper().lower());
    // eosio::print("\nlu: ", p.X.lower().upper());
    // eosio::print("\nll: ", p.X.lower().lower());

    // uint64_t foo = 1ULL;
    // printhex((void *)&foo, 8);
    // printhex((void *)&EC::GEN_ORDER.upper().lower(), 8);
    // printhex((void *)&EC::GEN_ORDER.lower().upper(), 8);
    // printhex((void *)&EC::GEN_ORDER.lower().lower(), 8);
    // eosio::print("\nll: ", EC::GEN_ORDER.lower().lower());
    // eosio::print("\nGEN ORDER: \n");
  }
};

EOSIO_ABI(musig, (exec))