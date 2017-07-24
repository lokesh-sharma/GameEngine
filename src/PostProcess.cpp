#include "PostProcess.h"
#include"display.h"
#include"SunRenderer.h"

PostProcess::PostProcess(Display*display , RenderingEngine* renderer)
{
    m_renderingEngine = renderer;
    m_display = display;
    m_width = display->getWidth();
    m_height  = display->getHeight();
    m_bright = new BrightFilter("./res/PostProcess/bright");
    m_bloom = new BloomFilter("./res/PostProcess/bloom");
    m_godRays = new GodRaysFilter("./res/PostProcess/godRays" , renderer->getSunrenderer()->getSunPos());
    m_default = new Fxaa("./res/PostProcess/fxaa" , m_display);
    m_horiGaussianBlur = new HoriGaussianBlurFilter("./res/PostProcess/hBlur",m_display->getWidth()/8);
    m_vertGaussianBlur = new VertGaussianBlurFilter("./res/PostProcess/vBlur" , m_display->getHeight()/8);
    m_scene = new Texture(0 , GL_TEXTURE_2D, m_width , m_height,GL_LINEAR , GL_RGBA ,
     GL_RGBA , true, GL_COLOR_ATTACHMENT0);
     m_afterBrigtnessCutOff = new Texture(0 , GL_TEXTURE_2D, m_width , m_height,GL_LINEAR , GL_RGBA ,
     GL_RGBA , true, GL_COLOR_ATTACHMENT0);
     m_godRaysSampler = new Texture(0 , GL_TEXTURE_2D, m_width , m_height,GL_LINEAR , GL_RGBA ,
     GL_RGBA , true, GL_COLOR_ATTACHMENT0);
      m_afterFxaa= new Texture(0 , GL_TEXTURE_2D, m_width , m_height,GL_LINEAR , GL_RGBA ,
     GL_RGBA , true, GL_COLOR_ATTACHMENT0);
     m_afterBloom = new Texture(0 , GL_TEXTURE_2D, m_width , m_height,GL_LINEAR , GL_RGBA ,
     GL_RGBA , true, GL_COLOR_ATTACHMENT0);
     m_afterHBlur = new Texture(0 , GL_TEXTURE_2D, m_width/8 , m_height/8,GL_LINEAR , GL_RGBA ,
     GL_RGBA , true, GL_COLOR_ATTACHMENT0);
     m_afterVBlur = new Texture(0 , GL_TEXTURE_2D, m_width/8 , m_height/8,GL_LINEAR , GL_RGBA ,
     GL_RGBA , true, GL_COLOR_ATTACHMENT0);
     m_afterSSAO = new Texture(0 , GL_TEXTURE_2D, m_width/2 , m_height/2,GL_LINEAR , GL_DEPTH_COMPONENT32F,
     GL_DEPTH_COMPONENT , true, GL_DEPTH_ATTACHMENT);

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
    delete m_godRaysSampler;
}
void PostProcess::applyFilter(DefaultFilter* filter ,  Texture* scene1 ,Texture* scene2, Texture* output)
{
    glBindVertexArray(m_vertexArrayObject);
    glEnableVertexAttribArray(0);
    if(output == NULL)
        m_display->bindAsRenderTarget();
    else
        output->bindAsRenderTarget();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene1->Bind(0);
    if(scene2!= NULL)
        scene2->Bind(1);
    filter->Bind();
    filter->UpdateFilter(*m_renderingEngine->getCamera());
    glDrawArrays(GL_TRIANGLE_STRIP , 0 , 4);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}


void PostProcess::applyPostProcess()
{
    glDisable(GL_DEPTH_TEST);
    applyFilter(m_default , m_scene ,0, m_afterFxaa);
    applyFilter(m_horiGaussianBlur , m_afterFxaa ,0 ,m_afterHBlur);
    applyFilter(m_vertGaussianBlur , m_afterHBlur ,0, m_afterVBlur);
    applyFilter(m_bright ,m_afterVBlur ,0, m_afterBrigtnessCutOff);
    applyFilter(m_bloom , m_afterFxaa , m_afterBrigtnessCutOff , m_afterBloom);
    applyFilter(m_godRays , m_afterBloom , m_godRaysSampler , 0);

    glEnable(GL_DEPTH_TEST);
}
