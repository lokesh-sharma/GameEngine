#ifndef GAME_H
#define GAME_H

#include"GameObject.h"

class Game
{
public:
    Game() { m_root = nullptr;}
    virtual void update(float delta) { m_root->update(delta); }
    GameObject* getRootObject() { return m_root;}
    void setEngine(CoreEngine* core) { getRootObject()->setEngine(core);}
    void addToScene(GameObject* child)
    {
        if(m_root == nullptr)
            m_root = child;
        else
            m_root->addChild(child);
    }
    virtual ~Game() {}
private:
    GameObject* m_root;
    Game(const Game& other) {}
    Game& operator=(const Game& other) {}
};

#endif // GAME_H
