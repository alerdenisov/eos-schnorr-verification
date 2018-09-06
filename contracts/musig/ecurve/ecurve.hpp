#ifndef ECURVE_H
#define ECURVE_H

#include "../bigint/al_uint256_t.h"

namespace EC
{
typedef al_uint256_t big;

struct G1Point
{
    big X;
    big Y;

    G1Point() : X(0), Y(0) {}
    G1Point(big x, big y) : X(x), Y(y) {}
};

struct G2Point : G1Point
{
    big Z;
    G2Point() : G1Point(), Z(0) {}
    G2Point(big x, big y, big z) : G1Point(x, y), Z(z) {}
};

big mulmod(const big &a, const big &b, const big &module)
{
    return (a * b) % module;
}

big addmod(const big &a, const big &b, const big &module)
{
    return (a + b) % module;
}
class ECurve
{
  private:
    // function _jAdd(
    //     uint256 x1, uint256 z1,
    //     uint256 x2, uint256 z2)
    //     public
    //     pure
    //     returns(uint256 x3, uint256 z3)
    // {
    //     (x3, z3) = (
    //         addmod(
    //             mulmod(z2, x1, n),
    //             mulmod(x2, z1, n),
    //             n
    //         ),
    //         mulmod(z1, z2, n)
    //     );
    // }
    G1Point _jAdd(G1Point a, G1Point b) const
    {
        return G1Point(
            addmod(
                mulmod(b.Y, a.X, n),
                mulmod(b.X, a.Y, n),
                n),
            mulmod(a.Y, b.Y, n));
    }

    G1Point _jMul(G1Point a, G1Point b) const
    {
        // (x3, z3) = (
        //     mulmod(x1, x2, n),
        //     mulmod(z1, z2, n)
        // );
        return G1Point(
            mulmod(a.X, b.X, n),
            mulmod(a.Y, b.Y, n));
    }

    G1Point _jSub(G1Point a, G1Point b) const
    {
        // (x3, z3) = (
        //     addmod(
        //         mulmod(z2, x1, n),
        //         mulmod(n - x2, z1, n),
        //         n
        //     ),
        //     mulmod(z1, z2, n)
        // );
        return G1Point(
            addmod(
                mulmod(b.Y, a.X, n),
                mulmod(n - b.X, a.Y, n),
                n),
            mulmod(a.X, b.X, n));
    }

    G1Point _jDiv(G1Point a, G1Point b) const
    {
        // (x3, z3) = (
        //     mulmod(x1, z2, n),
        //     mulmod(z1, x2, n)
        // );
        return G1Point(
            mulmod(a.X, b.Y, n),
            mulmod(a.Y, b.X, n));
    }

    // function _ecAdd(
    //     uint256 x1, uint256 y1, uint256 z1,
    //     uint256 x2, uint256 y2, uint256 z2)
    //     public
    //     pure
    //     returns(uint256 x3, uint256 y3, uint256 z3)
    // {
    // }
    G2Point _ecadd(G2Point lhs, G2Point rhs) const
    {
        // uint256 lx;
        // uint256 lz;
        // uint256 da;
        // uint256 db;
        G1Point l;
        G1Point d;
        G1Point s;

        big rx;
        big ry;
        big rz;

        // if (x1 == 0 && y1 == 0) {
        //     return (x2, y2, z2);
        // }
        if (lhs.X == 0 && lhs.Y == 0)
        {
            return G2Point(rhs.X, rhs.Y, rhs.Z);
        }

        // if (x2 == 0 && y2 == 0) {
        //     return (x1, y1, z1);
        // }
        if (rhs.X == 0 && rhs.Y == 0)
        {
            return G2Point(lhs.X, lhs.Y, lhs.Z);
        }

        // if (x1 == x2 && y1 == y2) {
        //     (lx, lz) = _jMul(x1, z1, x1, z1);
        //     (lx, lz) = _jMul(lx, lz, 3, 1);
        //     (lx, lz) = _jAdd(lx, lz, a, 1);

        //     (da,db) = _jMul(y1, z1, 2, 1);
        // } else {
        //     (lx, lz) = _jSub(y2, z2, y1, z1);
        //     (da, db) = _jSub(x2, z2, x1, z1);
        // }
        if (lhs.X == rhs.X && lhs.Y == rhs.Y)
        {
            l = _jMul(G1Point(lhs.X, lhs.Z), G1Point(lhs.X, lhs.Z));
            l = _jMul(G1Point(l.X, l.Y), G1Point(3, 1));
            l = _jAdd(G1Point(l.X, l.Y), G1Point(a, 1));

            d = _jMul(G1Point(lhs.Y, lhs.Z), G1Point(2, 1));
        }
        else
        {
            l = _jSub(G1Point(rhs.Y, rhs.Z), G1Point(lhs.Y, lhs.Z));
            d = _jSub(G1Point(rhs.X, rhs.Z), G1Point(lhs.X, lhs.Z));
        }

        // (lx, lz) = _jDiv(lx, lz, da, db);
        l = _jDiv(l, d);

        // (x3, da) = _jMul(lx, lz, lx, lz);
        s = _jMul(l, l);
        rx = s.X;
        d.X = s.Y;

        // (x3, da) = _jSub(x3, da, x1, z1);
        s = _jSub(G1Point(rx, d.X), G1Point(lhs.X, lhs.Z));
        rx = s.X;
        d.X = s.Y;

        // (x3, da) = _jSub(x3, da, x2, z2);
        s = _jSub(G1Point(rx, d.X), G1Point(rhs.X, rhs.Z));
        rx = s.X;
        d.X = s.Y;

        // (y3, db) = _jSub(x1, z1, x3, da);
        s = _jSub(G1Point(lhs.X, lhs.Z), G1Point(rx, d.X));
        ry = s.X;
        d.Y = s.Y;
        // (y3, db) = _jMul(y3, db, lx, lz);
        s = _jMul(G1Point(ry, d.Y), l);
        ry = s.X;
        d.Y = s.Y;
        // (y3, db) = _jSub(y3, db, y1, z1);
        s = _jMul(G1Point(ry, d.Y), G1Point(lhs.Y, lhs.Z));
        ry = s.X;
        d.Y = s.Y;

        // if (da != db) {
        if (d.X != d.Y)
        {
            // x3 = mulmod(x3, db, n);
            // y3 = mulmod(y3, da, n);
            // z3 = mulmod(da, db, n);
            rx = mulmod(rx, d.Y, n);
            ry = mulmod(ry, d.X, n);
            rz = mulmod(d.X, d.Y, n);
        }
        // } else {
        else
        {
            // z3 = da;
            rz = d.X;
        }

        return G2Point(rx, ry, rz);
    }

