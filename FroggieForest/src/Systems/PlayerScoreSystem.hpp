/**
 * @file PlayerScoreSystem.hpp
 * @brief Player score display system
 */

#ifndef PLAYERSCORESYSTEM_HPP
#define PLAYERSCORESYSTEM_HPP

#include <string>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
 * @class PlayerScoreSystem
 * @brief Manages player score display
 */
class PlayerScoreSystem : public System
{
    TTF_Font* font;
    const int fontSize = 32;
    const char* fontPath = "assets/fonts/VarelaRound-Regular.ttf";
    const int margin = 10;
    const char* scorePrefix = "Score: ";

    public:
    /**
     * @brief Construct a PlayerScoreSystem
     * @throws std::runtime_error If font loading fails
     */
    PlayerScoreSystem() {
        // Load the font
        font = TTF_OpenFont(fontPath, fontSize);
        if (!font) {
            throw std::runtime_error("Failed to load font: " + std::string(TTF_GetError()));
        }

        if (TTF_Init() != 0) {
            throw std::runtime_error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
        }

    }

    ~PlayerScoreSystem() {
        if(font) {
            TTF_CloseFont(font);
        }
        TTF_Quit();
    }

    void Update(SDL_Renderer* renderer, int score) {
       
        int windowWidth, windowHeight;
        SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

        std::string scoreText = scorePrefix + std::to_string(score);

        SDL_Surface* surface = TTF_RenderText_Blended(font, scoreText.c_str(), {0, 0, 0, 0});

        if (!surface) {
            throw std::runtime_error("Failed to render text: " + std::string(TTF_GetError()));
            return;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (!texture) {
            SDL_FreeSurface(surface);
            throw std::runtime_error("Failed to create texture: " + std::string(SDL_GetError()));
            return;
        }

        SDL_Rect destRect {
            windowWidth - margin - surface->w, //right align with margin
            margin,
            surface->w,
            surface->h
        };

        SDL_RenderCopy(renderer, texture, nullptr, &destRect);

        // Clean up
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
};


#endif // PLAYERSCORESYSTEM_HPP