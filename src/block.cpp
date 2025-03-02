// this file is for block class implementation
//
// created by Gabriel LU on Mar 1, 2025
//

#include "block.h"

Block::Block(BlockType type, std::string texture_path_in) : instance_VBO(0), VAO(0), VBO(0), EBO(0), texture(0), block_type(type), texture_path(std::move(texture_path_in))
{
    // initialize the vertices and indices
    int block_id = static_cast<int>(block_type);

    // set up vertices and indices for a cube
    // each vertex: position (x,y,z), texture coordinates (s,t)

    // calculate texture coordinates based on the block type
    // each block type gets its own column in the texture atlas
    // each column has 6 faces vertically arranged in the order:
    // TOP, BOTTOM, FRONT, BACK, LEFT, RIGHT

    float atlas_width = static_cast<float>(BlockType::BLOCK_COUNT);
    float atlas_height = static_cast<float>(BlockFace::FACE_COUNT);

    float block_width = 1.0f / atlas_width;
    float face_height = 1.0f / atlas_height;

    // start s coord for each block type
    float s_start = block_id / block_width;
    float s_end = s_start + block_width;

    // calculate texture coordinates for each face
    std::vector<std::vector<glm::vec2>> tex_coords(6);

    for (int i = 0; i < 6; i++)
    {
        // i refer to face count
        float t_start = i / atlas_height;
        float t_end = t_start + face_height;

        // define the four corners of the texture for this face
        tex_coords[i] = {
            glm::vec2(s_start, t_end),   // bottom left
            glm::vec2(s_end, t_end),     // bottom right
            glm::vec2(s_start, t_start), // top left
            glm::vec2(s_end, t_start)    // top right
        };
    }

    // cube corner positions
    glm::vec3 corners[8] = {
        glm::vec3(0.0f, 0.0f, 0.0f), // 0: bottom-left-back
        glm::vec3(1.0f, 0.0f, 0.0f), // 1: bottom-right-back
        glm::vec3(1.0f, 1.0f, 0.0f), // 2: top-right-back
        glm::vec3(0.0f, 1.0f, 0.0f), // 3: top-left-back
        glm::vec3(0.0f, 0.0f, 1.0f), // 4: bottom-left-front
        glm::vec3(1.0f, 0.0f, 1.0f), // 5: bottom-right-front
        glm::vec3(1.0f, 1.0f, 1.0f), // 6: top-right-front
        glm::vec3(0.0f, 1.0f, 1.0f)  // 7: top-left-front
    };

    // define faces (each face has 4 vertices)
    // format: position.x, position.y, position.z, texcoord.s, texcoord.t

    // TOP face (y = 1.0f)
    vertices.push_back(corners[3].x);
    vertices.push_back(corners[3].y);
    vertices.push_back(corners[3].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::TOP)][0].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::TOP)][0].y);

    vertices.push_back(corners[2].x);
    vertices.push_back(corners[2].y);
    vertices.push_back(corners[2].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::TOP)][1].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::TOP)][1].y);

    vertices.push_back(corners[6].x);
    vertices.push_back(corners[6].y);
    vertices.push_back(corners[6].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::TOP)][3].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::TOP)][3].y);

    vertices.push_back(corners[7].x);
    vertices.push_back(corners[7].y);
    vertices.push_back(corners[7].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::TOP)][2].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::TOP)][2].y);

    // BOTTOM face (y = 0.0f)
    vertices.push_back(corners[0].x);
    vertices.push_back(corners[0].y);
    vertices.push_back(corners[0].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BOTTOM)][0].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BOTTOM)][0].y);

    vertices.push_back(corners[4].x);
    vertices.push_back(corners[4].y);
    vertices.push_back(corners[4].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BOTTOM)][2].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BOTTOM)][2].y);

    vertices.push_back(corners[5].x);
    vertices.push_back(corners[5].y);
    vertices.push_back(corners[5].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BOTTOM)][3].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BOTTOM)][3].y);

    vertices.push_back(corners[1].x);
    vertices.push_back(corners[1].y);
    vertices.push_back(corners[1].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BOTTOM)][1].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BOTTOM)][1].y);

    // FRONT face (z = 1.0f)
    vertices.push_back(corners[4].x);
    vertices.push_back(corners[4].y);
    vertices.push_back(corners[4].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::FRONT)][0].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::FRONT)][0].y);

    vertices.push_back(corners[7].x);
    vertices.push_back(corners[7].y);
    vertices.push_back(corners[7].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::FRONT)][2].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::FRONT)][2].y);

    vertices.push_back(corners[6].x);
    vertices.push_back(corners[6].y);
    vertices.push_back(corners[6].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::FRONT)][3].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::FRONT)][3].y);

    vertices.push_back(corners[5].x);
    vertices.push_back(corners[5].y);
    vertices.push_back(corners[5].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::FRONT)][1].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::FRONT)][1].y);

    // BACK face (z = 0.0f)
    vertices.push_back(corners[1].x);
    vertices.push_back(corners[1].y);
    vertices.push_back(corners[1].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BACK)][0].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BACK)][0].y);

    vertices.push_back(corners[2].x);
    vertices.push_back(corners[2].y);
    vertices.push_back(corners[2].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BACK)][2].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BACK)][2].y);

    vertices.push_back(corners[3].x);
    vertices.push_back(corners[3].y);
    vertices.push_back(corners[3].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BACK)][3].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BACK)][3].y);

    vertices.push_back(corners[0].x);
    vertices.push_back(corners[0].y);
    vertices.push_back(corners[0].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BACK)][1].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::BACK)][1].y);

    // LEFT face (x = 0.0f)
    vertices.push_back(corners[0].x);
    vertices.push_back(corners[0].y);
    vertices.push_back(corners[0].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::LEFT)][0].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::LEFT)][0].y);

    vertices.push_back(corners[3].x);
    vertices.push_back(corners[3].y);
    vertices.push_back(corners[3].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::LEFT)][2].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::LEFT)][2].y);

    vertices.push_back(corners[7].x);
    vertices.push_back(corners[7].y);
    vertices.push_back(corners[7].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::LEFT)][3].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::LEFT)][3].y);

    vertices.push_back(corners[4].x);
    vertices.push_back(corners[4].y);
    vertices.push_back(corners[4].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::LEFT)][1].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::LEFT)][1].y);

    // RIGHT face (x = 1.0f)
    vertices.push_back(corners[1].x);
    vertices.push_back(corners[1].y);
    vertices.push_back(corners[1].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::RIGHT)][0].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::RIGHT)][0].y);

    vertices.push_back(corners[5].x);
    vertices.push_back(corners[5].y);
    vertices.push_back(corners[5].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::RIGHT)][1].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::RIGHT)][1].y);

    vertices.push_back(corners[6].x);
    vertices.push_back(corners[6].y);
    vertices.push_back(corners[6].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::RIGHT)][3].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::RIGHT)][3].y);

    vertices.push_back(corners[2].x);
    vertices.push_back(corners[2].y);
    vertices.push_back(corners[2].z);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::RIGHT)][2].x);
    vertices.push_back(tex_coords[static_cast<int>(BlockFace::RIGHT)][2].y);

    // setup indices for drawing triangles
    // each face consists of 2 triangles, so we have 12 triangles in total (36 indices)
    for (int i = 0; i < 6; i++)
    {
        // i refer to face count
        int base = i * 4;

        // First triangle
        indices.push_back(base + 0);
        indices.push_back(base + 1);
        indices.push_back(base + 2);

        // Second triangle
        indices.push_back(base + 0);
        indices.push_back(base + 2);
        indices.push_back(base + 3);
    }
}

