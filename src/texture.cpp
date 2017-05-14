#include "../include/texture.h"
#include "../include/stb_image.h"
#include <iostream>


Texture::Texture(const std::string& fileName , int numTextures, GLenum targetType , GLfloat filter ,
	GLenum internalFormat ,GLenum format , bool clamp , GLenum attachment)
{
	int width, height, numComponents;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data =stbi_load(fileName.c_str() , &width , &height , &numComponents , 4);

    m_width = width;
    m_height = height;
    m_textureTarget = targetType;
    if(data == NULL)
		std::cerr << "Unable to load texture: " << fileName << std::endl;
    m_numTextures = numTextures;
    m_texture = new GLuint[numTextures];
    m_frameBuffer = 0 ;
    m_renderBuffer = 0;
    initTextures(&data , width , height , &filter ,&internalFormat , &format , clamp);
    if(attachment!=GL_NONE)
    initRenderTargets(&attachment);

    stbi_image_free(data);
}
Texture::Texture(unsigned char* data ,GLenum targetType,int width , int height , GLfloat filter ,GLenum internalFormat,
	GLenum format , bool clamp , GLenum attach)
{
    m_numTextures = 1;
    m_texture = new GLuint[m_numTextures];
    m_frameBuffer = 0;
    m_renderBuffer = 0;
    m_width = width;
    m_height = height;
    m_textureTarget = targetType;

    initTextures(&data , width , height , &filter , &internalFormat , &format , clamp);
    initRenderTargets(&attach);

}

Texture::~Texture()
{
	glDeleteTextures(m_numTextures, m_texture);
	if(m_frameBuffer) glDeleteFramebuffers(1 , &m_frameBuffer);
	if(m_renderBuffer) glDeleteRenderbuffers(1 , &m_renderBuffer);
	delete [] m_texture;
}
void Texture::bindAsRenderTarget()
{
    glBindFramebuffer(GL_FRAMEBUFFER , m_frameBuffer);
    glViewport(0, 0, m_width, m_height);
}
void Texture::initTextures(unsigned char** data ,int width , int height , GLfloat* filters ,
     GLenum* internalFormats , GLenum *formats, bool clamp )
{
    glGenTextures(m_numTextures, m_texture);
    for(int i = 0 ; i< m_numTextures ; i++)
    {   glBindTexture(m_textureTarget, m_texture[i]);

       glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, filters[i]);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, filters[i]);

        if(clamp)
        {
            glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            if(m_textureTarget == GL_TEXTURE_CUBE_MAP)
                glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        }
        if(m_textureTarget == GL_TEXTURE_CUBE_MAP){

            for(int j = 0 ; j< 6 ; j++)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + j, 0, internalFormats[i], width, height, 0, formats[i], GL_UNSIGNED_BYTE,NULL);
        }
        else glTexImage2D(m_textureTarget, 0, internalFormats[i], width, height, 0, formats[i], GL_UNSIGNED_BYTE, data[i]);
        if(filters[i] == GL_LINEAR_MIPMAP_LINEAR)
        {
            glGenerateMipmap(m_textureTarget);
            glTexParameterf(m_textureTarget , GL_TEXTURE_MAX_ANISOTROPY_EXT , 8.0f);
        }
    }
}
void Texture::initRenderTargets(GLenum* attachments)
{

    if(attachments == 0){
        return ;
    }
    GLenum drawBuffers[m_numTextures];
    bool has_depth = false;
    for(int i = 0 ; i < m_numTextures ; i++)
    {
        //std::cout<<i<<std::endl;
        if(attachments[i] == GL_DEPTH_ATTACHMENT)
        {
            has_depth = true;
            drawBuffers[i] = GL_NONE;
        }
        else
            drawBuffers[i] = attachments[i];

        if(attachments[i] == GL_NONE)
            continue;

        if(m_frameBuffer == 0)
        {
            //std::cout<<"hello";
            glGenFramebuffers(1 , &m_frameBuffer);
            glBindFramebuffer(GL_FRAMEBUFFER , m_frameBuffer);
        }

        glFramebufferTexture(GL_FRAMEBUFFER , attachments[i] ,m_texture[i],0);

        //glFramebufferTexture(GL_FRAMEBUFFER,attachments[i],
        //m_texture[i], 0);
    }

    if(m_frameBuffer == 0)
        return;

    if(!has_depth)
    {
        glGenRenderbuffers(1 , &m_renderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER , m_renderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER , GL_DEPTH_COMPONENT , m_width , m_height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER ,GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER ,m_renderBuffer);
    }
   // std::cout<<drawBuffers[0]<<"  "<<GL_COLOR_ATTACHMENT0<<std::endl;

    glDrawBuffers(m_numTextures , drawBuffers);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr<<"frame buffer creation failed \n";
}
void Texture::Bind(GLuint id)
{
    glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(m_textureTarget, m_texture[0]);

}
