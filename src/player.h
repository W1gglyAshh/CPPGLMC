// this file is for Player class definition
//
// created by Gabriel LU on Mar 3, 2025
//

#include "include.h"
#include "camera.h"

class Player {
private:
    PlayerPrivileges pp;
    std::unique_ptr<Camera> camera;
    
    glm::vec3 player_position;
    
    unsigned int player_ID;
    std::string player_name;
    
    enum class PlayerState: int
    {
        STANDING = 0,
        WALKING,
        RUNNING,
        CROUCHING,
        JUMPING
    };
public:
    Player(unsigned int ID, PlayerPrivileges pp_in);
    ~Player() = default;
    
    void tpPosition(glm::vec3 target_pos);
    void setPrivilege(PlayerPrivileges target_pp);
    
    void setFirstPerson();
    void setThirdPerson();
    
    void update();
    
    // TODO: add player collision
};
