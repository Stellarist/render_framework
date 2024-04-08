#pragma once

#include "AABB.hpp"
#include "Component.hpp"
#include "Node.hpp"
#include <glm/glm.hpp>
#include <vector>

// TODO
class SubMesh;
///

class Mesh : public Component {
public:
	Mesh(const std::string& name);
	virtual ~Mesh() = default;

	virtual std::type_index getType() override;

	auto getBounds() const -> const AABB&;
	void updateBounds(const std::vector<glm::vec3>& vertex_data, const std::vector<uint16_t>& index_data = {});
	auto getSubmeshes() const -> const std::vector<SubMesh*>&;
	void addSubmesh(SubMesh& submesh);
	auto getNodes() const -> const std::vector<Node*>&;
	void addNode(Node& node);

private:
	AABB                  bounds;
	std::vector<Node*>    nodes;
	std::vector<SubMesh*> sub_meshes;
};

Mesh::Mesh(const std::string& name) :
    Component{name}
{}

std::type_index Mesh::getType()
{
	return typeid(Mesh);
}

const AABB& Mesh::getBounds() const
{
	return bounds;
}

void Mesh::updateBounds(const std::vector<glm::vec3>& vertex_data, const std::vector<uint16_t>& index_data)
{
	bounds.update(vertex_data, index_data);
}

const std::vector<SubMesh*>& Mesh::getSubmeshes() const
{
	return sub_meshes;
}

void Mesh::addSubmesh(SubMesh& submesh)
{
	sub_meshes.push_back(&submesh);
}

const std::vector<Node*>& Mesh::getNodes() const
{
	return nodes;
}

void Mesh::addNode(Node& node)
{
	nodes.push_back(&node);
}
