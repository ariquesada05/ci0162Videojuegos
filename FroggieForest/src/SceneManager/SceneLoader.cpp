#include "./SceneLoader.hpp"

#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <filesystem>

#include "../Components/CircleColliderComponent.hpp"
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
#include "../AudioManager/AudioManager.hpp"
#include "../Components/EnemyColliderComponent.hpp"
#include "../Components/StateComponent.hpp"
#include "../Components/StatsComponent.hpp"
#include "../Components/PlayerScoreComponent.hpp"
#include "../Components/PlayerVelocity.hpp"
#include "../StatsManager/StatsManager.hpp"
#include "../Components/LapseComponent.hpp"
#include "../Components/AttackCycleComponent.hpp"
#include "../Components/DamageColliderComponent.hpp"


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
                            std::unique_ptr<AudioManager> &audioManager,
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

  sol::table sounds = scene["sounds"];
  LoadSounds(sounds, audioManager);

  sol::table music = scene["music"];
  LoadMusic(music, audioManager);

  sol::table animations = scene["animations"];
  LoadAnimations(animations, animationManager);

  if (sol::optional<sol::table> hasStats = scene["stats"];
    hasStats != sol::nullopt)
  {
    sol::table stats = hasStats.value();

    int index = 0;
    while (true)
    {
        sol::optional<sol::table> stat = stats[index];

        if (stat == sol::nullopt)
        {
            break;
        }

        std::string tag = stat.value()["tag"];
        int health = stat.value()["health"];
        int points = stat.value()["points"];
        int damage = stat.value()["damage"];

        StatsManager::GetInstance().AddStat(
            tag,
            StatsComponent(health, points, damage)
        );

        index++;
    }
    }
  
  if (const sol::optional<sol::table> hasDamageColliders = scene["damage_colliders"]) {
        const sol::table damageColliders = *hasDamageColliders;
        LoadDamageColliders(damageColliders);
    }

  sol::table fonts = scene["fonts"];
  LoadFonts(fonts, assetManager);

  sol::table keys = scene["keys"];
  LoadKeys(keys, controllerManager);

  // La tabla "buttons" es opcional: si la escena no la declara, sol recibiría
  // nil y reventaría al construir el sol::table ("type check failed in
  // constructor"). Se lee protegida, igual que "stats"/"damage_colliders".
  if (sol::optional<sol::table> hasButtons = scene["buttons"];
      hasButtons != sol::nullopt)
  {
    LoadButtons(hasButtons.value(), controllerManager);
  }

  sol::table maps = scene["maps"];
  LoadMap(maps, registry, lua);

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
    int offsetX = animation["offset_x"].get_or(0); // opcional; recentra frames anchos

    animationManager->addAnimation(animationId, textureId, width, height, numFrames, speedRate, isLoop, offsetX);

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

    while(true) {
        // std::cout << "loading entity" << std::endl;
        sol::optional<sol::table> hasEntity = entities[index];

        if(hasEntity == sol::nullopt) {
            break;
        }

        sol::table entity = entities[index];
        Entity newEntity = registry->createEntity();

        newEntity.removeComponent<TransformComponent>();
        newEntity.removeComponent<RigidBodyComponent>();
        newEntity.removeComponent<SpriteComponent>();
        newEntity.removeComponent<CircleColliderComponent>();
        newEntity.removeComponent<AnimationComponent>();
        newEntity.removeComponent<ScriptComponent>();
        newEntity.removeComponent<TextComponent>();
        newEntity.removeComponent<ClickableComponent>();
        newEntity.removeComponent<CameraFollowComponent>();
        newEntity.removeComponent<BoxColliderComponent>();
        newEntity.removeComponent<TagComponent>();
        newEntity.removeComponent<StateComponent>();
        
        LoadEntity(lua, newEntity, entity);

        index++;
      }
}

