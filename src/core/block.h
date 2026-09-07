#pragma once
#include "crypto/crypto.h"
#include "vector"

inline constexpr std::size_t kHeaderSize = 88;

struct BlockHeader {
    AeCrypto::Hash256 prev_hash;   // 32
    AeCrypto::Hash256 merkle_root; // 32
    std::uint32_t version{1};      // 4
    std::uint32_t bits{0};         // 4
    std::uint64_t timestamp{0};    // 8
    std::uint64_t nonce{0};        // 8

    [[nodiscard]] std::array<std::byte, kHeaderSize> serialize() const;
    [[nodiscard]] AeCrypto::Hash256 hash() const;
};

struct Block {
    BlockHeader header;
    std::vector<std::string> body;
};