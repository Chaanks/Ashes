#include "Image/TestImage.hpp"

#include "Command/TestCommandBuffer.hpp"
#include "Command/TestQueue.hpp"
#include "Core/TestDevice.hpp"
#include "Core/TestPhysicalDevice.hpp"
#include "Core/TestInstance.hpp"
#include "Miscellaneous/TestDeviceMemory.hpp"
#include "Command/TestQueue.hpp"
#include "Image/TestImageView.hpp"

#include <Ashes/Miscellaneous/Extent2D.hpp>
#include <Ashes/Sync/ImageMemoryBarrier.hpp>
#include <Ashes/Image/ImageSubresourceRange.hpp>

namespace test_renderer
{
	Image::Image( Image && rhs )
		: ashes::Image{ std::move( rhs ) }
		, m_device{ rhs.m_device }
	{
	}

	Image & Image::operator=( Image && rhs )
	{
		ashes::Image::operator=( std::move( rhs ) );
		return *this;
	}

	Image::Image( Device const & device
		, ashes::ImageCreateInfo const & createInfo )
		: ashes::Image{ device, createInfo }
		, m_device{ device }
	{
	}

	Image::Image( Device const & device
		, VkFormat format
		, VkExtent2D const & dimensions )
		: ashes::Image{ device
			, {
				0u,
				VK_IMAGE_TYPE_2D,
				format,
				VkExtent3D{ dimensions.width, dimensions.height, 1u },
				1u,
				1u,
				VK_SAMPLE_COUNT_1_BIT,
				VK_IMAGE_TILING_OPTIMAL,
				( isDepthOrStencilFormat( format )
					? ashes::ImageUsageFlag::eDepthStencilAttachment
					: ashes::ImageUsageFlag::eColourAttachment ),
				VK_SHARING_MODE_EXCLUSIVE,
				{},
				VK_IMAGE_LAYOUT_UNDEFINED
			} }
		, m_device{ device }
	{
	}

	Image::Image( Device const & device
		, VkFormat format
		, VkExtent2D const & dimensions
		, ashes::ImageUsageFlags usageFlags
		, VkImageTiling tiling
		, VkMemoryPropertyFlags memoryFlags )
		: Image{ device
			, {
				0u,
				VK_IMAGE_TYPE_2D,
				format,
				VkExtent3D{ dimensions.width, dimensions.height, 1u },
				1u,
				1u,
				VK_SAMPLE_COUNT_1_BIT,
				tiling,
				usageFlags,
				VK_SHARING_MODE_EXCLUSIVE,
				{},
				VK_IMAGE_LAYOUT_UNDEFINED
			} }
	{
	}

	Image::~Image()
	{
	}

	ashes::MemoryRequirements Image::getMemoryRequirements()const
	{
		ashes::MemoryRequirements result{};
		result.size = ashes::getSize( getDimensions(), getFormat() );
		result.type = ashes::ResourceType::eImage;
		auto extent = ashes::getMinimalExtent3D( getFormat() );
		result.alignment = ashes::getSize( extent, getFormat() );
		result.memoryTypeBits = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
			| ( ( checkFlag( m_createInfo.usage, ashes::ImageUsageFlag::eTransferDst )
				&& checkFlag( m_createInfo.usage, ashes::ImageUsageFlag::eTransferSrc ) )
				? VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
				: VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
		return result;
	}

	ashes::ImageViewPtr Image::createView( ashes::ImageViewCreateInfo const & createInfo )const
	{
		return std::make_shared< ImageView >( m_device
			, *this
			, createInfo );
	}

	void Image::doBindMemory()
	{
	}
}