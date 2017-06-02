#include "Player.h"

 Player::Player(PhysicsEngine* pEngine)
{
    m_name = "minh";
    m_health=100;
    btTransform startTransform;
    startTransform.setIdentity ();
    startTransform.setOrigin (btVector3(0, 1, 4));

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
    charCon->setMaxJumpHeight(1.5);



}
void Player::update()
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
    charCon->jump(btVector3(0,6,0));
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
