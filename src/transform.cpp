#include"transform.h"
#include"camera.h"

void Transform::rotate(const glm::quat rotation)
{
    rot = glm::quat(glm::normalize(rotation*rot));
}
void Transform::rotate(const glm::vec3 axis , float angle)
{
    rotate(glm::angleAxis(angle , axis));
}
bool Transform::hasChanged() const
{
    if(m_parent!=nullptr && m_parent->hasChanged())
        return true;
    if(pos != oldPos)
        return true;
    if(rot != oldrot)
        return true;
    if(scale!= oldScale)
        return true;
    return false;
}
glm::mat4 Transform::getParentMatrix() const
{
    if(m_parent!= nullptr && m_parent->hasChanged()){
        parentMatrix = m_parent->GetModel();
        }
    return parentMatrix;
}
