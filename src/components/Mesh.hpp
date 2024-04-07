#pragma once

#include "Component.hpp"

// TODO
class Mesh : public Component {
public:
	Mesh(const std::string& name);
	virtual ~Mesh() = default;

	void update_bounds(const std::vector<glm::vec3>& vertex_data, const std::vector<uint16_t>& index_data = {});

	virtual std::type_index get_type() override;

	const AABB& get_bounds() const;

	void add_submesh(SubMesh& submesh);

	const std::vector<SubMesh*>& get_submeshes() const;

	void add_node(Node& node);

	const std::vector<Node*>& get_nodes() const;

private:
	AABB bounds;

	std::vector<SubMesh*> submeshes;

	std::vector<Node*> nodes;
};
