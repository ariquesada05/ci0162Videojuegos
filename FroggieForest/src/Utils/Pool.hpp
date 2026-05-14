/**
 * @file Pool.hpp
 * @brief Object pooling utility for performance
 * 
 * Provides generic object pooling to reuse allocated memory.
 */

#ifndef POOL_HPP
#define POOL_HPP

#include <vector>

/**
 * @class IPool
 * @brief Abstract base class for object pools
 */
class IPool
{
public:
  /**
   * @brief Destroy the pool
   */
  virtual ~IPool() = default;
};

/**
 * @class Pool
 * @brief Generic object pool template
 * 
 * @tparam TComponent The type of objects to pool
 * 
 * Manages a vector of components, providing methods to add, 
 * remove, and retrieve objects efficiently.
 */
template <typename TComponent>
class Pool : public IPool
{
private:
  std::vector<TComponent> data; ///< Pooled objects

public:
  /**
   * @brief Construct a pool with initial size
   * @param size Initial pool size (default 1000)
   */
  Pool(int size = 1000)
  {
    data.resize(size);
  }

  /**
   * @brief Destroy the pool
   */
  virtual ~Pool() = default;

  /**
   * @brief Check if pool is empty
   * @return bool True if pool contains no objects
   */
  bool isEmpty() const
  {
    return data.empty();
  }

  /**
   * @brief Get the pool size
   * @return int Number of objects in pool
   */
  int getSize() const
  {
    return data.size();
  }

  /**
   * @brief Resize the pool
   * @param size New pool size
   */
  void resize(int size)
  {
    data.resize(size);
  }

  /**
   * @brief Clear all objects from pool
   */
  void clear()
  {
    data.clear();
  }

  /**
   * @brief Add object to pool
   * @param component Object to add
   */
  void add(const TComponent &component)
  {
    data.push_back(component);
  }

  /**
   * @brief Set object at index
   * @param index Pool index
   * @param component Object to set
   */
  void set(size_t index, const TComponent &component)
  {
    data[index] = component;
  }

  /**
   * @brief Get object at index
   * @param index Pool index
   * @return TComponent& Reference to object
   */
  TComponent &get(size_t index)
  {
    return static_cast<TComponent &>(data[index]);
  }

  /**
   * @brief Array access operator
   * @param index Pool index
   * @return TComponent& Reference to object at index
   */
  TComponent &operator[](size_t index)
  {
    return static_cast<TComponent &>(data[index]);
  }
};

#endif // POOL_HPP
