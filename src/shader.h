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
    void setUniformVal(const std::string &name, auto value) const;
    
    static bool isSuccessful(unsigned int target, GLenum pname);
};
