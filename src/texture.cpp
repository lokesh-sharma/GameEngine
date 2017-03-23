#include "../include/texture.h"
#include "../include/stb_image.h"
#include <iostream>

Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data =stbi_load(fileName.c_str() , &width , &height , &numComponents , 4);

    if(data == NULL)
		std::cerr << "Unable to load texture: " << fileName << std::endl;

    glGenTextures(1, &m_texture);

    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);


    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_MAX_ANISOTROPY_EXT , 8.0f);
    stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind(GLuint id)
{
    if(id == 0)
        glActiveTexture(GL_TEXTURE0);
    else if(id == 1)
        glActiveTexture(GL_TEXTURE1);
    else if(id == 2)
        glActiveTexture(GL_TEXTURE2);
    else if(id == 3)
        glActiveTexture(GL_TEXTURE3);
    else if(id == 4)
        glActiveTexture(GL_TEXTURE4);
    else if(id == 5)
        glActiveTexture(GL_TEXTURE5);
    else if(id == 6)
        glActiveTexture(GL_TEXTURE6);
    else if(id == 7)
        glActiveTexture(GL_TEXTURE7);
    else if(id == 8)
        glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, m_texture);

}
