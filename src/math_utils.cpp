using namespace std;
using u64 = unsigned long long;
#include <bits/stdc++.h>

// ---------- Função gcd manual ----------
long long gcd_manual(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// ---------- Multiplicação modular segura ----------
u64 mul_mod(u64 a, u64 b, u64 mod) {
    u64 res = 0;
    a %= mod;
    while (b > 0) {
        if (b & 1)
            res = (res + a) % mod;
        a = (a * 2) % mod;
        b >>= 1;
    }
    return res;
}

u64 pow_mod(u64 base, u64 exp, u64 mod) {
    u64 res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            res = mul_mod(res, base, mod);
        base = mul_mod(base, base, mod);
        exp >>= 1;
    }
    return res;
}

// ---------- Algoritmo de Euclides Estendido ----------
long long egcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

long long modinv(long long a, long long m) {
    long long x, y;
    long long g = egcd(a, m, x, y);
    if (g != 1) return -1;
    x %= m;
    if (x < 0) x += m;
    return x;
}

// ---------- Checagem simples de primalidade ----------
bool is_prime(u64 n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (u64 i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;
    return true;
}

// ---------- Gera um primo pequeno aleatório ----------
u64 random_prime() {
    static mt19937_64 rng(time(nullptr));
    while (true) {
        u64 x = rng() % 200 + 50; // entre 50 e 249
        if (is_prime(x)) return x;
    }
}