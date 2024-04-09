#pragma once

#include "base/Component.hpp"
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

	glm::vec3 getEmissive();
	void      setEmissive(const glm::vec3& emissive);
	bool      getDoubleSided();
	void      setDoubleSided(bool double_sided);
	float     getAlphaCutoff();
	void      setAlphaCutoff(float alpha_cutoff);
	AlphaMode getAlphaMode();
	void      setAlphaMode(AlphaMode alpha_mode);
	auto      getTextures() -> std::unordered_map<std::string, Texture*>&;
	auto      getTextures() const -> const std::unordered_map<std::string, Texture*>&;

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

glm::vec3 Material::getEmissive()
{
	return emissive;
}

void Material::setEmissive(const glm::vec3& emissive)
{
	this->emissive = emissive;
}

bool Material::getDoubleSided()
{
	return double_sided;
}

void Material::setDoubleSided(bool double_sided)
{
	this->double_sided = double_sided;
}

float Material::getAlphaCutoff()
{
	return alpha_cutoff;
}

void Material::setAlphaCutoff(float alpha_cutoff)
{
	this->alpha_cutoff = alpha_cutoff;
}

AlphaMode Material::getAlphaMode()
{
	return alpha_mode;
}

void Material::setAlphaMode(AlphaMode alpha_mode)
{
	this->alpha_mode = alpha_mode;
}

auto Material::getTextures() -> std::unordered_map<std::string, Texture*>&
{
	return textures;
}

auto Material::getTextures() const -> const std::unordered_map<std::string, Texture*>&
{
	return textures;
}
