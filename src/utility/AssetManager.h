#pragma once

#include <map>
#include <string>
#include <vector>

class AssetManager
{
public:
    // Singleton pattern
    static AssetManager &Instance()
    {
        static AssetManager instance;
        return instance;
    }
    
    AssetManager();

    void SetPath(std::string path);
    std::string GetPath();

    std::vector<unsigned char> LoadTexture(const std::string &filename, int &width, int &height, int &channels);
    void PackTextures(const std::map<std::string, std::string> &textures, const std::string &atlasFilename);
    void ProcessTextures();

    int GetTexIndexFromName(const std::string& textureName);
    
private:
    std::string assetPath;
    std::map<std::string, int> textureMappings;
};
