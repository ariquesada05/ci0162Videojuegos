/**
 * @file StatsSystem.hpp
 * @brief Statistics rendering system
 */

#ifndef STATSSYSTEM_HPP
#define STATSSYSTEM_HPP

#include <algorithm>
#include <vector>
#include <sstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../ECS/ECS.hpp"
#include "../Components/PlayerScoreComponent.hpp"
#include "../Components/StatsComponent.hpp"

/**
 * @brief SDL surface deleter for unique_ptr
 */
inline auto surfaceDeleter = [](SDL_Surface* surface) {
    SDL_FreeSurface(surface);
};

/**
 * @brief SDL texture deleter for unique_ptr
 */
inline auto textureDeleter = [](SDL_Texture* texture) {
    SDL_DestroyTexture(texture);
};

/**
 * @brief Font deleter for unique_ptr
 */
inline auto fontDeleter = [](TTF_Font* font) {
    if (!font) return ;
    TTF_CloseFont(font);
};

/**
 * @class StatsSystem
 * @brief Renders game statistics
 */
class StatsSystem : public System
{
    std::unique_ptr<TTF_Font, decltype(fontDeleter)> font{nullptr, fontDeleter};
    const int fontSize = 32;
    const char* fontPath = "./assets/fonts/VarelaRound-Regular.ttf";
    const int margin = 10;
public:
    StatsSystem()  {
        requireComponent<TagComponent>();
        requireComponent<StatsComponent>();
        font.reset(TTF_OpenFont(fontPath, fontSize));
        if (!font) {
            throw std::runtime_error("Failed to load font: " + std::string(TTF_GetError()));
        }
    }

    void Update(SDL_Renderer* renderer) {
        auto entities = getEntities();

        auto foundEntities = std::find_if(
            entities.begin(),
            entities.end(),
            [&](Entity entity) {
                return entity.getComponent<TagComponent>().tag == "Stats";
            }
        );

        if (foundEntities == entities.end()) {
            return;
        }

        auto& stats = foundEntities->getComponent<StatsComponent>();

        auto& points = stats.Points;
        auto& health = stats.Health;

        std::stringstream statsText;

        statsText << "Points: " << points;
        std::string pointsText = statsText.str();

        statsText.str("");
        statsText.clear();

        statsText << "Health: " << health;
        std::string healthText = statsText.str();
        std::cout << health << std::endl;


        int windowWidth, windowHeight;
        SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

        std::unique_ptr<SDL_Surface, decltype(surfaceDeleter)> surface(
            //TODO: ARREGLAR COLOR
            TTF_RenderText_Blended(font.get(), pointsText.c_str(), {0, 0, 0, 255}),
            surfaceDeleter
        );

        std::unique_ptr<SDL_Texture, decltype(textureDeleter)> texture(
            SDL_CreateTextureFromSurface(renderer, surface.get()),
            textureDeleter
        );

        SDL_Rect destRect {
            margin,
            margin,
            surface->w,
            surface->h
        };

        SDL_RenderCopy(renderer, texture.get(), nullptr, &destRect);

        surface.reset(
            TTF_RenderText_Blended(font.get(), healthText.c_str(), {0, 0, 0,255})
        );
        texture.reset(
            SDL_CreateTextureFromSurface(renderer, surface.get())
        );

        int previousHeight = surface->h;

        surface.reset(
            TTF_RenderText_Blended(
                font.get(),
                healthText.c_str(),
                SDL_Color{255,255,255,255}
            )
        );

        texture.reset(
            SDL_CreateTextureFromSurface(renderer, surface.get())
        );

        destRect.y += previousHeight + margin;

        SDL_RenderCopy(renderer, texture.get(), nullptr, &destRect);

    }

};
#endif

