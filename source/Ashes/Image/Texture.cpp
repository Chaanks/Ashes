/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#include "Ashes/Image/Texture.hpp"

#include "Ashes/Buffer/StagingBuffer.hpp"
#include "Ashes/Command/CommandBuffer.hpp"
#include "Ashes/Core/Device.hpp"
#include "Ashes/Image/ImageSubresource.hpp"
#include "Ashes/Image/SubresourceLayout.hpp"
#include "Ashes/Image/TextureView.hpp"
#include "Ashes/Sync/Fence.hpp"
#include "Ashes/Sync/ImageMemoryBarrier.hpp"

namespace ashes
{
	Texture::Texture( Texture && rhs )
		: m_device{ rhs.m_device }
		, m_flags{ rhs.m_flags }
		, m_imageType{ rhs.m_imageType }
		, m_format{ rhs.m_format }
		, m_dimensions{ rhs.m_dimensions }
		, m_mipLevels{ rhs.m_mipLevels }
		, m_arrayLayers{ rhs.m_arrayLayers }
	{
		registerObject( m_device, "Texture", this );
	}

	Texture::~Texture()
	{
		unregisterObject( m_device, this );
	}

	Texture & Texture::operator=( Texture && rhs )
	{
		if ( &rhs != this )
		{
			m_flags = rhs.m_flags;
			m_imageType = rhs.m_imageType;
			m_format = rhs.m_format;
			m_dimensions = rhs.m_dimensions;
			m_mipLevels = rhs.m_mipLevels;
			m_arrayLayers = rhs.m_arrayLayers;
			registerObject( m_device, "Texture", this );
		}

		return *this;
	}

	Texture::Texture( Device const & device
		, ImageCreateFlags flags
		, TextureType type
		, Format format
		, Extent3D dimensions
		, uint32_t mipLevels
		, uint32_t arrayLayers )
		: m_device{ device }
		, m_flags{ flags }
		, m_imageType{ type }
		, m_format{ format }
		, m_dimensions{ dimensions }
		, m_mipLevels{ mipLevels }
		, m_arrayLayers{ arrayLayers }
	{
		registerObject( m_device, "Texture", this );
	}

	void Texture::bindMemory( DeviceMemoryPtr memory )
	{
		assert( !m_storage && "A resource can only be bound once to a device memory object." );
		m_storage = std::move( memory );
		doBindMemory();
	}

