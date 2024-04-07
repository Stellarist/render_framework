#pragma once

#include "Component.hpp"
#include "Transform.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class Node {
public:
	Node(const size_t id, const std::string& name);
	virtual ~Node() = default;

	const size_t       getId() const;
	const std::string& getName() const;
	Node*              getParent() const;
	void               setParent(Node& parent);
	Transform&         getTransform();

	template <typename T>
	T&         getComponent() const;
	Component& getComponent(std::type_index type) const;
	void       setComponent(Component& component);

	template <typename T>
	bool hasComponent() const;
	bool hasComponent(std::type_index type) const;

	const std::vector<Node*>& getChildren() const;
	void                      addChild(Node& child);

private:
	size_t      id;
	std::string name;
	Node*       parent{nullptr};
	Transform   transform;

	std::vector<Node*>                              children;
	std::unordered_map<std::type_index, Component*> components;
};

template <typename T>
inline T& Node::getComponent() const
{
	return dynamic_cast<T&>(getComponent(typeid(T)));
}

template <typename T>
inline bool Node::hasComponent() const
{
	return hasComponent(typeid(T));
}
