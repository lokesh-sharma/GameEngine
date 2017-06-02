#ifndef FORWARDAMBIENT_H_INCLUDED
#define FORWARDAMBIENT_H_INCLUDED

#include"Light.h"
#include"shader.h"

class ForwardAmbient : public Shader
{
public:
    ForwardAmbient(const std::string fileName) : Shader(fileName)
    {
        m_uniforms["eyePos"] = glGetUniformLocation(m_program , "eyePos");
        m_uniforms["clipPlane"] = glGetUniformLocation(m_program , "clipPlane");
        m_uniforms["MaterialAmbientColor"] = glGetUniformLocation(m_program, "MaterialAmbientColor");
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
    }
    void Update(const Transform& transform,const Camera&c,const Material& m , RenderingEngine* renderer)
    {
        Shader::Update(transform , c,m ,renderer );
        glm::vec4 color = m.getAmbientColor();
        setUniformVector4f("MaterialAmbientColor" , color.x , color.y ,color.z,color.w);
        setUniformSampler("diffuse" , 0);
        setUniformSampler("normalMap" , 1);
        setUniformSampler("dispMap" , 2);
        setUniformSampler("shadowMap" , 3);
        setUniform1f("dispMapScale" , m.getDispMapScale());
        float baseBias = m.getDispMapScale()/2.0f;
        setUniform1f("dispMapBias" , -baseBias + baseBias*m.getDispMapOffset());

        glm::vec3 p = c.getPos();
        setUniformVector3f("eyePos" , p.x , p.y , p.z);
        glm::vec4 plane = renderer->getClipingPlane();
        setUniformVector4f("clipPlane" ,plane.x , plane.y , plane.z , plane.w );

    }
};

#endif // FORWARDAMBIENT_H_INCLUDED
