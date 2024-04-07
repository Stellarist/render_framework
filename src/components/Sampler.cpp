#include "Sampler.hpp"

Sampler::Sampler(const std::string& name, SamplerImpl&& sampler) :
    Component(name),
    sampler(std::move(sampler))
{}

std::type_index getType()
{
	return typeid(Sampler);
}
