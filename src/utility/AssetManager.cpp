#include "AssetManager.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <stb_image.h>
#include <stb_image_write.h>
#include <utility>

AssetManager::AssetManager()
{
    assetPath = "resources/";
    textureMappings = {};
}

void AssetManager::SetPath(std::string path)
{
    assetPath = std::move(path);
    assetPath.append("/");
}

std::string AssetManager::GetPath()
{
    return assetPath;
}

// Load a texture file into memory
std::vector<unsigned char> AssetManager::LoadTexture(const std::string& filename, int& width, int& height, int& channels)
{
    // Load the image using stb_image
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load image " << filename << ": " << stbi_failure_reason() << std::endl;
        return {};
    }

    // Convert the loaded image to a vector
    std::vector<unsigned char> imageData;

    if (channels == 3) {
        imageData.resize(width * height * 4);
        for (int i = 0; i < width * height; i++) {
            imageData[i * 4 + 0] = data[i * 3 + 0];
            imageData[i * 4 + 1] = data[i * 3 + 1];
            imageData[i * 4 + 2] = data[i * 3 + 2];
            imageData[i * 4 + 3] = 255;
        }
    }
    else {
        imageData = std::vector(data, data + width * height * channels);
    }

    // Free the loaded image
    stbi_image_free(data);

    return imageData;
}

// Save an atlas image and a text file with the mapping from texture names to filenames
void AssetManager::PackTextures(const std::map<std::string, std::string>& textures, const std::string& atlasFilename)
{
    // Load all the textures into memory
    std::map<std::string, std::vector<unsigned char>> loadedTextures;
    for (const auto &[name, filename] : textures) {
        int width, height, channels;

        loadedTextures[name] = LoadTexture(filename, width, height, channels);
    }

    const int textureSize = 16;
    
    // Find the size of the square atlas needed to fit all the textures
    const int atlasSize = static_cast<int>(std::ceil(std::sqrt(loadedTextures.size())));
    const int atlasWidth = atlasSize * textureSize;
    const int atlasHeight = atlasSize * textureSize;
    // Allocate memory for the atlas image
    std::vector<unsigned char> atlasImage(atlasWidth * atlasHeight * 4);

    // Copy the textures into the atlas
    int x = 0, y = 0, i = 0;
    for (const auto &[name, image] : loadedTextures) {
        for (int row = 0; row < textureSize; ++row) {
            for (int col = 0; col < textureSize; ++col) {
                const int atlasPos = (y + row) * atlasWidth * 4 + (x + col) * 4;
                const int imagePos = row * textureSize * 4 + col * 4;
                
                atlasImage[atlasPos + 0] = image[imagePos + 0];
                atlasImage[atlasPos + 1] = image[imagePos + 1];
                atlasImage[atlasPos + 2] = image[imagePos + 2];
                atlasImage[atlasPos + 3] = image[imagePos + 3];
            }
        }

        textureMappings[name] = i;

        i++;
        x += textureSize;
        if (x >= atlasWidth) {
            x = 0;
            y += textureSize;
        }
    }

    // Save the atlas image to a file using stb_image_write
	if (!stbi_write_png(atlasFilename.data(), atlasWidth, atlasHeight, 4, atlasImage.data(), 0)) {
		std::cout << "Failed to write atlas image to " << atlasFilename << ": " << stbi_failure_reason() << std::endl;
	}
    else
    {
        std::cout << "Atlas created at: " << atlasFilename << std::endl;
    }
}

void AssetManager::ProcessTextures()
{
    // Get all .png files in a folder
    std::map<std::string, std::string> textures;
    std::filesystem::path folder((GetPath() + "textures/blocks"));
    
    for (const auto &entry : std::filesystem::directory_iterator(folder)) {
        if (entry.path().extension() == ".png") {
            auto name = entry.path().stem().string();
            auto filename = entry.path().string();
            textures[name] = filename;
        }
    }
    
    PackTextures(textures, GetPath() + "textures/blocks/block_atlas.png");
}

int AssetManager::GetTexIndexFromName(const std::string& textureName)
{
    for (const auto &[name, index] : textureMappings)
    {
        if (name == textureName)
            return index;
    }

    return textureMappings["default"];
}
