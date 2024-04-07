#include "Scene.hpp"
#include <queue>

Scene::Scene(const std::string& name) :
    name(name)
{}

const std::string& Scene::getName() const
{
	return name;
}

void Scene::setName(const std::string& name)
{
	this->name = name;
}

void Scene::setNodes(std::vector<std::unique_ptr<Node>>&& nodes)
{
	assert(!nodes.empty() && "Nodes cannot be empty.");
	this->nodes = std::move(nodes);
}

void Scene::addNode(std::unique_ptr<Node>&& node)
{
	nodes.emplace_back(std::move(node));
}

void Scene::addChild(Node& child)
{
	root->addChild(child);
}

// TODO: replace SubMesh
auto Scene::getModel(uint32_t index) -> std::unique_ptr<Component>
{
	// auto meshed = std::move(components.at(typeid(SubMesh)));

	// assert(index < meshed.size() && "Index out of bounds.");
	// return std::move(meshed[index]);
}

auto Scene::getComponents(const std::type_index& type) const -> const std::vector<std::unique_ptr<Component>>&
{
	return components.at(type);
}

void Scene::setComponents(const std::type_index& type, std::vector<std::unique_ptr<Component>>&& components)
{
	this->components[type] = std::move(components);
}

void Scene::addComponent(std::unique_ptr<Component>&& component, Node& node)
{
	node.setComponent(*component);
	if (component)
		components[component->getType()].emplace_back(std::move(component));
}

void Scene::addComponent(std::unique_ptr<Component>&& component)
{
	if (component)
		components[component->getType()].emplace_back(std::move(component));
}

bool Scene::hasComponent(const std::type_index& type) const
{
	return components.count(type) > 0;
}

Node* Scene::findNode(const std::string& name)
{
	for (auto node : root->getChildren()) {
		std::queue<Node*> traverse_node;
		traverse_node.push(node);

		while (!traverse_node.empty()) {
			auto node = traverse_node.front();
			traverse_node.pop();
			if (node->getName() == name)
				return node;

			for (auto child_node : node->getChildren())
				traverse_node.push(child_node);
		}
	}
	return nullptr;
}

void Scene::setRoot(Node& node)
{
	this->root = &node;
}

Node& Scene::getRoot()
{
	return *root;
}
