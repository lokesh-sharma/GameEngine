#ifndef GAME_H
#define GAME_H

#include"GameObject.h"

class Game
{
public:
    Game() { m_root = nullptr;}
    virtual void update() { m_root->update(); }
    GameObject* getRootObject() { return m_root;}
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
