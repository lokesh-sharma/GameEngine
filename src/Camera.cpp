#include"camera.h"

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
{
    this->pos = pos;
    this->forward = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->projection = glm::perspective(fov, aspect, zNear, zFar);
    this->oldMousePos = glm::vec2(400,300);
}
void Camera::moveSideways(float d)
{
    glm::vec3 right = glm::cross(forward , up);
    right =  glm::normalize(right);
    glm::vec4 temp = glm::vec4(pos,1);
    glm::mat4 posMat = glm::translate(right*d);
    temp = posMat*temp;
    pos = glm::vec3(temp);
}
void Camera::moveforwardBack(float d)
{
    glm::vec4 temp = glm::vec4(pos,1);
    glm::mat4 posMat = glm::translate(glm::normalize(forward)*d);
    temp = posMat*temp;
    pos = glm::vec3(temp);

}
void Camera::update(const glm::vec2 mousePos)
{
    glm::vec2 delta = mousePos - oldMousePos;
    float x = delta.x;
    float y = delta.y;
    x = x*0.4;
    y = y*0.4;
    forward = glm::mat3(glm::rotate( -x , up))*forward;
    glm::vec3 right = glm::cross(forward , up);
    forward = glm::mat3(glm::rotate(-y , right ))*forward;
    oldMousePos = mousePos;

    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_D))
    {
            moveSideways(0.5);
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_A))
    {
            moveSideways(-0.5);
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_W))
    {
            moveforwardBack(0.5);
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_S))
    {
            moveforwardBack(-0.5);
    }
}
