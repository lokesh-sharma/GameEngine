#ifndef MATRIAL_H_INCLUDED
#define MATRIAL_H_INCLUDED

#include<glm/glm.hpp>
#include<map>
#include<iostream>
#include"texture.h"

class Material
{
public:
    Material()
    {
        specPower = 7.0f;
        specIntensity=0.8f;
        ambient = glm::vec4(0.2f , 0.2f , 0.2f , 1.0f);
        dispMapScale = 0.03f;
        dispMapOffset = 0.0;
        //texture_map["normal"] = new Texture("./res/default_normal.jpg");

    }
    Texture* getTexture(const std::string& uName)
    {

        return texture_map[uName];
    }
    Texture* getDiffuseTexture()
    {

        return texture_map["diffuse"];
    }
    Texture* getNormalMap()
    {
        return texture_map["normal"];
    }
    Texture* getDispMap()
    {
        return texture_map["dispMap"];
    }
    void addTexture(const std::string& uName , const std::string fName)
    {
        texture_map[uName] = new Texture(fName);
    }
    void addTexture(const std::string& uName , Texture* tex)
    {
        texture_map[uName] = tex;
    }
    float getSpecularPower() const { return specPower;}
    float getSpecularIntensity() const { return specIntensity;}
    float getDispMapScale() const { return dispMapScale;}
    float getDispMapOffset() const { return dispMapOffset;}
    glm::vec4 getAmbientColor() const { return ambient;}

    void setAmbientColor(glm::vec4 color) { ambient = color; }
     void setSpecularPower(float specPw)  {  specPower = specPw;}
    void setSpecularIntensity(float specI)  { specIntensity = specI;}
    void setDispMapScale(float dispS) { dispMapScale = dispS;}
    void setDispMapOffset(float dispO)  {  dispMapOffset = dispO;}

private:
    float specPower;
    float specIntensity;
    float dispMapScale;
    float dispMapOffset;
    glm::vec4 ambient;

    std::map<std::string , Texture*> texture_map;

};


#endif // MATRIAL_H_INCLUDED
