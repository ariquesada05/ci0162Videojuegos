/**
 * @file AssetManager.hpp
 * @brief Manager for loading and storing game assets (textures and fonts)
 * 
 * The AssetManager handles the loading, caching, and retrieval of game resources
 * such as textures and fonts using SDL2.
 */

#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <map>
#include <string>
#include <iostream>

/**
 * @class AssetManager
 * @brief Manages game assets (textures and fonts)
 * 
 * Singleton-like manager that provides caching and retrieval of textures and fonts
 * loaded from disk. Prevents duplicate loading of the same assets.
 */
class AssetManager
{
private:
  std::map<std::string, SDL_Texture *> textures;  ///< Cache of loaded textures
  std::map<std::string, TTF_Font *> fonts;        ///< Cache of loaded fonts

public:
  /**
   * @brief Construct a new AssetManager
   */
  AssetManager();
  
  /**
   * @brief Destroy the AssetManager and free all resources
   */
  ~AssetManager();

  /**
   * @brief Clear all cached assets from memory
   */
  void ClearAssets();

  /**
   * @brief Load and cache a texture
   * @param renderer The SDL renderer to use for loading the texture
   * @param textureID A unique identifier for this texture
   * @param filePath The path to the texture file on disk
   */
  void AddTexture(SDL_Renderer *renderer, const std::string &textureID, const std::string &filePath);

  /**
   * @brief Retrieve a cached texture
   * @param textureID The unique identifier of the texture
   * @return SDL_Texture* Pointer to the texture, or nullptr if not found
   */
  SDL_Texture *getTexture(const std::string &textureID);

  /**
   * @brief Load and cache a font
   * @param fontID A unique identifier for this font
   * @param filePath The path to the font file on disk
   * @param fontSize The size of the font in pixels
   */
  void AddFont(const std::string &fontID, const std::string &filePath, int fontSize);

  /**
   * @brief Retrieve a cached font
   * @param fontID The unique identifier of the font
   * @return TTF_Font* Pointer to the font, or nullptr if not found
   */
  TTF_Font *getFont(const std::string &fontID);
};

#endif // ASSETMANAGER_HPP