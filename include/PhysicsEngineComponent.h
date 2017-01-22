#ifndef PHYSICSENGINECOMPONENT_H
#define PHYSICSENGINECOMPONENT_H

#include"GameComponent.h"
#include"PhysicsEngine.h"

class PhysicsEngineComponent : public GameComponent
{
public:
    PhysicsEngineComponent(PhysicsEngine* engine) : m_physicsEngine(engine) {}
    PhysicsEngine* getEngine() const { return m_physicsEngine ; }
    void update(float delta);
private:
    PhysicsEngine* m_physicsEngine;
};

#endif // PHYSICSENGINECOMPONENT_H
