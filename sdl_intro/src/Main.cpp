#include <SDL2/SDL.h>

#include <iostream>
#include <glm/glm.hpp>
#include <sol/sol.hpp>

int main(int argc, char* argv[]) { //whitout the args it didnt work
    std::cout << "Intro a SDL" << std::endl;

    glm::vec2 pos=glm::vec2(40, 30);

    sol::state lua;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    int width = 800;
    int height = 600;

    bool isRunning = true;

    SDL_Rect rect{ //rectangle to be drawn
        (width / 2) - 25, //x position of the rectangle
        (height / 2) - 25, //y position of the rectangle        
        50, //width of the rectangle
        50 //height of the rectangle
    };


    //initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL: " << std::endl;
    }

    //site where the window will be created
    window = SDL_CreateWindow(
        "Intro a SDL", // title of the window
        SDL_WINDOWPOS_CENTERED, //x position of the window
        SDL_WINDOWPOS_CENTERED, //y position of the window
        width,
        height,
        SDL_WINDOW_SHOWN
    ); //flags

    //renderer creation
    renderer = SDL_CreateRenderer(window, 
        -1, //window driver, index of the rendering driver
        0 //flags
    ); 

    while (isRunning) {
        // register who stores the events data 
        SDL_Event sdlEvent;

        //SDLPollEvent gets the events from the event queue and stores them in the variable or register SDL_Event type
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT: //when the user clicks the close button of the window
                    isRunning = false;
                    break;
                case SDL_KEYDOWN: //when the user presses a key
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) { //if the key is escape
                        isRunning = false;
                    }
                    break;
            }
        }

        //set the color which will be used to paint the screen.
        SDL_SetRenderDrawColor(renderer, 255, 209, 220, 1); //red, green, blue, alpha

        //clear the screen with the color set
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 150, 10, 250, 255);

        //draw the rectangle
        SDL_RenderFillRect(renderer, &rect);

        //update the screen
        SDL_RenderPresent(renderer);
    }
    // free recurses 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    //like a destructor, it will free all the recurses used by SDL (it is bc is c, not c++)
    SDL_Quit();

    return 0;

}