#include"Light.h"
#include"ForwardDirectional.h"
#include"ForwardPoint.h"
#include"ForwardSpot.h"

glm::vec3 DirectionalLight::getDirection() const
{
    return -GameComponent::getTransform()->getUp();
}

glm::vec3 SpotLight::getDirection()
{
    return m_parent->getTransform()->getForward();
}
DirectionalLight:: DirectionalLight(const glm::vec3 color , float inten ) :
    BaseLight(color , inten )
{
    m_shader = new ForwardDirectional("./res/forward-directional");
}
PointLight::PointLight(const glm::vec3 color , float inten , glm::vec3 pos ,float c
    , float l,float e, float r):
    BaseLight(color , inten) , atten(c,l,e) , range(r) , position(pos)
{
        m_shader = new ForwardPoint("./res/forward-pointLight");
}
SpotLight::SpotLight(const glm::vec3 color , float inten , glm::vec3 pos ,glm::vec3 dir,
    float c, float l,float e , float r , float cut) :
    PointLight(color , inten,pos,c ,l , e , r) , cut_off(cut) , direction(dir)
{
        m_shader = new ForwardSpot("./res/forward-spotLight");
}
