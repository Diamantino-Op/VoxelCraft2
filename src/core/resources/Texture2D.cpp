#include "Texture2D.h"
#include "../Renderer.h"
#include "../managers/PipelineManager.h"

Texture2D::~Texture2D() {
    Renderer::Instance->Device.destroySampler(_textureSampler);
    Renderer::Instance->Device.destroyImageView(_textureImageSet.imageView);
    vmaDestroyImage(Renderer::Instance->Allocator, _textureImageSet.image, _textureImageSet.allocation);
}

void Texture2D::load(unsigned char* data, int width, int height, LoadTextureInfo info) {
    this->_width = width;
    this->_height = height;

    this->_mipmapLevels = static_cast<unsigned int>(std::floor(std::log2(std::max(_width, _height)))) + 1;

    _pipeline = PipelineManager::getPipeline(info.pipeline);
    if (_pipeline == nullptr) {
        throw std::runtime_error("The specified pipeline provided to the texture does not exist!");
    }

    vk::ImageCreateFlagBits createFlags = {};
    vk::ImageViewType imageViewType = vk::ImageViewType::e2D;

    auto imageSize = width * height * 4;

    // ON CPU
    vk::Buffer stagingBuffer = nullptr;
    VmaAllocation stagingBufferAlloc = VK_NULL_HANDLE;
    VmaAllocationInfo stagingBufferAllocInfo = {};
    Renderer::Instance->createBuffer(stagingBuffer, stagingBufferAlloc, stagingBufferAllocInfo,
                                     imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VMA_MEMORY_USAGE_CPU_ONLY,
                                     VMA_ALLOCATION_CREATE_MAPPED_BIT);

    // Copy the into the staging buffer.
    memcpy(stagingBufferAllocInfo.pMappedData, data, imageSize);

    // ON GPU
    Renderer::Instance->createImage(_textureImageSet.image, _textureImageSet.allocation, width, height, vk::SampleCountFlagBits::e1, info.format, vk::ImageTiling::eOptimal, 1, _mipmapLevels, vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled, createFlags);

    // Transition image for transfer
    Renderer::Instance->transitionImageLayout(_textureImageSet.image, info.format, vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal, 1, _mipmapLevels);

    // Transfer to GPU
    Renderer::Instance->copyBufferToImage(stagingBuffer, _textureImageSet.image, width, height, 1);

    // Still on eTransferDstOptimal while generating mipmaps
    Renderer::Instance->generateMipmaps(_textureImageSet.image, info.format, _width, _height, _mipmapLevels);

    // Cleanup staging buffers
    vmaDestroyBuffer(Renderer::Instance->Allocator, stagingBuffer, stagingBufferAlloc);

    // Create the texture image view
    _textureImageSet.imageView = Renderer::Instance->createImageView(_textureImageSet.image, info.format, vk::ImageAspectFlagBits::eColor, imageViewType, 1, _mipmapLevels);

    // Setup sampling
    vk::SamplerCreateInfo samplerInfo = {
            .magFilter = info.filter,
            .minFilter = info.filter,
            .mipmapMode = info.mipmapMode,
            .addressModeU = info.addressMode,
            .addressModeV = info.addressMode,
            .addressModeW = info.addressMode,
            .mipLodBias = 0.0f,
            .anisotropyEnable = VK_TRUE,
            .maxAnisotropy = 16.0f,
            .compareEnable = VK_FALSE,
            .compareOp = vk::CompareOp::eAlways,
            .minLod = 0.0f,
            .maxLod = static_cast<float>(_mipmapLevels),
            .borderColor = vk::BorderColor::eIntOpaqueBlack,
            .unnormalizedCoordinates = VK_FALSE };

    _textureSampler = Renderer::Instance->Device.createSampler(samplerInfo);

    // Setup the descriptor set
    _descriptorSet = _pipeline->createTexSamplerDescriptorSet();

    // Bind the uniform buffer
    vk::DescriptorImageInfo imageInfo = {
            .sampler = _textureSampler,
            .imageView = _textureImageSet.imageView,
            .imageLayout = vk::ImageLayout::eShaderReadOnlyOptimal };

    vk::WriteDescriptorSet descriptorWrite = {
            .dstSet = _descriptorSet,
            .dstBinding = 0,
            .dstArrayElement = 0,
            .descriptorCount = 1,
            .descriptorType = vk::DescriptorType::eCombinedImageSampler,
            .pImageInfo = &imageInfo };

    Renderer::Instance->Device.updateDescriptorSets(descriptorWrite, nullptr);
}

void Texture2D::bind(vk::CommandBuffer &commandBuffer) const {
    commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, _pipeline->getPipelineLayout(), 2, 1, &_descriptorSet, 0, nullptr);
}
