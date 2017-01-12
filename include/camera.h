#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include<glm/detail/func_geometric.hpp>
#include"InputHandler.h"
#include"transform.h"
#include "GameComponent.h"

#include<iostream>
class InputHandler;

class Camera : public GameComponent
{
public:
    Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
    void update();
	glm::mat4 getMVP() const ;
	glm::mat4 getModel() const { return getTransform()->GetModel();}
	glm::vec3 getPos() const { return getTransform()->GetPos();}
	void addToEngine(CoreEngine* core);
private:
    glm::mat4 projection;
    glm::vec2 screenMiddle;
    mutable Transform m_transform;
    void move(const glm::vec3 direction , float distance);
};

#endif
