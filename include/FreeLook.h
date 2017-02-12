#ifndef FREELOOK_H
#define FREELOOK_H


#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include<glm/detail/func_geometric.hpp>
#include"InputHandler.h"
#include"transform.h"
#include "GameComponent.h"
#include"camera.h"

#include<iostream>
class InputHandler;

class FreeLook : public Camera
{
public:
    FreeLook(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
    void update();
	glm::mat4 getMVP() const ;
	glm::mat4 getModel() const { return getTransform()->GetModel()*m_transform.GetModel();}
	glm::vec3 getPos() const;
	void addToEngine(CoreEngine* core);
private:
    glm::vec2 screenMiddle;
    mutable Transform m_transform;
    void move(const glm::vec3 direction , float distance);
};

#endif // FREELOOK_H
