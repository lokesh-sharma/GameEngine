#ifndef GUIMANAGER_H
#define GUIMANAGER_H
#include<vector>
#include<string>
#include"GuiShader.h"

class GUIManager
{
public:
    GUIManager();
    void addGUI(std::string filename , glm::vec3 position , glm::vec3 scale);
    void renderGUI();
    ~GUIManager();
private:
    struct GUITexture
    {
        GLuint texture;
        glm::vec3 pos;
        glm::vec3 scale;
    };
    GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffer;
	GuiShader* m_guiShader;
    std::vector< GUITexture> m_textures;

};

#endif // GUIMANAGER_H
