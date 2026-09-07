#pragma once
#include <array>
#include <cstddef>
#include <span>
#include <string>

namespace AeCrypto {
// Hash , 256 bits = 32 octets
using Hash256 = std::array<std::uint8_t, 32>;

/*
SHA256 hash some bytes
    @param data bytes to hash
*/
[[nodiscard]] Hash256 sha256(std::span<const std::byte> data);

/*
Double SHA256 hash some bytes
    @param data bytes to double hash
*/
[[nodiscard]] Hash256 sha256d(std::span<const std::byte> data);

/*
SA256 hash a string
    @param text text to hash
*/
[[nodiscard]] Hash256 sha256(std::string_view text);

/*
Optimized convert of a SHA256 hash to a string
    @param hs Hash to convert in ex

*/
[[nodiscard]] std::string to_hex(const Hash256 &hs);
} // namespace AeCrypto
