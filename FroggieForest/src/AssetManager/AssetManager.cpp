#include "AssetManager.hpp"

AssetManager::AssetManager()
{
  std::cout << "[AssetManager] Se ejecuta constructor" << std::endl;
}

AssetManager::~AssetManager()
{
  std::cout << "[AssetManager] Se ejecuta destrucción" << std::endl;
  ClearAssets();
}

void AssetManager::ClearAssets()
{
  for (auto texture : textures)
  {
    SDL_DestroyTexture(texture.second);
  }

  for (auto font : fonts)
  {
    TTF_CloseFont(font.second);
  }
  fonts.clear();
  textures.clear();
}

void AssetManager::AddTexture(SDL_Renderer *renderer, const std::string &textureID, const std::string &filePath)
{
  SDL_Surface *surface = IMG_Load(filePath.c_str());
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  textures.emplace(textureID, texture);
}

SDL_Texture *AssetManager::getTexture(const std::string &textureID)
{
  auto it = textures.find(textureID);
  if (it == textures.end())
  {
    return nullptr;
  }
  return it->second;
}

void AssetManager::AddFont(const std::string &fontID, const std::string &filePath, int fontSize)
{
  TTF_Font *font = TTF_OpenFont(filePath.c_str(), fontSize);
  if (font == nullptr)
  {
    std::string error = TTF_GetError();
    std::cerr << "Error loading font: " << error << std::endl;
    return;
  }
  fonts.emplace(fontID, font);
}

TTF_Font *AssetManager::getFont(const std::string &fontID)
{
  auto it = fonts.find(fontID);
  if (it == fonts.end())
  {
    return nullptr;
  }
  return it->second;
}