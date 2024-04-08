#pragma once

#include "Camera.hpp"

class OrthoCamera : public Camera {
public:
	OrthoCamera(const std::string& name);
	OrthoCamera(const std::string& name, float left, float right, float bottom, float top, float near_plane, float far_plane);
	virtual ~OrthoCamera() = default;

	float getLeft() const;
	void  setLeft(float left);
	float getRight() const;
	void  setRight(float right);
	float getTop() const;
	void  setTop(float top);
	float getBottom() const;
	void  setBottom(float bottom);
	float getNearPlane() const;
	void  setNearPlane(float near_plane);
	float getFarPlane() const;
	void  setFarPlane(float far_plane);

	virtual glm::mat4 getProjection() override;

private:
	float left{-1.0f};
	float right{1.0f};
	float top{1.0f};
	float bottom{-1.0f};
	float near_plane{0.0f};
	float far_plane{1.0f};
};

OrthoCamera::OrthoCamera(const std::string& name) :
    Camera{name}
{}

OrthoCamera::OrthoCamera(const std::string& name, float left, float right, float bottom, float top, float near_plane, float far_plane) :
    Camera{name},
    left{left},
    right{right},
    top{top},
    bottom{bottom},
    near_plane{near_plane},
    far_plane{far_plane}
{}

float OrthoCamera::getLeft() const
{
	return left;
}

void OrthoCamera::setLeft(float new_left)
{
	left = new_left;
}

float OrthoCamera::getRight() const
{
	return right;
}

void OrthoCamera::setRight(float new_right)
{
	right = new_right;
}

float OrthoCamera::getTop() const
{
	return top;
}

void OrthoCamera::setTop(float new_top)
{
	top = new_top;
}

float OrthoCamera::getBottom() const
{
	return bottom;
}

void OrthoCamera::setBottom(float new_bottom)
{
	bottom = new_bottom;
}

void OrthoCamera::setNearPlane(float new_near_plane)
{
	near_plane = new_near_plane;
}

float OrthoCamera::getNearPlane() const
{
	return near_plane;
}

void OrthoCamera::setFarPlane(float new_far_plane)
{
	far_plane = new_far_plane;
}

float OrthoCamera::getFarPlane() const
{
	return far_plane;
}

glm::mat4 OrthoCamera::getProjection()
{
	return glm::ortho(left, right, bottom, top, far_plane, near_plane);
}
