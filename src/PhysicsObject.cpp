#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(glm::vec3 pos , glm::vec3 extents , float mass , int shapeType)
{
    btTransform t ;
    t.setIdentity();
    t.setOrigin(btVector3(pos.x , pos.y, pos.z));
    btVector3 interia(0,0,0);
    btVector3 halfExtents(extents.x/2 , extents.y/2 , extents.z/2);
    btMotionState * motion = new btDefaultMotionState(t);

    if(shapeType == TYPE_BOUNDINGSPHERE)
    {
        btSphereShape *sphere = new btSphereShape(halfExtents.getX());
        if(mass!= 0.0f)
            sphere->calculateLocalInertia(mass , interia);
        btRigidBody::btRigidBodyConstructionInfo info(mass , motion , sphere , interia);
        m_body = new btRigidBody(info);
    }
    else if(shapeType == TYPE_BOX)
    {
        btBoxShape* box = new btBoxShape(halfExtents);
        if(mass!= 0.0f)
            box->calculateLocalInertia(mass , interia);
        btRigidBody::btRigidBodyConstructionInfo info(mass , motion , box , interia);
        m_body = new btRigidBody(info);

    }
    else if(shapeType == TYPE_CYLINDER)
    {
        btCylinderShape* cylinder = new btCylinderShape(halfExtents);
        if(mass!= 0.0f)
            cylinder->calculateLocalInertia(mass , interia);
        btRigidBody::btRigidBodyConstructionInfo info(mass , motion , cylinder , interia);
        m_body = new btRigidBody(info);
    }
    else if(shapeType == TYPE_CONE)
    {
        btConeShape* cone = new btConeShape(halfExtents.getX() , halfExtents.getY());
         if(mass!= 0.0f)
            cone->calculateLocalInertia(mass , interia);
        btRigidBody::btRigidBodyConstructionInfo info(mass , motion , cone , interia);
        m_body = new btRigidBody(info);
    }

}
PhysicsObject::PhysicsObject(Mesh* mesh , glm::vec3 pos ,float mass , int isStaticObject)
{
    if(isStaticObject)
    {
        m_body = triangleMeshFromMesh(mesh , pos);
        m_isActive = false;
        m_body->setRestitution(0.4);
        //m_body->setDamping(1.0f , 1.0f);
        //m_body->setFriction(10.0f);
    }
    else
    {
        m_body = convexHullFromMesh(mesh , pos , mass);
        m_body->setRestitution(0.4);
        //m_body->setDamping(1.0f , 1.0f);
         //m_body->setFriction(10.0f);
        m_isActive = true;
    }
    m_body->setUserPointer(this);
}
void PhysicsObject::integrate()
{
    if(m_isActive)
        m_body->activate();
    btTransform t ;
    m_body->getMotionState()->getWorldTransform(t);
    btVector3 pos = t.getOrigin();
    btQuaternion  quat = t.getRotation();
    float angle = quat.getAngle();
    btVector3 axis = quat.getAxis();
    m_transform.SetPos(glm::vec3(pos.getX() , pos.getY() , pos.getZ()));
    glm::quat q = glm::angleAxis(float(angle*(180.0/3.14)) , glm::vec3(axis.getX() , axis.getY() , axis.getZ()));
    m_transform.SetRot(q);

    std::cout<<pos.getY()<<std::endl;
//    m_position += m_velocity*delta;
}
btRigidBody* PhysicsObject::triangleMeshFromMesh(Mesh* mesh , glm::vec3 pos )
{
    const std::vector<glm::vec3>& verts = mesh->getMeshData()->getVerts();
    btTriangleMesh* me = new btTriangleMesh();
    for (int i=0; i < verts.size(); i += 3)
    {
        glm::vec3 v1 = verts[i];
        glm::vec3 v2 = verts[i+1];
        glm::vec3 v3 = verts[i+2];

        btVector3 bv1 = btVector3(v1.x, v1.y, v1.z);
        btVector3 bv2 = btVector3(v2.x, v2.y, v2.z);
        btVector3 bv3 = btVector3(v3.x, v3.y, v3.z);

        me->addTriangle(bv1, bv2, bv3);
    }
     btCollisionShape* shape = new btBvhTriangleMeshShape(me ,false);
     btVector3 interia(0,0,0);
    shape->calculateLocalInertia(0,interia);
    btTransform t ;
    t.setIdentity();
    t.setOrigin(btVector3(pos.x , pos.y, pos.z));
    btMotionState * motion = new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(0 , motion , shape , interia) ;
    btRigidBody*  body = new btRigidBody(info);

    if(body == NULL)
        std::cerr<<"error";
    return body;
}
btRigidBody* PhysicsObject::convexHullFromMesh(Mesh* mesh , glm::vec3 pos , float mass)
{
    const std::vector<glm::vec3>& verts = mesh->getMeshData()->getVerts();
    btConvexHullShape* shape = new btConvexHullShape();
    for(int i = 0 ; i< verts.size() ; i++)
    {
        glm::vec3 v = verts[i];
        btVector3 bv = btVector3(v.x , v.y , v.z);
        shape->addPoint(bv);
    }
    btVector3 interia(0,0,0);
    shape->calculateLocalInertia(mass,interia);
    btTransform t ;
    t.setIdentity();
    t.setOrigin(btVector3(pos.x , pos.y, pos.z));
    btMotionState * motion = new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(mass , motion , shape , interia) ;
    btRigidBody*  body = new btRigidBody(info);

    if(body == NULL)
        std::cerr<<"error";
    return body;
}

