// this file is for shader management class definition
//
// created by Gabriel LU on Mar 1, 2025
//

#include "include.h"

class Shader
{
  private:
    unsigned int id;
    std::string vertex_source;
    std::string fragment_source;

  public:
    Shader(std::string frag_path, std::string vert_path);
    ~Shader();

    void compile();
    void use() const;
    
    void setID(unsigned int id_in);

    static bool isSuccessful(unsigned int target, GLenum pname);
    
    template <typename T>
    void setUniformVal(const std::string &name, T value) const
    {
        GLint loc = glGetUniformLocation(id, name.c_str());
        // error checking
        if (loc == -1)
        {
            std::cerr << "Uniform variable " << name << " not found!" << std::endl;
            return;
        }
        
        if constexpr (std::is_same_v<T, bool>)
        {
            glUniform1i(loc, static_cast<int>(value));
        } else if constexpr (std::is_same_v<T, int>)
        {
            glUniform1i(loc, value);
        } else if constexpr (std::is_same_v<T, float>)
        {
            glUniform1f(loc, value);
        } else if constexpr (std::is_same_v<T, glm::vec2>)
        {
            glUniform2fv(loc, 1, glm::value_ptr(value));
        } else if constexpr (std::is_same_v<T, glm::vec3>)
        {
            glUniform3fv(loc, 1, glm::value_ptr(value));
        } else if constexpr (std::is_same_v<T, glm::vec4>)
        {
            glUniform4fv(loc, 1, glm::value_ptr(value));
        } else if constexpr (std::is_same_v<T, glm::mat4>)
        {
            glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
        } else
        {
            static_assert(!sizeof(T), "Unsupported uniform type!");
        }
    }
};
