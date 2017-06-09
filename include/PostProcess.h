#ifndef POSTPROCESS_H
#define POSTPROCESS_H
#include"texture.h"
#include"shader.h"

class Display;
class DefaultShader : public Shader
{
public:
    DefaultShader(const std::string fileName) : Shader(fileName , false)
    {
         m_uniforms["scene"] = glGetUniformLocation(m_program , "scene");
    }
    void Update()
    {
        setUniformSampler("scene" , 0);
    }
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
    DefaultShader* m_default;
    GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffer;
	int m_width;
	int m_height;
};



#endif // POSTPROCESS_H
