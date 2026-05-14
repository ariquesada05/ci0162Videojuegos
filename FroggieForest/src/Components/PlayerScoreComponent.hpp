/**
 * @file PlayerScoreComponent.hpp
 * @brief Player score tracking component
 */

#ifndef PLAYERSCORECOMPONENT_HPP
#define PLAYERSCORECOMPONENT_HPP

/**
 * @struct PlayerScoreComponent
 * @brief Stores the player's current score
 * 
 * Tracks the player's score value during gameplay.
 */
struct PlayerScoreComponent {
    int playerScore; ///< Current player score value

    /**
     * @brief Construct a PlayerScoreComponent
     * @param playerScore The initial score (default: 0)
     */
    PlayerScoreComponent(int playerScore = 0){
        this->playerScore = playerScore;
    }
};

#endif 