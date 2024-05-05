#pragma once

#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

#include "base/Component.hpp"

// TODO: implement samplerImpl
class SamplerImpl;
//////

class Sampler : public Component {
public:
	Sampler(const std::string& name, SamplerImpl&& sampler);
	Sampler(Sampler&& other) = default;
	virtual ~Sampler() = default;

	virtual std::type_index getType() override;

private:
	SamplerImpl sampler;
};

Sampler::Sampler(const std::string& name, SamplerImpl&& sampler) :
    Component(name),
    sampler(std::move(sampler))
{}

std::type_index getType()
{
	return typeid(Sampler);
}
