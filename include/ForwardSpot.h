#ifndef FORWARDSPOT_H_INCLUDED
#define FORWARDSPOT_H_INCLUDED


#include"Light.h"
#include"shader.h"

class ForwardSpot : public Shader
{
public:
    ForwardSpot(const std::string fileName): Shader(fileName)
    {
         m_uniforms["fogColor"] = glGetUniformLocation(m_program , "fogColor");
        m_uniforms["eyePos"] = glGetUniformLocation(m_program , "eyePos");
         m_uniforms["clipPlane"] = glGetUniformLocation(m_program , "clipPlane");
        m_uniforms["shadowTexelSize"] = glGetUniformLocation(m_program , "shadowTexelSize");
        m_uniforms["shadowBias"] = glGetUniformLocation(m_program , "shadowBias");
        m_uniforms["lightMatrix"] = glGetUniformLocation(m_program , "lightMatrix");
        m_uniforms["specularPower"] = glGetUniformLocation(m_program , "specularPower");
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

        std::string light = "spotLight";
        m_uniforms[light + ".base.color"] = glGetUniformLocation(m_program ,(light+".base.color").c_str());
        m_uniforms[light + ".base.intensity"] = glGetUniformLocation(m_program ,(light+".base.intensity").c_str());
        m_uniforms[light + ".position"] = glGetUniformLocation(m_program ,(light+".position").c_str());
        m_uniforms[light + ".atten.constant"] = glGetUniformLocation(m_program ,(light+".atten.constant").c_str());
        m_uniforms[light + ".atten.linear"] = glGetUniformLocation(m_program ,(light+".atten.linear").c_str());
        m_uniforms[light + ".atten.exponent"] = glGetUniformLocation(m_program ,(light+".atten.exponent").c_str());
        m_uniforms[light + ".range"] = glGetUniformLocation(m_program ,(light+".range").c_str());
        m_uniforms[light + ".cut_off"] = glGetUniformLocation(m_program ,(light+".cut_off").c_str());
        m_uniforms[light + ".direction"] = glGetUniformLocation(m_program ,(light+".direction").c_str());
    }
    void Update(const Transform& transform, const Camera&c,const Material& material,RenderingEngine* renderer)
    {
        renderer->getDirShadowMap()->Bind(3);
        glm::mat4 lightMat = renderer->getLightMatrix()*transform.GetModel();
        setUniformMatrix4f("lightMatrix" , &lightMat[0][0]);
        Shader::Update(transform , c,material , renderer);
        SpotLight* spotLight = renderer->getActiveSpotLight();
        std::string light = "spotLight";
        setUniformSampler("diffuse" , 0);
        setUniformSampler("normalMap" , 1);
        setUniformSampler("dispMap" , 2);
        setUniformSampler("shadowMap" , 3);
        glm::vec3 color = spotLight->getColor();
        setUniformVector3f(light+".base.color" ,color.x , color.y , color.z);
        setUniform1f(light+".base.intensity" , spotLight->getIntensity());
        setUniform1f("specularPower" , material.getSpecularPower());
        setUniform1f("specularIntensity" , material.getSpecularIntensity());
        setUniform1f("dispMapScale" , material.getDispMapScale());
        float baseBias = material.getDispMapScale()/2.0f;
        setUniform1f("dispMapBias" , -baseBias + baseBias*material.getDispMapOffset());

        glm::vec3 p = c.getPos();
        setUniformVector3f("eyePos" , p.x , p.y , p.z);

        setUniform1f(light+".range" , spotLight->getRange());
        Attenuation atten = spotLight->getAttenuation();
        setUniform1f(light+".atten.constant" , atten.getConstant());
        setUniform1f(light+".atten.linear" , atten.getLinear());
        setUniform1f(light+".atten.exponent" , atten.getExponent());
        glm::vec3 pos  = spotLight->getPosition();
        setUniformVector3f(light + ".position" , pos.x , pos.y , pos.z);
        setUniform1f(light+".cut_off" , spotLight->getCutOff());
        setUniform1f("shadowBias" , renderer->getShadowBias());
        glm::vec3 tSize = renderer->getShadowTexelSize();
        setUniformVector3f("shadowTexelSize" , tSize.x , tSize.y , tSize.z);
        glm::vec3 dir = spotLight->getDirection();
        setUniformVector3f(light + ".direction" , dir.x , dir.y , dir.z);

        glm::vec4 plane = renderer->getClipingPlane();
        setUniformVector4f("clipPlane" ,plane.x , plane.y , plane.z , plane.w );
        glm::vec4 fc = renderer->getFogColor();
        setUniformVector4f("fogColor" , fc.x , fc.y , fc.z , fc.w);
    }
};

#endif // FORWARDSPOT_H_INCLUDED
