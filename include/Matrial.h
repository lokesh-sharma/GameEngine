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
        specPower = 1.0f;
        specIntensity=0.3f;
        ambient = glm::vec4(0.1f , 0.1f , 0.1f , 1.0f);
        dispMapScale = 0.02f;
        dispMapOffset = 0;
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
    float getSpecularPower() const { return specPower;}
    float getSpecularIntensity() const { return specIntensity;}
    float getDispMapScale() const { return dispMapScale;}
    float getDispMapOffset() const { return dispMapOffset;}
    glm::vec4 getAmbientColor() const { return ambient;}

private:
    float specPower;
    float specIntensity;
    float dispMapScale;
    float dispMapOffset;
    glm::vec4 ambient;

    std::map<std::string , Texture*> texture_map;

};


#endif // MATRIAL_H_INCLUDED
