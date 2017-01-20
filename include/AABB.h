#ifndef AABB_H
#define AABB_H
#include"IntersectData.h"
#include<glm/glm.hpp>

class AABB
{
public:
    AABB(glm::vec3 min , glm::vec3 max) : m_minExtents(min) , m_maxExtents(max) {}
    IntersectData doesIntersectAABB(const AABB& other);
    inline glm::vec3 getMinExtends() const { return m_minExtents;}
    inline glm::vec3 getMaxExtends() const { return m_maxExtents;}
private:
    const glm::vec3 m_minExtents;
    const glm::vec3 m_maxExtents;
};

#endif // AABB_H
