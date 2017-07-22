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
    virtual void UpdateFilter(const Camera& c)
    {
        setUniformSampler("scene" , 0);
    }
};
class SSAOFilter : public DefaultFilter
{
private:
    std::vector<glm::vec3> ssaoKernel;
    int kernelSize ;
    float Lerp(float  a , float b , float factor)
    {
        return a + factor*(b-a);
    }

public:
    SSAOFilter(const std::string fileName ) : DefaultFilter(fileName)
    {
        kernelSize = 64;
        srand(time(NULL));

        for(int i = 0 ; i < kernelSize ; i++)
        {
            float number1 = rand();
            number1 = number1/RAND_MAX;
            float number2 = rand();
            number2 = number2/RAND_MAX;
            float number3 = rand();
            number3 = number3/RAND_MAX;
            glm::vec3 sample(number1*2-1 , number2*2-1 , number3*2-1);
            //sample = glm::normalize(sample);
            float number4 = rand();
            number4 = number4/RAND_MAX;
            number4 = number4*2 -1;
            float number5 = rand();
            number5 = number5/RAND_MAX;
            number5 = number5*2 -1;
            sample = sample*number4*number5;
            //float scale = i/64.0;
            //scale = Lerp(0.1, 1.0 , scale*scale);
            //sample *= scale;
            ssaoKernel.push_back(sample);


        }
        m_uniforms["noiseTexture"] = glGetUniformLocation(m_program , "noiseTexture");
        m_uniforms["inv_proj"] = glGetUniformLocation(m_program , "inv_proj");
        m_uniforms["proj"] = glGetUniformLocation(m_program , "proj");
        for(int i = 0 ; i< kernelSize ; i++)
        {
            std::string s = "samples";
            s += "[" + std::to_string(i) + "]";
            m_uniforms[s] = glGetUniformLocation(m_program , s.c_str());
        }
    }
    virtual void UpdateFilter(const Camera& c)
    {
        for(int i = 0 ; i< kernelSize ; i++)
        {
            std::string s = "samples";
            s += "[" + std::to_string(i) + "]";
            setUniformVector3f(s , ssaoKernel[i].x , ssaoKernel[i].y ,ssaoKernel[i].z );
        }
        setUniformSampler("scene" , 0);
        setUniformSampler("noiseTexture" , 1);
        setUniformMatrix4f("inv_proj" , &c.getInverseProj()[0][0]);
        setUniformMatrix4f("proj" , &c.getMVP()[0][0]);
    }
};
class BloomFilter : public DefaultFilter
{
public:
    BloomFilter(const std::string fileName) : DefaultFilter(fileName)
    {
        m_uniforms["highlights"] = glGetUniformLocation(m_program , "highlights");
    }
    virtual void UpdateFilter(const Camera& c)
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
    virtual void UpdateFilter(const Camera& c)
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
    void UpdateFilter(const Camera& c)
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
    void UpdateFilter(const Camera& c)
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
    void UpdateFilter(const Camera& c)
    {
        setUniformSampler("scene" , 0);
        setUniformVector3f("inverseFilterTextureSize" , 1.0/m_display->getWidth(), 1.0/m_display->getHeight() , 0.0f);
    }
};
class PostProcess
{
public:
    PostProcess(Display*d , RenderingEngine* renderer);
    Texture* getBaseTexture() { return m_scene;}
    void applyPostProcess();
    void applyFilter(DefaultFilter* filter ,  Texture* scene1 , Texture*scene2=0 ,Texture* output=0);

    Texture* getSSAOTexture() { return m_afterSSAO;}
    virtual ~PostProcess();
private:
    RenderingEngine* m_renderingEngine;
    Display* m_display;
    Texture* m_scene;
    Texture* m_afterFxaa;
    Texture* m_afterHBlur;
    Texture* m_afterVBlur;
    Texture* m_afterBrigtnessCutOff;
    Texture* m_afterSSAO;
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
