#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include"GameObject.h"
#include"camera.h"
#include"InputHandler.h"
#include<vector>
class Display;
class DirectionalLight;
class PointLight;
class SpotLight;
class RenderingEngine
{
public:
    RenderingEngine();
    void init(Display* d);
    void render(GameObject* object);
    void setDisplay(Display* d) { display = d;}
    void addDirectionalLight(DirectionalLight* light);
    void addPointLight(PointLight* light);
    void addSpotLight(SpotLight* light);
    void addCamera(Camera* c) { camera = c;}
    PointLight* getActivePointLight() { return active_point_light;}
    DirectionalLight* getActiveDirectionalLight() { return active_dir_light;}
    SpotLight* getActiveSpotLight() { return active_spot_light;}
    CoreEngine* getCoreEngine() { return core;}
    void setCoreEngine(CoreEngine* c) { core = c ;}
    Camera* getCamera() { return camera;}
    virtual ~RenderingEngine();
private:
    std::vector<DirectionalLight*>dir_lights;
    std::vector<PointLight*>point_lights;
    std::vector<SpotLight*>spot_lights;
    PointLight* active_point_light;
    DirectionalLight* active_dir_light;
    SpotLight* active_spot_light;
    Shader* ambientShader;
    Camera* camera;
    Display* display;
    CoreEngine* core;
    RenderingEngine(const RenderingEngine& other) {}
    RenderingEngine& operator=(const RenderingEngine& other) {}
};

#endif // RENDERINGENGINE_H
