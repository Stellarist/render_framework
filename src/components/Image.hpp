#pragma once

#include "base/Component.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

// TODO
class ImageImpl;
class ImageView;

struct ImageFormat {
	uint32_t format;
};

struct ImageExtent {
	uint32_t width;
	uint32_t height;
	uint32_t depth;
};

struct Mipmap {
	uint32_t    level = 0;
	uint32_t    offset = 0;
	ImageExtent extent = {0, 0, 0};
};

class Image : public Component {
public:
	enum ContentType {
		Unknown,
		Color,
		Other
	};

	Image(const std::string& name, std::vector<uint8_t>&& data = {}, std::vector<Mipmap>&& mipmaps = {{}});
	virtual ~Image() = default;

	virtual std::type_index getType() override;
	virtual void            createImage() = 0;

	static auto load(const std::string& name, const std::string& uri, ContentType content_type) -> std::unique_ptr<Image>;

	auto getData() const -> const std::vector<uint8_t>&;
	void setData(const uint8_t* raw_data, size_t size);
	auto getMutData() -> std::vector<uint8_t>&;
	auto clearData() -> void;
	auto getFormat() const -> ImageFormat;
	void setFormat(ImageFormat format);
	auto getExtent() const -> const ImageExtent&;
	void setWidth(uint32_t width);
	void setHeight(uint32_t height);
	void setDepth(uint32_t depth);
	void setLayers(uint32_t layers);
	auto getLayers() const -> const uint32_t;
	auto getMipmap(size_t index) -> Mipmap&;
	auto getMipmaps() const -> const std::vector<Mipmap>&;
	auto getMutMipmaps() -> std::vector<Mipmap>&;
	auto getOffsets() const -> const std::vector<std::vector<uint64_t>>&;
	void setOffsets(const std::vector<std::vector<uint64_t>>& offsets);
	void generateMipmaps();
	auto getImage() const -> const ImageImpl&;
	auto getImageView() const -> const ImageView&;

private:
	std::vector<uint8_t>               data;
	ImageFormat                        format{0};
	uint32_t                           layers{1};
	std::vector<Mipmap>                mipmaps{{}};
	std::vector<std::vector<uint64_t>> offsets;
	std::unique_ptr<ImageImpl>         image;
	std::unique_ptr<ImageView>         image_view;
};
