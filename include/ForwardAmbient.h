#ifndef FORWARDAMBIENT_H_INCLUDED
#define FORWARDAMBIENT_H_INCLUDED

#include"Light.h"
#include"shader.h"

class ForwardAmbient : public Shader
{
public:
    ForwardAmbient(const std::string fileName) : Shader(fileName) {}
    void Update()
    {
        Shader::Update(const Transform& transform, const Camera& camera)
    }
    void setAmbient(glm::vec4 color)
    {
        setUniformVector4f("MaterialAmbientColor" , color.x , color.y ,color.z,color.w);
    }
};

#endif // FORWARDAMBIENT_H_INCLUDED
