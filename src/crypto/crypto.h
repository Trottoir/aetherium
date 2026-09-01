#pragma once
#include <array>
#include <string>

// Hash , 256 bits = 32 octets
using Hash256 = std::array<std::uint8_t, 32>;

namespace AeCrypto {

/*
Hashes a char to its Sha256 byte array
*/
[[nodiscard]] Hash256 sha256(char ch);
/*
Print a Sha256 hash
*/
void printHash256(Hash256 hs);
} // namespace AeCrypto
