#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include<vector>
#include"transform.h"
#include"shader.h"
#include"GameComponent.h"

class GameObject
{
private:
    std::vector<GameObject*> m_children;
    std::vector<GameComponent*> m_components;
    Transform trans;
public:
    void update()
    {
        for(int i = 0 ; i< m_children.size() ;i++)
            m_children[i]->update();
        for(int i = 0 ; i< m_components.size() ;i++)
            m_components[i]->update(trans);
    }
    void render(BasicShader& bs, const Camera& camera)
    {
        for(int i = 0 ; i< m_children.size() ;i++)
            m_children[i]->render(bs,camera);
         for(int i = 0 ; i< m_components.size() ;i++)
            m_components[i]->render(trans,bs,camera);
    }
    void addChild(GameObject* object)
    {
        m_children.push_back(object);
    }
    void addComponent(GameComponent* component)
    {
        m_components.push_back(component);
    }
};

#endif // GAMEOBJECT_H_INCLUDED
