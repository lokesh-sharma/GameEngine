#ifndef PLANE_H
#define PLANE_H
#include"IntersectData.h"
#include"BoundingSphere.h"
#include<glm/glm.hpp>

class Plane
{
public:
    Plane(const glm::vec3 normal , const glm::vec3 distance): m_normal(glm::normalize(normal)) ,
     m_distance(distance)
    {
    }
    inline glm::vec3 getNormal() { return m_normal ;}
    inline glm::vec3 getDistance() { return m_distance; }
    IntersectData doesIntersectSphere(const BoundingSphere& sphere) const;
private:
    const glm::vec3 m_normal;
    const glm::vec3 m_distance;
};

#endif // PLANE_H
