#pragma once

#include "Component.hpp"
#include <glm/glm.hpp>
#include <string>
#include <typeinfo>
#include <vector>

class AABB : public Component {
public:
	AABB();
	AABB(const glm::vec3& min, const glm::vec3& max);
	virtual ~AABB() = default;

	virtual std::type_index getType() override;

	void update(const glm::vec3& point);
	void update(const std::vector<glm::vec3>& vertex_data, const std::vector<uint16_t>& index_data);
	void reset();
	void transform(const glm::mat4& transform);

	glm::vec3 getScale() const;
	glm::vec3 getCenter() const;
	glm::vec3 getMin() const;
	glm::vec3 getMax() const;

private:
	glm::vec3 min;
	glm::vec3 max;
};
