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
    void render(const Transform& t,BasicShader& bs,const Camera& c)
    {
        bs.Bind();
        bs.Update(t ,c,*m_material);
        m_material->getBaseTexture()->Bind();
        m_mesh->Draw();
    }
};

#endif // MESHRENDERER_H_INCLUDED
