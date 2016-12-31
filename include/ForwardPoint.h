#ifndef FORWARDPOINT_H_INCLUDED
#define FORWARDPOINT_H_INCLUDED

#include"Light.h"
#include"shader.h"

class ForwardPoint : public Shader
{
private:
    PointLight pointLight;
public:
    ForwardPoint(const std::string fileName): Shader(fileName) ,
    pointLight(glm::vec3(1.0f,1.0f,1.0f),5.0f,glm::vec3(0.0f,1.0f,0.0f))
    {
        m_uniforms["eyePos"] = glGetUniformLocation(m_program , "eyePos");
        m_uniforms["specularPower"] = glGetUniformLocation(m_program , "specularPower");
        m_uniforms["specularIntensity"] = glGetUniformLocation(m_program , "specularIntensity");
        std::string light = "pointLight";
        m_uniforms[light + ".base.color"] = glGetUniformLocation(m_program ,(light+".base.color").c_str());
        m_uniforms[light + ".base.intensity"] = glGetUniformLocation(m_program ,(light+".base.intensity").c_str());
        m_uniforms[light + ".position"] = glGetUniformLocation(m_program ,(light+".position").c_str());
        m_uniforms[light + ".atten.constant"] = glGetUniformLocation(m_program ,(light+".atten.constant").c_str());
        m_uniforms[light + ".atten.linear"] = glGetUniformLocation(m_program ,(light+".atten.linear").c_str());
        m_uniforms[light + ".atten.exponent"] = glGetUniformLocation(m_program ,(light+".atten.exponent").c_str());
        m_uniforms[light + ".range"] = glGetUniformLocation(m_program ,(light+".range").c_str());
    }
    void Update(const Transform& t , const Camera&c,const Material& material)
    {
        Shader::Update(t,c,material);
        std::string light = "pointLight";
        glm::vec3 color = pointLight.getColor();
        setUniformVector3f(light+".base.color" ,color.x , color.y , color.z);
        setUniform1f(light+".base.intensity" , pointLight.getIntensity());
        setUniform1f("specularPower" , material.getSpecularPower());
        setUniform1f("specularIntensity" , material.getSpecularIntensity());
        glm::vec3 p = c.getPos();
        setUniformVector3f("eyePos" , p.x , p.y , p.z);

        setUniform1f(light+".range" , pointLight.getRange());
        Attenuation atten = pointLight.getAttenuation();
        setUniform1f(light+".atten.constant" , atten.getConstant());
        setUniform1f(light+".atten.linear" , atten.getLinear());
        setUniform1f(light+".atten.exponent" , atten.getExponent());
        glm::vec3 pos  = pointLight.getPosition();
        setUniformVector3f(light + ".position" , pos.x , pos.y , pos.z);
    }
};


#endif // FORWARDPOINT_H_INCLUDED
