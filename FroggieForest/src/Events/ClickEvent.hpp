/**
 * @file ClickEvent.hpp
 * @brief Mouse click event
 */

#ifndef CLICK_EVENT_HPP
#define CLICK_EVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

/**
 * @class ClickEvent
 * @brief Event fired when the mouse is clicked
 * 
 * Contains information about which mouse button was clicked and the position.
 */
class ClickEvent : public Event
{
public:
  int buttonCode; ///< SDL mouse button code (SDL_BUTTON_LEFT, etc.)
  int posX;       ///< X coordinate of the click
  int posY;       ///< Y coordinate of the click

  /**
   * @brief Construct a new ClickEvent
   * @param buttonCode The SDL mouse button code
   * @param posX The X coordinate of the click
   * @param posY The Y coordinate of the click
   */
  ClickEvent(int buttonCode = 0, int posX = 0, int posY = 0)
  {
    this->buttonCode = buttonCode;
    this->posX = posX;
    this->posY = posY;
  }
};

#endif // CLICK_EVENT_HPP