#include "Block.h"

BlockTexture::BlockTexture()
{
    this->top = "air";
    this->front = "air";
    this->right = "air";
    this->left = "air";
    this->back = "air";
    this->bottom = "air";
}

BlockTexture::BlockTexture(const std::string& all)
{
    this->top = all;
    this->front = all;
    this->right = all;
    this->left = all;
    this->back = all;
    this->bottom = all;
}

BlockTexture::BlockTexture(const std::string& topBottom, const std::string& side)
{
    this->top = topBottom;
    this->front = side;
    this->right = side;
    this->left = side;
    this->back = side;
    this->bottom = topBottom;
}

BlockTexture::BlockTexture(const std::string& top, const std::string& side, const std::string& bottom)
{
    this->top = top;
    this->front = side;
    this->right = side;
    this->left = side;
    this->back = side;
    this->bottom = bottom;
}

BlockTexture::BlockTexture(const std::string& top, const std::string& front, const std::string& right, const std::string& left, const std::string& back, const std::string& bottom)
{
    this->top = top;
    this->front = front;
    this->right = right;
    this->left = left;
    this->back = back;
    this->bottom = bottom;
}

std::string BlockTexture::GetTopTextureName()
{
    return this->top;
}

std::string BlockTexture::GetFrontTextureName()
{
    return this->front;
}

std::string BlockTexture::GetRightTextureName()
{
    return this->right;
}

std::string BlockTexture::GetLeftTextureName()
{
    return this->left;
}

std::string BlockTexture::GetBackTextureName()
{
    return this->back;
}

std::string BlockTexture::GetBottomTextureName()
{
    return this->bottom;
}

Block::Block()
{
    this->id = 0; 
    this->name = "air";
    this->blockTexture = BlockTexture("air");
    this->type = AIR;
}

Block::Block(int id, const std::string& name, const BlockTexture& blockTexture, BlockType type)
{
    this->id = id;
    this->name = name;
    this->blockTexture = blockTexture;
    this->type = type;
}

int Block::GetId() const
{
    return this->id;
}

std::string Block::GetName()
{
    return this->name;
}

BlockTexture Block::GetBlockTexture()
{
    return this->blockTexture;
}

Block::BlockType Block::GetType() const
{
    return this->type;
}
