#include "rsa.hpp"

bool RSA::init(u64 p_, u64 q_, u64 e_) {
    if (!is_prime(p_) || !is_prime(q_) || p_ == q_) return false;
    p = p_; q = q_;
    n = p * q;
    phi = (p - 1) * (q - 1);
    e = e_;
    if (gcd_manual((long long)e, (long long)phi) != 1) return false;
    long long dinv = modinv((long long)e, (long long)phi);
    if (dinv < 0) return false;
    d = (u64)dinv;
    return true;
}

void RSA::generate_auto() {
    do {
        p = random_prime();
        q = random_prime();
    } while (p == q);
    phi = (p - 1) * (q - 1);
    e = 31;
    long long dinv = modinv((long long)e, (long long)phi);
    if (dinv < 0) dinv += phi;
    d = (u64)dinv;
    n = p * q;
}

u64 RSA::sign(u64 hash_value) const {
    return pow_mod(hash_value % n, d, n);
}

bool RSA::verify(u64 hash_value, u64 signature) const {
    return pow_mod(signature, e, n) == (hash_value % n);
}
