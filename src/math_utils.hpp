#pragma once
#include <bits/stdc++.h>
using namespace std;
using u64 = unsigned long long;

long long gcd_manual(long long a, long long b);
u64 mul_mod(u64 a, u64 b, u64 mod);
u64 pow_mod(u64 base, u64 exp, u64 mod);
long long egcd(long long a, long long b, long long &x, long long &y);
long long modinv(long long a, long long m);
bool is_prime(u64 n);
u64 random_prime();
