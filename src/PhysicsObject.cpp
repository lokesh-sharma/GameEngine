#include "PhysicsObject.h"

void PhysicsObject::integrate(float delta)
{
    m_position += m_velocity*delta;
}
