#ifndef FORWARDPOINT_H_INCLUDED
#define FORWARDPOINT_H_INCLUDED

#include"Light.h"
#include"shader.h"
#include"RenderingEngine.h"

class ForwardPoint : public Shader
{
public:
    ForwardPoint(const std::string fileName): Shader(fileName)
    {
        m_uniforms["eyePos"] = glGetUniformLocation(m_program , "eyePos");
        m_uniforms["specularPower"] = glGetUniformLocation(m_program , "specularPower");
        m_uniforms["shadowTexelSize"] = glGetUniformLocation(m_program , "shadowTexelSize");
	m_uniforms["shadowBias"] = glGetUniformLocation(m_program , "shadowBias");
        m_uniforms["specularIntensity"] = glGetUniformLocation(m_program , "specularIntensity");
         m_uniforms["dispMapScale"] = glGetUniformLocation(m_program , "dispMapScale");
        m_uniforms["dispMapBias"] = glGetUniformLocation(m_program , "dispMapBias");
        int diffuseLocation = glGetUniformLocation(m_program , "diffuse");
        if(diffuseLocation>=0)
            m_uniforms["diffuse"] = diffuseLocation;
        int normalMapLocation = glGetUniformLocation(m_program , "normalMap");
        if(normalMapLocation>=0)
            m_uniforms["normalMap"] = normalMapLocation;
         int dispMapLocation = glGetUniformLocation(m_program , "dispMap");
        if(dispMapLocation>=0)
            m_uniforms["dispMap"] = dispMapLocation;
        int shadowMapLocation = glGetUniformLocation(m_program , "shadowMap");
        if(shadowMapLocation>=0)
            m_uniforms["shadowMap"] = shadowMapLocation;
        std::string light = "pointLight";
        m_uniforms[light + ".base.color"] = glGetUniformLocation(m_program ,(light+".base.color").c_str());
        m_uniforms[light + ".base.intensity"] = glGetUniformLocation(m_program ,(light+".base.intensity").c_str());
        m_uniforms[light + ".position"] = glGetUniformLocation(m_program ,(light+".position").c_str());
        m_uniforms[light + ".atten.constant"] = glGetUniformLocation(m_program ,(light+".atten.constant").c_str());
        m_uniforms[light + ".atten.linear"] = glGetUniformLocation(m_program ,(light+".atten.linear").c_str());
        m_uniforms[light + ".atten.exponent"] = glGetUniformLocation(m_program ,(light+".atten.exponent").c_str());
        m_uniforms[light + ".range"] = glGetUniformLocation(m_program ,(light+".range").c_str());
    }
    void Update(const Transform& transform,const Camera&c,const Material& material, RenderingEngine* renderer)
    {
        renderer->getPointShadowMap()->Bind(3);
        Shader::Update(transform,c,material,renderer);
        PointLight* pointLight = renderer->getActivePointLight();
        setUniformSampler("diffuse" , 0);
        setUniformSampler("normalMap" , 1);
        setUniformSampler("dispMap" , 2);
        setUniformSampler("shadowMap" , 3);
         setUniform1f("dispMapScale" , material.getDispMapScale());
        float baseBias = material.getDispMapScale()/2.0f;
        setUniform1f("dispMapBias" , -baseBias + baseBias*material.getDispMapOffset());
        std::string light = "pointLight";
        glm::vec3 color = pointLight->getColor();
        setUniformVector3f(light+".base.color" ,color.x , color.y , color.z);
        setUniform1f(light+".base.intensity" , pointLight->getIntensity());
        setUniform1f("specularPower" , material.getSpecularPower());
        setUniform1f("specularIntensity" , material.getSpecularIntensity());
        glm::vec3 p = c.getPos();
        setUniformVector3f("eyePos" , p.x , p.y , p.z);
        setUniform1f("shadowBias" , renderer->getShadowBias());
        glm::vec3 tSize = renderer->getShadowTexelSize();
        setUniformVector3f("shadowTexelSize" , tSize.x , tSize.y , tSize.z);

        setUniform1f(light+".range" , pointLight->getRange());
        Attenuation atten = pointLight->getAttenuation();
        setUniform1f(light+".atten.constant" , atten.getConstant());
        setUniform1f(light+".atten.linear" , atten.getLinear());
        setUniform1f(light+".atten.exponent" , atten.getExponent());
        glm::vec3 pos  = pointLight->getPosition();
        setUniformVector3f(light + ".position" , pos.x , pos.y , pos.z);
    }
};


#endif // FORWARDPOINT_H_INCLUDED
