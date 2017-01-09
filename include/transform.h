#ifndef TRANSFORM_INCLUDED_H
#define TRANSFORM_INCLUDED_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include<glm/gtx/quaternion.hpp>
#include<glm/gtc/quaternion.hpp>
#include<iostream>

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::quat& rot = glm::quat(1,0,0,0), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->pos = pos;
		this->rot = rot;
		this->scale = scale;
	}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(pos);
		glm::mat4 scaleMat = glm::scale(scale);
		glm::mat4 rotMat = glm::toMat4(rot);
		return  posMat * rotMat *scaleMat;
	}

	glm::vec3 getForward() { return glm::normalize(rot*glm::vec3(0,0,-1));}
	glm::vec3 getUp() { return glm::normalize(rot*glm::vec3(0,1,0));}
	glm::vec3 getRight() { return glm::normalize(rot*glm::vec3(1,0,0));}

	inline glm::vec3 GetPos() { return pos; }
	inline glm::quat GetRot() { return rot; }
	inline glm::vec3 GetScale() { return scale; }

	inline void SetPos(glm::vec3 pos) { this->pos = pos; }
	inline void SetRot(glm::quat rot) { this->rot = rot; }
	inline void SetScale(glm::vec3 scale) { this->scale = scale; }

	void rotate(const glm::quat rotation);
	void rotate(const glm::vec3 axis , float angle);
protected:
private:
	glm::vec3 pos;
	glm::quat rot;
	glm::vec3 scale;
};

#endif
