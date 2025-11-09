#pragma once
#include "math_utils.hpp"

struct RSA {
    u64 p, q, n, phi, e, d;

    bool init(u64 p_, u64 q_, u64 e_);
    void generate_auto();
    u64 sign(u64 hash_value) const;
    bool verify(u64 hash_value, u64 signature) const;
};
