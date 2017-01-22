#ifndef PHYSICSOBJECTCOMPONENT_H
#define PHYSICSOBJECTCOMPONENT_H

#include"PhysicsObject.h"
#include"GameComponent.h"

class PhysicsObjectComponent : public GameComponent
{
public:
    PhysicsObjectComponent(PhysicsObject* object) : m_phyObject(object) {};
    virtual void update(float delta);
private:
    PhysicsObject* m_phyObject;
};

#endif // PHYSICSOBJECTCOMPONENT_H
