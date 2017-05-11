#ifndef SHADOWSHADER_H_INCLUDED
#define SHADOWSHADER_H_INCLUDED

#include"Light.h"
#include"shader.h"

class ShadowShader : public Shader
{
public:
    ShadowShader(const std::string fileName) : Shader(fileName)
    {
    }
    void Update(const Transform& transform,const Camera&c,const Material& m , RenderingEngine* renderer)
    {
        Shader::Update(transform , c,m ,renderer );
    }
};

#endif // SHADOWSHADER_H_INCLUDED
