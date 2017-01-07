#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include<glm/detail/func_geometric.hpp>
#include"InputHandler.h"
#include"transform.h"

#include<iostream>
class InputHandler;

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);

    void update(const glm::vec2 mousePos);

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}
	glm::vec3& getForward() { return forward;}
	glm::mat4 getMVP() const { return GetViewProjection()*transform.GetModel();}
	glm::mat4 getModel() const { return transform.GetModel();}
	glm::vec3& getPos() { return pos;}
	glm::vec3 getPos() const { return pos;}
	glm::vec3& getUp() { return up;}

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec2 oldMousePos;
	Transform transform;

	void moveSideways(float d);
    void moveforwardBack(float d);

};

#endif
