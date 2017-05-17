#ifndef SKYBOXMANAGER_H
#define SKYBOXMANAGER_H
#include<vector>
#include<string>
#include"SkyBoxShader.h"

class Camera;
class SkyBoxManager
{
public:
    SkyBoxManager();
    void addSkyBox(std::string filename , std::string format);
    void renderSkyBox(const Camera& c);
    void setActiveSkybox(std::string id);
    ~SkyBoxManager();
private:
    struct SkyBoxTexture
    {
        std::string id;
        GLuint texture;
    };
    int m_activeSkyBox;
    SkyBoxShader* m_skyBoxShader;

    std::vector<SkyBoxTexture>m_skyBoxes;
    GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffer;

};

#endif // SKYBOXMANAGER_H
