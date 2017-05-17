#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include"camera.h"


class FPSCamera : public Camera
{
public:
    FPSCamera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
    void update();
	glm::mat4 getMVP() const ;
	glm::mat4 getModel() const { return getTransform()->GetModel();}
	virtual glm::quat getRot() const { return (m_rot) ;}
	glm::vec3 getPos() const;
	void addToEngine(CoreEngine* core);
private:
    glm::vec2 screenMiddle;
    glm::quat m_rot;
};

#endif // FPSCAMERA_H
