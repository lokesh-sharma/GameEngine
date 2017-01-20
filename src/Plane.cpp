#include "Plane.h"

IntersectData Plane::doesIntersectSphere(const BoundingSphere& sphere) const
{
    float distanceFromCenter = glm::dot(sphere.getCenter()-m_distance , m_normal);
    if(distanceFromCenter<0)
        distanceFromCenter = -distanceFromCenter;

    float distance = distanceFromCenter-sphere.getRadius();

    return IntersectData(distance < 0 , distance);

}
