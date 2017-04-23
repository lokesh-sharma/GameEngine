#include "../include/texture.h"
#include "../include/stb_image.h"
#include <iostream>


Texture::Texture(const std::string& fileName, int numTextures , GLenum targetType , GLfloat filter,
GLenum attachment)
{
	int width, height, numComponents;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data =stbi_load(fileName.c_str() , &width , &height , &numComponents , 4);

    m_textureTarget = targetType;
    if(data == NULL)
		std::cerr << "Unable to load texture: " << fileName << std::endl;
    m_numTextures = numTextures;
    m_texture = new GLuint[numTextures];
    m_frameBuffer = 0 ;
    initTextures(&data , width , height , &filter );
    initRenderTargets(&attachment);

    stbi_image_free(data);
}
Texture::Texture(unsigned char* data ,int width , int height , GLfloat filter , GLenum attach)
{
    m_numTextures = 1;
    m_frameBuffer = 0;
    m_textureTarget = GL_TEXTURE_2D;
    initTextures(&data , width , height , &filter );
    initRenderTargets(&attach);
}

Texture::~Texture()
{
	glDeleteTextures(m_numTextures, m_texture);
	if(m_frameBuffer) glDeleteFramebuffers(1 , &m_frameBuffer);
	delete [] m_texture;
}
void Texture::bindAsRenderTarget()
{
    glBindFramebuffer(GL_FRAMEBUFFER , m_frameBuffer);
    glViewport(0, 0, m_width, m_height);
}
void Texture::initTextures(unsigned char** data ,int width , int height , GLfloat* filters)
{
    glGenTextures(m_numTextures, m_texture);
    for(int i = 0 ; i< m_numTextures ; i++)
    {   glBindTexture(m_textureTarget, m_texture[i]);

        glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, filters[i]);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, filters[i]);


        glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(m_textureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data[i]);
        glGenerateMipmap(m_textureTarget);
        glTexParameterf(m_textureTarget , GL_TEXTURE_MAX_ANISOTROPY_EXT , 8.0f);
    }
}
void Texture::initRenderTargets(GLenum* attachments)
{
    if(attachments == 0)
        return ;
    GLenum drawBuffers[m_numTextures];
    for(int i = 0 ; i < m_numTextures ; i++)
    {
        if(attachments[i] == GL_DEPTH_ATTACHMENT)
            drawBuffers[i] = GL_NONE;
        else
            drawBuffers[i] = attachments[i];

        if(attachments[i] == GL_NONE)
            continue;
        if(m_frameBuffer == 0)
        {
            glGenFramebuffers(1 , &m_frameBuffer);
            glBindFramebuffer(GL_FRAMEBUFFER , m_frameBuffer);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER , attachments[i] ,
        m_textureTarget , m_texture[i],0);
    }
    if(m_frameBuffer == 0){

        return;
        }
    glDrawBuffers(m_numTextures , drawBuffers);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr<<"frame buffer creation failed \n";
}
void Texture::Bind(GLuint id)
{
    glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, m_texture[0]);

}
