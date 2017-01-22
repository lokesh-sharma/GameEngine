#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include<vector>
#include"transform.h"
class Camera;
class Shader;
class GameComponent;
class CoreEngine;
class RenderingEngine;

class GameObject
{
private:
    std::vector<GameObject*> m_children;
    std::vector<GameComponent*> m_components;
    Transform m_transform;
    CoreEngine* coreEngine;
public:
    GameObject() : m_transform(Transform()){}
    void update(float delta);

    void render(Shader& bs, const Camera& camera , RenderingEngine* renderingEngine);

    void addChild(GameObject* object);

    void addComponent(GameComponent* component);
    void setEngine(CoreEngine* core);
    //Transform* getTransform() const  { return &m_transform;}
    Transform* getTransform()  { return &m_transform;}
};

#endif // GAMEOBJECT_H_INCLUDED
