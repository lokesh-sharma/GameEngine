#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture(const std::string& fileName , int numTextures=1, GLenum targetType = GL_TEXTURE_2D
	, GLfloat filter = GL_LINEAR_MIPMAP_LINEAR , GLenum attachment= GL_NONE);

	void Bind(GLuint id);
    void bindAsRenderTarget() ;
    void initTextures(unsigned char** data ,int width , int height , GLfloat* filters);
    void initRenderTargets(GLenum* attachments);
	virtual ~Texture();
protected:
private:
	Texture(const Texture& texture) {}
	void operator=(const Texture& texture) {}

	GLuint* m_texture;
	GLenum m_textureTarget ;
	GLuint m_frameBuffer;
	int m_height;
	int m_width;
	int m_numTextures;
};

#endif
