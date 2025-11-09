#include "hash_utils.hpp"


// hash simplificado
u64 simple_hash(const string &msg) {
    u64 h = 5381;
    for (char c : msg) {
        h = ((h << 5) + h) + (unsigned char)c;  // h = h*33 + c
        h ^= (h >> 7);
    }
    return h;
}
