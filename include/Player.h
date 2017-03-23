#ifndef PLAYER_H
#define PLAYER_H
#include"MeshRenderer.h"
#include"btBulletDynamicsCommon.h"
#include"BulletCollision/CollisionDispatch/btGhostObject.h"
#include"BulletDynamics/Character/btKinematicCharacterController.h"
#include"LinearMath/btTransform.h"
#include"LinearMath/btVector3.h"
#include"PhysicsObject.h"
#include"PhysicsEngine.h"

class Player : public GameComponent
{

private:
    std::string m_name;
    int m_health;
    PhysicsObject* m_body;
    btPairCachingGhostObject * m_ghostObject;
    btKinematicCharacterController* charCon;
    void renderCrossHair() const;
public:
    Player(PhysicsEngine* pEngine)
    {
        m_name = "minh";
        m_health=100;
        btTransform startTransform;
        startTransform.setIdentity ();
        startTransform.setOrigin (btVector3(0, 0, 4));

        btConvexShape* capsule = new btCapsuleShape(0.5, 1);

        m_ghostObject = new btPairCachingGhostObject();
        m_ghostObject->setWorldTransform(startTransform);
        pEngine->getBroadPhase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
        m_ghostObject->setCollisionShape(capsule);
        m_ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
        charCon = new btKinematicCharacterController (m_ghostObject, capsule,0.05f);
        charCon->setGravity(pEngine->getDynamicWorld()->getGravity());

        pEngine->getDynamicWorld()->addCollisionObject(m_ghostObject, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::AllFilter);
        pEngine->getDynamicWorld()->addAction(charCon);
        charCon->setMaxJumpHeight(1);



    }
    void update()
    {
        btTransform t ;
        t = charCon->getGhostObject()->getWorldTransform();
        btVector3 pos = t.getOrigin();
        btQuaternion  quat = t.getRotation();
        float angle = quat.getAngle();
        btVector3 axis = quat.getAxis();
        getTransform()->SetPos(glm::vec3(pos.getX() , pos.getY() , pos.getZ()));
        glm::quat q = glm::angleAxis(float(angle*(180.0/3.14)) , glm::vec3(axis.getX() , axis.getY() , axis.getZ()));
        //getTransform()->SetRot(q);
        glm::vec3 fb = getTransform()->getForward();
        glm::vec3 rl = getTransform()->getRight();
        glm::vec3 dir(0,0,0);
        if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_SPACE)){
        if(charCon->onGround())
        charCon->jump(btVector3(0,4,0));
        }

        if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_W) )
            dir += fb;
        if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_S) )
            dir -= fb;
        if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_A) )
            dir -= rl;
        if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_D) )
            dir += rl;

        if(dir != glm::vec3(0,0,0))
        {
            if(charCon->onGround() )
                charCon->setWalkDirection(btVector3(dir.x , dir.y , dir.z).normalized()/10);
            else
               charCon->setWalkDirection(btVector3(dir.x , dir.y , dir.z).normalized()/30);
        }

        else
            charCon->setWalkDirection(btVector3(0 , 0 , 0));
       //charCon->setVelocityForTimeInterval(btVector3(wd.x , wd.y , wd.z).normalized()*4 , 0.01f);



    }
    void render(Shader& bs,const Camera& c ,RenderingEngine* renderingEngine)
    {

    }
    void setHealth(int health) { m_health = health ;}
    void setName(const std::string& name) { m_name = name ;}


};

#endif // PLAYER_H
