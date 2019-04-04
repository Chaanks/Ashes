/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#include "AshesPP/Image/Image.hpp"

#include "AshesPP/Buffer/StagingBuffer.hpp"
#include "AshesPP/Command/CommandBuffer.hpp"
#include "AshesPP/Core/Device.hpp"
#include "AshesPP/Image/ImageView.hpp"
#include "AshesPP/Sync/Fence.hpp"

namespace ashes
{
	Image::Image( Image && rhs )
		: m_device{ rhs.m_device }
		, m_createInfo{ std::move( rhs.m_createInfo ) }
		, m_internal{ rhs.m_internal }
		, m_ownInternal{ rhs.m_ownInternal }
	{
		rhs.m_internal = VK_NULL_HANDLE;
		registerObject( m_device, "Image", this );
	}

	Image & Image::operator=( Image && rhs )
	{
		if ( &rhs != this )
		{
			m_createInfo = std::move( rhs.m_createInfo );
			m_internal = rhs.m_internal;
			m_ownInternal = rhs.m_ownInternal;
			rhs.m_internal = VK_NULL_HANDLE;
			registerObject( m_device, "Image", this );
		}

		return *this;
	}

	Image::Image( Device const & device
		, VkImageCreateInfo createInfo )
		: m_device{ device }
		, m_ownInternal{ true }
		, m_createInfo{ std::move( createInfo ) }
	{
		DEBUG_DUMP( m_createInfo );
		auto res = m_device.vkCreateImage( m_device
			, &m_createInfo
			, nullptr
			, &m_internal );
		checkError( res, "Image creation" );
		registerObject( m_device, "Image", this );
	}

	Image::Image( Device const & device
		, VkImage image )
		: m_device{ device }
		, m_ownInternal{ false }
		, m_internal{ image }
	{
	}

	Image::~Image()
	{
		if ( m_ownInternal )
		{
			unregisterObject( m_device, this );

			if ( m_internal != VK_NULL_HANDLE )
			{
				m_device.vkDestroyImage( m_device
					, m_internal
					, nullptr );
			}
		}
	}

	void Image::bindMemory( DeviceMemoryPtr memory )
	{
		assert( !m_storage && "A resource can only be bound once to a device memory object." );
		m_storage = std::move( memory );
		auto res = m_device.vkBindImageMemory( m_device
			, m_internal
			, *m_storage
			, 0 );
		checkError( res, "Image storage binding" );
	}

	Image::Mapped Image::lock( uint32_t offset
		, uint32_t size
		, VkMemoryMapFlags flags )const
	{
		assert( m_storage && "The resource is not bound to a device memory object." );
		Mapped mapped{};
		VkImageSubresource subResource{};
		subResource.aspectMask = getAspectMask( getFormat() );
		VkSubresourceLayout subResourceLayout;
		m_device.getImageSubresourceLayout( *this, subResource, subResourceLayout );

		mapped.data = m_storage->lock( offset
			, size
			, flags );

		if ( mapped.data )
		{
			mapped.arrayPitch = subResourceLayout.arrayPitch;
			mapped.depthPitch = subResourceLayout.depthPitch;
			mapped.rowPitch = subResourceLayout.rowPitch;
			mapped.size = subResourceLayout.size;
			mapped.data += subResourceLayout.offset;
		}

		return mapped;
	}

	void Image::invalidate( uint32_t offset
		, uint32_t size )const
	{
		assert( m_storage && "The resource is not bound to a device memory object." );
		return m_storage->invalidate( offset, size );
	}

	void Image::flush( uint32_t offset
		, uint32_t size )const
	{
		assert( m_storage && "The resource is not bound to a device memory object." );
		return m_storage->flush( offset, size );
	}

	void Image::unlock()const
	{
		assert( m_storage && "The resource is not bound to a device memory object." );
		return m_storage->unlock();
	}

	void Image::generateMipmaps( CommandPool const & commandPool
		, Queue const & queue )const
	{
		auto commandBuffer = commandPool.createCommandBuffer();
		commandBuffer->begin( VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT );
		generateMipmaps( *commandBuffer );
		commandBuffer->end();
		auto fence = m_device.createFence();
		queue.submit( *commandBuffer, fence.get() );
		fence->wait( FenceTimeout );
	}

