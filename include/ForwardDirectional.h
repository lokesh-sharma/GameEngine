#ifndef FORWARDDIRECTIONAL_H_INCLUDED
#define FORWARDDIRECTIONAL_H_INCLUDED

#include"Light.h"
#include"shader.h"

class ForwardDirectional: public Shader
{
public:
    ForwardDirectional(const std::string fileName): Shader(fileName)
    {
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

	std::string light = "directionalLight";
    m_uniforms[light + ".base.color"] = glGetUniformLocation(m_program ,(light+".base.color").c_str());
    m_uniforms[light + ".base.intensity"] = glGetUniformLocation(m_program ,(light+".base.intensity").c_str());
    m_uniforms[light + ".direction"] = glGetUniformLocation(m_program ,(light+".direction").c_str());

    }
    void Update(const Transform& transform,const Camera&c,const Material& material , RenderingEngine* renderingEngine)
    {
         renderingEngine->getDirShadowMap()->Bind(3);
        glm::mat4 lightMat = renderingEngine->getLightMatrix()*transform.GetModel();
        setUniformMatrix4f("lightMatrix" , &lightMat[0][0]);
        Shader::Update(transform , c,material,renderingEngine);
        setUniformSampler("diffuse" , 0);
        setUniformSampler("normalMap" , 1);
        setUniformSampler("dispMap" , 2);
        setUniformSampler("shadowMap" , 3);
         setUniform1f("dispMapScale" , material.getDispMapScale());
        float baseBias = material.getDispMapScale()/2.0f;
        setUniform1f("dispMapBias" , -baseBias + baseBias*material.getDispMapOffset());
        std::string light = "directionalLight";
        DirectionalLight* dirlight = renderingEngine->getActiveDirectionalLight();
        glm::vec3 color = dirlight->getColor();
        setUniformVector3f(light+".base.color" ,color.x , color.y , color.z);
        setUniform1f(light+".base.intensity" , dirlight->getIntensity());
        glm::vec3 dir = dirlight->getDirection();
        setUniformVector3f(light+".direction" ,dir.x , dir.y , dir.z);
        setUniform1f("specularPower" , material.getSpecularPower());
        setUniform1f("shadowBias" , renderingEngine->getShadowBias());
        glm::vec3 tSize = renderingEngine->getShadowTexelSize();
        setUniformVector3f("shadowTexelSize" , tSize.x , tSize.y , tSize.z);
        setUniform1f("specularIntensity" , material.getSpecularIntensity());
        glm::vec3 p = c.getPos();
        setUniformVector3f("eyePos" , p.x , p.y , p.z);

        glm::vec4 plane = renderingEngine->getClipingPlane();
        setUniformVector4f("clipPlane" ,plane.x , plane.y , plane.z , plane.w );
    }

};

#endif // FORWARDDIRECTIONAL_H_INCLUDED
