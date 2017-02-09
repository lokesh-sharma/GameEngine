#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include<glm/glm.hpp>
#include"mesh.h"
#include"transform.h"
#include"btBulletDynamicsCommon.h"
#include"LinearMath/btTransform.h"
#include"LinearMath/btVector3.h"

class PhysicsObject
{
public:
    PhysicsObject(Mesh* mesh , glm::vec3 pos ,float mass , int isStaticObject);
    void integrate();
    btRigidBody* getRigidBody() { return m_body;}
    Transform* getTransform() { return &m_transform ;}
private:
    Transform m_transform;
    bool m_isActive;
    btRigidBody* m_body;

    btRigidBody* triangleMeshFromMesh(Mesh* mesh , glm::vec3 pos);
    btRigidBody* convexHullFromMesh(Mesh* mesh , glm::vec3 pos , float mass);
};

#endif // PHYSICSOBJECT_H
