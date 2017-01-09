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
