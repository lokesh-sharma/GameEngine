#include "FPSCamera.h"

#include"display.h"
#include"CoreEngine.h"

FPSCamera::FPSCamera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar):
Camera(pos,fov,aspect,zNear,zFar)
{
    int width = TheInputHandler::getInstance()->getDisplay()->getWidth();
    int height = TheInputHandler::getInstance()->getDisplay()->getHeight();
    screenMiddle = glm::vec2(width/2 , height/2);
    m_rot = glm::quat(1,0,0,0);
}
void FPSCamera::update()
{
    glm::vec2 mousePos = TheInputHandler::getInstance()->getMousePos();
    glm::vec2 delta = mousePos - screenMiddle;
    float x = -delta.x;
    float y = -delta.y;

    if(x)
    {
       getTransform()->rotate(glm::vec3(0,1,0) , x*0.1);
       //std::cout<<getTransform()->getRight().x<<std::endl;
       glm::quat rot = glm::angleAxis(x*0.1f ,glm::vec3(0,1,0));
        m_rot = glm::normalize(rot*m_rot);
    }
    if(y)
    {
         glm::quat rot = glm::angleAxis(y*0.1f ,getTransform()->getRight());
         m_rot = glm::normalize(rot*m_rot);
    }
    if(x || y)
        TheInputHandler::getInstance()->setMousePos(screenMiddle.x , screenMiddle.y);

}
void FPSCamera::addToEngine(CoreEngine* core)
{
        core->getRenderingEngine()->addCamera(this);
}
glm::mat4 FPSCamera::getMVP() const
{
    glm::vec3 pos =getTransform()->GetPos();
    pos.y += 2;
    glm::mat4 transformedposmat = glm::translate(-pos);
    glm::mat4 transformedrotmat = glm::toMat4(glm::conjugate(m_rot));
    return projection*transformedrotmat*transformedposmat;
}
glm::vec3 FPSCamera::getPos() const
{
    return getTransform()->GetPos();
}
