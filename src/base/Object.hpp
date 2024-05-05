#pragma once

#include <typeindex>

static uint64_t id_counter = 0;

class Object {
public:
	Object() = default;
	virtual ~Object() = default;

	virtual std::type_index getType() = 0;

	uint64_t getId() const;

private:
	uint64_t id;
};

Object::Object() :
    id(id_counter++)
{}

uint64_t Object::getId() const
{
	return id;
}