	void Image::generateMipmaps( CommandBuffer & commandBuffer )const
	{
		auto const width = int32_t( getDimensions().width );
		auto const height = int32_t( getDimensions().height );

		for ( uint32_t layer = 0u; layer < getLayerCount(); ++layer )
		{
			auto srcView = createView( VkImageViewCreateInfo
				{
					VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
					nullptr,
					0u,
					*this,
					VkImageViewType( getType() ),
					getFormat(),
					VkComponentMapping{},
					VkImageSubresourceRange
					{
						getAspectMask( getFormat() ),
						0,
						1u,
						layer,
						1u
					}
				} );
			commandBuffer.memoryBarrier( VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT
				, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT
				, srcView->makeTransferSource( VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED, 0u ) );

			// Copy down mips from n-1 to n
			for ( uint32_t level = 1; level < getMipmapLevels(); level++ )
			{
				VkImageBlit imageBlit{};

				// Source
				imageBlit.srcSubresource.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
				imageBlit.srcSubresource.baseArrayLayer = layer;
				imageBlit.srcSubresource.layerCount = 1;
				imageBlit.srcSubresource.mipLevel = level - 1;
				imageBlit.srcOffsets[0].x;
				imageBlit.srcOffsets[0].y;
				imageBlit.srcOffsets[0].z;
				imageBlit.srcOffsets[1].x = int32_t( width >> ( level - 1 ) );
				imageBlit.srcOffsets[1].y = int32_t( height >> ( level - 1 ) );
				imageBlit.srcOffsets[1].z = 1;

				// Destination
				imageBlit.dstSubresource.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
				imageBlit.dstSubresource.baseArrayLayer = layer;
				imageBlit.dstSubresource.layerCount = 1;
				imageBlit.dstSubresource.mipLevel = level;
				imageBlit.dstOffsets[0].x;
				imageBlit.dstOffsets[0].y;
				imageBlit.dstOffsets[0].z;
				imageBlit.dstOffsets[1].x = int32_t( width >> level );
				imageBlit.dstOffsets[1].y = int32_t( height >> level );
				imageBlit.dstOffsets[1].z = 1;

				VkImageSubresourceRange mipSubRange
				{
					VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT,
					level,
					1u,
					layer,
					1u
				};

				// Transiton current mip level to transfer dest
				VkImageMemoryBarrier dstTransitionBarrier
				{
					VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					nullptr,
					0u,
					VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT,
					VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED,
					VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					~( 0u ),
					~( 0u ),
					*this,
					mipSubRange
				};
				commandBuffer.memoryBarrier( VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT
					, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT
					, dstTransitionBarrier );

				// Blit from previous level
				commandBuffer.blitImage( *this
					, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
					, *this
					, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
					, { imageBlit }
					, VkFilter::VK_FILTER_LINEAR );

				// Transiton current mip level to transfer source for read in next iteration
				VkImageMemoryBarrier srcTransitionBarrier
				{
					VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					nullptr,
					VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT,
					VkAccessFlagBits::VK_ACCESS_TRANSFER_READ_BIT,
					VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
					~( 0u ),
					~( 0u ),
					*this,
					mipSubRange
				};
				commandBuffer.memoryBarrier( VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT
					, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT
					, srcTransitionBarrier );
			}

			srcView = createView(
				{
					VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
					nullptr,
					0u,
					*this,
					VkImageViewType( getType() ),
					getFormat(),
					VkComponentMapping{},
					VkImageSubresourceRange
					{
						getAspectMask( getFormat() ),
						0,
						getMipmapLevels(),
						layer,
						1u
					}
				} );
			commandBuffer.memoryBarrier( VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT
				, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT
				, srcView->makeShaderInputResource( VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED, 0u ) );
		}
	}

	VkMemoryRequirements Image::getMemoryRequirements()const
	{
		return m_device.getImageMemoryRequirements( m_internal );
	}

	ImageViewPtr Image::createView( VkImageViewCreateInfo const & createInfo )const
	{
		return std::make_unique< ImageView >( m_device
			, *this
			, createInfo );
	}

	ImageViewPtr Image::createView( VkImageViewType type
		, VkFormat format
		, uint32_t baseMipLevel
		, uint32_t levelCount
		, uint32_t baseArrayLayer
		, uint32_t layerCount
		, VkComponentMapping const & mapping )const
	{
		return createView(
		{
			VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			nullptr,
			0u,
			*this,
			type,
			format,
			mapping,
			{
				getAspectMask( format ),
				baseMipLevel,
				levelCount,
				baseArrayLayer,
				layerCount
			}
		} );
	}
}
