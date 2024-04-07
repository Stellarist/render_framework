#pragma once

#include "Node.hpp"
#include <algorithm>
#include <memory>
#include <string>
#include <typeindex>
#include <vector>

class Scene {
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

template <typename T>
void setComponents(std::vector<std::unique_ptr<Component>>&& components)
{
	std::vector<std::unique_ptr<Component>> result(components.size());
	std::transform(components.begin(), components.end(), result.begin(), [](auto& component) -> std::unique_ptr<Component> {
		return std::unique_ptr<Component>(std::move(component));
	});
	setComponents(typeid(T), std::move(result));
}

template <typename T>
void Scene::clearComponents()
{
	setComponents<T>(typeid(T), {});
}

template <typename T>
bool Scene::hasComponent() const
{
	return hasComponent(typeid(T));
}
