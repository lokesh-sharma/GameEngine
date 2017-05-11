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
class Texture;
class Material;
class Mesh;
class RenderingEngine
{
public:
    RenderingEngine(Display* d);
    void render(GameObject* object);
    void addDirectionalLight(DirectionalLight* light);
    void addPointLight(PointLight* light);
    void addSpotLight(SpotLight* light);
    void addCamera(Camera* c) { camera = c;}
    PointLight* getActivePointLight() { return active_point_light;}
    DirectionalLight* getActiveDirectionalLight() { return active_dir_light;}
    SpotLight* getActiveSpotLight() { return active_spot_light;}
    Texture* getShadowMap() { return temptarget ; }
    glm::mat4 getLightMatrix() { return m_lightMatrix;}
    CoreEngine* getCoreEngine() { return core;}
    float getShadowBias() { return shadowMapBias;}
    void setShadowBias(float b) { shadowMapBias = b;}
    glm::vec3 getShadowTexelSize() { return shadowTexelSize ;}
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
    Shader* shadowShader;
    Camera* camera;
    Camera* altCamera;
    Texture* temptarget;
    float shadowMapBias ;
    glm::vec3 shadowTexelSize;
    Mesh * mesh ;
    Transform temp_transform;
    Material* temp_material;
    GameObject* cameraObject;
    glm::mat4 m_lightMatrix;
    Display* display;
    CoreEngine* core;
    RenderingEngine(const RenderingEngine& other) {}
    RenderingEngine& operator=(const RenderingEngine& other) {}
};

#endif // RENDERINGENGINE_H
