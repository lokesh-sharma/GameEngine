#include "GUIManager.h"
#include"GuiShader.h"
#include "stb_image.h"

GUIManager::GUIManager(float aspect)
{
    m_guiShader = new GuiShader("./res/guiShader");
    m_aspect = aspect;
    float vertices[] = { -1 , 1 , -1 , -1 , 1 , 1 , 1 ,  -1};
    glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(1, &m_vertexArrayBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}
void GUIManager::addGUI(std::string fileName , glm::vec3 position , glm::vec3 scale)
{
    int width, height, numComponents;
    unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

    if(data == NULL)
		std::cerr << "Unable to load texture: " << fileName << std::endl;

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    float textureAspect = width/height;
    scale.x /= m_aspect;
    scale.x *= textureAspect;
    struct GUITexture t = {texture , position , scale};

    m_textures.push_back(t);

}
void GUIManager::renderGUI()
{
    glBindVertexArray(m_vertexArrayObject);
    glEnableVertexAttribArray(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    for(int i = 0 ;i < m_textures.size() ; i++)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,m_textures[i].texture);
        m_guiShader->Bind();
        m_guiShader->UpdateGUI(m_textures[i].pos , m_textures[i].scale);
        glDrawArrays(GL_TRIANGLE_STRIP , 0 , 4);
    }

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

}
GUIManager::~GUIManager()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
    for(int i = 0 ; i< m_textures.size() ; i++)
        glDeleteTextures(1, &m_textures[i].texture);
}
