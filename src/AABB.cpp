#include "AABB.h"

IntersectData AABB::doesIntersectAABB(const AABB& other)
{
    glm::vec3 distances1 = other.getMinExtends() - m_maxExtents;
    glm::vec3 distances2 = other.getMaxExtends() - m_minExtents;

    glm::vec3 distances = glm::min(distances1 , distances2);
    float d = distances.x;
    if(distances.y > d)
        d = distances.y;
    if(distances.z > d)
        d = distances.z;
    return IntersectData(d <0 , d);
}
