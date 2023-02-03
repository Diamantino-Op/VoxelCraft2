#pragma once

#include <utility>
#include <string>
#include <glm/vec3.hpp>

#include "../graphics/utility/CascadedShadowMap.h"

// Textures for each side of a block
class BlockTexture
{
public:
	BlockTexture(const std::string& all);
	BlockTexture(const std::string& topBottom, const std::string& side);
	BlockTexture(const std::string& top, const std::string& side, const std::string& bottom);
	BlockTexture(const std::string& top, const std::string& front, const std::string& right, const std::string& left, const std::string& back, const std::string& bottom);

	std::string GetTopTextureName();
	std::string GetFrontTextureName();
	std::string GetRightTextureName();
	std::string GetLeftTextureName();
	std::string GetBackTextureName();
	std::string GetBottomTextureName();
	
private:
	std::string top;
	std::string front;
	std::string right;
	std::string left;
	std::string back;
	std::string bottom;
};

// Defines info for each block
class Block
{
public:
	enum BlockType : unsigned int
	{
		AIR,
		GROUND,
		PLANT,
		STONE,
		METAL,
		WOOD
	};

	Block(int id, const std::string& name, const BlockTexture& blockTexture, BlockType type);

	int GetId() const;
	std::string GetName();
	BlockTexture GetBlockTexture();
	[[nodiscard]] BlockType GetType() const;

private:
	int id;
	std::string name;
	BlockTexture blockTexture;
	BlockType type;

public:
	bool operator ==(const Block &rhs) const
	{
		return type == rhs.type || name == rhs.name;
	}
};

typedef std::pair<glm::ivec3, Block> BlockInfo;