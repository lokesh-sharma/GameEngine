#include "Collider.h"
#include"BoundingSphere.h"

IntersectData Collider::doesIntersect(const Collider& other) const
{
    if(m_type == TYPE_BOUNDINGSPHERE && other.getType() == TYPE_BOUNDINGSPHERE)
    {
        BoundingSphere* self = (BoundingSphere*)this;
        return self->intersectBoundingSphere((BoundingSphere&)other);
    }

    return IntersectData(false , 0);
}
