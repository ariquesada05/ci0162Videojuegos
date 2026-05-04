#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <map>
#include <string>
#include <iostream>

class AssetManager
{
private:
  std::map<std::string, SDL_Texture *> textures;
  std::map<std::string, TTF_Font *> fonts;

public:
  AssetManager();
  ~AssetManager();

  void ClearAssets();

  void AddTexture(SDL_Renderer *renderer, const std::string &textureID, const std::string &filePath);

  SDL_Texture *getTexture(const std::string &textureID);

  void AddFont(const std::string &fontID, const std::string &filePath, int fontSize);

  TTF_Font *getFont(const std::string &fontID);
};

#endif // ASSETMANAGER_HPP