#ifndef PLAYER_H
#define PLAYER_H
#include"MeshRenderer.h"
#include"btBulletDynamicsCommon.h"
#include"LinearMath/btTransform.h"
#include"LinearMath/btVector3.h"
#include"PhysicsObject.h"

class Player : public GameComponent
{

private:
    std::string m_name;
    int m_health;
    PhysicsObject* m_body;
    void renderCrossHair() const;
public:
    Player(PhysicsObject* body)
    {
        m_name = "minh";
        m_health=100;
        m_body = body;
        m_body->getRigidBody()->setAngularFactor(btVector3(0,0,0));
        //m_body->getRigidBody()->setDamping(0.8f , 0.8f);
        //m_body->getRigidBody()->setFriction(0.8f);
        m_body->disableRotation();
    }
    void update()
    {
        btTransform t1  = m_body->getRigidBody()->getWorldTransform();
        glm::quat q = getTransform()->GetRot();
        //t1.setRotation(bq);
        glm::quat before = m_body->getTransform()->GetRot();
        m_body->getTransform()->SetRot(q);
        glm::quat after = m_body->getTransform()->GetRot();

        if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_SPACE))
            m_body->getRigidBody()->applyCentralForce(btVector3(0,20,0));
        if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_UP))
        {
            glm::vec3 forward = glm::normalize(getTransform()->getForward());
            forward=forward*5.0f;
            glm::vec3 right = getTransform()->getRight();
            m_body->getRigidBody()->applyCentralForce(btVector3(forward.x , forward.y,forward.z));
        }
        if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_DOWN))
        {
            glm::vec3 forward = glm::normalize(getTransform()->getForward());
            forward=forward*(-5.0f);
            m_body->getRigidBody()->applyCentralForce(btVector3(forward.x , forward.y,forward.z));
        }
        if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_LEFT))
        {
            glm::vec3 forward = glm::normalize(getTransform()->getForward());
            glm::vec3 right = glm::normalize(getTransform()->getRight());
            right=right*(-5.0f);
            m_body->getRigidBody()->applyCentralForce(btVector3(right.x , right.y,right.z));
        }
        if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_RIGHT))
        {
            glm::vec3 right = glm::normalize(getTransform()->getRight());
            right=right*5.0f;
            m_body->getRigidBody()->applyCentralForce(btVector3(right.x , right.y,right.z));
        }

    }
    void render(Shader& bs,const Camera& c ,RenderingEngine* renderingEngine)
    {

    }
    void setHealth(int health) { m_health = health ;}
    void setName(const std::string& name) { m_name = name ;}


};

#endif // PLAYER_H
