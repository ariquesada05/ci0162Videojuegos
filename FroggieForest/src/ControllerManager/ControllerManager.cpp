#include "./ControllerManager.hpp"

#include <iostream>

ControllerManager::ControllerManager()
{
  std::cout << "[ControllerManager] Constructor" << std::endl;
}

ControllerManager::~ControllerManager()
{
  std::cout << "[ControllerManager] Destructor" << std::endl;
}

void ControllerManager::Clear()
{
  actionKeyName.clear();
  keyDown.clear();
}

// keyboard
void ControllerManager::AddActionKey(const std::string &action, int keyCode)
{
  actionKeyName.emplace(action, keyCode);
  keyDown.emplace(keyCode, false);
}

void ControllerManager::KeyDown(int keyCode)
{
  auto it = keyDown.find(keyCode);
  if (it != keyDown.end())
  {
    keyDown[keyCode] = true;
  }
}

void ControllerManager::KeyUp(int keyCode)
{
  auto it = keyDown.find(keyCode);
  if (it != keyDown.end())
  {
    keyDown[keyCode] = false;
  }
}

bool ControllerManager::IsActionActivated(const std::string &action)
{
  auto it = actionKeyName.find(action);
  if (it != actionKeyName.end())
  {
    int keyCode = actionKeyName[action];
    return keyDown[keyCode];
  }

  return false;
}

void ControllerManager::AddMouseButton(const std::string &action, int mouseButton)
{
  mouseButtonName.emplace(action, mouseButton);
  mouseButtonDown.emplace(mouseButton, false);
}

void ControllerManager::MouseButtonDown(int mouseButton)
{
  auto it = mouseButtonDown.find(mouseButton);
  if (it != mouseButtonDown.end())
  {
    mouseButtonDown[mouseButton] = true;
  }
}

void ControllerManager::MouseButtonUp(int mouseButton)
{
  auto it = mouseButtonDown.find(mouseButton);
  if (it != mouseButtonDown.end())
  {
    mouseButtonDown[mouseButton] = false;
  }
}

bool ControllerManager::IsMouseButtonActivated(const std::string &action)
{
  auto it = mouseButtonName.find(action);
  if (it != mouseButtonName.end())
  {
    int mouseButton = mouseButtonName[action];
    return mouseButtonDown[mouseButton];
  }
  return false;
}

void ControllerManager::SetMousePos(int x, int y)
{
  mousePosX = x;
  mousePosY = y;
}

std::tuple<int, int> ControllerManager::GetMousePos()
{
  return {mousePosX, mousePosY};
}
