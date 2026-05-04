#include "./SceneLoader.hpp"

#include <glm/glm.hpp>
#include <iostream>
#include <sstream>

#include "../Components/CircleColiderComponent.hpp"
#include "../Components/ClickableComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/CameraFollowComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../Game/Game.hpp"

SceneLoader::SceneLoader()
{
  std::cout << "[SceneLoader] Constructor" << std::endl;
}

SceneLoader::~SceneLoader()
{
  std::cout << "[SceneLoader] Destructor" << std::endl;
}

void SceneLoader::LoadScene(const std::string &scenePath, sol::state &lua,
                            std::unique_ptr<AnimationManager> &animationManager,
                            std::unique_ptr<AssetManager> &assetManager,
                            std::unique_ptr<ControllerManager> &controllerManager,
                            std::unique_ptr<Registry> &registry, SDL_Renderer *renderer)
{
  sol::load_result script_result = lua.load_file(scenePath);
  if (!script_result.valid())
  {
    sol::error error = script_result;
    std::string err = error.what();
    std::cerr << "[Scene Loader] " << err << std::endl;
    return;
  }

  lua.script_file(scenePath);

  sol::table scene = lua["scene"];

  sol::table sprites = scene["sprites"];
  LoadSprites(renderer, sprites, assetManager);

  sol::table animations = scene["animations"];
  LoadAnimations(animations, animationManager);

  sol::table fonts = scene["fonts"];
  LoadFonts(fonts, assetManager);

  sol::table keys = scene["keys"];
  LoadKeys(keys, controllerManager);

  sol::table buttons = scene["buttons"];
  LoadButtons(buttons, controllerManager);

  sol::table maps = scene["maps"];
  LoadMap(maps, registry);

  sol::table entities = scene["entities"];
  LoadEntities(lua, entities, registry);

  std::cout << "[SceneLoader] Scene loaded" << std::endl;
}

void SceneLoader::LoadSprites(SDL_Renderer *renderer, sol::table sprites, std::unique_ptr<AssetManager> &assetManager)
{
  int index = 0;
  while (true)
  {
    sol::optional<sol::table> hasSprite = sprites[index];
    if (hasSprite == sol::nullopt)
    {
      break;
    }

    sol::table sprite = sprites[index];
    std::string id = sprite["assetId"];
    std::string path = sprite["filePath"];

    assetManager->AddTexture(renderer, id, path);

    index++;
  }
}

void SceneLoader::LoadAnimations(const sol::table &animations, std::unique_ptr<AnimationManager> &animationManager)
{
  int index = 0;
  while (true)
  {
    sol::optional<sol::table> hasAnimation = animations[index];
    if (hasAnimation == sol::nullopt)
    {
      break;
    }
    sol::table animation = animations[index];
    std::string animationId = animation["animation_id"];
    std::string textureId = animation["texture_id"];
    int width = animation["w"];
    int height = animation["h"];
    int numFrames = animation["num_frames"];
    int speedRate = animation["speed_rate"];
    bool isLoop = animation["is_loop"];

    animationManager->addAnimation(animationId, textureId, width, height, numFrames, speedRate, isLoop);

    index++;
  }
}

void SceneLoader::LoadKeys(const sol::table &keys, std::unique_ptr<ControllerManager> &controllerManager)
{
  int index = 0;
  while (true)
  {
    sol::optional<sol::table> hasKey = keys[index];
    if (hasKey == sol::nullopt)
    {
      break;
    }

    sol::table key = keys[index];
    std::string keyName = key["action"];
    int keyCode = key["key"];

    controllerManager->AddActionKey(keyName, keyCode);

    index++;
  }
}