	Texture::Mapped Texture::lock( uint32_t offset
		, uint32_t size
		, MemoryMapFlags flags )const
	{
		assert( m_storage && "The resource is not bound to a device memory object." );
		Mapped mapped{};
		ImageSubresource subResource{};
		subResource.aspectMask = getAspectMask( getFormat() );
		SubresourceLayout subResourceLayout;
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

	void Texture::invalidate( uint32_t offset
		, uint32_t size )const
	{
		assert( m_storage && "The resource is not bound to a device memory object." );
		return m_storage->invalidate( offset, size );
	}

	void Texture::flush( uint32_t offset
		, uint32_t size )const
	{
		assert( m_storage && "The resource is not bound to a device memory object." );
		return m_storage->flush( offset, size );
	}

	void Texture::unlock()const
	{
		assert( m_storage && "The resource is not bound to a device memory object." );
		return m_storage->unlock();
	}

	void Texture::generateMipmaps( CommandPool const & commandPool
		, Queue const & queue )const
	{
		auto commandBuffer = commandPool.createCommandBuffer();
		commandBuffer->begin( ashes::CommandBufferUsageFlag::eOneTimeSubmit );
		generateMipmaps( *commandBuffer );
		commandBuffer->end();
		auto fence = m_device.createFence();
		queue.submit( *commandBuffer, fence.get() );
		fence->wait( FenceTimeout );
	}

	void Texture::generateMipmaps( CommandBuffer & commandBuffer )const
	{
		auto const width = int32_t( getDimensions().width );
		auto const height = int32_t( getDimensions().height );

		for ( uint32_t layer = 0u; layer < m_arrayLayers; ++layer )
		{
			auto srcView = createView(
				{
					ashes::TextureViewType( getType() ),
					getFormat(),
					ashes::ComponentMapping{},
					ashes::ImageSubresourceRange
					{
						ashes::getAspectMask( getFormat() ),
						0,
						1u,
						layer,
						1u
					}
				} );
			commandBuffer.memoryBarrier( ashes::PipelineStageFlag::eTransfer
				, ashes::PipelineStageFlag::eTransfer
				, srcView->makeTransferSource( ashes::ImageLayout::eUndefined, 0u ) );

			// Copy down mips from n-1 to n
			for ( uint32_t level = 1; level < getMipmapLevels(); level++ )
			{
				ImageBlit imageBlit{};

				// Source
				imageBlit.srcSubresource.aspectMask = ashes::ImageAspectFlag::eColour;
				imageBlit.srcSubresource.baseArrayLayer = layer;
				imageBlit.srcSubresource.layerCount = 1;
				imageBlit.srcSubresource.mipLevel = level - 1;
				imageBlit.srcOffset.x = 0;
				imageBlit.srcOffset.y = 0;
				imageBlit.srcOffset.z = 0;
				imageBlit.srcExtent.width = int32_t( width >> ( level - 1 ) );
				imageBlit.srcExtent.height = int32_t( height >> ( level - 1 ) );
				imageBlit.srcExtent.depth = 1;

				// Destination
				imageBlit.dstSubresource.aspectMask = ashes::ImageAspectFlag::eColour;
				imageBlit.dstSubresource.baseArrayLayer = layer;
				imageBlit.dstSubresource.layerCount = 1;
				imageBlit.dstSubresource.mipLevel = level;
				imageBlit.dstOffset.x = 0;
				imageBlit.dstOffset.y = 0;
				imageBlit.dstOffset.z = 0;
				imageBlit.dstExtent.width = int32_t( width >> level );
				imageBlit.dstExtent.height = int32_t( height >> level );
				imageBlit.dstExtent.depth = 1;

				ashes::ImageSubresourceRange mipSubRange
				{
					ashes::ImageAspectFlag::eColour,
					level,
					1u,
					layer,
					1u
				};

				// Transiton current mip level to transfer dest
				ashes::ImageMemoryBarrier dstTransitionBarrier
				{
					0u,
					ashes::AccessFlag::eTransferWrite,
					ashes::ImageLayout::eUndefined,
					ashes::ImageLayout::eTransferDstOptimal,
					~( 0u ),
					~( 0u ),
					*this,
					mipSubRange
				};
				commandBuffer.memoryBarrier( ashes::PipelineStageFlag::eTransfer
					, ashes::PipelineStageFlag::eTransfer
					, dstTransitionBarrier );

				// Blit from previous level
				commandBuffer.blitImage( *this
					, ashes::ImageLayout::eTransferSrcOptimal
					, *this
					, ashes::ImageLayout::eTransferDstOptimal
					, { imageBlit }
					, ashes::Filter::eLinear );

				// Transiton current mip level to transfer source for read in next iteration
				ashes::ImageMemoryBarrier srcTransitionBarrier
				{
					ashes::AccessFlag::eTransferWrite,
					ashes::AccessFlag::eTransferRead,
					ashes::ImageLayout::eTransferDstOptimal,
					ashes::ImageLayout::eTransferSrcOptimal,
					~( 0u ),
					~( 0u ),
					*this,
					mipSubRange
				};
				commandBuffer.memoryBarrier( ashes::PipelineStageFlag::eTransfer
					, ashes::PipelineStageFlag::eTransfer
					, srcTransitionBarrier );
			}

			srcView = createView(
				{
					ashes::TextureViewType( getType() ),
					getFormat(),
					ashes::ComponentMapping{},
					ashes::ImageSubresourceRange
					{
						ashes::getAspectMask( getFormat() ),
						0,
						getMipmapLevels(),
						layer,
						1u
					}
				} );
			commandBuffer.memoryBarrier( ashes::PipelineStageFlag::eTransfer
				, ashes::PipelineStageFlag::eFragmentShader
				, srcView->makeShaderInputResource( ashes::ImageLayout::eUndefined, 0u ) );
		}
	}

	TextureViewPtr Texture::createView( TextureViewType type
		, Format format
		, uint32_t baseMipLevel
		, uint32_t levelCount
		, uint32_t baseArrayLayer
		, uint32_t layerCount
		, ComponentMapping const & mapping )const
	{
		return createView(
		{
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