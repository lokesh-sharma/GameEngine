#ifndef TESTGAME_H
#define TESTGAME_H


class TestGame
{
public:
    TestGame();
    void render();
    void update();
    virtual ~TestGame();
private:
    TestGame(const TestGame& other) {}
    TestGame& operator=(const TestGame& other) {}
};

#endif // TESTGAME_H
