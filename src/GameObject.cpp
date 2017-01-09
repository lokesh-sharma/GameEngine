#include"GameObject.h"
#include"GameComponent.h"
#include"camera.h"
#include"shader.h"

void GameObject::update()
{
    for(int i = 0 ; i< m_children.size() ;i++)
        m_children[i]->update();
    for(int i = 0 ; i< m_components.size() ;i++)
        m_components[i]->update();
}
void GameObject::render(Shader& bs, const Camera& camera , RenderingEngine* renderingEngine)
{
    for(int i = 0 ; i< m_children.size() ;i++)
        m_children[i]->render(bs,camera , renderingEngine);
        for(int i = 0 ; i< m_components.size() ;i++)
        m_components[i]->render(bs,camera , renderingEngine);
}
void GameObject::addChild(GameObject* object)
{
    m_children.push_back(object);
}
void GameObject::setEngine(CoreEngine* core)
{
    coreEngine = core;
    for(int i = 0 ; i< m_children.size() ;i++)
        m_children[i]->setEngine(core);
}
void GameObject::addComponent(GameComponent* component)
{
    component->setParent(this);
    m_components.push_back(component);
    component->addToEngine(coreEngine);
}
