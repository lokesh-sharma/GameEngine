#include "SkyBoxManager.h"
#include"camera.h"
#include"stb_image.h"
#include<iostream>

SkyBoxManager::SkyBoxManager()
{
    m_activeSkyBox = -1;
    m_skyBoxShader = new SkyBoxShader("./res/skyBoxShader");
    GLfloat vertices[] = {
    // Positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
    };
    glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(1, &m_vertexArrayBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, 18*6*sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}
void SkyBoxManager::addSkyBox(std::string fileName , std::string format)
{
    int width, height, numComponents;
	stbi_set_flip_vertically_on_load(0);
	unsigned char* faces[6];
	faces[0]=stbi_load((fileName + "/posx." + format).c_str() , &width , &height , &numComponents , 4);
	faces[1]=stbi_load((fileName + "/negx." + format).c_str() , &width , &height , &numComponents , 4);
	faces[2]=stbi_load((fileName + "/posy." + format).c_str() , &width , &height , &numComponents , 4);
	faces[3]=stbi_load((fileName + "/negy." + format).c_str() , &width , &height , &numComponents , 4);
	faces[4]=stbi_load((fileName + "/posz." + format).c_str() , &width , &height , &numComponents , 4);
	faces[5]=stbi_load((fileName + "/negz." + format).c_str() , &width , &height , &numComponents , 4);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    for(int j = 0 ; j< 6 ; j++)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + j, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,faces[j]);

    SkyBoxTexture t = { fileName , texture };
    m_skyBoxes.push_back(t);
    m_activeSkyBox = m_skyBoxes.size() - 1 ;
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
void SkyBoxManager::renderSkyBox(const Camera& c , RenderingEngine* renderer)
{
    if(m_activeSkyBox == -1)
        return;

    glBindVertexArray(m_vertexArrayObject);
    glEnableVertexAttribArray(0);

    glDepthMask(false);
    glDepthFunc(GL_LEQUAL);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP , m_skyBoxes[m_activeSkyBox].texture);
    m_skyBoxShader->Bind();
    m_skyBoxShader->UpdateSkyBox(c , renderer);
    glDrawArrays(GL_TRIANGLES , 0 , 36);

    glDepthFunc(GL_LESS);
    glDepthMask(true);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

SkyBoxManager::~SkyBoxManager()
{
    delete m_skyBoxShader;
    glDeleteVertexArrays(1, &m_vertexArrayObject);
    for(int i = 0 ; i< m_skyBoxes.size() ; i++)
        glDeleteTextures(1, &m_skyBoxes[i].texture);
}
