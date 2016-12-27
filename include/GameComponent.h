#ifndef GAMECOMPONENT_H_INCLUDED
#define GAMECOMPONENT_H_INCLUDED

#include"transform.h"
#include"shader.h"
class GameComponent
{
public:
    virtual void update(const Transform& t)=0;
    virtual void render(const Transform& t,const BasicShader& bs)=0;
};


#endif // GAMECOMPONENT_H_INCLUDED
