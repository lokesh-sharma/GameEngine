#ifndef LIGHT_H
#define LIGHT_H
#include<glm/glm.hpp>
#include"GameComponent.h"
#include"transform.h"
#include"CoreEngine.h"
class Shader;

class BaseLight:public GameComponent
{
private:
    glm::vec3 color;
    float intensity;
protected:
    Shader* m_shader;
public:
    BaseLight(const glm::vec3 color , float inten): GameComponent() ,color(color)
    , intensity(inten) ,m_shader(nullptr){}
    glm::vec3 getColor() const { return color;}

    float getIntensity() const { return intensity;}
    virtual Shader* getShader() { return m_shader;}
    virtual void addToEngine(CoreEngine*core)
    {
        //core->getRenderingEngine()->addLight(this);
    }
};

class DirectionalLight : public BaseLight
{
public:
    DirectionalLight(const glm::vec3 color , float inten);
    glm::vec3 getDirection() const ;
    virtual void addToEngine(CoreEngine*core)
    {
        core->getRenderingEngine()->addDirectionalLight(this);
    }
};

class Attenuation
{
private:
    float constant;
    float linear;
    float exponent;
public:
    Attenuation(float c=0 , float l=0 , float e=1) : constant(c) , linear(l) , exponent(e) {}
    float getConstant() const { return constant;}
    float getLinear() const { return linear;}
    float getExponent() const { return exponent;}
};
class PointLight : public BaseLight
{
private:
    Attenuation atten;
    float range;
public:
    PointLight(const glm::vec3 color , float inten ,float c=0
    , float l=0,float e=1 , float r=50);
    Attenuation getAttenuation() const { return atten ;}
    glm::vec3 getPosition() const { return getTransform()->GetPos() ;}
    float getRange() const { return range ;}
    virtual void addToEngine(CoreEngine*core)
    {
        core->getRenderingEngine()->addPointLight(this);
    }
};
class SpotLight : public PointLight
{
private:
    float cut_off;
public:
    SpotLight(const glm::vec3 color , float inten ,
    float c=0, float l=0,float e=1 , float r=50 , float cut = 0.354);
    float getCutOff() const { return cut_off;}
    glm::vec3 getDirection() ;
    virtual void addToEngine(CoreEngine*core)
    {
        core->getRenderingEngine()->addSpotLight(this);
    }
};

#endif // LIGHT_H
