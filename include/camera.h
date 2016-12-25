#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include<glm/detail/func_geometric.hpp>
#include<iostream>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, -1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, zNear, zFar);
		this->oldMousePos = glm::vec2(400,300);
	}
    void update(const glm::vec2 mousePos)
    {
        glm::vec2 delta = mousePos - oldMousePos;
        float x = delta.x;
        float y = delta.y;
        x = x*0.4;
        y = y*0.4;
        forward = glm::mat3(glm::rotate( -x , up))*forward;
        glm::vec3 right = glm::cross(forward , up);
        forward = glm::mat3(glm::rotate(-y , right ))*forward;
        oldMousePos = mousePos;
    }
    void moveSideways(float d)
    {
        glm::vec3 right = glm::cross(forward , up);
        right =  glm::normalize(right);
        glm::vec4 temp = glm::vec4(pos,1);
        glm::mat4 posMat = glm::translate(right*d);
        temp = posMat*temp;
        pos = glm::vec3(temp);
    }
    void moveforwardBack(float d)
    {
        glm::vec4 temp = glm::vec4(pos,1);
        glm::mat4 posMat = glm::translate(glm::normalize(forward)*d);
        temp = posMat*temp;
        pos = glm::vec3(temp);

    }
	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}
	glm::vec3& getForward() { return forward;}
	glm::vec3& getPos() { return pos;}
	glm::vec3& getUp() { return up;}

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec2 oldMousePos;

};

#endif
