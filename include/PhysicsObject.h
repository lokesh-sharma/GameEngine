#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include<glm/glm.hpp>
#include"BoundingSphere.h"

class PhysicsObject
{
public:
    PhysicsObject(glm::vec3 pos , glm::vec3 vel , float r) : m_position(pos) , m_velocity(vel),
    m_radius(r) {}
    glm::vec3 getVelocity() const { return m_velocity;}
    glm::vec3 getPosition() const { return m_position;}
    void setVelocity(glm::vec3 vel) { m_velocity = vel; }
    float getRadius() const { return m_radius;}
    BoundingSphere getBoundingSphere() const { return BoundingSphere(m_position ,m_radius);}
    void integrate(float delta) ;
private:
    glm::vec3 m_position;
    glm::vec3 m_velocity;
    float m_radius;
};

#endif // PHYSICSOBJECT_H
