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
    enum
    {
        TYPE_BOUNDINGSPHERE,
        TYPE_BOX,
        TYPE_CYLINDER,
        TYPE_CONE,
        TYPE_SIZE
    };
    PhysicsObject(Mesh* mesh , glm::vec3 pos ,float mass , int isStaticObject);
    PhysicsObject(glm::vec3 pos , glm::vec3 halfExtents , float mass , int shapeType);
    void integrate();
    btRigidBody* getRigidBody() { return m_body;}
    Transform* getTransform() { return &m_transform ;}
    void disableRotation() { m_disableRotation = true ;}
private:
    Transform m_transform;
    bool m_isActive;
    bool m_disableRotation;
    btRigidBody* m_body;

    btRigidBody* triangleMeshFromMesh(Mesh* mesh , glm::vec3 pos);
    btRigidBody* convexHullFromMesh(Mesh* mesh , glm::vec3 pos , float mass);
};

#endif // PHYSICSOBJECT_H
