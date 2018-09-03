#ifndef ECURVE_H
#define ECURVE_H

#include "../bigint/al_uint256_t.h"

namespace EC
{
// 0x30644e72e131a029b85045b68181585d97816a916871ca8d3c208c16d87cfd47
const al_uint256_t FIELD_ORDER = al_uint256_t(
    (uint64_t)0x30644e72e131a029ULL,
    (uint64_t)0xb85045b68181585dULL,
    (uint64_t)0x97816a916871ca8dULL,
    (uint64_t)0x3c208c16d87cfd47ULL);

// 0x30644e72e131a029b85045b68181585d2833e84879b9709143e1f593f0000001
const al_uint256_t GEN_ORDER = al_uint256_t(
    (uint64_t)0x30644e72e131a029ULL,
    (uint64_t)0xb85045b68181585dULL,
    (uint64_t)0x2833e84879b97091ULL,
    (uint64_t)0x43e1f593f0000001ULL);

const al_uint256_t CURVE_B = al_uint256_t(
    (uint64_t)0x0,
    (uint64_t)0x0,
    (uint64_t)0x0,
    (uint64_t)0x3);

// 0xc19139cb84c680a6e14116da060561765e05aa45a1c72a34f082305b61f3f52
const al_uint256_t CURVE_A = al_uint256_t(
    (uint64_t)0xc19139cb84c680a,
    (uint64_t)0x6e14116da0605617,
    (uint64_t)0x65e05aa45a1c72a3,
    (uint64_t)0x4f082305b61f3f52);

class ECurve
{
private:
public:
  // 21888242871839275222246405745257275088696311157297823662689037894645226208583
  ECurve() {}
};
} // namespace EC
#endif