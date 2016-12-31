#ifndef FORWARDDIRECTIONAL_H_INCLUDED
#define FORWARDDIRECTIONAL_H_INCLUDED

#include"Light.h"
#include"shader.h"

class ForwardDirectional: public Shader
{
private:
    DirectionalLight dirlight;
public:
    ForwardDirectional(const std::string fileName): Shader(fileName) ,
    dirlight(glm::vec3(1.0f,1.0f,1.0f) , 1.0f , glm::vec3(0.0f , -1.0f , 0.0f))
    {
    m_uniforms["Normal"] = glGetUniformLocation(m_program, "Normal");
	m_uniforms["MaterialAmbientColor"] = glGetUniformLocation(m_program, "MaterialAmbientColor");
	m_uniforms["eyePos"] = glGetUniformLocation(m_program , "eyePos");
	m_uniforms["specularPower"] = glGetUniformLocation(m_program , "specularPower");
	m_uniforms["specularIntensity"] = glGetUniformLocation(m_program , "specularIntensity");
	std::string light = "directionalLight";
    m_uniforms[light + ".base.color"] = glGetUniformLocation(m_program ,(light+".base.color").c_str());
    m_uniforms[light + ".base.intensity"] = glGetUniformLocation(m_program ,(light+".base.intensity").c_str());
    m_uniforms[light + ".direction"] = glGetUniformLocation(m_program ,(light+".direction").c_str());

    }
    void Update(const Transform& t , const Camera&c,const Material& material)
    {
        Shader::Update(t,c,material);
        std::string light = "directionalLight";
        glm::vec3 color = dirlight.getColor();
        setUniformVector3f(light+".base.color" ,color.x , color.y , color.z);
        setUniform1f(light+".base.intensity" , dirlight.getIntensity());
        glm::vec3 dir = dirlight.getDirection();
        setUniformVector3f(light+".direction" ,dir.x , dir.y , dir.z);
        glm::vec4 co = material.getAmbientColor();
        setUniformVector4f("MaterialAmbientColor" , co.x , co.y ,co.z,co.w);
        setUniform1f("specularPower" , material.getSpecularPower());
        setUniform1f("specularIntensity" , material.getSpecularIntensity());
        glm::vec3 p = c.getPos();
        setUniformVector3f("eyePos" , p.x , p.y , p.z);
    }

};

#endif // FORWARDDIRECTIONAL_H_INCLUDED
