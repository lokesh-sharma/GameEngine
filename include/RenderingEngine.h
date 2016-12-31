#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include"GameObject.h"
#include"camera.h"
#include"InputHandler.h"
class RenderingEngine
{
public:
    RenderingEngine();
    void render(GameObject* object);
    virtual ~RenderingEngine();
private:
    Shader* ambientShader;
    Shader* directionalShader;
    Shader* pointShader;
    Camera* camera;
    RenderingEngine(const RenderingEngine& other) {}
    RenderingEngine& operator=(const RenderingEngine& other) {}
};

#endif // RENDERINGENGINE_H
