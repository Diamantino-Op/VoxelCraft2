#pragma once

#include <array>

#include "Block.h"

class Blocks
{
public:
    // Singleton pattern
    static Blocks &Instance()
    {
        static Blocks instance;
        return instance;
    }
    
    Block GetBlockById(int id);
    Block GetBlockByName(const std::string& name);

    Block defaultBlock;
    
private:
    Blocks();
    
    std::array<Block, 22> blocks;
    
};
