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
    void update(const Transform& t)
    {
    }
    void render(Shader& bs,const Camera& c ,RenderingEngine* renderingEngine)
    {
        bs.Bind();
        bs.Update(*getTransform(),c,*m_material, renderingEngine);
        m_material->getDiffuseTexture()->Bind();
        m_mesh->Draw();
    }
};

#endif // MESHRENDERER_H_INCLUDED
