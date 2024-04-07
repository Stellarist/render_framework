#include "Camera.hpp"
#include "Transform.hpp"
#include <stdexcept>

Camera::Camera(const std::string& name) :
    Component{name}
{}

std::type_index Camera::getType()
{
	return typeid(Camera);
}

glm::mat4 Camera::getView()
{
	if (!node)
		throw std::runtime_error{"Camera component is not attached to a node"};

	auto& transform = node->getComponent<Transform>();
	return glm::inverse(transform.getWorldMatrix());
}

void Camera::setNode(Node& node)
{
	this->node = &node;
}

Node* Camera::getNode()
{
	return node;
}

const glm::mat4 Camera::getPreRotation()
{
	return pre_rotation;
}

void Camera::setPreRotation(const glm::mat4& pre_rotation)
{
	this->pre_rotation = pre_rotation;
}
