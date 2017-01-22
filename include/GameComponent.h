#ifndef GAMECOMPONENT_H_INCLUDED
#define GAMECOMPONENT_H_INCLUDED

#include"transform.h"
#include"GameObject.h"

class Camera;
class Shader;
class RenderingEngine;
class CoreEngine;
class GameComponent
{
protected:
    GameObject* m_parent;
public:
    GameComponent() : m_parent(nullptr) {}
    virtual void update(float delta) {};
    virtual void render(Shader& bs,const Camera& c , RenderingEngine* renderingEngine) {};
    virtual void setParent(GameObject* gObject)
    {
        m_parent = gObject;
    }
    virtual Transform* getTransform() const { return m_parent->getTransform();}
    virtual void addToEngine(CoreEngine* core) {};
};


#endif // GAMECOMPONENT_H_INCLUDED
