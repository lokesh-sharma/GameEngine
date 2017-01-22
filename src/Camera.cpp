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
    m_transform.SetPos(pos);
    m_transform.setParent(getTransform());
}
void Camera::update(float d)
{
    glm::vec2 mousePos = TheInputHandler::getInstance()->getMousePos();
    glm::vec2 delta = mousePos - screenMiddle;
    float x = -delta.x;
    float y = -delta.y;

    if(x)
    {
        m_transform.rotate(glm::vec3(0,1,0) , x*0.1);
    }
    if(y)
    {
         m_transform.rotate(m_transform.getRight() , y*0.1);
    }
    if(x || y)
        TheInputHandler::getInstance()->setMousePos(screenMiddle.x , screenMiddle.y);


    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_D))
    {
            move( m_transform.getRight() , 0.1);
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_A))
    {
             move( m_transform.getRight() , -0.1);
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_W))
    {
             move( m_transform.getForward() , 0.1);
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_S))
    {
             move( m_transform.getForward() , -0.1);
    }

}
void Camera::move(const glm::vec3 direction , float distance)
{
     m_transform.SetPos( m_transform.GetPos() + direction*distance);

}
void Camera::addToEngine(CoreEngine* core)
{
        core->getRenderingEngine()->addCamera(this);
}
glm::mat4 Camera::getMVP() const
{
    glm::mat4 posmat = glm::translate(-m_transform.GetPos());
    glm::mat4 rotmat = glm::toMat4(glm::conjugate(m_transform.GetRot()));
    glm::mat4 transformedposmat = glm::translate(-getTransform()->GetPos());
    glm::mat4 transformedrotmat = glm::toMat4(glm::conjugate(getTransform()->GetRot()));

    return projection *rotmat*posmat*transformedrotmat*transformedposmat;

    return projection*glm::lookAt( m_transform.GetPos() , m_transform.GetPos() +  m_transform.getForward()
     ,  m_transform.getUp())*getTransform()->GetModel();
}
glm::vec3 Camera::getPos() const
{
    glm::mat4 posmat = glm::translate(-m_transform.GetPos());
     glm::mat4 rotmat = glm::toMat4(glm::conjugate(m_transform.GetRot()));
    glm::mat4 transformedposmat = glm::translate(getTransform()->GetPos());
    glm::mat4 transformedrotmat = glm::toMat4(getTransform()->GetRot());
    glm::vec4 temp ;
    temp.x = m_transform.GetPos().x;
    temp.y = m_transform.GetPos().y;
    temp.z = m_transform.GetPos().z;
    temp.w = 0;
    glm::vec4 t1 = posmat*transformedrotmat*transformedposmat*temp;
    glm::vec3 t2 ;
    t2.x = t1.x;
    t2.y = t1.y;
    t2.z = t1.z;
    return t2;
}
