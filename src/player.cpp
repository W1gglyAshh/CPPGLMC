// this file is for Player class implementation
//
// created by Gabriel LU on Mar 3, 2025
//

#include "player.h"

Player::Player(unsigned int ID, PlayerPrivileges pp_in) : pp(pp_in), player_position(glm::vec3{0.0f, 0.0f, 0.0f}), player_ID(ID)
{
}
