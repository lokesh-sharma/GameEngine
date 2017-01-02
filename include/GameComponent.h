#ifndef GAMECOMPONENT_H_INCLUDED
#define GAMECOMPONENT_H_INCLUDED

#include"transform.h"
#include"camera.h"

class Shader;
class GameComponent
{
public:
    virtual void update(const Transform& t) {};
    virtual void render(Shader& bs,const Camera& c) {};
};


#endif // GAMECOMPONENT_H_INCLUDED
