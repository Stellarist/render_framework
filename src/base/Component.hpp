#pragma once

#include "Object.hpp"
#include <string>
#include <typeindex>

class Component : public Object {
public:
	Component() = default;
	Component(const std::string& name);
	Component(Component&&) = default;
	virtual ~Component() = default;

	const std::string&      getName() const;
	virtual std::type_index getType() = 0;

private:
	std::string name;
};

Component::Component(const std::string& name) :
    name(name)
{}

const std::string& Component::getName() const
{
	return name;
}
