#include "crypto/crypto.h"
#include <iostream>

int main() {
    Hash256 hash = AeCrypto::sha256('e');

    AeCrypto::printHash256(hash);
}