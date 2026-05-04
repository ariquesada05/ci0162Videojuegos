#ifndef CONTROLLER_MANAGER_HPP
#define CONTROLLER_MANAGER_HPP

#include <SDL2/SDL.h>

#include <map>
#include <string>

class ControllerManager
{
private:
  std::map<std::string, int> actionKeyName;
  std::map<int, bool> keyDown;
  std::map<std::string, int> mouseButtonName;
  std::map<int, bool> mouseButtonDown;

  int mousePosX = 0;
  int mousePosY = 0;

public:
  ControllerManager();
  ~ControllerManager();

  void Clear();

  // keyboard
  void AddActionKey(const std::string &action, int keyCode);
  void KeyDown(int keyCode);
  void KeyUp(int keyCode);
  bool IsActionActivated(const std::string &action);

  // mouse
  void AddMouseButton(const std::string &action, int mouseButton);
  void MouseButtonDown(int mouseButton);
  void MouseButtonUp(int mouseButton);
  bool IsMouseButtonActivated(const std::string &action);

  void SetMousePos(int x, int y);
  std::tuple<int, int> GetMousePos();
};

#endif // CONTROLLER_MANAGER_HPP