#include "PhysicsObjectComponent.h"

void PhysicsObjectComponent::update(float delta)
{
    getTransform()->SetTransform(*(m_phyObject->getTransform()));

}
