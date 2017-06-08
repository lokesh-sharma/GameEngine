#ifndef SHADOWSHADER_H_INCLUDED
#define SHADOWSHADER_H_INCLUDED

#include"Light.h"
#include"shader.h"
#include"string"
#include <glm/gtc/type_ptr.hpp>

class DirectionalShadowShader : public Shader
{
public:
    DirectionalShadowShader(const std::string fileName) : Shader(fileName , true)
    {
        int diffuseLocation = glGetUniformLocation(m_program , "diffuse");
        if(diffuseLocation>=0)
            m_uniforms["diffuse"] = diffuseLocation;
    }
    void Update(const Transform& transform,const Camera&c,const Material& m , RenderingEngine* renderer)
    {
        Shader::Update(transform , c,m ,renderer );
        setUniformSampler("diffuse" , 0);
    }
};
class PointShadowShader : public Shader
{
private:
public:
    PointShadowShader(const std::string fileName) : Shader(fileName , true)
    {
        int diffuseLocation = glGetUniformLocation(m_program , "diffuse");
        if(diffuseLocation>=0)
            m_uniforms["diffuse"] = diffuseLocation;
        std::string shadowMat = "shadowMatrices";
        for(int i = 0 ; i< 6 ; i++){
            std::string index = "[" + std::to_string(i) + "]";
            m_uniforms[shadowMat+index] = glGetUniformLocation(m_program, (shadowMat+index).c_str());
        }
        m_uniforms["lightPos"] = glGetUniformLocation(m_program , "lightPos");
        m_uniforms["farPlane"] = glGetUniformLocation(m_program , "farPlane");
    }
    void Update(const Transform& transform,const Camera&c,const Material& m , RenderingEngine* renderer)
    {

        Shader::Update(transform , c,m ,renderer );
        setUniformSampler("diffuse" , 0);
        glm::mat4 shadowProj  = renderer->getActivePointLight()->getShadowInfo()->getProjection();
        glm::mat4 pMatrix = renderer->getActivePointLight()->getTransform()->getParentMatrix();
        glm::vec3 pos = renderer->getActivePointLight()->getTransform()->GetPos();

       glm::vec4 transformedPos = pMatrix*glm::vec4(pos.x , pos.y , pos.z , 1);
        glm::vec3 lightPos = glm::vec3(transformedPos.x,transformedPos.y,transformedPos.z);


        std::vector<glm::mat4> shadowTransforms;
        shadowTransforms.push_back(shadowProj *
                 glm::lookAt(lightPos, lightPos + glm::vec3(1.0,0.0,0.0), glm::vec3(0.0,-1.0,0.0)));
        shadowTransforms.push_back(shadowProj *
                 glm::lookAt(lightPos, lightPos + glm::vec3(-1.0,0.0,0.0), glm::vec3(0.0,-1.0,0.0)));
        shadowTransforms.push_back(shadowProj *
                 glm::lookAt(lightPos, lightPos + glm::vec3(0.0,1.0,0.0), glm::vec3(0.0,0.0,-1.0)));
        shadowTransforms.push_back(shadowProj *
                 glm::lookAt(lightPos, lightPos + glm::vec3(0.0,-1.0,0.0), glm::vec3(0.0,0.0,-1.0)));
        shadowTransforms.push_back(shadowProj *
                 glm::lookAt(lightPos, lightPos + glm::vec3(0.0,0.0,1.0), glm::vec3(0.0,-1.0,0.0)));
        shadowTransforms.push_back(shadowProj *
                 glm::lookAt(lightPos, lightPos + glm::vec3(0.0,0.0,-1.0), glm::vec3(0.0,-1.0,0.0)));
        std::string shadowMat = "shadowMatrices";
        for(int i = 0 ; i< 6 ; i++)
        {
            std::string uname = shadowMat + "[" + std::to_string(i) + "]";
            setUniformMatrix4f( uname.c_str(), glm::value_ptr(shadowTransforms[i]));
        }
        setUniform1f("farPlane" , 25.0f);
        setUniformVector3f("lightPos" , lightPos.x , lightPos.y , lightPos.z);
    }
};

#endif // SHADOWSHADER_H_INCLUDED
