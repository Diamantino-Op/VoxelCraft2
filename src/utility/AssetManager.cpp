#include "AssetManager.h"

#include <fstream>
#include <iostream>
#include <stb_image.h>
#include <utility>

AssetManager::AssetManager()
{
    assetPath = "";
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
    std::vector<unsigned char> imageData(data, data + width * height * channels);

    // Free the loaded image
    stbi_image_free(data);

    return imageData;
}

// Save an atlas image and a text file with the mapping from texture names to filenames
void AssetManager::PackTextures(const std::map<std::string, std::string>& textures, const std::string& atlasFilename, const std::string& mappingFilename)
{
    // Determine the size of the atlas
    int atlasWidth = 0;
    int atlasHeight = 0;
    for (const auto &[name, filename] : textures) {
        int width, height, channels;
        auto data = LoadTexture(filename, width, height, channels);
        if (data.empty()) {
            return;
        }

        atlasWidth = std::max(atlasWidth, width);
        atlasHeight += height;
    }

    // Allocate memory for the atlas image
    std::vector<unsigned char> atlasImage(atlasWidth * atlasHeight * 4);

    // Copy the textures into the atlas
    int y = 0;
    for (const auto &[name, filename] : textures) {
        int width, height, channels;
        auto data = LoadTexture(filename, width, height, channels);
        if (data.empty()) {
            return;
        }

        // Copy the texture data into the atlas image
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                atlasImage[((y + i) * atlasWidth + j) * 4 + 0] = data[(i * width + j) * channels + 0];
                atlasImage[((y + i) * atlasWidth + j) * 4 + 1] = data[(i * width + j) * channels + 1];
                atlasImage[((y + i) * atlasWidth + j) * 4 + 2] = data[(i * width + j) * channels + 2];
                atlasImage[((y + i) * atlasWidth + j) * 4 + 3] = channels == 3 ? 255 : data[(i * width + j) * channels + 3];
            }
        }

        y += height;
    }

    // Save the atlas image to a file using stb_image_write
	if (!stbi_write_png(atlasFilename.c_str(), atlasWidth, atlasHeight, 4, atlasImage.data(), 0)) {
		std::cout << "Failed to write atlas image to " << atlasFilename << ": " << stbi_failure_reason() << std::endl;
	}
	
	// Write the mapping from texture names to filenames to a text file
	std::ofstream mappingFile(mappingFilename);
	if (!mappingFile) {
		std::cerr << "Failed to open mapping file " << mappingFilename << " for writing" << std::endl;
		return;
	}

	for (const auto &[name, filename] : textures) {
		mappingFile << name << ":" << filename << std::endl;
	}
}
