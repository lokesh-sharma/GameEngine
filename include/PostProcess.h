#ifndef POSTPROCESS_H
#define POSTPROCESS_H
#include"texture.h"
#include"shader.h"
#include"display.h"
class DefaultShader : public Shader
{
public:
    DefaultShader(const std::string fileName) : Shader(fileName , false)
    {
         m_uniforms["scene"] = glGetUniformLocation(m_program , "scene");
    }
    void UpdateFilter()
    {
        setUniformSampler("scene" , 0);
    }
};
class Fxaa : public Shader
{
private:
    Display* m_display;
public:
    Fxaa(const std::string fileName) : Shader(fileName , false)
    {
         m_uniforms["scene"] = glGetUniformLocation(m_program , "scene");
         m_uniforms["inverseFilterTextureSize"] = glGetUniformLocation(m_program , "inverseFilterTextureSize");
    }
    void UpdateFilter()
    {
        setUniformSampler("scene" , 0);

        setUniformVector3f("inverseFilterTextureSize" , 1.0/m_display->getWidth(), 1.0/m_display->getHeight() , 0.0f);
    }
    void setDisplay(Display*d) { m_display = d;}
};
class PostProcess
{
public:
    PostProcess(Display*d);
    Texture* getBaseTexture() { return m_scene;}
    void applyPostProcess();
    virtual ~PostProcess();
private:
    Display* m_display;
    Texture* m_scene;
    Fxaa* m_default;
    GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffer;
	int m_width;
	int m_height;
};



#endif // POSTPROCESS_H
