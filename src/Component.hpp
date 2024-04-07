#pragma once

#include <string>
#include <typeindex>

class Component {
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
