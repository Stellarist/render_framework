#include "Node.hpp"
#include "Component.hpp"

Node::Node(const size_t id, const std::string& name) :
    id(id),
    name(name),
    transform(*this)
{
	setComponent(transform);
}

const size_t Node::getId() const
{
	return id;
}

const std::string& Node::getName() const
{
	return name;
}

Node* Node::getParent() const
{
	return parent;
}

void Node::setParent(Node& parent)
{
	this->parent = &parent;
	transform.invalidateWorldMatrix();
}

Transform& Node::getTransform()
{
	return transform;
}

Component& Node::getComponent(std::type_index type) const
{
	return *components.at(type);
}

void Node::setComponent(Component& component)
{
	components[component.getType()] = &component;
}

bool Node::hasComponent(std::type_index type) const
{
	return components.count(type) > 0;
}

const std::vector<Node*>& Node::getChildren() const
{
	return children;
}

void Node::addChild(Node& child)
{
	children.push_back(&child);
}
