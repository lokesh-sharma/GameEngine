#include "SunRenderer.h"

SunRenderer::SunRenderer(glm::vec3 pos , glm::vec3 scale)
{
    m_position = pos;
    m_scale = scale;
    m_sunShader = new SunShader("./res/Shaders/sunShader");
    m_sunImage = new Texture("./res/Textures/sun.png");
    GLfloat vertices[] = { 1 ,1, 0 , 1 ,-1, 0 , -1 ,1, 0 , -1 ,1, 0 , 1 ,-1, 0 , -1 ,-1, 0 } ;
    glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(1, &m_vertexArrayBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, 18*sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}
void SunRenderer::renderSun(const Camera& c)
{
    glBindVertexArray(m_vertexArrayObject);
    glEnableVertexAttribArray(0);
    Transform t ;
    t.SetPos(m_position);
    t.SetScale(m_scale);
    t.SetRot(c.getRot());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);

    glDepthMask(false);
    glDepthFunc(GL_LEQUAL);
    m_sunImage->Bind(0);
    m_sunShader->Bind();
    m_sunShader->UpdateSunShader(t , c , m_position);
    glDrawArrays(GL_TRIANGLES , 0 , 6);

    glDepthFunc(GL_LESS);
    glDepthMask(true);
    glDisable(GL_BLEND);

    glDisableVertexAttribArray(0);
}

SunRenderer::~SunRenderer()
{
    glDeleteBuffers(1, &m_vertexArrayBuffer);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
    delete m_sunShader;
}
