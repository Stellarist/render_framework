#pragma once

#include "Component.hpp"
#include "Node.hpp"
#include "Transform.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>

class Camera : public Component {
public:
	Camera(const std::string& name);
	virtual ~Camera() = default;

	virtual std::type_index getType() override;
	virtual glm::mat4       getProjection() = 0;

	auto  getView() -> glm::mat4;
	Node* getNode();
	void  setNode(Node& node);
	auto  getPreRotation() -> const glm::mat4;
	void  setPreRotation(const glm::mat4& pre_rotation);

private:
	Node*     node{nullptr};
	glm::mat4 pre_rotation{1.0f};
};

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
