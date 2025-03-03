// this file is for Player class implementation
//
// created by Gabriel LU on Mar 3, 2025
//

#include "player.h"

Player::Player(unsigned int ID, PlayerPrivileges pp_in) : pp(pp_in), player_position(glm::vec3{0.0f, 0.0f, 0.0f}), player_ID(ID)
{
    // TODO: the direction value would be in the future game save file (implemented later)
    camera = std::make_unique<Camera>(player_position, glm::vec3{0.0f, 0.0f, -1.0f});
}
