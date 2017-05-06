#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture(const std::string& fileName , int numTextures=1, GLenum targetType = GL_TEXTURE_2D
	, GLfloat filter = GL_LINEAR_MIPMAP_LINEAR , GLenum attachment=GL_NONE);
	Texture(unsigned char* data ,int width , int height , GLfloat filter, GLenum attach);

	void Bind(GLuint id);
    void bindAsRenderTarget() ;
    void initTextures(unsigned char** data ,int width , int height , GLfloat* filters);
    void initRenderTargets(GLenum* attachments=0);
    GLuint getTexture(int id) { return m_texture[id];}
	virtual ~Texture();
protected:
private:
	Texture(const Texture& texture) {}
	void operator=(const Texture& texture) {}

	GLuint* m_texture;
	GLenum m_textureTarget ;
	GLuint m_frameBuffer;
	GLuint m_renderBuffer;
	int m_height;
	int m_width;
	int m_numTextures;
};

#endif
