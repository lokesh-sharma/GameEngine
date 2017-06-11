#ifndef POSTPROCESS_H
#define POSTPROCESS_H
#include"texture.h"
#include"shader.h"
#include"display.h"
class DefaultFilter : public Shader
{
public:
    DefaultFilter(const std::string fileName) : Shader(fileName , false)
    {
         m_uniforms["scene"] = glGetUniformLocation(m_program , "scene");
    }
    virtual void UpdateFilter()
    {
        setUniformSampler("scene" , 0);
    }
};

class BloomFilter : public DefaultFilter
{
public:
    BloomFilter(const std::string fileName) : DefaultFilter(fileName)
    {
        m_uniforms["highlights"] = glGetUniformLocation(m_program , "highlights");
    }
    virtual void UpdateFilter()
    {
        setUniformSampler("scene" , 0);
        setUniformSampler("highlights" , 1);
    }
};
class BrightFilter : public DefaultFilter
{
public:
    BrightFilter(const std::string fileName) : DefaultFilter(fileName)
    {
        m_uniforms["highlights"] = glGetUniformLocation(m_program , "highlights");
    }
    virtual void UpdateFilter()
    {
        setUniformSampler("scene" , 0);
        setUniformSampler("highlights" , 1);
    }
};
class HoriGaussianBlurFilter:public DefaultFilter
{
private:
    float m_width;
public:
    HoriGaussianBlurFilter(const std::string fileName , float width) : DefaultFilter(fileName),
    m_width(width)
    {
         //m_uniforms["scene"] = glGetUniformLocation(m_program , "scene");
         m_uniforms["width"] = glGetUniformLocation(m_program , "width");

    }
    void UpdateFilter()
    {
        setUniformSampler("scene" , 0);
        setUniform1f("width" , m_width );
    }

};
class VertGaussianBlurFilter:public DefaultFilter
{
private:
    float m_height;
public:
    VertGaussianBlurFilter(const std::string fileName , float height) : DefaultFilter(fileName),
    m_height(height)
    {
         m_uniforms["height"] = glGetUniformLocation(m_program , "height");

    }
    void UpdateFilter()
    {
         setUniformSampler("scene" , 0);
         setUniform1f("height" , m_height);
    }

};
class Fxaa : public DefaultFilter
{
private:
    Display* m_display;
public:
    Fxaa(const std::string fileName , Display*d) : DefaultFilter(fileName) , m_display(d)
    {
         m_uniforms["inverseFilterTextureSize"] = glGetUniformLocation(m_program , "inverseFilterTextureSize");
    }
    void UpdateFilter()
    {
        setUniformSampler("scene" , 0);
        setUniformVector3f("inverseFilterTextureSize" , 1.0/m_display->getWidth(), 1.0/m_display->getHeight() , 0.0f);
    }
};
class PostProcess
{
public:
    PostProcess(Display*d);
    Texture* getBaseTexture() { return m_scene;}
    void applyPostProcess();
    void applyFilter(DefaultFilter* filter ,  Texture* scene1 , Texture*scene2=0 ,Texture* output=0);
    virtual ~PostProcess();
private:
    Display* m_display;
    Texture* m_scene;
    Texture* m_afterFxaa;
    Texture* m_afterHBlur;
    Texture* m_afterVBlur;
    Texture* m_afterBrigtnessCutOff;
    DefaultFilter* m_default;
    DefaultFilter* m_horiGaussianBlur;
    DefaultFilter* m_vertGaussianBlur;
    DefaultFilter* m_bright;
    DefaultFilter* m_bloom;
    GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffer;
	int m_width;
	int m_height;
};



#endif // POSTPROCESS_H
