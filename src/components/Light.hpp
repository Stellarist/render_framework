#pragma once

#include "Component.hpp"
#include "Node.hpp"
#include <glm/glm.hpp>
#include <string>
#include <typeinfo>
#include <vector>

enum LightType {
	Directional = 0,
	Point = 1,
	Spot = 2,
	Max
};

struct LightProperties {
	glm::vec3 direction{0.0f, 0.0f, -1.0f};
	glm::vec3 color{1.0f, 1.0f, 1.0f};
	float     intensity{1.0f};
	float     range{0.0f};
	float     inner_cone_angle{0.0f};
	float     outer_cone_angle{0.0f};
};

class Light : public Component {
public:
	Light(const std::string& name);
	Light(Light&& other) = default;
	virtual ~Light() = default;

	virtual std::type_index getType() override;

	Node* getNode();
	void  setNode(Node& node);
	auto  getLightType() -> const LightType&;
	void  setLightType(const LightType& type);
	auto  getProperties() -> const LightProperties&;
	void  setProperties(const LightProperties& properties);

private:
	Node*           node{nullptr};
	LightType       light_type;
	LightProperties properties;
};

Light::Light(const std::string& name) :
    Component{name}
{}

std::type_index Light::getType()
{
	return typeid(Light);
}

void Light::setNode(Node& node)
{
	this->node = &node;
}

Node* Light::getNode()
{
	return node;
}

void Light::setLightType(const LightType& type)
{
	this->light_type = type;
}

const LightType& Light::getLightType()
{
	return light_type;
}

void Light::setProperties(const LightProperties& properties)
{
	this->properties = properties;
}

const LightProperties& Light::getProperties()
{
	return properties;
}
