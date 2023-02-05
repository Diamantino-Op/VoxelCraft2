#include "Blocks.h"

#include <iostream>

Blocks::Blocks()
{
    defaultBlock = Block(MAXINT, "default", BlockTexture("default"), Block::AIR);
    
    blocks = {};
}

void Blocks::Init()
{
    int id = 0;
    
    blocks = {
        Block(0, "air", BlockTexture("air"), Block::AIR),
        Block(++id, "acacia_leaves", BlockTexture("acacia_leaves"), Block::PLANT),
        Block(++id, "acacia_log", BlockTexture("acacia_log_top", "acacia_log"), Block::WOOD),
        Block(++id, "birch_leaves", BlockTexture("birch_leaves"), Block::PLANT),
        Block(++id, "birch_log", BlockTexture("birch_log_top", "birch_log"), Block::WOOD),
        Block(++id, "coal_ore", BlockTexture("coal_ore"), Block::STONE),
        Block(++id, "copper_ore", BlockTexture("copper_ore"), Block::STONE),
        Block(++id, "dark_oak_leaves", BlockTexture("dark_oak_leaves"), Block::PLANT),
        Block(++id, "dark_oak_log", BlockTexture("dark_oak_log_top", "dark_oak_log"), Block::WOOD),
        Block(++id, "diamond_ore", BlockTexture("diamond_ore"), Block::STONE),
        Block(++id, "dirt", BlockTexture("dirt"), Block::GROUND),
        Block(++id, "emerald_ore", BlockTexture("emerald_ore"), Block::STONE),
        Block(++id, "grass_block", BlockTexture("grass_block_top", "grass_block_side", "dirt"), Block::GROUND),
        Block(++id, "iron_ore", BlockTexture("iron_ore"), Block::STONE),
        Block(++id, "jungle_leaves", BlockTexture("jungle_leaves"), Block::PLANT),
        Block(++id, "jungle_log", BlockTexture("jungle_log_top", "jungle_log"), Block::WOOD),
        Block(++id, "lapis_ore", BlockTexture("lapis_ore"), Block::STONE),
        Block(++id, "oak_leaves", BlockTexture("oak_leaves"), Block::PLANT),
        Block(++id, "oak_log", BlockTexture("oak_log_top", "oak_log"), Block::WOOD),
        Block(++id, "spruce_leaves", BlockTexture("spruce_leaves"), Block::PLANT),
        Block(++id, "spruce_log", BlockTexture("spruce_log_top", "spruce_log"), Block::WOOD),
        Block(++id, "stone", BlockTexture("stone"), Block::STONE)
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