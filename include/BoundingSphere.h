#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H
#include<glm/glm.hpp>
#include"IntersectData.h"
#include"Collider.h"

class BoundingSphere : public Collider
{
public:
    BoundingSphere(glm::vec3 center , float radius) : Collider(Collider::TYPE_BOUNDINGSPHERE),
    m_radius(radius) , m_center(center)
    {}
    IntersectData intersectBoundingSphere(const BoundingSphere& other);
    virtual void transform(glm::vec3 translation);
    virtual glm::vec3 getCenter() const { return m_center; }
    inline float getRadius() const { return m_radius;}

private:
    float m_radius;
    glm::vec3 m_center;
};

#endif // BOUNDINGSPHERE_H
