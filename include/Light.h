#ifndef LIGHT_H
#define LIGHT_H
#include<glm/glm.hpp>

class BaseLight
{
private:
    glm::vec3 color;
    float intensity;
public:
    BaseLight(const glm::vec3 color , float inten): color(color) , intensity(inten) {}
    glm::vec3 getColor() const { return color;}
    float getIntensity() const { return intensity;}
};

class DirectionalLight : public BaseLight
{
private:
    glm::vec3 direction;
public:
    DirectionalLight(const glm::vec3 color , float inten , glm::vec3 dir) :
    BaseLight(color , inten ) , direction(dir) {}
    glm::vec3 getDirection() const { return direction ;}
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
    glm::vec3 position;
    Attenuation atten;
    float range;
public:
    PointLight(const glm::vec3 color , float inten , glm::vec3 pos ,float c=0
    , float l=0,float e=1 , float r=5):
    BaseLight(color , inten) , atten(c,l,e) , range(r) , position(pos){}
    Attenuation getAttenuation() const { return atten ;}
    glm::vec3 getPosition() const { return position ;}
    float getRange() const { return range ;}
};
class SpotLight : public PointLight
{
private:
    float cut_off;
    glm::vec3 direction;
public:
    SpotLight(const glm::vec3 color , float inten , glm::vec3 pos ,glm::vec3 dir,
    float c=0, float l=0,float e=1 , float r=5 , float cut = 0.354) :
    PointLight(color , inten,pos,c ,l , e , r) , cut_off(cut) , direction(dir){}
    float getCutOff() const { return cut_off;}
    glm::vec3 getDirection() const { return direction ;}
};

#endif // LIGHT_H
