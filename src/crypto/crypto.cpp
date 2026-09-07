#include "crypto/crypto.h"
#include <memory>
#include <openssl/evp.h>
#include <stdexcept>

namespace {
constexpr char kDigits[] = "0123456789abcdef";
struct EvpCtxDeleter {
    void operator()(EVP_MD_CTX *ctx) const noexcept { EVP_MD_CTX_free(ctx); }
};
} // namespace

// Open SSL C library usage to hash
namespace AeCrypto {

Hash256 sha256(std::span<const std::byte> data) {
    // Unique pointer to automatically de-allocate memory of the context
    std::unique_ptr<EVP_MD_CTX, EvpCtxDeleter> ctx{EVP_MD_CTX_new()};
    // Initialize digest with default eng
    int err = EVP_DigestInit_ex(ctx.get(), EVP_sha256(), nullptr);

    if (err == 0) {
        throw std::runtime_error("SHA256: setup err");
    }

    // Pass the data
    err = EVP_DigestUpdate(ctx.get(), data.data(), data.size());
    if (err == 0) {
        throw std::runtime_error("SHA256: Digest update err");
    }

    Hash256 out{};
    unsigned int len = 0;
    // Hash
    err = EVP_DigestFinal_ex(ctx.get(), out.data(), &len);
    if (err == 0) {
        throw std::runtime_error("SHA256: Hashing final err");
    }

    return out;
}

// Double hash SHA256 some bytes
// TODO Initialize only one time the evp
Hash256 sha256d(std::span<const std::byte> data) {
    Hash256 h = sha256(data);
    return sha256(std::as_bytes(std::span{h}));
}

Hash256 sha256(std::string_view text) {
    return sha256(std::as_bytes(std::span{text.data(), text.size()}));
}

std::string to_hex(const Hash256 &hs) {
    std::string s;
    // 1 byte = 2 chars so reserve twice the size of the array
    s.reserve(hs.size() * 2);
    for (std::uint8_t byte : hs) {
        // Shift the 2 sets of 4 bits to the right and keep only what left
        // gives the first hexa char
        s += kDigits[byte >> 4];

        // Keep only what left in the lower 4 bits
        // gives the second hexa char
        s += kDigits[byte & 0x0F]; // then low
    }
    return s;
}

} // namespace AeCrypto