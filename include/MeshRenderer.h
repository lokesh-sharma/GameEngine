#ifndef MESHRENDERER_H_INCLUDED
#define MESHRENDERER_H_INCLUDED

#include"mesh.h"
#include"texture.h"
#include"GameComponent.h"
#include"shader.h"
#include"Matrial.h"

class MeshRenderer: public GameComponent
{
private:
    Mesh* m_mesh;
    Material* m_material;
public:
    MeshRenderer(Mesh* mesh , Material* material)
    {
        m_mesh = mesh;
        m_material = material;
    }
    void update()
    {

    }
    void render(Shader& bs,const Camera& c ,RenderingEngine* renderingEngine)
    {
        bs.Bind();
        bs.Update(*getTransform(),c,*m_material, renderingEngine);
        m_material->getDiffuseTexture()->Bind(0);
        m_material->getNormalMap()->Bind(1);
        m_material->getDispMap()->Bind(2);
        renderingEngine->getShadowMap()->Bind(3);
        m_mesh->Draw();
    }
};

#endif // MESHRENDERER_H_INCLUDED
