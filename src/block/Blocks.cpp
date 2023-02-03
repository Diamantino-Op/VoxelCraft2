#include "Blocks.h"

Blocks::Blocks()
{
    defaultBlock = Block(MAXINT, "default", BlockTexture("default"), Block::AIR);
    
    int id = 0;
    
    blocks = {
        Block(0, "air", BlockTexture("air"), Block::AIR),
        Block(++id, "acacia_leaves", BlockTexture("acacia_leaves"), Block::PLANT),
        Block(++id, "acacia_log", BlockTexture("acacia_log_top", "acacia_log"), Block::WOOD),
        Block(++id, "birch_leaves", BlockTexture("birch_leaves"), Block::PLANT),
        Block(++id, "birch_log", BlockTexture("birch_log_top", "birch_log"), Block::WOOD),
        Block(++id, "coal_ore", BlockTexture("coal_ore"), Block::STONE),
        Block(++id, "copper_ore", BlockTexture("copper_ore"), Block::STONE)
    };
}

Block Blocks::GetBlockById(int id)
{
    for (Block block : blocks)
    {
        if (block.GetId() == id)
            return block;
    }

    return defaultBlock;
}

Block Blocks::GetBlockByName(const std::string& name)
{
    for (Block block : blocks)
    {
        if (block.GetName() == name)
            return block;
    }

    return defaultBlock;
}