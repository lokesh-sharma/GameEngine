#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H
#include<vector>
#include"PhysicsObject.h"

class PhysicsEngine
{
public:
    PhysicsEngine() {};
    void addObject(PhysicsObject*object);
    void simulate(float delta);
    void handleCollisions();
    inline PhysicsObject* getObject(int index) {  return m_objects[index] ;}
    int getNumObjects() const { return m_objects.size() ;}
private:
    std::vector<PhysicsObject*> m_objects;
};

#endif // PHYSICSENGINE_H
