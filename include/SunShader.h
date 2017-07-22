#ifndef SUNSHADER_H_INCLUDED
#define SUNSHADER_H_INCLUDED

#include"Light.h"
#include"shader.h"
#include"string"
#include <glm/gtc/type_ptr.hpp>

class SunShader : public Shader
{
public:
    SunShader(const std::string fileName) : Shader(fileName , false)
    {
        m_uniforms["sunPos"] = glGetUniformLocation(m_program , "sunPos");
    }
    void UpdateSunShader(const Transform& transform  , const Camera&camera , glm::vec3 pos)
    {
        glm::mat4 proj = camera.getProjection();
        glm::mat4 view = glm::mat4_cast(glm::conjugate(camera.getRot()));
        glm::mat4 MVP = camera.getMVP();
        glm::mat4 model = transform.GetModel();
        glm::mat4 temp = proj*view*model;
        MVP = MVP*model;
        setUniformMatrix4f("MVP" , &temp[0][0]);
        setUniformMatrix4f("Model" , &model[0][0]);
        setUniformVector3f("sunPos" , pos.x , pos.y , pos.z);
    }
};


#endif // SUNSHADER_H_INCLUDED
