#pragma once

#include <map>

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

    void Init();
    
    Block& GetBlockById(int id);
    Block& GetBlockByName(const std::string& name);
    
private:
    Blocks();
    
    std::map<std::string, Block> blocks;
    
};
