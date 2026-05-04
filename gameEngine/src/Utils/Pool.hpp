#ifndef POOL_HPP
#define POOL_HPP

#include <vector>

class IPool
{
public:
  virtual ~IPool() = default;
};

template <typename TComponent>
class Pool : public IPool // Hereda de IPool
{
private:
  std::vector<TComponent> data;

public:
  Pool(int size = 1000)
  {
    data.resize(size);
  }
  virtual ~Pool() = default;

  bool isEmpty() const
  {
    return data.empty();
  }

  int getSize() const
  {
    return data.size();
  }

  void resize(int size)
  {
    data.resize(size);
  }

  void clear()
  {
    data.clear();
  }

  void add(const TComponent &component)
  {
    data.push_back(component);
  }

  void set(size_t index, const TComponent &component)
  {
    data[index] = component;
  }

  TComponent &get(size_t index)
  {
    return static_cast<TComponent &>(data[index]);
  }

  TComponent &operator[](size_t index)
  {
    return static_cast<TComponent &>(data[index]);
  }
};

#endif // POOL_HPP
