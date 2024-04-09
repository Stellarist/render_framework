#pragma once

#include "base/Component.hpp"
#include <cassert>
#include <string>
#include <typeindex>

// TODO : implment
class Image;
class Sampler;
/***/

class Texture : public Component {
public:
	Texture(const std::string& name);
	Texture(Texture&& other) = default;
	virtual ~Texture() = default;

	virtual std::type_index getType() override;

	Image*   getImage();
	void     setImage(Image& image);
	Sampler* getSampler();
	void     setSampler(Sampler& sampler);

private:
	Image*   image;
	Sampler* sampler;
};

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
