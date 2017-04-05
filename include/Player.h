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
    Player(PhysicsEngine* pEngine);
    void update();
    void render(Shader& bs,const Camera& c ,RenderingEngine* renderingEngine)
    {

    }
    void setHealth(int health) { m_health = health ;}
    void setName(const std::string& name) { m_name = name ;}


};

#endif // PLAYER_H
