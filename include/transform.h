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
		m_parent = nullptr;
		initOldStuff = false;
		parentMatrix = glm::mat4();
	}
	void update()
	{
        if(initOldStuff)
        {
            this->oldPos = pos;
            this->oldrot = rot;
            this->oldScale = scale;
        }
        else
        {
            this->oldPos = pos + glm::vec3(1,0,0);
            this->oldrot = rot + glm::quat(1,1,1,1);
            this->oldScale = scale + glm::vec3(1,1,1);
            initOldStuff = true;
        }
	}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(pos);
		glm::mat4 scaleMat = glm::scale(scale);
		glm::mat4 rotMat = glm::toMat4(rot);
		return  getParentMatrix()*posMat * rotMat *scaleMat;
	}

	glm::vec3 getForward() { return glm::normalize(rot*glm::vec3(0,0,-1));}
	glm::vec3 getUp() { return glm::normalize(rot*glm::vec3(0,1,0));}
	glm::vec3 getRight() { return glm::normalize(rot*glm::vec3(1,0,0));}

	bool hasChanged() const ;
	glm::mat4 getParentMatrix() const ;
	void setParent(Transform* t) { m_parent = t;}

	inline glm::vec3 GetPos() { return pos; }
	inline glm::quat GetRot() { return rot; }
	inline glm::vec3 GetScale() { return scale; }

	inline void SetPos(glm::vec3 pos) { this->pos = pos; }
	inline void SetRot(glm::quat rot) { this->rot = rot;}
	inline void SetScale(glm::vec3 scale) { this->scale = scale; }
	inline void SetTransform(Transform& t)
	{
        pos = t.GetPos();
        rot = t.GetRot();
        scale = t.GetScale();
	}

	void rotate(const glm::quat rotation);
	void rotate(const glm::vec3 axis , float angle);
	glm::vec3 getTransformedPos();
protected:
private:
    Transform* m_parent;
    mutable glm::mat4 parentMatrix;
    bool initOldStuff;
	glm::vec3 pos;
	glm::quat rot;
	glm::vec3 scale;

	glm::vec3 oldPos;
	glm::vec3 oldScale;
	glm::quat oldrot;
};

#endif
