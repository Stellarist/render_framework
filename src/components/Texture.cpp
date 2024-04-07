#include "Texture.hpp"
#include <cassert>

Texture::Texture(const std::string& name) :
    Component(name)
{}

std::type_index getType()
{
	return typeid(Texture);
}

void Texture::setImage(Image& image)
{
	this->image = &image;
}

Image* Texture::getImage()
{
	return image;
}

void Texture::setSampler(Sampler& sampler)
{
	this->sampler = &sampler;
}

Sampler* Texture::getSampler()
{
	assert(sampler && "Texture has no sampler");
	return sampler;
}
