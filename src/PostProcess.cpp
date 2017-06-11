#include "PostProcess.h"
#include"display.h"

PostProcess::PostProcess(Display*display)
{
    m_display = display;
    m_width = display->getWidth();
    m_height  = display->getHeight();
    m_default = new Fxaa("./res/PostProcess/fxaa" , m_display);
    m_horiGaussianBlur = new HoriGaussianBlurFilter("./res/PostProcess/hBlur",m_display->getWidth());
    m_vertGaussianBlur = new VertGaussianBlurFilter("./res/PostProcess/vBlur" , m_display->getHeight());
    m_scene = new Texture(0 , GL_TEXTURE_2D, m_width , m_height,GL_LINEAR , GL_RGBA ,
     GL_RGBA , true, GL_COLOR_ATTACHMENT0);
      m_afterFxaa= new Texture(0 , GL_TEXTURE_2D, m_width , m_height,GL_LINEAR , GL_RGBA ,
     GL_RGBA , true, GL_COLOR_ATTACHMENT0);
     m_afterHBlur = new Texture(0 , GL_TEXTURE_2D, m_width , m_height,GL_LINEAR , GL_RGBA ,
     GL_RGBA , true, GL_COLOR_ATTACHMENT0);
     m_afterVBlur = new Texture(0 , GL_TEXTURE_2D, m_width , m_height,GL_LINEAR , GL_RGBA ,
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
    delete m_scene;
    delete m_afterFxaa;
    delete m_afterHBlur;
    delete m_afterVBlur;
    delete m_default;
    delete m_horiGaussianBlur;
    delete m_vertGaussianBlur;
}
void PostProcess::applyFilter(DefaultFilter* filter ,  Texture* scene , Texture* output)
{
    glBindVertexArray(m_vertexArrayObject);
    glEnableVertexAttribArray(0);
    if(output == NULL)
        m_display->bindAsRenderTarget();
    else
        output->bindAsRenderTarget();

    scene->Bind(0);
    filter->Bind();
    filter->UpdateFilter();
    glDrawArrays(GL_TRIANGLE_STRIP , 0 , 4);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void PostProcess::applyPostProcess()
{
    glDisable(GL_DEPTH_TEST);
    applyFilter(m_default , m_scene , m_afterFxaa);
    applyFilter(m_horiGaussianBlur , m_afterFxaa , m_afterHBlur);
    applyFilter(m_vertGaussianBlur , m_afterHBlur , 0);
    glEnable(GL_DEPTH_TEST);
}
