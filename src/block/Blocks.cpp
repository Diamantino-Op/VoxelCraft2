#include "Blocks.h"

#include <iostream>
#include <ranges>

Blocks::Blocks()
{
    blocks = {};
}

void Blocks::Init()
{
    int id = 0;
    
    blocks["air"] = Block(0, "air", BlockTexture("air"), Block::AIR);
    blocks["acacia_leaves"] = Block(++id, "acacia_leaves", BlockTexture("acacia_leaves"), Block::PLANT);
    blocks["acacia_log"] = Block(++id, "acacia_log", BlockTexture("acacia_log_top", "acacia_log"), Block::WOOD);
    blocks["birch_leaves"] = Block(++id, "birch_leaves", BlockTexture("birch_leaves"), Block::PLANT);
    blocks["birch_log"] = Block(++id, "birch_log", BlockTexture("birch_log_top", "birch_log"), Block::WOOD);
    blocks["coal_ore"] = Block(++id, "coal_ore", BlockTexture("coal_ore"), Block::STONE);
    blocks["copper_ore"] = Block(++id, "copper_ore", BlockTexture("copper_ore"), Block::STONE);
    blocks["dark_oak_leaves"] = Block(++id, "dark_oak_leaves", BlockTexture("dark_oak_leaves"), Block::PLANT);
    blocks["dark_oak_log"] = Block(++id, "dark_oak_log", BlockTexture("dark_oak_log_top", "dark_oak_log"), Block::WOOD);
    blocks["diamond_ore"] = Block(++id, "diamond_ore", BlockTexture("diamond_ore"), Block::STONE);
    blocks["dirt"] = Block(++id, "dirt", BlockTexture("dirt"), Block::GROUND);
    blocks["emerald_ore"] = Block(++id, "emerald_ore", BlockTexture("emerald_ore"), Block::STONE);
    blocks["grass_block"] = Block(++id, "grass_block", BlockTexture("grass_block_top", "grass_block_side", "dirt"), Block::GROUND);
    blocks["iron_ore"] = Block(++id, "iron_ore", BlockTexture("iron_ore"), Block::STONE);
    blocks["jungle_leaves"] = Block(++id, "jungle_leaves", BlockTexture("jungle_leaves"), Block::PLANT);
    blocks["jungle_log"] = Block(++id, "jungle_log", BlockTexture("jungle_log_top", "jungle_log"), Block::WOOD);
    blocks["lapis_ore"] = Block(++id, "lapis_ore", BlockTexture("lapis_ore"), Block::STONE);
    blocks["oak_leaves"] = Block(++id, "oak_leaves", BlockTexture("oak_leaves"), Block::PLANT);
    blocks["oak_log"] = Block(++id, "oak_log", BlockTexture("oak_log_top", "oak_log"), Block::WOOD);
    blocks["spruce_leaves"] = Block(++id, "spruce_leaves", BlockTexture("spruce_leaves"), Block::PLANT);
    blocks["spruce_log"] = Block(++id, "spruce_log", BlockTexture("spruce_log_top", "spruce_log"), Block::WOOD);
    blocks["stone"] = Block(++id, "stone", BlockTexture("stone"), Block::STONE);
}

Block& Blocks::GetBlockById(int id)
{
    for (auto& block : blocks | std::views::values)
    {
        if (block.GetId() == id)
            return block;
    }

    return blocks["air"];
}

Block& Blocks::GetBlockByName(const std::string& name)
{
    for (auto& block : blocks | std::views::values)
    {
        if (block.GetName() == name)
            return block;
    }

    return blocks["air"];
}