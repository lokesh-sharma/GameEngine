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
    virtual void update();
	virtual glm::mat4 getMVP() const ;
	virtual glm::mat4 getModel() const { return getTransform()->GetModel();}
	virtual glm::quat getRot() const { return getTransform()->GetRot() ;}
	virtual glm::mat4 getProjection() const { return projection;}
	virtual glm::vec3 getPos() const;
	virtual void setProjection(glm::mat4 proj) { projection = proj; }
	virtual void addToEngine(CoreEngine* core);
protected:
    glm::mat4 projection;
};

#endif
