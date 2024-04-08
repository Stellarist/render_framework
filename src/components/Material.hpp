#pragma once

#include "Component.hpp"
#include "texture.hpp"
#include <glm/glm.hpp>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

enum class AlphaMode {
	Opaque,
	Mask,
	Blend
};

class Material : public Component {
public:
	Material(const std::string& name);
	Material(Material&& other) = default;
	virtual ~Material() = default;

	virtual std::type_index getType() override;

private:
	glm::vec3 emissive{0.0f, 0.0f, 0.0f};
	bool      double_sided{false};
	float     alpha_cutoff{0.5f};
	AlphaMode alpha_mode{AlphaMode::Opaque};

	std::unordered_map<std::string, Texture*> textures;
};

Material::Material(const std::string& name) :
    Component{name}
{}

std::type_index Material::getType()
{
	return typeid(Material);
}
