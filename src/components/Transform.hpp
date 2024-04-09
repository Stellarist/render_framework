#pragma once

#include "base/Component.hpp"
#include "base/Node.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform : public Component {
public:
	Transform(Node& node);
	virtual ~Transform() = default;

	Node&                   getNode() const;
	virtual std::type_index getType() override;

	const glm::vec3& getTranslation() const;
	const glm::quat& getRotation() const;
	const glm::vec3& getScale() const;

	void setTranslation(const glm::vec3& translation);
	void setRotation(const glm::quat& rotation);
	void setScale(const glm::vec3& scale);

	glm::mat4 getMatrix() const;
	glm::mat4 getWorldMatrix();
	void      setMatrix(const glm::mat4& matrix);
	void      invalidateWorldMatrix();

private:
	Node&     node;
	glm::vec3 translation{0.0f, 0.0f, 0.0f};
	glm::quat rotation{1.0f, 0.0f, 0.0f, 0.0f};
	glm::vec3 scale{1.0f, 1.0f, 1.0f};
	glm::mat4 world_matrix{1.0f};
	bool      update_world_matrix{true};

	void update_world_transform();
};

Transform::Transform(Node& node) :
    node(node)
{}

Node& Transform::getNode() const
{
	return node;
}

std::type_index Transform::getType()
{
	return typeid(Transform);
}

const glm::vec3& Transform::getTranslation() const
{
	return translation;
}

const glm::quat& Transform::getRotation() const
{
	return rotation;
}

const glm::vec3& Transform::getScale() const
{
	return scale;
}

void Transform::setTranslation(const glm::vec3& translation)
{
	this->translation = translation;
	invalidateWorldMatrix();
}

void Transform::setRotation(const glm::quat& rotation)
{
	this->rotation = rotation;
	invalidateWorldMatrix();
}

void Transform::setScale(const glm::vec3& scale)
{
	this->scale = scale;
	invalidateWorldMatrix();
}

glm::mat4 Transform::getMatrix() const
{
	return glm::translate(glm::mat4(1.0f), translation) *
	       glm::mat4_cast(rotation) *
	       glm::scale(glm::mat4(1.0f), scale);
}

glm::mat4 Transform::getWorldMatrix()
{
	update_world_transform();
	return world_matrix;
}

void Transform::setMatrix(const glm::mat4& matrix)
{
	this->world_matrix = matrix;
	invalidateWorldMatrix();
}

void Transform::invalidateWorldMatrix()
{
	update_world_matrix = true;
}

void Transform::update_world_transform()
{
	if (!update_world_matrix)
		return;

	world_matrix = getMatrix();
	if (auto parent = node.getParent(); parent) {
		auto& transform = parent->getComponent<Transform>();
		world_matrix = transform.getWorldMatrix() * world_matrix;
	}

	update_world_matrix = false;
}