    // function _inverse(uint256 val) public pure
    //     returns(uint256 invVal)
    // {
    //     uint256 t = 0;
    //     uint256 newT = 1;
    //     uint256 r = n;
    //     uint256 newR = val;
    //     uint256 q;
    //     while (newR != 0) {
    //         q = r / newR;

    //         (t, newT) = (newT, addmod(t, (n - mulmod(q, newT, n)), n));
    //         (r, newR) = (newR, r - q * newR );
    //     }

    //     return t;
    // }

    big _inverse(big s) const
    {
        big t = big(0);
        big newT = big(1);
        big r = big(n);
        big newR = big(s);

        big tmpT;
        big tmpR;
        big q;

        while (newR != 0)
        {
            q = r / newR;

            tmpT = big(newT);
            newT = addmod(t, (n - mulmod(q, newT, n)), n);
            t = big(tmpT);

            tmpR = big(newR);
            newR = r - q * newR;
            r = tmpR;
        }

        return t;
    }

    // function _ecMul(uint256 d, uint256 x1, uint256 y1, uint256 z1) public pure
    //     returns(uint256 x3, uint256 y3, uint256 z3)
    // {
    //     uint256 remaining = d;
    //     uint256 px = x1;
    //     uint256 py = y1;
    //     uint256 pz = z1;
    //     uint256 acx = 0;
    //     uint256 acy = 0;
    //     uint256 acz = 1;

    //     if (d == 0) {
    //         return (0, 0, 1);
    //     }

    //     while (remaining != 0) {
    //         if ((remaining & 1) != 0) {
    //             (acx,acy,acz) = _ecAdd(acx, acy, acz, px, py, pz);
    //         }
    //         remaining = remaining / 2;
    //         (px, py, pz) = _ecDouble(px, py, pz);
    //     }

    //     (x3, y3, z3) = (acx, acy, acz);
    // }

    G2Point _ecdouble(G2Point p) const
    {
        return _ecadd(p, p);
    }

    G2Point _ecmul(big d, G2Point p) const
    {
        big remaining = big(d);
        G2Point tmp = G2Point(p);
        // big acx = al_uint256_0;
        // big acy = al_uint256_0;
        // big acz = al_uint256_0;

        G2Point ac = G2Point(0, 0, 1);

        if (d == 0)
        {
            return G2Point(0, 0, 1);
        }

        while (remaining != 0)
        {
            if ((remaining & 1) != 0)
            {
                ac = _ecadd(ac, tmp);
            }

            remaining = remaining / 2;
            tmp = _ecdouble(tmp);
        }

        return ac;
    }

  public:
    const G1Point &g;
    const big &n;
    const big &a;
    const big &b;
    // 21888242871839275222246405745257275088696311157297823662689037894645226208583
    // uint256 constant public gx = 0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798;
    // uint256 constant public gy = 0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8;
    // uint256 constant public n = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F;
    // uint256 constant public a = 0;
    // uint256 constant public b = 7;
    ECurve(
        const G1Point &g,
        const big &n,
        const big &a,
        const big &b) : g(g), n(n), a(a), b(b) {}

    G1Point ecmul(
        const G1Point p,
        const big s) const
    {
        // uint256 z;
        // (x2, y2, z) = _ecMul(scalar, x1, y1, 1);
        // z = _inverse(z);
        // x2 = mulmod(x2, z, n);
        // y2 = mulmod(y2, z, n);

        G2Point m = _ecmul(s, G2Point(p.X, p.Y, 1));
        // TODO: Inverse Z part
        auto z = big(m.Z); // _inverse(m.Z);
        return G1Point(
            mulmod(m.X, z, n),
            mulmod(m.Y, z, n));
    }

    G1Point ecadd(
        const G1Point lhs,
        const G1Point rhs) const
    {
        // uint256 z;
        // (x3, y3, z) = _ecAdd(x1, y1, 1, x2, y2, 1);
        // z = _inverse(z);
        // x3 = mulmod(x3, z, n);
        // y3 = mulmod(y3, z, n);
        G2Point r = _ecadd(G2Point(lhs.X, lhs.Y, 1), G2Point(rhs.X, rhs.Y, 1));
        auto rz = big(r.Z);
        // auto rz = _inverse(r.Z);
        return G1Point(
            mulmod(r.X, rz, n),
            mulmod(r.Y, rz, n));
    }
};
} // namespace EC
#endif