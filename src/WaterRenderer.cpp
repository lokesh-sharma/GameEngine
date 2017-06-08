#include "WaterRenderer.h"
#include"camera.h"
#include"transform.h"
#include"RenderingEngine.h"

WaterRenderer::WaterRenderer()
{
    m_waveSpeed = 0.001f;
    m_waterShader = new WaterShader("./res/waterShader");
    m_dudvMap = new Texture("./res/waterDUDV.png");
    m_normalMap = new Texture("./res/waterDUDVnormal.png");
    m_reflectionMap = new Texture(0 , GL_TEXTURE_2D, 1024 , 1024,GL_LINEAR , GL_RGBA ,
     GL_RGBA , true, GL_COLOR_ATTACHMENT0);
    m_refractionMap = new Texture(0 , GL_TEXTURE_2D, 1024 , 1024,GL_LINEAR , GL_RGBA ,
     GL_RGBA , true, GL_COLOR_ATTACHMENT0);
    GLfloat vertices[] = { -1 ,0, -1 , -1 ,0, 1 , 1 ,0, -1 , 1 ,0, -1 , -1 ,0, 1 , 1 ,0, 1 } ;
    glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(1, &m_vertexArrayBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, 18*sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}
void WaterRenderer::render(const Camera& c , RenderingEngine* renderer)
{
    static int counter = 0;
    counter++;
    glBindVertexArray(m_vertexArrayObject);
    glEnableVertexAttribArray(0);

    m_reflectionMap->Bind(0);
    m_refractionMap->Bind(1);
    m_dudvMap->Bind(2);
    m_normalMap->Bind(3);
    renderer->getDepthMap()->Bind(4);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);


    for(int i = 0 ; i< m_quads.size() ; i++)
    {
        Transform t ;
        t.SetPos(m_quads[i].position);
        t.SetScale(m_quads[i].scale);
        t.SetRot(glm::quat(1,0,0,0));
        m_waterShader->Bind();

        m_waterShader->setUniform1f("moveFactor" , counter*m_waveSpeed);
        m_waterShader->setUniformVector3f("lightPos" , 100 , 100 , -100);
        m_waterShader->setUniformVector3f("lightColor" , 1 , 1, 1);
        m_waterShader->UpdateWaterShader(t , c);
        glDrawArrays(GL_TRIANGLES , 0 , 6);
    }

    glDisable(GL_BLEND);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

}
WaterRenderer::~WaterRenderer()
{
     glDeleteVertexArrays(1, &m_vertexArrayObject);
     delete m_waterShader;
     delete m_normalMap;
     delete m_dudvMap;
     delete m_reflectionMap;
     delete m_refractionMap;
}

void WaterRenderer::addWaterQuad(WaterQuad q)
{
    m_quads.push_back(q);
}
