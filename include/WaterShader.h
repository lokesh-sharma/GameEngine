#ifndef WATERSHADER_H_INCLUDED
#define WATERSHADER_H_INCLUDED

#include"Light.h"
#include"shader.h"
#include"string"
#include <glm/gtc/type_ptr.hpp>

class WaterShader : public Shader
{
public:
    WaterShader(const std::string fileName) : Shader(fileName , false)
    {
        m_uniforms["reflectionMap"] = glGetUniformLocation(m_program , "reflectionMap");
        m_uniforms["refractionMap"] = glGetUniformLocation(m_program , "refractionMap");
        m_uniforms["dudvMap"] = glGetUniformLocation(m_program , "dudvMap");
        m_uniforms["normalMap"] = glGetUniformLocation(m_program , "normalMap");
        m_uniforms["depthMap"] = glGetUniformLocation(m_program , "depthMap");
        m_uniforms["moveFactor"] = glGetUniformLocation(m_program , "moveFactor");
        m_uniforms["eyePos"] = glGetUniformLocation(m_program , "eyePos");
        m_uniforms["lightPos"] = glGetUniformLocation(m_program , "lightPos");
        m_uniforms["lightColor"] = glGetUniformLocation(m_program , "lightColor");
    }
    void UpdateWaterShader(const Transform& transform  , const Camera&camera)
    {
        glm::mat4 MVP = camera.getMVP();
        glm::mat4 model = transform.GetModel();
        MVP = MVP*model;
        glm::vec3 pos = camera.getPos();
        setUniformVector3f("eyePos" , pos.x , pos.y , pos.z);
        setUniformMatrix4f("MVP" , &MVP[0][0]);
        setUniformMatrix4f("Model" , &model[0][0]);
        setUniformSampler("reflectionMap" , 0);
        setUniformSampler("refractionMap" , 1);
        setUniformSampler("dudvMap" , 2);
        setUniformSampler("normalMap" , 3);
        setUniformSampler("depthMap" , 4);
    }
};


#endif // WATERSHADER_H_INCLUDED
