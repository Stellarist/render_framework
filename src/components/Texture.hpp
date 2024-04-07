#pragma once

#include "Component.hpp"
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
