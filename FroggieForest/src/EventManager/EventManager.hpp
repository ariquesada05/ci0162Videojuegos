/**
 * @file EventManager.hpp
 * @brief Event dispatcher and subscription system
 * 
 * Provides a publish-subscribe system for game events, allowing systems to
 * subscribe to and respond to specific event types.
 */

#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <map>
#include <list>
#include <map>
#include <functional>
#include <memory>
#include <typeindex>
#include <iostream>
#include "Event.hpp"

/**
 * @class IEventCallback
 * @brief Base interface for event callbacks
 * 
 * Defines the interface that all event callbacks must implement.
 */
class IEventCallback
{
private:
  virtual void Call(Event &event) = 0;

public:
  virtual ~IEventCallback() = default;

  /**
   * @brief Execute the callback with the given event
   * @param event The event to pass to the callback
   */
  void Execute(Event &event)
  {
    Call(event);
  }
};

/**
 * @class EventCallback
 * @brief Template implementation of event callbacks
 * 
 * @tparam TOwner The class type that owns the callback method
 * @tparam TEvent The event type this callback handles
 * 
 * Wraps a member function to be called when a specific event type is emitted.
 */
template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback
{
private:
  typedef void (TOwner::*CallbackFunction)(TEvent &);

  TOwner *ownerInstance;            ///< Pointer to the object that owns the callback
  CallbackFunction callbackFunction; ///< Pointer to the member function

  virtual void Call(Event &event) override
  {
    std::invoke(callbackFunction, ownerInstance, static_cast<TEvent &>(event));
  }

public:
  /**
   * @brief Construct a new EventCallback
   * @param ownerInstance Pointer to the object that owns the callback method
   * @param callbackFunction Pointer to the member function to call
   */
  EventCallback(TOwner *ownerInstance, CallbackFunction callbackFunction)
  {
    this->ownerInstance = ownerInstance;
    this->callbackFunction = callbackFunction;
  }

  virtual ~EventCallback() = default;
};

/** @brief List of event callbacks */
typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

/**
 * @class EventManager
 * @brief Central event management system
 * 
 * Manages event subscriptions and dispatching. Uses a publish-subscribe pattern
 * to decouple event producers from consumers.
 */
class EventManager
{
private:
  std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers; ///< Subscribers for each event type

public:
  /**
   * @brief Construct a new EventManager
   */
  EventManager()
  {
    std::cout << "[EventManager] Constructor" << std::endl;
  }

  /**
   * @brief Destroy the EventManager
   */
  ~EventManager()
  {
    std::cout << "[EventManager] Destructor" << std::endl;
  }

  /**
   * @brief Clear all subscribers
   */
  void Reset()
  {
    subscribers.clear();
  }

  /**
   * @brief Subscribe to an event type
   * 
   * @tparam TEvent The event type to subscribe to
   * @tparam TOwner The class type that owns the callback method
   * @param ownerInstance Pointer to the object instance
   * @param callbackFunction Pointer to the member function to call when the event is emitted
   */
  template <typename TEvent, typename TOwner>
  void SubscribeToEvent(TOwner *ownerInstance, void (TOwner::*callbackFunction)(TEvent &))
  {
    if (!subscribers[typeid(TEvent)])
    {
      subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
    }
    auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);
    subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
  }

  /**
   * @brief Emit an event to all subscribers
   * 
   * @tparam TEvent The event type to emit
   * @tparam TArgs Argument types for the event constructor
   * @param args Arguments to pass to the event constructor
   */
  template <typename TEvent, typename... TArgs>
  void EmitEvent(TArgs &&...args)
  {
    auto handlers = subscribers[typeid(TEvent)].get();
    if (handlers)
    {
      for (auto it = handlers->begin(); it != handlers->end(); it++)
      {
        auto handler = it->get();
        TEvent event(std::forward<TArgs>(args)...);
        handler->Execute(event);
      }
    }
  }
};


#endif // EVENT_MANAGER_HPP