Block::~Block()
{
    if (VAO != 0)
        glDeleteVertexArrays(1, &VAO);
    if (VBO != 0)
        glDeleteBuffers(1, &VBO);
    if (EBO != 0)
        glDeleteBuffers(1, &EBO);
    if (instance_VBO != 0)
        glDeleteBuffers(1, &instance_VBO);
    if (texture != 0)
        glDeleteTextures(1, &texture);
}

void Block::init()
{
    log("Generating buffers and array objects...");
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glGenBuffers(1, &instance_VBO);
    
    if (VAO == 0 || VBO == 0 || EBO == 0 || instance_VBO == 0)
    {
        log("Failed to generate buffers or array object! Aborting...");
        return;
    }
    
    log("Succeeded. Binding...");
    
    glBindVertexArray(VAO);
    if (glGetError() != GL_NO_ERROR) log("Failed to bind vertex array! Error code: " + std::to_string(glGetError()));
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    if (glGetError() != GL_NO_ERROR) log("Failed array buffer! Error code: " + std::to_string(glGetError()));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    if (glGetError() != GL_NO_ERROR) log("Failed element buffer! Error code: " + std::to_string(glGetError()));
    
    log("Succeeded binding.");
    // position attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);
    
    // texture coordinates attrib
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    loadTexture();
    
    if (!positions.empty())
    {
        updateInstanceData();
    }
}

void Block::loadTexture()
{
    
    glGenTextures(1, &texture);
    if (texture == 0)
    {
        log("Failed to generate texture! Aborting...");
        return;
    }
    log("Successfully generated texture. Binding...");
    
    glBindTexture(GL_TEXTURE_2D, texture);
    if (glGetError() != GL_NO_ERROR) log("Failed to bind texture! Error code: " + std::to_string(glGetError()));
    
    log("Succeeded binding. Loading texture...");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    int w, h, nr_channel;
    unsigned char *data = stbi_load(texture_path.c_str(), &w, &h, &nr_channel, 0);
    
    if (data)
    {
        GLenum format = GL_RGB;
        switch (nr_channel) {
            case 1: format = GL_RED; break;
            case 3: format = GL_RGB; break;
            case 4: format = GL_RGBA; break;
            default: log("Unsupported texture format! Aborting..."); return;
        }
        
        glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else
    {
        log("Failed to load texture!");
        return;
    }
    
    stbi_image_free(data);
    log("Temporary texture data freed.");
}


// instance rendering: for better performance
void Block::updateInstanceData()
{
    if (positions.empty()) return;
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(2);
    // instanced
    glVertexAttribDivisor(1, 2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Block::renderInstanced() const
{
    if (positions.empty()) return;
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    
    // draw all instances
    glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, positions.size());
}
//


void Block::render() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Block::setPositions(const std::vector<glm::vec3> &positions_in)
{
    positions = positions_in;
}

void Block::addBlock(const glm::vec3 &position)
{
    positions.push_back(position);
}

void Block::removeBlock(const glm::vec3 &position)
{
    auto it = std::find(positions.begin(), positions.end(), position);
    if (it != positions.end())
        positions.erase(it);
}
