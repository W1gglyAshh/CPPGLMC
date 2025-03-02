// this file is for implementing the functions in shader class
//
// created by Gabriel LU on Mar 1, 2025
//

#include "shader.h"

Shader::Shader(std::string frag_path, std::string vert_path)
    : id(0)
{
    std::ifstream vert_file, frag_file;
    
    // ensure ifstream objects can throw exceptions
    vert_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    frag_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try
    {
        vert_file.open(vert_path);
        frag_file.open(frag_path);
        
        std::stringstream vert_stream, frag_stream;
        
        vert_stream << vert_file.rdbuf();
        frag_stream << frag_file.rdbuf();
        
        vert_file.close();
        frag_file.close();
        
        vertex_source = vert_stream.str();
        fragment_source = frag_stream.str();
    } catch (std::ifstream::failure &e)
    {
        log("Failed to read shader files!");
        log(e.what());
    }
    log("Ended reading shader files.");
}

Shader::~Shader()
{
    glDeleteProgram(id);
    std::cout << "Shader program freed." << std::endl;
}

void Shader::compile()
{
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER), fragment = glCreateShader(GL_FRAGMENT_SHADER);
    
    if (!vertex || !fragment)
    {
        log("Failed to create shader objects!");
        return;
    }
    log("Shader objects created. Compiling...");
    
    const char *vert_src = vertex_source.c_str();
    const char *frag_src = fragment_source.c_str();
    
    glShaderSource(vertex, 1, &vert_src, nullptr);
    glShaderSource(fragment, 1, &frag_src, nullptr);
    glCompileShader(vertex);
    glCompileShader(fragment);
    
    if (!isSuccessful(vertex, GL_COMPILE_STATUS) || !isSuccessful(fragment, GL_COMPILE_STATUS))
    {
        log("Failed to compile shaders!");
        return;
    }
    log("Shaders compiled successfully. Linking...");
    
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    
    if (!isSuccessful(id, GL_LINK_STATUS))
    {
        log("Failed to link shaders!");
        return;
    }
    log("Shaders linked successfully. Cleaning up...");
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    log("Shader objects freed.");
}

void Shader::use() const
{
    glUseProgram(id);
}

void Shader::setID(unsigned int id_in)
{
    id = id_in;
}

template <typename T>
void Shader::setUniformVal(const std::string &name, T value) const
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

bool Shader::isSuccessful(unsigned int target, GLenum pname)
{
    GLint success;
    glGetShaderiv(target, pname, &success);
    
    if (success == GL_FALSE)
    {
        GLint log_length;
        glGetShaderiv(target, GL_INFO_LOG_LENGTH, &log_length);
        
        std::string info_log(log_length, '\0');
        glGetShaderInfoLog(target, log_length, nullptr, &info_log[0]);
        
        log(info_log);
        return false;
    }
    return true;
}
