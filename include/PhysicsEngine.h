#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H
#include<vector>
#include<map>
#include"PhysicsObject.h"
#include"btBulletDynamicsCommon.h"
#include"LinearMath/btTransform.h"
#include"LinearMath/btVector3.h"

class PhysicsEngine
{
public:
    PhysicsEngine() ;
    void addObject(PhysicsObject*object , std::string id );
    void simulate(float delta);
    void handleCollisions();
    PhysicsObject* getObject(std::string name) {  return m_objects[name] ;}
    int getNumObjects() const { return m_objects.size() ;}
private:
    btDynamicsWorld* world;
    btDispatcher* dispatcher;
    btBroadphaseInterface* broadPhase;
    btConstraintSolver* solver;
    btCollisionConfiguration* collisionConfig;
    std::map<std::string , PhysicsObject*> m_objects;
};

#endif // PHYSICSENGINE_H
