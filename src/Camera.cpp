#include"camera.h"
#include"display.h"
#include"CoreEngine.h"

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar):
GameComponent()
{
    this->projection = glm::perspective(fov, aspect, zNear, zFar);
    int width = TheInputHandler::getInstance()->getDisplay()->getWidth();
    int height = TheInputHandler::getInstance()->getDisplay()->getHeight();
    screenMiddle = glm::vec2(width/2 , height/2);
    initialPos = pos;
}
void Camera::update()
{
    getTransform()->SetPos(initialPos);
    glm::vec2 mousePos = TheInputHandler::getInstance()->getMousePos();
    glm::vec2 delta = mousePos - screenMiddle;
    float x = -delta.x;
    float y = -delta.y;

    if(x)
    {
        getTransform()->rotate(glm::vec3(0,1,0) , x*0.1);
    }
    if(y)
    {
        getTransform()->rotate(getTransform()->getRight() , y*0.1);
    }
    if(x || y)
        TheInputHandler::getInstance()->setMousePos(screenMiddle.x , screenMiddle.y);


    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_D))
    {
            move(getTransform()->getRight() , 0.5);
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_A))
    {
             move(getTransform()->getRight() , -0.5);
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_W))
    {
             move(getTransform()->getForward() , 0.5);
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_S))
    {
             move(getTransform()->getForward() , -0.5);
    }
    initialPos = getTransform()->GetPos();

}
void Camera::move(const glm::vec3 direction , float distance)
{
    getTransform()->SetPos(getTransform()->GetPos() + direction*distance);

}
void Camera::addToEngine(CoreEngine* core)
{
        core->getRenderingEngine()->addCamera(this);
}
glm::mat4 Camera::getMVP() const
{
    return projection*glm::lookAt(getTransform()->GetPos() ,getTransform()->GetPos() + getTransform()->getForward()
     , getTransform()->getUp());
}
