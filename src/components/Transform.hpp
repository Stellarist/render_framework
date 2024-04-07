#pragma once

#include "Component.hpp"
#include "Node.hpp"
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
