#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include<glm/glm.hpp>
#include"BoundingSphere.h"

class PhysicsObject
{
public:
    PhysicsObject(Collider* collider , glm::vec3 vel):m_position(collider->getCenter()),
    m_oldPosition(collider->getCenter()) , m_velocity(vel) , m_collider(collider)
    {}
    glm::vec3 getVelocity() const { return m_velocity;}
    glm::vec3 getPosition() const { return m_position;}
    void setVelocity(glm::vec3 vel) { m_velocity = vel; }
    const Collider& getCollider()
    {
        glm::vec3 translation = m_position - m_oldPosition;
        m_oldPosition = m_position;
        m_collider->transform(translation);
        return *m_collider;
    }
    void integrate(float delta) ;
private:
    glm::vec3 m_position;
    glm::vec3 m_oldPosition;
    glm::vec3 m_velocity;

    mutable Collider*  m_collider;
};

#endif // PHYSICSOBJECT_H
