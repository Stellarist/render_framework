#pragma once

#include <array>
#include <glm.hpp>
#include <stdexcept>
#include <vulkan/vulkan.hpp>

struct Vertex {
	glm::vec2 pos;
	glm::vec3 color;

	static VkVertexInputBindingDescription getBindingDescription()
	{
		VkVertexInputBindingDescription binding_description{
		    .binding = 0,
		    .stride = sizeof(Vertex),
		    .inputRate = VK_VERTEX_INPUT_RATE_VERTEX};

		return binding_description;
	}

	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 2> attribute_descriptions{
		    VkVertexInputAttributeDescription{
		        .location = 0,
		        .binding = 0,
		        .format = VK_FORMAT_R32G32_SFLOAT,
		        .offset = offsetof(Vertex, pos)},

		    VkVertexInputAttributeDescription{
		        .location = 1,
		        .binding = 0,
		        .format = VK_FORMAT_R32G32B32_SFLOAT,
		        .offset = offsetof(Vertex, color)}};

		return attribute_descriptions;
	}
};

class VertexBuffer {
public:
	VertexBuffer(VkDevice& device);
	~VertexBuffer();

	void create(const std::vector<Vertex>& vertices);
	void destroy();

	void bind() const;
	void unbind() const;

	const VkBuffer&     getBuffer() const;
	const VkDeviceSize& getDeviceSize() const;

	static void createVertexBuffer();

private:
	VkBuffer       buffer;
	VkDevice&      device;
	VkDeviceMemory device_memory;
	VkDeviceSize   device_size;
};

VertexBuffer::VertexBuffer()
{
	VkMemoryAllocateInfo info{
	    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
	    .allocationSize = };
}

void VertexBuffer::bind() const
{
	auto binding_description = Vertex::getBindingDescription();
	auto attribute_descriptions = Vertex::getAttributeDescriptions();

	VkPipelineVertexInputStateCreateInfo info{
	    .vertexBindingDescriptionCount = 1,
	    .pVertexBindingDescriptions = &Vertex::getBindingDescription(),
	    .vertexAttributeDescriptionCount = static_cast<uint32_t>(Vertex::getAttributeDescriptions().size()),
	    .pVertexAttributeDescriptions = Vertex::getAttributeDescriptions().data()};
}

void VertexBuffer::createVertexBuffer(const void* data, unsigned int size)
{
	VkBufferCreateInfo info{
	    .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
	    .size = size,
	    .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
	    .sharingMode = VK_SHARING_MODE_EXCLUSIVE};

	if (vkCreateBuffer(device, &info, nullptr, &buffer))
		throw std::runtime_error("Failed to create vertex buffer.");
}
