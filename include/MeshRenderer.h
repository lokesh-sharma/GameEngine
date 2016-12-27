#ifndef MESHRENDERER_H_INCLUDED
#define MESHRENDERER_H_INCLUDED

#include"mesh.h"
#include"texture.h"
#include"GameComponent.h"
#include"shader.h"

class MeshRenderer: public GameComponent
{
private:
    Mesh* m_mesh;
    Texture* m_texture;
public:
    MeshRenderer(Mesh* mesh , Texture* texture)
    {
        m_mesh = mesh;
        m_texture = texture;
    }
    void update(const Transform& t)
    {
    }
    void render(const Transform& t,const BasicShader& bs)
    {
        bs.Bind();
        m_texture->Bind();
        m_mesh->Draw();
    }
};

#endif // MESHRENDERER_H_INCLUDED
