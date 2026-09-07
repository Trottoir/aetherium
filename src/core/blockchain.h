#pragma once
#include "core/block.h"

class Blockchain {

  public:
    Blockchain() {
        // Genesis block creation
        Block genesis = Block{
            .header = BlockHeader{.timestamp = Blockchain::timestamp_now()},
            .body = {""}};
        blocks.push_back(genesis);
    }

    /* Retrieve a block by reference with its ID
        @param id ID of the block to retrieve
    */
    [[nodiscard]] const Block &get_block(std::size_t id) const;

    /* Add a block into the chain
        @param b Body of the Block to write
    */
    void add_block(std::vector<std::string> b);

    /* Prints all the blocks of the chain
      @param b Body of the Block to write
    */
    void print() const;

    // Get the current timestamp rounded in second
    [[nodiscard]] static std::uint64_t timestamp_now();

  private:
    // Vector of all the blocks of the chain
    std::vector<Block> blocks;
};