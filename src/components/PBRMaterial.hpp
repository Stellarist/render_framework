#pragma once

#include "Material.hpp"
#include <glm/glm.hpp>
#include <string>
#include <typeinfo>

class PBRMaterial : public Material {
public:
	PBRMaterial(const std::string& name);
	virtual ~PBRMaterial() = default;

	virtual std::type_index getType() override;

private:
	glm::vec4 base_color_factor{0.0f, 0.0f, 0.0f, 0.0f};

	float metallic_factor{0.0f};
	float roughness_factor{0.0f};
};

PBRMaterial::PBRMaterial(const std::string& name) :
    Material{name}
{}

std::type_index PBRMaterial::getType()
{
	return typeid(PBRMaterial);
}
