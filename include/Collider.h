#ifndef COLLIDER_H
#define COLLIDER_H

#include"IntersectData.h"
#include<glm/glm.hpp>

class Collider
{
public:
    enum
    {
        TYPE_BOUNDINGSPHERE,
        TYPE_AABB,
        TYPE_SIZE
    };
    Collider(int type ): m_type(type){};
    IntersectData doesIntersect(const Collider& other)const;
    virtual void transform(glm::vec3 translation) {} ;
    virtual glm::vec3 getCenter() const { return glm::vec3(0, 0 , 0);}
    inline int getType() const { return m_type;}
private:
    int m_type;
};

#endif // COLLIDER_H
