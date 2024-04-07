#pragma once

#include "Component.hpp"
#include "Node.hpp"
#include <glm/glm.hpp>
#include <memory>
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
