#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include"GameObject.h"
#include"camera.h"
#include"InputHandler.h"
#include<vector>
class Display;
class DirectionalLight;
class PointLight;
class RenderingEngine
{
public:
    RenderingEngine();
    void init(Display* d);
    void render(GameObject* object);
    void setDisplay(Display* d) { display = d;}
    void addDirectionalLight(DirectionalLight* light);
    void addPointLight(PointLight* light);
    void addCamera(Camera* c) { camera = c;}
    PointLight* getActivePointLight() { return active_point_light;}
    DirectionalLight* getActiveDirectionalLight() { return active_dir_light;}
    virtual ~RenderingEngine();
private:
    std::vector<DirectionalLight*>dir_lights;
    std::vector<PointLight*>point_lights;
    PointLight* active_point_light;
    DirectionalLight* active_dir_light;
    Shader* ambientShader;
    Camera* camera;
    Display* display;
    RenderingEngine(const RenderingEngine& other) {}
    RenderingEngine& operator=(const RenderingEngine& other) {}
};

#endif // RENDERINGENGINE_H
