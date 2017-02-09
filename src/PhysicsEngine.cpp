#include "PhysicsEngine.h"
#include "BoundingSphere.h"
#include<iostream>

PhysicsEngine::PhysicsEngine()
{
    collisionConfig = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfig);
    broadPhase = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();
    world = new btDiscreteDynamicsWorld(dispatcher , broadPhase ,solver ,collisionConfig);
    world->setGravity(btVector3(0 ,-10 , 0));
}
void PhysicsEngine::addObject(PhysicsObject*object , std::string id)
{
    m_objects[id] = object;
    world->addRigidBody(object->getRigidBody());
}
void PhysicsEngine::simulate(float delta)
{
    std::map<std::string , PhysicsObject*>::iterator it;
    for(it = m_objects.begin() ; it!= m_objects.end() ; it++)
    {
        it->second->integrate();
    }
    world->stepSimulation(delta);
}
void PhysicsEngine::handleCollisions()
{

}
