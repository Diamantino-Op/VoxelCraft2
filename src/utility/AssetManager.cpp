#include "AssetManager.h"

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
