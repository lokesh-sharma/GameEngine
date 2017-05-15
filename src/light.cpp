#include"Light.h"
#include"ForwardDirectional.h"
#include"ForwardPoint.h"
#include"ForwardSpot.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include<glm/detail/func_geometric.hpp>

glm::vec3 DirectionalLight::getDirection() const
{
    return GameComponent::getTransform()->getForward();
}

glm::vec3 SpotLight::getDirection()
{
    return m_parent->getTransform()->getForward();
}
DirectionalLight:: DirectionalLight(const glm::vec3 color , float inten ) :
    BaseLight(color , inten )
{
    m_shader = new ForwardDirectional("./res/forward-directional");
    m_shadowInfo = new ShadowInfo(glm::ortho(-10.0f,10.0f,-10.0f,10.0f,-10.0f,20.0f), 3.0/1024.0);
}
PointLight::PointLight(const glm::vec3 color , float inten , float c
    , float l,float e, float r):
    BaseLight(color , inten) , atten(c,l,e) , range(r)
{
        m_shader = new ForwardPoint("./res/forward-pointLight");
        m_shadowInfo = new ShadowInfo(glm::perspective(90.0f, 1.0f, 1.0f, 25.0f)
        , 3.0/1024.0);
}
SpotLight::SpotLight(const glm::vec3 color , float inten,
    float c, float l,float e , float r , float cut) :
    PointLight(color , inten,c ,l , e , r) , cut_off(cut)
{
        m_shader = new ForwardSpot("./res/forward-spotLight");
        m_shadowInfo = new ShadowInfo(glm::perspective(90.0f, 1.0f, 1.0f, 25.0f)
        , 3.0/1024.0);
}
