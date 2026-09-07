#include "core/block.h"
#include <cassert>
#include <chrono>
#include <cstddef>
#include <vector>
namespace {

/* Serialize a native variable in bytes and append
    @param out& Array of byte where the header is serialized
    @param pos Position where the bytes starts to be appended
    @param value Variable to serialize
    @return Position where the next object will start to be appended
*/
template <typename T>
std::size_t put_le(std::array<std::byte, kHeaderSize> &out, std::size_t pos,
                   T value) {
    // Array overflow
    assert(pos + sizeof(T) <= out.size());
    for (std::size_t i = 0; i < sizeof(T); ++i) {
        // on each iteration, shift by 8 so 1 byte
        out[pos + i] = static_cast<std::byte>((value >> (8 * i)) & 0xFF);
    }
    return pos + sizeof(T);
}

/* Serialize an hash already in bytes
    @param out& Array of byte where the header is serialized
    @param pos  Position where the bytes starts to be appended
    @param b    Hash to serialize
    @return Position where the next object will start to be appended
*/
std::size_t put_bytes(std::array<std::byte, kHeaderSize> &out, std::size_t pos,
                      const AeCrypto::Hash256 &b) {
    // Array overflow
    assert(pos + b.size() <= out.size());
    for (size_t i = 0; i < b.size(); i++) {
        out[i + pos] = (static_cast<std::byte>(b[i]));
    }
    return pos + b.size();
}

} // namespace

/* Serialize a BlockHeader in an array of bytes
    @return The BlockHeader fully serialized
*/
std::array<std::byte, kHeaderSize> BlockHeader::serialize() const {
    std::array<std::byte, kHeaderSize> o = {};
    std::size_t pos = 0;
    pos = put_le(o, pos, version);
    pos = put_bytes(o, pos, prev_hash);
    pos = put_bytes(o, pos, merkle_root);
    pos = put_le(o, pos, bits);
    pos = put_le(o, pos, timestamp);
    pos = put_le(o, pos, nonce);

    // All 88 slots must have been iterated
    assert(pos == kHeaderSize);
    return o;
}

// Double hash the serialized BlockHeader
AeCrypto::Hash256 BlockHeader::hash() const {
    return AeCrypto::sha256d(serialize());
}
