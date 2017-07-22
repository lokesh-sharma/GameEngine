#ifndef SUNRENDERER_H
#define SUNRENDERER_H

#include"camera.h"
#include"transform.h"
#include"SunShader.h"
#include"texture.h"

class SunRenderer
{
public:
    SunRenderer(glm::vec3 pos , glm::vec3 scale);
    void renderSun(const Camera& c);
    virtual ~SunRenderer();
private:
    Texture* m_sunImage;
    SunShader* m_sunShader;
    glm::vec3 m_position;
    glm::vec3 m_scale;
    GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffer;

};

#endif // SUNRENDERER_H
