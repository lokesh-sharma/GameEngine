#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H
#include<glm/glm.hpp>
#include"IntersectData.h"

class BoundingSphere
{
public:
    BoundingSphere(glm::vec3 center , float radius) : m_radius(radius) , m_center(center) {}
    IntersectData intersectBoundingSphere(const BoundingSphere& other);
    inline float getRadius() const { return m_radius;}
    inline glm::vec3 getCenter() const { return m_center;}
private:
    const float m_radius;
    const glm::vec3 m_center;
};

#endif // BOUNDINGSPHERE_H
