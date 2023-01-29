#pragma once

#include <string>

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

private:
    std::string assetPath;
};
