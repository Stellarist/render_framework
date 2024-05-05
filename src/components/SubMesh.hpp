#pragma once

#include "base/Component.hpp"
#include <Material.hpp>
#include <memory>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

// TODO: implement ShaderVariant
struct VertexAttribute {
	int           format = 0;
	std::uint32_t stride = 0;
	std::uint32_t offset = 0;
};

class SubMesh : public Component {
public:
	SubMesh(const std::string& name = {});
	virtual ~SubMesh() = default;

	virtual std::type_index getType() override;

	int           index_type{};
	std::uint32_t index_offset = 0;
	std::uint32_t vertices_count = 0;
	std::uint32_t vertex_indices = 0;

	std::unordered_map<std::string, core::Buffer> vertex_buffers;
	std::unique_ptr<core::Buffer>                 index_buffer;

	void                 setAttribute(const std::string& name, const VertexAttribute& attribute);
	bool                 getAttribute(const std::string& name, VertexAttribute& attribute) const;
	void                 setMaterial(const Material& material);
	const Material*      getMaterial() const;
	const ShaderVariant& getShaderVariant() const;
	ShaderVariant&       getMutShaderVariant();

private:
	const Material* material{nullptr};
	ShaderVariant   shader_variant;

	std::unordered_map<std::string, VertexAttribute> vertex_attributes;

	void computeShaderVariant();
};
