#include "PhysicsObjectComponent.h"

void PhysicsObjectComponent::update(float delta)
{
    getTransform()->SetPos(m_phyObject->getPosition());

}
