#ifndef GAMECOMPONENT_H_INCLUDED
#define GAMECOMPONENT_H_INCLUDED

class GameComponent
{
public:
    virtual void update()=0;
    virtual void render()=0;
};


#endif // GAMECOMPONENT_H_INCLUDED
