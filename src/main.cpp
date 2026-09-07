#include "core/block.h"
#include "core/blockchain.h"
#include "crypto/crypto.h"

#include <cstddef>
#include <iomanip>
#include <iostream>

int main() {
    Blockchain chain{};

    for (size_t i = 0; i < 100; i++) {
        chain.add_block({"e"});
    }

    chain.print();

    // tests();
}
