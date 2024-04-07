#pragma once

#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

#include "Component.hpp"

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