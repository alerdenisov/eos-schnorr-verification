#include <eosiolib/eosio.hpp>
#include "./bigint/BigIntegerLibrary.hpp"

using namespace eosio;

class musig : public eosio::contract
{
public:
  using contract::contract;

  // @abi action
  void exec()
  {
    BigInteger a = 65536;
    print("Too much: ", (a * a * a * a * a * a));
  }
};

EOSIO_ABI(musig, (exec))