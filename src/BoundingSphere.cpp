#include "BoundingSphere.h"

IntersectData BoundingSphere::intersectBoundingSphere(const BoundingSphere& other)
{
    float radiusDistance = m_radius + other.getRadius();
    float centerDistance = glm::length(other.getCenter()-m_center);

    return IntersectData(centerDistance< radiusDistance , centerDistance-radiusDistance);
}
void BoundingSphere::transform(glm::vec3 translation)
{
    m_center += translation;
}
