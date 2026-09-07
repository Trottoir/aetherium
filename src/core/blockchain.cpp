#include "core/blockchain.h"
#include <iostream>

Block const &Blockchain::get_block(std::size_t id) const {
    if (blocks.size() <= id) {
        throw std::runtime_error("get_block: ID not in the chain yet");
    }
    return blocks[id];
}

void Blockchain::add_block(std::vector<std::string> bdy) {
    // Hash the previous serialized block
    Block b{.header =
                BlockHeader{
                    .prev_hash = blocks.back().header.hash(),
                    .merkle_root = {},
                    .version = 1,
                    .bits = 1,
                    .timestamp = timestamp_now(),
                    .nonce = 1,
                },
            // Use ::move to remove the allocate memory
            .body = std::move(bdy)};
    blocks.push_back(std::move(b));
}

void Blockchain::print() const {
    size_t c = 0;
    for (const Block &b : blocks) {
        std::cout << c << "-" << AeCrypto::to_hex(b.header.prev_hash) << "\n";
        c++;
    }
}
std::uint64_t Blockchain::timestamp_now() {
    return std::chrono::duration_cast<std::chrono::seconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}
