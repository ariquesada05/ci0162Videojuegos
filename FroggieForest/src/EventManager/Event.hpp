/**
 * @file Event.hpp
 * @brief Base class for all events in the event system
 */

#ifndef EVENT_HPP
#define EVENT_HPP

/**
 * @class Event
 * @brief Base class for all game events
 * 
 * This is the abstract base class for all events in the event system.
 * Derived classes should inherit from this and add their own specific data.
 */
class Event
{
public:
  /**
   * @brief Construct a new Event
   */
  Event() = default;
};

#endif // EVENT_HPP