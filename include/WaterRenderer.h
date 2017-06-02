#ifndef WATERRENDERER_H
#define WATERRENDERER_H
#include<vector>
#include"WaterShader.h"
#include"texture.h"
class RenderingEngine;

class WaterRenderer
{
public:
    struct WaterQuad
    {
        glm::vec3 position;
        glm::vec3 scale;
    };
    WaterRenderer();
    void addWaterQuad(WaterQuad q);
    Texture* getReflectionMap() { return m_reflectionMap;}
    Texture* getRefractionMap() { return m_refractionMap;}
    void setWaveSpeed(float v ) { m_waveSpeed = v;};
    void render(const Camera& c , RenderingEngine* render);
    virtual ~WaterRenderer();
private:
    WaterShader* m_waterShader;
    Texture* m_dudvMap;
    Texture* m_normalMap;
    Texture* m_reflectionMap;
    Texture* m_refractionMap;
    float m_waveSpeed;
    std::vector<WaterQuad> m_quads;
    GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffer;
};

#endif // WATERRENDERER_H