void SceneLoader::LoadEntity(sol::state &lua, Entity &newEntity, sol::table entityTable)
{
  sol::optional<sol::table> hasComponents = entityTable["components"];
  if (hasComponents == sol::nullopt) {
    return;
  }

  sol::table components = hasComponents.value();

  //* AnimationComponent
  if (sol::optional<sol::table> hasAnimationComponent = components["animation"];
      hasAnimationComponent != sol::nullopt)
  {
    newEntity.addComponent<AnimationComponent>(
        components["animation"]["num_frames"],
        components["animation"]["speed_rate"],
        components["animation"]["is_loop"]);
  }

  //* CameraFollowComponent
  if (sol::optional<sol::table> hasCameraFollowComponent = components["camera_follow"];
      hasCameraFollowComponent != sol::nullopt)
  {
    newEntity.addComponent<CameraFollowComponent>();
  }

  //* BoxColliderComponent
  if (sol::optional<sol::table> hasBoxColliderComponent = components["box_collider"];
      hasBoxColliderComponent != sol::nullopt)
  {
    newEntity.addComponent<BoxColliderComponent>(
      
        components["box_collider"]["width"],
        components["box_collider"]["height"],
        glm::vec2(
            components["box_collider"]["offset"]["x"],
            components["box_collider"]["offset"]["y"]));
          std::cout << "ADDING DAMAGE TO ENTITY ID: "
          << newEntity.getID()
          << std::endl;        

        newEntity.addComponent<DamageColliderComponent>(
        components["box_collider"]["width"],
        components["box_collider"]["height"]

      );
  }

  //* CircleColliderComponent
  if (sol::optional<sol::table> hasCircleColliderComponent = components["circleCollider"];
      hasCircleColliderComponent != sol::nullopt)
  {
    newEntity.addComponent<CircleColliderComponent>(
        components["circleCollider"]["radius"],
        components["circleCollider"]["width"],
        components["circleCollider"]["height"]);
  }

  //* ClickableComponent
  if (sol::optional<sol::table> hasClickableComponent = components["clickable"];
      hasClickableComponent != sol::nullopt)
  {
    newEntity.addComponent<ClickableComponent>();
  }

//* TagComponent
if (sol::optional<sol::table> hasTagComponent = components["tag"];
    hasTagComponent != sol::nullopt)
{
    std::string tag = components["tag"]["tag"];

    newEntity.addComponent<TagComponent>(tag);

    if (StatsManager::GetInstance().HasStat(tag))
    {
        auto stats =
            StatsManager::GetInstance().GetStat(tag);

        newEntity.addComponent<StatsComponent>(
            stats.Health,
            stats.Points,
            stats.Damage
        );

        std::cout << "STATS ADDED TO ENTITY: "
                  << tag
                  << std::endl;
    }
}
 


  //* RigidBodyComponent
  if (sol::optional<sol::table> hasRigidBodyComponent = components["rigid_body"];
      hasRigidBodyComponent != sol::nullopt)
  {
    newEntity.addComponent<RigidBodyComponent>(
        components["rigid_body"]["is_dynamic"],
        components["rigid_body"]["is_solid"],
        components["rigid_body"]["mass"]);
         
  }

  //* SpriteComponent
  if (sol::optional<sol::table> hasSpriteComponent = components["sprite"];
      hasSpriteComponent != sol::nullopt)
  {
    // z_index es opcional; por defecto 0 (misma capa que el fondo/tiles)
    int zIndex = components["sprite"]["z_index"].get_or(0);

    newEntity.addComponent<SpriteComponent>(
        components["sprite"]["assetId"],
        components["sprite"]["width"],
        components["sprite"]["height"],
        components["sprite"]["src_rect"]["x"],
        components["sprite"]["src_rect"]["y"],
        zIndex);
  }

  //* TextComponent
  if (sol::optional<sol::table> hasTextComponent = components["text"];
      hasTextComponent != sol::nullopt)
  {
    newEntity.addComponent<TextComponent>(
        components["text"]["text"],
        components["text"]["fontId"],
        components["text"]["r"],
        components["text"]["g"],
        components["text"]["b"],
        components["text"]["a"]);
  }

  //* TransformComponent
  if (sol::optional<sol::table> hasTransformComponent = components["transform"];
      hasTransformComponent != sol::nullopt)
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
  if (sol::optional<sol::table> hasScriptComponent = components["script"];
      hasScriptComponent != sol::nullopt)
  {
    sol::table scriptTable = hasScriptComponent.value();

    sol::optional<std::string> hasPath = scriptTable["path"];
    if (hasPath == sol::nullopt) {
      std::cerr << "[SceneLoader] Script component without 'path' field\n";
      return;
    }

    lua["on_init"] = sol::nil;
    lua["on_click"] = sol::nil;
    lua["update"] = sol::nil;
    lua["on_collision"] = sol::nil;
    lua["on_damage"] = sol::nil;

    std::string path = hasPath.value();
    std::cout << "[SceneLoader] Loading script: " << path << std::endl;
  

    sol::load_result script_result = lua.load_file(path);
    if (!script_result.valid()) {
      sol::error err = script_result;
      std::cerr << "[SceneLoader] Error loading script " << path
                << ": " << err.what() << std::endl;
      return;
    }

    lua.script_file(path);

    sol::function onInit= sol::nil;
    if (sol::optional<sol::function> hasOnInit = lua["on_init"];
        hasOnInit != sol::nullopt)
    {
      onInit = hasOnInit.value();
      lua["this"] = newEntity;
    onInit();
      
    }
    sol::function onCollision = sol::nil;
    if (sol::optional<sol::function> hasOnCollision = lua["on_collision"];
        hasOnCollision != sol::nullopt)
    {
      onCollision = hasOnCollision.value();
    }

    sol::function onClick = sol::nil;
    if (sol::optional<sol::function> hasOnClick = lua["on_click"];
        hasOnClick != sol::nullopt)
    {
      onClick = hasOnClick.value();
    }

    sol::function onDamage = sol::nil;
    if (sol::optional<sol::function> hasOnDamage = lua["on_damage"];
        hasOnDamage != sol::nullopt)
    {
      onDamage = hasOnDamage.value();
    }

    sol::function update = sol::nil;
    if (sol::optional<sol::function> hasUpdate = lua["update"];
        hasUpdate != sol::nullopt)
    {
      update = hasUpdate.value();
    }

    newEntity.addComponent<ScriptComponent>(update, onClick, onInit, onCollision, onDamage);
  }

  //player velocity component
  if (sol::optional<sol::table> hasPlayerVelocityComponent = components["player_velocity"];
      hasPlayerVelocityComponent != sol::nullopt)
  {
    int velocity = (int)components["player_velocity"]["playerVelocity"];
    newEntity.addComponent<PlayerVelocity>(velocity);
  }


  //Player score component
  if (sol::optional<sol::table> hasPlayerScoreComponent = components["player_score"];
      hasPlayerScoreComponent != sol::nullopt)
  {
    int score = (int)components["player_score"]["playerScore"];
    newEntity.addComponent<PlayerScoreComponent>(score);
  }

  //*lapse component
  if (sol::optional<sol::table> hasLapseComponent = components["lapse"];
      hasLapseComponent != sol::nullopt)
  {
    newEntity.addComponent<LapseComponent>();
    int index = 0;

    auto& component = newEntity.getComponent<LapseComponent>();
    while (true)
    {
      sol::optional<sol::table> lapse = components["lapse"][index];
      if (lapse == sol::nullopt)
      {
        break;
      }

      const std::string& name = lapse.value()["name"];

      if (name == "global")
      {
        component.Global.TimeLimit = (double)lapse.value()["seconds"];
      }
      else
      {
        component.PlayerActions.insert({name, 
          TimingTracer{lapse.value()["seconds"], 
            (double)lapse.value()["seconds"]
          }
        }
      );
      }

      index++;
    }
  }

  //*attack cycle component
  if (sol::optional<sol::table> hasAttack = components["attacks"];
      hasAttack != sol::nullopt)
  {
    newEntity.addComponent<AttackCycleComponent>();
    auto& component = newEntity.getComponent<AttackCycleComponent>();

    int index = 0;
    while (true)
    {
      const sol::optional<sol::table> attack = components["attack"][index];
      if (attack == sol::nullopt)
      {
        break;
      }

      const std::string name = attack.value()["name"];
      const std::pair<int, int> awareness = {
        attack.value()["awareness"]["x"],
        attack.value()["awareness"]["y"]
      };
      component.Attacks.emplace_back(name, awareness);

      index++;
    }
  }
  
    if (newEntity.hasComponent<BoxColliderComponent>() &&
      newEntity.hasComponent<TagComponent>())
    {
      auto& tag = newEntity.getComponent<TagComponent>();

      if (tag.tag == "player" || tag.tag == "enemy01")
      {
          auto& box = newEntity.getComponent<BoxColliderComponent>();

          // Por defecto el damage collider iguala al box collider.
          int dcWidth = box.width;
          int dcHeight = box.height;
          int dcOffsetX = 0;
          int dcOffsetY = 0;

          // Solo el jugador puede declarar un "damage_collider" explícito (con
          // tamaño/offset) para tener un hitbox de ataque más grande que su
          // cuerpo, sin afectar la física (que usa el box). Los enemigos
          // mantienen su damage collider igual al box, como antes.
          if (tag.tag == "player")
          {
              if (sol::optional<sol::table> hasDamageCollider = components["damage_collider"];
                  hasDamageCollider != sol::nullopt)
              {
                  dcWidth = components["damage_collider"]["width"].get_or(box.width);
                  dcHeight = components["damage_collider"]["height"].get_or(box.height);
                  dcOffsetX = components["damage_collider"]["offset"]["x"].get_or(0);
                  dcOffsetY = components["damage_collider"]["offset"]["y"].get_or(0);
              }
          }

          newEntity.addComponent<DamageColliderComponent>(
              dcWidth,
              dcHeight,
              dcOffsetX,
              dcOffsetY
          );

      }
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

void SceneLoader::LoadMap(const sol::table map, std::unique_ptr<Registry> &registry, sol::state &lua)
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
      }else if (name.compare("enemies") == 0)
      {
        LoadEnemiesColliders(registry, objectGroup);
      }else if (name.compare("spawn") == 0)
      {
        LoadEnemies(lua, objectGroup, registry);
      }else if (name.compare("platforms")==0)
      {
        LoadPlatforms(lua, objectGroup, registry);
      }else if (name.compare("items") == 0)
      {
          LoadItems(lua, objectGroup, registry);
      }
      else if (name.compare("traps") == 0)
      {
          LoadTraps(lua, objectGroup, registry);
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

void SceneLoader::LoadColliders(std::unique_ptr<Registry> &registry,
                                tinyxml2::XMLElement *objectGroup)
{
    tinyxml2::XMLElement *object = objectGroup->FirstChildElement("object");

    while (object != nullptr)
    {
        const char *name = nullptr;
        std::string tag = "unknown";

        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;

        object->QueryStringAttribute("name", &name);

        if (name != nullptr)
        {
            tag = name;
        }

        object->QueryIntAttribute("x", &x);
        object->QueryIntAttribute("y", &y);
        object->QueryIntAttribute("width", &w);
        object->QueryIntAttribute("height", &h);

        if (w <= 0 || h <= 0)
        {
            object = object->NextSiblingElement("object");
            continue;
        }

        std::cout << "COLLIDER LOADED -> tag: " << tag
                  << " x: " << x
                  << " y: " << y
                  << " w: " << w
                  << " h: " << h
                  << std::endl;

        Entity collider = registry->createEntity();

        collider.addComponent<TagComponent>(tag);

        collider.addComponent<TransformComponent>(
            glm::vec2(x, y));

        collider.addComponent<BoxColliderComponent>(w, h);

        collider.addComponent<RigidBodyComponent>(
            false,
            true,
            9999999999.0f);

        object = object->NextSiblingElement("object");
    }
}

void SceneLoader::LoadEnemiesColliders(std::unique_ptr<Registry> &registry, 
  tinyxml2::XMLElement *objectGroup)
{
  tinyxml2::XMLElement *object = objectGroup->FirstChildElement("object");

  //const float SCALE = 1.0f;

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
      //glm::vec2(SCALE, SCALE));
    collider.addComponent<EnemyColliderComponent>(w,h);
    collider.addComponent<RigidBodyComponent>(false, true, 9999999999.0f);

    object = object->NextSiblingElement("object");
  }
}


void SceneLoader::LoadEnemies(
    sol::state &lua,
    tinyxml2::XMLElement *objectGroup,
    std::unique_ptr<Registry> &registry)
{
    tinyxml2::XMLElement *object =
        objectGroup->FirstChildElement("object");

    std::vector<Entity> enemies;

    std::cout << "Loading enemies..." << std::endl;

    while (object != nullptr)
    {
        // Datos del objeto TMX
        const char *name;
        std::string tag;

        int x, y;

        object->QueryStringAttribute("name", &name);
        tag = name;

        object->QueryIntAttribute("x", &x);
        object->QueryIntAttribute("y", &y);

        // Crear entidad VACÍA
        Entity enemy = registry->createEntity();

        enemies.push_back(enemy);

        object = object->NextSiblingElement("object");
    }

    if (enemies.empty())
    {
        std::cout << "No enemies found in the scene."
                  << std::endl;
        return;
    }

    // Cargar tabla Lua
    sol::load_result load_result =
        lua.load_file("./assets/scripts/enemies.lua");

    if (!load_result.valid())
    {
        sol::error error = load_result;

        std::cerr << "Failed to load enemies script: "
                  << error.what()
                  << std::endl;

        return;
    }

    load_result();

    sol::object obj = lua["enemies"];

    if (!obj.is<sol::table>())
    {
        std::cerr << "Enemies data is not a table"
                  << std::endl;

        return;
    }

    sol::table enemiesTable = obj.as<sol::table>();

    // Reiniciar lectura de objetos TMX
    object = objectGroup->FirstChildElement("object");

    int index = 0;

    while (object != nullptr)
    {
        const char *name;
        std::string tag;

        int x, y;

        object->QueryStringAttribute("name", &name);
        tag = name;

        object->QueryIntAttribute("x", &x);
        object->QueryIntAttribute("y", &y);

        Entity enemy = enemies[index];

        // Obtener datos Lua
        sol::table enemyData = enemiesTable[tag];

        // Cargar TODOS los componentes desde Lua
        LoadEntity(lua, enemy, enemyData);

        // Ajustar posición desde TMX
        auto &transform =
            enemy.getComponent<TransformComponent>();

        transform.position = glm::vec2(x, y);

        // Estado extra
        enemy.addComponent<StateComponent>();

        object = object->NextSiblingElement("object");

        index++;
    }
}

void SceneLoader::LoadSounds(const sol::table &sounds, std::unique_ptr<AudioManager> &audioManager)
{
  int index = 0;
  while (true)
  {
    sol::optional<sol::table> hasSound = sounds[index];
    if (hasSound == sol::nullopt)
    {
      break;
    }

    sol::table sound = sounds[index];
    std::string soundId = sound["soundId"];
    std::string path = sound["filePath"];

    audioManager->AddSoundEffect(soundId, path);

    index++;
  }
}

void SceneLoader::LoadMusic(const sol::table &music, std::unique_ptr<AudioManager> &audioManager)
{
  int index = 0;
  while (true)
  {
    sol::optional<sol::table> hasMusic = music[index];
    if (hasMusic == sol::nullopt)
    {
      break;
    }

    sol::table musicTrack = music[index];
    std::string musicId = musicTrack["musicId"];
    std::string path = musicTrack["filePath"];

    audioManager->AddMusic(musicId, path);

    index++;
  }
}

void SceneLoader::LoadDamageColliders(const sol::table &damageColliders)
{
  int index = 0;
  while (true)
  {
      sol::optional<sol::table> hasCollider = damageColliders[index];
      if (hasCollider == sol::nullopt)
      {
        break;
      }

      std::string tag = damageColliders[index]["class"];
      
      tagsWithDamageColliders.insert(tag);

      index++;
  }
}
  
void SceneLoader::LoadStats(const sol::table &stats){
  int index = 0;
  while (true)
  {
    sol::optional<sol::table> hasStat = stats[index];
    if (hasStat == sol::nullopt)
    {
      break;
    }

    sol::table stat = stats[index];

    StatsComponent newStat {
      stat["health"],
      stat["points"],
      stat["damage"]
    };
   
    StatsManager::GetInstance().AddStat(stat["tag"], newStat);

    index++;
  }

}

void SceneLoader::LoadItems(sol::state &lua,
                            tinyxml2::XMLElement *objectGroup,
                            std::unique_ptr<Registry> &registry)
{
    sol::load_result load_result =
        lua.load_file("./assets/scripts/items.lua");

    if (!load_result.valid())
    {
        sol::error error = load_result;
        std::cerr << "Failed to load items script: "
                  << error.what() << std::endl;
        return;
    }

    load_result();

    sol::table itemsTable = lua["items"];

    tinyxml2::XMLElement *object = objectGroup->FirstChildElement("object");

    while (object != nullptr)
    {
        const char *name = nullptr;
        int x = 0;
        int y = 0;

        object->QueryStringAttribute("name", &name);
        object->QueryIntAttribute("x", &x);
        object->QueryIntAttribute("y", &y);

        std::string tag = name ? name : "unknown";

        std::cout << "ITEM FOUND: " << tag << std::endl;

        sol::optional<sol::table> hasItem = itemsTable[tag];

        if (hasItem != sol::nullopt)
        {
            Entity item = registry->createEntity();

            LoadEntity(lua, item, hasItem.value());

            auto &transform = item.getComponent<TransformComponent>();
            transform.position = glm::vec2(x, y);
        }

        object = object->NextSiblingElement("object");
    }
}

void SceneLoader::LoadTraps(sol::state &lua,
                            tinyxml2::XMLElement *objectGroup,
                            std::unique_ptr<Registry> &registry)
{
    sol::load_result load_result =
        lua.load_file("./assets/scripts/traps.lua");

    if (!load_result.valid())
    {
        sol::error error = load_result;
        std::cerr << "Failed to load traps script: "
                  << error.what() << std::endl;
        return;
    }

    load_result();

    sol::table trapsTable = lua["traps"];

    tinyxml2::XMLElement *object = objectGroup->FirstChildElement("object");

    while (object != nullptr)
    {
        const char *name = nullptr;
        int x = 0;
        int y = 0;

        object->QueryStringAttribute("name", &name);
        object->QueryIntAttribute("x", &x);
        object->QueryIntAttribute("y", &y);

        std::string tag = name ? name : "unknown";

        sol::optional<sol::table> hasTrap = trapsTable[tag];

        if (hasTrap != sol::nullopt)
        {
            Entity trap = registry->createEntity();

            LoadEntity(lua, trap, hasTrap.value());

            auto &transform = trap.getComponent<TransformComponent>();
            transform.position = glm::vec2(x, y);
        }

        object = object->NextSiblingElement("object");
    }
}

void SceneLoader::LoadPlatforms(sol::state &lua,
                                tinyxml2::XMLElement *objectGroup,
                                std::unique_ptr<Registry> &registry)
{
    sol::load_result load_result =
        lua.load_file("./assets/scripts/platforms.lua");

    if (!load_result.valid())
    {
        sol::error error = load_result;
        std::cerr << "Failed to load platforms script: "
                  << error.what() << std::endl;
        return;
    }

    load_result();

    sol::object obj = lua["platforms"];

    if (!obj.is<sol::table>())
    {
        std::cerr << "Platforms data is not a table" << std::endl;
        return;
    }

    sol::table platformsTable = obj.as<sol::table>();

    tinyxml2::XMLElement *object = objectGroup->FirstChildElement("object");

    while (object != nullptr)
    {
        const char *name = nullptr;
        int x = 0, y = 0;

        object->QueryStringAttribute("name", &name);
        object->QueryIntAttribute("x", &x);
        object->QueryIntAttribute("y", &y);

        std::string tag = name ? name : "unknown";

        sol::optional<sol::table> hasPlatform = platformsTable[tag];

        if (hasPlatform != sol::nullopt)
        {
            Entity platform = registry->createEntity();

            LoadEntity(lua, platform, hasPlatform.value());

            auto &transform = platform.getComponent<TransformComponent>();
            transform.position = glm::vec2(x, y);
        }

        object = object->NextSiblingElement("object");
    }
}

