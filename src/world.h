// this file is for world class - the main class of the game which manages all the other classes (except Window class)
//
// created by Gabriel LU on Mar 2, 2025
//

#pragma once

#include "block.h"
#include "camera.h"
#include "include.h"
#include "shader.h"

class World
{
  private:
    std::vector<std::unique_ptr<Camera>> cameras;

  public:
};
