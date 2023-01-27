#pragma once

#include <vector>
#include <unordered_map>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "../../block/Block.h"
#include "../../graphics/utility/Texture.h"
#include "../../utility/Math.h"
#include "../TerrainGenerator.h"
#include "../../graphics/utility/Shader.h"

class Chunk;
class Camera;
struct CascadeShaderInfo;

// Loads, unloads, and draws chunks
class ChunkManager
{
public:
	// Singleton pattern
	static ChunkManager &Instance()
	{
		static ChunkManager instance;
		return instance;
	}

	// Raycast data
	struct RaycastResult
	{
		bool hit;
		BlockInfo block;
		glm::vec3 pos;
		Math::Direction normal;
	};

	// Load and unload chunks for this frame
	void UpdateChunks(glm::vec3 playerPos, float dt);

	// Draw all chunks with lighting calculations
	void DrawChunksLit(const Camera &camera, const std::vector<CascadeShaderInfo> &cascadeInfo);

	// Draw chunks with given shader and camera
	void DrawChunks(const glm::mat4 &cameraMatrix, const Shader &shader) const;

	// World block getters/setters
	void SetBlock(glm::ivec3 pos, const Block &block, bool network = false);
	const Block &GetBlock(glm::ivec3 pos);

	// Utility functions
	std::vector<BlockInfo> GetBlocksInVolume(glm::vec3 pos, glm::vec3 size);
	RaycastResult Raycast(glm::vec3 pos, glm::vec3 dir, float length = INFINITY);

	// Rendering functions
	Shader &GetShader();

private:
	typedef std::unordered_map<glm::ivec2, Chunk *> ChunkContainer;

	Shader shader_;
	Texture texture_;
	ChunkContainer chunks_;
	TerrainGenerator noise_;

	ChunkManager();
	~ChunkManager();
	Chunk *AddChunk(glm::ivec2 coord); // adds completed chunk to buffer, generates surrounding chunks
	[[nodiscard]] bool ChunkInRange(glm::vec3 playerPos, glm::vec3 chunkPos) const; // if chunk should stay loaded
	[[nodiscard]] int BuiltNeighborCount(glm::ivec2 coord) const; // how many surrounding chunks' meshes are built
	[[nodiscard]] int BuiltNeighborCount(glm::ivec2 coord, glm::ivec2 exclude) const;
	Chunk *GetChunk(glm::ivec3 pos); // Chunk getters
	[[nodiscard]] const Chunk *GetChunk(glm::ivec3 pos) const;
	Chunk *GetChunk(glm::ivec2 chunkCoord);
	[[nodiscard]] const Chunk *GetChunk(glm::ivec2 chunkCoord) const;
	[[nodiscard]] glm::ivec2 ToRelativePosition(glm::ivec3 pos) const; // Convert block coord to local coord
	[[nodiscard]] glm::ivec2 ToChunkPosition(glm::ivec3 pos) const; // Convert world coord to chunk coord

public: // Remove functions for singleton
	ChunkManager(ChunkManager const &) = delete;
	void operator=(ChunkManager const &) = delete;
};