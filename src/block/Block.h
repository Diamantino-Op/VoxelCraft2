#pragma once

#include <utility>
#include <glm/vec3.hpp>

// Textures for each side of a block
struct SideTextureIndices
{
	SideTextureIndices(int i) : top(i), side(i), bottom(i) {}
	SideTextureIndices(int top, int side, int bottom) : top(top), side(side), bottom(bottom) {}

	unsigned top;
	unsigned side;
	unsigned bottom;
};

// Defines info for each block
struct Block
{
	// This matches order in sprite sheet
	enum BlockType : unsigned char
	{
		BLOCK_ERROR = 255,

		BLOCK_AIR = 0,
		BLOCK_GRASS,
		BLOCK_DIRT,
		BLOCK_STONE,
		BLOCK_LOG,
		BLOCK_LEAVES,

		BLOCK_COUNT
	};

	BlockType type;

	bool operator==(const Block &rhs) const
	{
		return type == rhs.type;
	}
};

typedef std::pair<glm::ivec3, Block> BlockInfo;

// Block-texture data
namespace BlockData
{
	static const SideTextureIndices sideIndices[Block::BLOCK_COUNT] =
	{
		0,
		{ 2, 1, 0 },
		0,
		3,
		{ 5, 4, 5 },
		6,
	};
}