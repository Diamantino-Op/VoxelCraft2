#pragma once

#include <array>

#include <glm/glm.hpp>

#include "../../graphics/utility/Mesh.h"
#include "../WorldConstants.h"
#include "../../block/Block.h"
#include "../TerrainGenerator.h"

// Collection of blocks, world is made of a 2d grid of chunks
class Chunk
{
public:
	Chunk(glm::ivec2 pos);

	// Generate block data
	void Generate(TerrainGenerator &gen);

	// Generate mesh from block data
	void BuildMesh();

	// Remove chunk's mesh
	void ClearMesh();

	// Does this chunk have a mesh?
	[[nodiscard]] bool MeshBuilt() const;

	// Individual block get/set
	void SetBlock(glm::ivec3 pos, const Block &block);
	[[nodiscard]] const Block &GetBlock(glm::ivec3 pos) const;

	// Position getters
	[[nodiscard]] glm::ivec2 GetCoord() const; // chunk coords
	[[nodiscard]] glm::vec3 GetWorldPos() const;
	[[nodiscard]] glm::vec3 GetRenderPos() const; // affected by height

	// Float-in timer
	void UpdateHeightTimer(float dt);
	void SetHeightTimerIncreasing(bool increasing);
	[[nodiscard]] bool HeightTimerHitZero() const;

	// Is this chunk inside a frustum?
	[[nodiscard]] bool IsVisible(const Math::Frastum &camera) const;

	// Draw the chunk
	void Draw();

private:
	glm::ivec2 position_;
	Mesh mesh_;
	float heightTimer_; // 0: down, 1: up
	bool heightTimerIncreasing_;
	int highestSolidBlock_; // Currently stores highest ever existed
	
	// low to high: x, z, y
	std::array<Block, World::chunkSize * World::chunkSize * World::chunkHeight> blocks_ = {};

	[[nodiscard]] glm::ivec3 WorldToLocal(glm::ivec3 pos) const; // world block coord to local block coord
	[[nodiscard]] glm::ivec3 LocalToWorld(glm::ivec3 pos) const; // local block coord to world block coord
	[[nodiscard]] bool OutOfBounds(glm::ivec3 pos) const; // is this local block coord invalid?
	[[nodiscard]] const Block &GetBlockLocal(glm::ivec3 pos) const; // get the block at a local coord
	void SetBlockLocal(glm::ivec3 pos, const Block &block); // set the block at a local coord
	[[nodiscard]] bool CheckForBlock(glm::ivec3 pos) const; // is a solid block at coord?

};

