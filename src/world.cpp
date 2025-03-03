// this file contains the implementation of the class World
//
// created by Gabriel LU on Mar 3, 2025
//

#include "world.h"

World::World(std::string name, unsigned int player_ID, PlayerPrivileges pp) : world_name(name)
{
    // initialize the shader
    shader = std::make_unique<Shader>("shaders/shader.vert", "shaders/shader.frag");
    
    // initialize the player
    player = std::make_unique<Player>(player_ID, pp);
    
    // initialize the blocks
    blocks.push_back(Block(BlockType::GRASS, "res/atlas.png"));
    blocks.push_back(Block(BlockType::DIRT, "res/atlas.png"));
    blocks.push_back(Block(BlockType::STONE, "res/atlas.png"));
    blocks.push_back(Block(BlockType::BEDROCK, "res/atlas.png"));
    blocks.push_back(Block(BlockType::WOOD, "res/atlas.png"));
    blocks.push_back(Block(BlockType::LEAF, "res/atlas.png"));
    blocks.push_back(Block(BlockType::SAND, "res/atlas.png"));
    blocks.push_back(Block(BlockType::WATER, "res/atlas.png"));
    blocks.push_back(Block(BlockType::LAVA, "res/atlas.png"));
    blocks.push_back(Block(BlockType::OBSIDIAN, "res/atlas.png"));
}
