#include "PhysicsObjectComponent.h"

void PhysicsObjectComponent::update()
{
    getTransform()->SetTransform(*(m_phyObject->getTransform()));

}
