#include "TerrainGenerator.h"
#include "WorldConstants.h"

#include <glm/gtc/noise.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/hash.hpp>

#include <random>

namespace Gen = World::Generation;

// Hardcoded tree data; in the future, this will go in an external data file
const std::string TerrainGenerator::tree[10][7][7] = {
	{{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "oak_log", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" }},
	{{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "oak_log", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" }},
	{{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "oak_log", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" }},
	{{ "air", "air", "air", "oak_leaves", "air", "air", "air" },{ "air", "air", "oak_leaves", "oak_leaves", "oak_leaves", "air", "air" },{ "air", "oak_leaves", "oak_leaves", "oak_leaves", "oak_leaves", "oak_leaves", "air" },{ "oak_leaves", "oak_leaves", "oak_leaves", "oak_log", "oak_leaves", "oak_leaves", "oak_leaves" },{ "air", "oak_leaves", "oak_leaves", "oak_leaves", "oak_leaves", "oak_leaves", "air" },{ "air", "air", "oak_leaves", "oak_leaves", "oak_leaves", "air", "air" },{ "air", "air", "air", "oak_leaves", "air", "air", "air" }},
	{{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "oak_leaves", "oak_leaves", "oak_leaves", "air", "air" },{ "air", "air", "oak_leaves", "oak_log", "oak_leaves", "air", "air" },{ "air", "air", "oak_leaves", "oak_leaves", "oak_leaves", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" }},
	{{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "oak_leaves", "oak_leaves", "oak_leaves", "air", "air" },{ "air", "oak_leaves", "oak_leaves", "oak_leaves", "oak_leaves", "oak_leaves", "air" },{ "air", "oak_leaves", "oak_leaves", "oak_log", "oak_leaves", "oak_leaves", "air" },{ "air", "oak_leaves", "oak_leaves", "oak_leaves", "oak_leaves", "oak_leaves", "air" },{ "air", "air", "oak_leaves", "oak_leaves", "oak_leaves", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" }},
	{{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "oak_leaves", "air", "air", "air" },{ "air", "air", "oak_leaves", "oak_log", "oak_leaves", "air", "air" },{ "air", "air", "air", "oak_leaves", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" }},
	{{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "oak_leaves", "air", "air", "air" },{ "air", "air", "oak_leaves", "oak_leaves", "oak_leaves", "air", "air" },{ "air", "oak_leaves", "oak_leaves", "oak_log", "oak_leaves", "oak_leaves", "air" },{ "air", "air", "oak_leaves", "oak_leaves", "oak_leaves", "air", "air" },{ "air", "air", "air", "oak_leaves", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" }},
	{{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "oak_leaves", "air", "air", "air" },{ "air", "air", "oak_leaves", "oak_leaves", "oak_leaves", "air", "air" },{ "air", "air", "air", "oak_leaves", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" }},
	{{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "oak_leaves", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" },{ "air", "air", "air", "air", "air", "air", "air" }}
};

int TerrainGenerator::GetHeight(glm::vec2 pos)
{
	// Get grid corners for interpolation
	const glm::vec2 scaled = pos / Gen::terrainInterpGrid;
	glm::vec2 min = floor(scaled) * Gen::terrainInterpGrid;
	glm::vec2 max = ceil(scaled) * Gen::terrainInterpGrid;

	if (min == max)
		return static_cast<int>(GetNoiseHeight(pos));

	// Interpolate x and y
	if (min.x != max.x && min.y != max.y)
	{
		// Get noise at each corner
		const float bl = GetNoiseHeight(min);
		const float tr = GetNoiseHeight(max);
		const float tl = GetNoiseHeight({ min.x, max.y });
		const float br = GetNoiseHeight({ max.x, min.y });

		// Interpolation values
		const float tx = (pos.x - min.x) / (max.x - min.x);
		const float ty = (pos.y - min.y) / (max.y - min.y);

		// Lerp y
		const float ml = glm::lerp(bl, tl, ty);
		const float mr = glm::lerp(br, tr, ty);

		// Lerp x
		return static_cast<int>(glm::lerp(ml, mr, tx));
	}
	
	// Interpolate one dimension
	const float minH = GetNoiseHeight(min);
	const float maxH = GetNoiseHeight(max);

	if (min.x == max.x) // Interpolate y
		return static_cast<int>(glm::lerp(minH, maxH, (pos.y - min.y) / (max.y - min.y)));
	else // Interpolate x
		return static_cast<int>(glm::lerp(minH, maxH, (pos.x - min.x) / (max.x - min.x)));
}

std::vector<glm::ivec2> TerrainGenerator::GenerateTreePoints(glm::ivec2 startCorner, glm::ivec2 endCorner)
{
	std::vector<glm::ivec2> points;
	std::uniform_real_distribution dist(0.0f, 1.0f);

	// Check each point for if a tree should be generated
	for (int z = startCorner.y; z < endCorner.y; z++)
	{
		for (int x = startCorner.x; x < endCorner.x; x++)
		{
			std::hash<glm::ivec2> hash;
			glm::ivec2 pos = { x, z };
			std::default_random_engine rng(static_cast<unsigned>(hash(pos)));

			// Generate tree if using coord as seed passes
			if (dist(rng) <= Gen::treeDensity)
			{
				points.push_back(pos);
			}
		}
	}

	return points;
}

float TerrainGenerator::GetNoiseHeight(glm::vec2 pos)
{
	// Check cache
	float cache = GetFromCache(pos);
	if (cache > 0.0f)
		return cache;

	// Calculate layered noise
	float height = ((simplex(pos / Gen::heightScale) + 1) / 2) * Gen::heightWeight * Gen::heightMaxHeight + ((simplex(pos / Gen::detailScale) + 1) / 2) * Gen::detailWeight * Gen::detailMaxHeight;

	// Apply biome height scalar
	height *= (glm::clamp(
		(simplex(pos / Gen::landScale) + Gen::landMountainBias * 2.0f) * Gen::landTransitionSharpness,
		-1.0f + Gen::landMinMult * 2.0f,
		1.0f
	) + 1.0f) / 2.0f;

	// Raise height by min
	height += Gen::minHeight;

	// Add and return
	AddToCache(pos, height);
	return height;
}

void TerrainGenerator::AddToCache(glm::vec2 pos, float height)
{
	if (cacheSize_ >= cacheCapacity)
		cacheSize_ = 0; // Reset cache

	// Add to cache
	cache_[cacheSize_] = { height, pos };
	cacheSize_++;
}

float TerrainGenerator::GetFromCache(glm::vec2 pos) const
{
	// Search from end
	for (int i = cacheSize_ - 1; i >= 0; i--)
	{
		if (cache_[i].pos == pos)
			return cache_[i].height;
	}
	return 0.0f;
}
