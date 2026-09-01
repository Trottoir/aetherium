#include "crypto/crypto.h"

#include <iostream>
#include <openssl/evp.h>

// Open SSL C library usage to hash
namespace AeCrypto {

Hash256 sha256(char ch) {
    // Allocate memory to the calcul
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    // Initialize le digest, default engine
    EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);

    // Pass the data
    EVP_DigestUpdate(ctx, &ch, 1);

    Hash256 out{};
    unsigned int len = 0;
    EVP_DigestFinal_ex(ctx, out.data(), &len);

    // Free the memory used during the computation
    EVP_MD_CTX_free(ctx);

    return out;
}

void printHash256(Hash256 hs) {
    for (std::uint8_t byte : hs) {
        printf("%02x", byte);
    }
    printf("\n");
}

} // namespace AeCrypto