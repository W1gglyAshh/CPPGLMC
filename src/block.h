// this file is for the Block class definition
//
// created by Gabriel LU on Mar 1, 2025
//

#pragma once

#include "include.h"

class Block
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    unsigned int instance_VBO;
    unsigned int VAO, VBO, EBO;
    unsigned int texture;

    BlockType block_type;

    std::vector<glm::vec3> positions;

    std::string texture_path;

  public:
    Block(BlockType type, std::string texture_path_in);
    ~Block();

    void init();
    void loadTexture();
    void render() const;
    
    void updateInstanceData();
    void renderInstanced() const;

    void setPositions(const std::vector<glm::vec3> &positions_in);
    void addBlock(const glm::vec3 &position);
    void removeBlock(const glm::vec3 &position);
};