void SceneLoader::LoadEntities(sol::state &lua, const sol::table &entities, std::unique_ptr<Registry> &registry)
{
  int index = 0;
  while (true)
  {
    sol::optional<sol::table> hasEntities = entities[index];
    if (hasEntities == sol::nullopt)
    {
      break;
    }

    sol::table entity = entities[index];
    Entity newEntity = registry->createEntity();

    sol::optional<sol::table> hasComponents = entity["components"];

    if (hasComponents != sol::nullopt)
    {
      sol::table components = hasComponents.value();

      //* AnimationComponent
      sol::optional<sol::table> hasAnimationComponent = components["animation"];
      if (hasAnimationComponent != sol::nullopt)
      {
        newEntity.addComponent<AnimationComponent>(
            components["animation"]["num_frames"],
            components["animation"]["speed_rate"],
            components["animation"]["is_loop"]);
      }

      //* CameraFollowComponent
      sol::optional<sol::table> hasCameraFollowComponent = components["camera_follow"];
      if (hasCameraFollowComponent != sol::nullopt)
      {
        newEntity.addComponent<CameraFollowComponent>();
      }

      //* BoxColliderComponent
      sol::optional<sol::table> hasBoxColliderComponent = components["box_collider"];
      if (hasBoxColliderComponent != sol::nullopt)
      {
        newEntity.addComponent<BoxColliderComponent>(
            components["box_collider"]["width"],
            components["box_collider"]["height"],
            glm::vec2(
                components["box_collider"]["offset"]["x"],
                components["box_collider"]["offset"]["y"]));
      }

      //* CircleColliderComponent
      sol::optional<sol::table> hasCircleColliderComponent = components["circle_collider"];
      if (hasCircleColliderComponent != sol::nullopt)
      {
        newEntity.addComponent<CircleColiderComponent>(
            components["circle_collider"]["radius"],
            components["circle_collider"]["width"],
            components["circle_collider"]["height"]);
      }

      //* ClickableComponent
      sol::optional<sol::table> hasClickableComponent = components["clickable"];
      if (hasClickableComponent != sol::nullopt)
      {
        newEntity.addComponent<ClickableComponent>();
      }

      //* RigidBodyComponent
      sol::optional<sol::table> hasRigidBodyComponent = components["rigid_body"];
      if (hasRigidBodyComponent != sol::nullopt)
      {
        newEntity.addComponent<RigidBodyComponent>(
            components["rigid_body"]["is_dynamic"],
            components["rigid_body"]["is_solid"],
            components["rigid_body"]["mass"] //
        );
      }

      //* SpriteComponent
      sol::optional<sol::table> hasSpriteComponent = components["sprite"];
      if (hasSpriteComponent != sol::nullopt)
      {
        newEntity.addComponent<SpriteComponent>(
            components["sprite"]["assetId"],
            components["sprite"]["width"],
            components["sprite"]["height"],
            components["sprite"]["src_rect"]["x"],
            components["sprite"]["src_rect"]["y"]);
      }

      //* TextComponent
      sol::optional<sol::table> hasTextComponent = components["text"];
      if (hasTextComponent != sol::nullopt)
      {
        newEntity.addComponent<TextComponent>(
            components["text"]["text"],
            components["text"]["fontId"],
            components["text"]["r"],
            components["text"]["g"],
            components["text"]["b"],
            components["text"]["a"]);
      }

      //* TagComponent
      sol::optional<sol::table> hasTagComponent = components["tag"];
      if (hasTagComponent != sol::nullopt)
      {
        std::string tag = components["tag"]["tag"];
        newEntity.addComponent<TagComponent>(tag);
      }

      //* TransformComponent
      sol::optional<sol::table> hasTransformComponent = components["transform"];
      if (hasTransformComponent != sol::nullopt)
      {
        newEntity.addComponent<TransformComponent>(
            glm::vec2(
                components["transform"]["position"]["x"],
                components["transform"]["position"]["y"]),
            glm::vec2(
                components["transform"]["scale"]["x"],
                components["transform"]["scale"]["y"]),
            components["transform"]["rotation"]);
      }

      //* ScriptComponent
      sol::optional<sol::table> hasScriptComponent = components["script"];
      if (hasScriptComponent != sol::nullopt)
      {
        lua["on_awake"] = sol::nil;
        lua["on_click"] = sol::nil;
        lua["update"] = sol::nil;
        lua["on_collision"] = sol::nil;

        std::string path = components["script"]["path"];
        lua.script_file(path);

        sol::optional<sol::function> hasOnAwake = lua["on_awake"];
        if (hasOnAwake != sol::nullopt)
        {
          lua["this"] = newEntity;
          sol::function onAwake = lua["on_awake"];
          onAwake();
        }

        sol::optional<sol::function> hasOnCollision = lua["on_collision"];
        sol::function onCollision = sol::nil;
        if (hasOnCollision != sol::nullopt)
        {
          onCollision = lua["on_collision"];
        }

        sol::optional<sol::function> hasOnClick = lua["on_click"];
        sol::function onClick = sol::nil;
        if (hasOnClick != sol::nullopt)
        {
          onClick = lua["on_click"];
        }

        sol::optional<sol::function> hasUpdate = lua["update"];
        sol::function update = sol::nil;
        if (hasUpdate != sol::nullopt)
        {
          update = lua["update"];
        }

        newEntity.addComponent<ScriptComponent>(update, onClick, onCollision);
      }
    }
    index++;
  }
}

void SceneLoader::LoadFonts(sol::table fonts, std::unique_ptr<AssetManager> &assetManager)
{
  int index = 0;
  while (true)
  {
    sol::optional<sol::table> hasFont = fonts[index];
    if (hasFont == sol::nullopt)
    {
      break;
    }

    sol::table font = fonts[index];
    std::string id = font["fontId"];
    std::string path = font["filePath"];
    int fontSize = font["fontSize"];

    assetManager->AddFont(id, path, fontSize);

    index++;
  }
}

void SceneLoader::LoadButtons(sol::table buttons, std::unique_ptr<ControllerManager> &controllerManager)
{
  int index = 0;
  while (true)
  {
    sol::optional<sol::table> hasButton = buttons[index];
    if (hasButton == sol::nullopt)
    {
      break;
    }

    sol::table button = buttons[index];
    std::string name = button["name"];
    int buttonCode = button["button"];

    controllerManager->AddMouseButton(name, buttonCode);

    index++;
  }
}

