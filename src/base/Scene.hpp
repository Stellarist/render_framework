#pragma once

#include "Node.hpp"
#include "SubMesh.hpp"
#include <algorithm>
#include <memory>
#include <queue>
#include <string>
#include <typeindex>
#include <vector>

class Scene : public Object {
public:
	Scene() = default;
	Scene(const std::string& name);

	auto getName() const -> const std::string&;
	void setName(const std::string& name);
	void setNodes(std::vector<std::unique_ptr<Node>>&& nodes);
	void addNode(std::unique_ptr<Node>&& node);
	void addChild(Node& child);
	auto getModel(uint32_t index = 0) -> std::unique_ptr<Component>;

	template <typename T>
	auto getComponents() -> std::vector<T*>;
	auto getComponents(const std::type_index& type) const -> const std::vector<std::unique_ptr<Component>>&;

	template <typename T>
	void setComponents(std::vector<std::unique_ptr<Component>>&& components);
	void setComponents(const std::type_index& type, std::vector<std::unique_ptr<Component>>&& components);

	template <typename T>
	void clearComponents();
	void addComponent(std::unique_ptr<Component>&& component);
	void addComponent(std::unique_ptr<Component>&& component, Node& node);

	template <typename T>
	bool hasComponent() const;
	bool hasComponent(const std::type_index& type) const;

	Node* findNode(const std::string& name);
	void  setRoot(Node& root);
	Node& getRoot();

private:
	std::string name;
	Node*       root;

	std::vector<std::unique_ptr<Node>> nodes;

	std::unordered_map<std::type_index, std::vector<std::unique_ptr<Component>>> components;
};

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

auto Scene::getModel(uint32_t index) -> std::unique_ptr<Component>
{
	auto meshed = std::move(components.at(typeid(SubMesh)));

	assert(index < meshed.size() && "Index out of bounds.");
	return std::move(meshed[index]);
}

template <typename T>
auto Scene::getComponents() -> std::vector<T*>
{
	auto result = std::vector<T*>{};
	if (hasComponent(typeid(T))) {
		auto& scene_components = components.at(typeid(T));
		result.reserve(scene_components.size());
		std::transform(scene_components.begin(), scene_components.end(), result.begin(), [](auto& component) -> T* {
			return dynamic_cast<T*>(component.get());
		});
	}
	return result;
}

auto Scene::getComponents(const std::type_index& type) const -> const std::vector<std::unique_ptr<Component>>&
{
	return components.at(type);
}

template <typename T>
void setComponents(std::vector<std::unique_ptr<Component>>&& components)
{
	std::vector<std::unique_ptr<Component>> result(components.size());
	std::transform(components.begin(), components.end(), result.begin(), [](auto& component) -> std::unique_ptr<Component> {
		return std::unique_ptr<Component>(std::move(component));
	});
	setComponents(typeid(T), std::move(result));
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

template <typename T>
void Scene::clearComponents()
{
	setComponents<T>(typeid(T), {});
}

void Scene::addComponent(std::unique_ptr<Component>&& component)
{
	if (component)
		components[component->getType()].emplace_back(std::move(component));
}

template <typename T>
bool Scene::hasComponent() const
{
	return hasComponent(typeid(T));
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