#ifndef GAME_H
#define GAME_H


class Game
{
public:
    Game();
    virtual void render()=0;
    virtual void update()=0;
    virtual ~Game();
private:
    Game(const Game& other) {}
    Game& operator=(const Game& other) {}
};

#endif // GAME_H
