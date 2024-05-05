#pragma once

#include "Camera.hpp"
#include <glm/glm.hpp>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

class PerspectiveCamera : public Camera {
public:
	PerspectiveCamera(const std::string& name);
	virtual ~PerspectiveCamera() = default;

	float getFarPlane() const;
	void  setFarPlane(float zfar);
	float getNearPlane() const;
	void  setNearPlane(float znear);
	float getAspectRatio();
	void  setAspectRatio(float aspect_ratio);
	float getFov();
	void  setFov(float fov);

	virtual glm::mat4 getProjection() override;

private:
	float aspect_ratio{1.0f};
	float fov{glm::radians(60.0f)};
	float far_plane{100.0};
	float near_plane{0.1f};
};

PerspectiveCamera::PerspectiveCamera(const std::string& name) :
    Camera(name)
{}

float PerspectiveCamera::getFarPlane() const
{
	return far_plane;
}

void PerspectiveCamera::setFarPlane(float zfar)
{
	far_plane = zfar;
}

float PerspectiveCamera::getNearPlane() const
{
	return near_plane;
}

void PerspectiveCamera::setNearPlane(float znear)
{
	near_plane = znear;
}

float PerspectiveCamera::getAspectRatio()
{
	return aspect_ratio;
}

void PerspectiveCamera::setAspectRatio(float aspect_ratio)
{
	this->aspect_ratio = aspect_ratio;
}

float PerspectiveCamera::getFov()
{
	return fov;
}

void PerspectiveCamera::setFov(float fov)
{
	this->fov = fov;
}

glm::mat4 PerspectiveCamera::getProjection()
{
	return glm::perspective(fov, aspect_ratio, near_plane, far_plane);
}