void SceneLoader::LoadMap(const sol::table map, std::unique_ptr<Registry> &registry)
{
  sol::optional<int> hasWidth = map["width"];
  if (hasWidth != sol::nullopt)
  {
    Game::GetInstance().mapWidth = map["width"];
  }

  sol::optional<int> hasHeight = map["height"];
  if (hasHeight != sol::nullopt)
  {
    Game::GetInstance().mapHeight = map["height"];
  }

  sol::optional<std::string> hasPath = map["map_path"];
  if (hasPath != sol::nullopt)
  {
    std::string path = map["map_path"];

    // Se carga el documento xml que contiene la información del mapa
    tinyxml2::XMLDocument xmlmap;

    if (xmlmap.LoadFile(path.c_str()) != tinyxml2::XML_SUCCESS)
    {
      std::cerr << "[SceneLoader] Error loading map XML file" << std::endl;
      return;
    }

    // Extraer la raiz del documento xml
    tinyxml2::XMLElement *root = xmlmap.RootElement();

    // Extraer las dimensiones del mapa
    int tWidth, tHeight, mWidth, mHeight;
    root->QueryIntAttribute("tilewidth", &tWidth);
    root->QueryIntAttribute("tileheight", &tHeight);
    root->QueryIntAttribute("width", &mWidth);
    root->QueryIntAttribute("height", &mHeight);

    // Calcular dimensiones del mapa
    Game::GetInstance().mapWidth = tWidth * mWidth;
    Game::GetInstance().mapHeight = tHeight * mHeight;

    // Se carga el documento con la información de los tiles
    std::string tilePath = map["tile_path"];
    std::string tileName = map["tile_name"];

    tinyxml2::XMLDocument xmltileset;
    xmltileset.LoadFile(tilePath.c_str());

    tinyxml2::XMLElement *xmlTilesetRoot = xmltileset.RootElement();

    // Extraer cantidad de columnas
    int columns;
    xmlTilesetRoot->QueryIntAttribute("columns", &columns);

    // Se obtiene la lista de layers
    tinyxml2::XMLElement *layerElement = root->FirstChildElement("layer");

    while (layerElement)
    {
      LoadLayer(registry, layerElement, tWidth, tHeight, mWidth, tileName, columns);
      layerElement = layerElement->NextSiblingElement("layer");
    }

    // Se obtiene la lista de object groups
    tinyxml2::XMLElement *objectGroup = root->FirstChildElement("objectgroup");

    while (objectGroup)
    {
      const char *objectGroupName;
      std::string name;
      objectGroup->QueryStringAttribute("name", &objectGroupName);
      name = objectGroupName;

      if (name.compare("colliders") == 0)
      {
        LoadColliders(registry, objectGroup);
      }

      objectGroup = objectGroup->NextSiblingElement("objectgroup");
    }
  }
}

void SceneLoader::LoadLayer(std::unique_ptr<Registry> &registry, tinyxml2::XMLElement *layerElement,
                            int tWidth, int tHeight, int mWidth, const std::string &tileSet, int columns)
{
  tinyxml2::XMLElement *xmlData = layerElement->FirstChildElement("data");
  const char *data = xmlData->GetText();

  std::stringstream tmpNumber;
  int pos = 0;
  int tileNumber = 0;

  while (true)
  {
    if (data[pos] == '\0')
    {
      break;
    }
    if (isdigit(data[pos]))
    {
      tmpNumber << data[pos];
    }
    else if (!isdigit(data[pos]) && tmpNumber.str().length() != 0)
    {
      int tileId = std::stoi(tmpNumber.str());
      if (tileId > 0)
      {
        Entity tile = registry->createEntity();
        tile.addComponent<TransformComponent>(
            glm::vec2((tileNumber % mWidth) * tWidth,
                      (tileNumber / mWidth) * tHeight) //
        );
        tile.addComponent<SpriteComponent>(
            tileSet,
            tWidth,
            tHeight,
            ((tileId - 1) % columns) * tWidth,
            ((tileId - 1) / columns) * tHeight //
        );
      }

      tileNumber++;
      tmpNumber.str("");
    }
    pos++;
  }
}

void SceneLoader::LoadColliders(std::unique_ptr<Registry> &registry, tinyxml2::XMLElement *objectGroup)
{
  tinyxml2::XMLElement *object = objectGroup->FirstChildElement("object");

  while (object != nullptr)
  {
    // Declarar variables
    const char *name;
    std::string tag;
    int x, y, w, h;

    // Extraer atributos
    object->QueryStringAttribute("name", &name);
    tag = name;

    // Extraer posición
    object->QueryIntAttribute("x", &x);
    object->QueryIntAttribute("y", &y);

    // Extraer dimensiones
    object->QueryIntAttribute("width", &w);
    object->QueryIntAttribute("height", &h);

    // Crear entidad
    Entity collider = registry->createEntity();
    collider.addComponent<TagComponent>(tag);
    collider.addComponent<TransformComponent>(
        glm::vec2(x, y));
    collider.addComponent<BoxColliderComponent>(w, h);
    collider.addComponent<RigidBodyComponent>(false, true, 9999999999.0f);

    object = object->NextSiblingElement("object");
  }
}
