#ifndef GAMECOMPONENT_H_INCLUDED
#define GAMECOMPONENT_H_INCLUDED

#include"transform.h"
#include"camera.h"
#include"GameObject.h"

class Shader;
class RenderingEngine;
class CoreEngine;
class GameComponent
{
protected:
    GameObject* m_parent;
public:
    GameComponent() : m_parent(nullptr) {}
    virtual void update(const Transform& t) {};
    virtual void render(Shader& bs,const Camera& c , RenderingEngine* renderingEngine) {};
    virtual void setParent(GameObject* gObject)
    {
        m_parent = gObject;
    }
    virtual Transform* getTransform() const { return m_parent->getTransform();}
    virtual void addToEngine(CoreEngine* core) {};
};


#endif // GAMECOMPONENT_H_INCLUDED
