#include "PostProcess.h"
#include"display.h"

PostProcess::PostProcess(Display*display)
{
    m_display = display;
    m_width = display->getWidth();
    m_height  = display->getHeight();
    m_default = new DefaultShader("./res/default");
    m_scene = new Texture(0 , GL_TEXTURE_2D, m_width , m_height,GL_LINEAR , GL_RGBA ,
     GL_RGBA , true, GL_COLOR_ATTACHMENT0);

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

PostProcess::~PostProcess()
{
    //dtor
}
void PostProcess::applyPostProcess()
{
    glBindVertexArray(m_vertexArrayObject);
    glEnableVertexAttribArray(0);
    m_display->bindAsRenderTarget();

    glDisable(GL_DEPTH_TEST);
    m_scene->Bind(0);
    m_default->Bind();
    m_default->Update();
    glDrawArrays(GL_TRIANGLE_STRIP , 0 , 4);

    glEnable(GL_DEPTH_TEST);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
