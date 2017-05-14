#include"camera.h"
#include"display.h"
#include"CoreEngine.h"

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar):
GameComponent()
{
    this->projection = glm::perspective(fov, aspect, zNear, zFar);
    //getTransform()->SetPos(pos);
}
void Camera::update()
{
}
void Camera::addToEngine(CoreEngine* core)
{
        core->getRenderingEngine()->addCamera(this);
}
glm::mat4 Camera::getMVP() const
{
    //glm::mat4 transformedposmat = glm::translate(-getTransform()->GetPos());
    //glm::mat4 transformedrotmat = glm::toMat4(glm::conjugate(getTransform()->GetRot()));

    return projection *getModel();
}
glm::vec3 Camera::getPos() const
{
    return getTransform()->GetPos();
}
