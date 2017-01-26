#include "PhysicsEngine.h"
#include "BoundingSphere.h"
#include<iostream>

void PhysicsEngine::addObject(PhysicsObject*object)
{
    m_objects.push_back(object);
}
void PhysicsEngine::simulate(float delta)
{
    for(int i = 0 ; i< m_objects.size() ; i++)
    {
        m_objects[i]->integrate(delta);
    }
}
void PhysicsEngine::handleCollisions()
{
    for(int i = 0 ; i< m_objects.size() ; i++)
    {
        for(int j = i+1 ; j< m_objects.size() ; j++)
        {
            IntersectData intersectData = m_objects[i]->getCollider().doesIntersect(
            m_objects[j]->getCollider());

            if(intersectData.getDoesIntersect())
            {
                m_objects[i]->setVelocity(-m_objects[i]->getVelocity());
                m_objects[j]->setVelocity(-m_objects[j]->getVelocity());
            }
        }
    }
}
