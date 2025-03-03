// this file is for world class - the main class of the game which manages all the other classes (except Window class)
//
// created by Gabriel LU on Mar 2, 2025
//

#pragma once

#include "block.h"
#include "camera.h"
#include "include.h"
#include "shader.h"
#include "player.h"

class World
{
  private:
    std::string world_name;
    
    std::vector<std::unique_ptr<Camera>> cameras;
    std::vector<Block> blocks;
    
    std::unique_ptr<Player> player;
    std::unique_ptr<Shader> shader;
  public:
    World(std::string name, unsigned int player_ID, PlayerPrivileges pp);
    ~World();

    void run();
};
