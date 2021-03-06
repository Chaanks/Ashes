/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#ifndef ___Ashes_StagingBuffer_HPP___
#define ___Ashes_StagingBuffer_HPP___
#pragma once

#include "Ashes/Buffer/Buffer.hpp"
#include "Ashes/Buffer/VertexBuffer.hpp"
#include "Ashes/Buffer/UniformBuffer.hpp"

namespace ashes
{
	/**
	*\~english
	*\brief
	*	Class grouping the functions to transfer data from/to VRAM.
	*\~french
	*\brief
	*	Classe regroupant les fonctions nécessaires au transfert de données depuis/vers la VRAM.
	*/
	class StagingBuffer
	{
	public:
		/**
		*\~english
		*\brief
		*	Constructor.
		*\param[in] device
		*	The logical device.
		*\param[in] target
		*	The buffer targets.
		*\param[in] size
		*	The buffer size.
		*\~french
		*\brief
		*	Constructeur.
		*\param[in] device
		*	Le LogicalDevice parent.
		*\param[in] target
		*	Les cibles du tampon.
		*\param[in] size
		*	La taille du tampon.
		*/
		StagingBuffer( Device const & device
			, BufferTargets target
			, uint32_t size = 10000000u );
		/**
		*\name
		*	Upload.
		**/
		/**@{*/
		/**
		*\name
		*	Buffer.
		**/
		/**@{*/
		template< typename T >
		inline void uploadBufferData( Queue const & queue
			, CommandPool const & commandPool
			, std::vector< T > const & data
			, Buffer< T > const & buffer )const;
		template< typename T >
		inline void uploadBufferData( Queue const & queue
			, CommandPool const & commandPool
			, ByteArray const & data
			, Buffer< T > const & buffer )const;
		template< typename T >
		inline void uploadBufferData( Queue const & queue
			, CommandPool const & commandPool
			, uint8_t const * const data
			, uint32_t size
			, Buffer< T > const & buffer )const;
		template< typename T >
		inline void uploadBufferData( Queue const & queue
			, CommandPool const & commandPool
			, std::vector< T > const & data
			, uint32_t offset
			, Buffer< T > const & buffer )const;
		template< typename T >
		inline void uploadBufferData( Queue const & queue
			, CommandPool const & commandPool
			, ByteArray const & data
			, uint32_t offset
			, Buffer< T > const & buffer )const;
		template< typename T >
		void uploadBufferData( Queue const & queue
			, CommandPool const & commandPool
			, uint8_t const * const data
			, uint32_t size
			, uint32_t offset
			, Buffer< T > const & buffer )const;
		template< typename T >
		inline void uploadBufferData( CommandBuffer const & commandBuffer
			, std::vector< T > const & data
			, Buffer< T > const & buffer )const;
		template< typename T >
		inline void uploadBufferData( CommandBuffer const & commandBuffer
			, ByteArray const & data
			, Buffer< T > const & buffer )const;
		template< typename T >
		inline void uploadBufferData( CommandBuffer const & commandBuffer
			, uint8_t const * const data
			, uint32_t size
			, Buffer< T > const & buffer )const;
		template< typename T >
		inline void uploadBufferData( CommandBuffer const & commandBuffer
			, std::vector< T > const & data
			, uint32_t offset
			, Buffer< T > const & buffer )const;
		template< typename T >
		inline void uploadBufferData( CommandBuffer const & commandBuffer
			, ByteArray const & data
			, uint32_t offset
			, Buffer< T > const & buffer )const;
		template< typename T >
		void uploadBufferData( CommandBuffer const & commandBuffer
			, uint8_t const * const data
			, uint32_t size
			, uint32_t offset
			, Buffer< T > const & buffer )const;
		/**@}*/
		/**
		*\name
		*	Vertex buffer.
		**/
		/**@{*/
		template< typename T >
		inline void uploadVertexData( Queue const & queue
			, CommandPool const & commandPool
			, std::vector< T > const & data
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void uploadVertexData( Queue const & queue
			, CommandPool const & commandPool
			, ByteArray const & data
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void uploadVertexData( Queue const & queue
			, CommandPool const & commandPool
			, uint8_t const * const data
			, uint32_t size
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void uploadVertexData( Queue const & queue
			, CommandPool const & commandPool
			, std::vector< T > const & data
			, uint32_t offset
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void uploadVertexData( Queue const & queue
			, CommandPool const & commandPool
			, ByteArray const & data
			, uint32_t offset
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void uploadVertexData( Queue const & queue
			, CommandPool const & commandPool
			, uint8_t const * const data
			, uint32_t size
			, uint32_t offset
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void uploadVertexData( CommandBuffer const & commandBuffer
			, std::vector< T > const & data
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void uploadVertexData( CommandBuffer const & commandBuffer
			, ByteArray const & data
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void uploadVertexData( CommandBuffer const & commandBuffer
			, uint8_t const * const data
			, uint32_t size
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void uploadVertexData( CommandBuffer const & commandBuffer
			, std::vector< T > const & data
			, uint32_t offset
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void uploadVertexData( CommandBuffer const & commandBuffer
			, ByteArray const & data
			, uint32_t offset
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void uploadVertexData( CommandBuffer const & commandBuffer
			, uint8_t const * const data
			, uint32_t size
			, uint32_t offset
			, VertexBuffer< T > const & buffer )const;
		/**@}*/
		/**
		*\name
		*	Uniform buffer.
		**/
		/**@{*/
		template< typename T >
		inline void uploadUniformData( Queue const & queue
			, CommandPool const & commandPool
			, std::vector< T > const & data
			, UniformBuffer< T > const & buffer
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eVertexShader )const;
		template< typename T >
		inline void uploadUniformData( Queue const & queue
			, CommandPool const & commandPool
			, T const * const data
			, uint32_t count
			, UniformBuffer< T > const & buffer
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eVertexShader )const;
		template< typename T >
		inline void uploadUniformData( Queue const & queue
			, CommandPool const & commandPool
			, std::vector< T > const & data
			, uint32_t offset
			, UniformBuffer< T > const & buffer
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eVertexShader )const;
		template< typename T >
		inline void uploadUniformData( Queue const & queue
			, CommandPool const & commandPool
			, T const * const data
			, uint32_t count
			, uint32_t offset
			, UniformBuffer< T > const & buffer
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eVertexShader )const;
		template< typename T >
		inline void uploadUniformData( CommandBuffer const & commandBuffer
			, std::vector< T > const & data
			, UniformBuffer< T > const & buffer
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eVertexShader )const;
		template< typename T >
		inline void uploadUniformData( CommandBuffer const & commandBuffer
			, T const * const data
			, uint32_t count
			, UniformBuffer< T > const & buffer
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eVertexShader )const;
		template< typename T >
		inline void uploadUniformData( CommandBuffer const & commandBuffer
			, std::vector< T > const & data
			, uint32_t offset
			, UniformBuffer< T > const & buffer
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eVertexShader )const;
		template< typename T >
		inline void uploadUniformData( CommandBuffer const & commandBuffer
			, T const * const data
			, uint32_t count
			, uint32_t offset
			, UniformBuffer< T > const & buffer
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eVertexShader )const;
		/**@}*/
		/**
		*\name
		*	Texture.
		**/
		/**@{*/
		void uploadTextureData( Queue const & queue
			, CommandPool const & commandPool
			, ImageSubresourceLayers const & subresourceLayers
			, Format format
			, Offset3D const & offset
			, Extent2D const & extent
			, uint8_t const * const data
			, ImageView const & texture
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eFragmentShader )const;
		inline void uploadTextureData( Queue const & queue
			, CommandPool const & commandPool
			, ImageSubresourceLayers const & subresourceLayers
			, Format format
			, Offset3D const & offset
			, Extent2D const & extent
			, ByteArray const & data
			, ImageView const & texture
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eFragmentShader )const;
		void uploadTextureData( Queue const & queue
			, CommandPool const & commandPool
			, Format format
			, uint8_t const * const data
			, ImageView const & texture
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eFragmentShader )const;
		inline void uploadTextureData( Queue const & queue
			, CommandPool const & commandPool
			, Format format
			, ByteArray const & data
			, ImageView const & texture
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eFragmentShader )const;
		void uploadTextureData( CommandBuffer const & commandBuffer
			, ImageSubresourceLayers const & subresourceLayers
			, Format format
			, Offset3D const & offset
			, Extent2D const & extent
			, uint8_t const * const data
			, ImageView const & texture
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eFragmentShader )const;
		inline void uploadTextureData( CommandBuffer const & commandBuffer
			, ImageSubresourceLayers const & subresourceLayers
			, Format format
			, Offset3D const & offset
			, Extent2D const & extent
			, ByteArray const & data
			, ImageView const & texture
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eFragmentShader )const;
		void uploadTextureData( CommandBuffer const & commandBuffer
			, Format format
			, uint8_t const * const data
			, ImageView const & texture
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eFragmentShader )const;
		inline void uploadTextureData( CommandBuffer const & commandBuffer
			, Format format
			, ByteArray const & data
			, ImageView const & texture
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eFragmentShader )const;
		/**@}*/
		/**@}*/
		/**
		*\name
		*	Download.
		**/
		/**@{*/
		/**
		*\name
		*	Buffer.
		**/
		/**@{*/
		template< typename T >
		inline void downloadBufferData( Queue const & queue
			, CommandPool const & commandPool
			, std::vector< T > & data
			, Buffer< T > const & buffer )const;
		template< typename T >
		inline void downloadBufferData( Queue const & queue
			, CommandPool const & commandPool
			, ByteArray & data
			, Buffer< T > const & buffer )const;
		template< typename T >
		inline void downloadBufferData( Queue const & queue
			, CommandPool const & commandPool
			, uint8_t * data
			, uint32_t size
			, Buffer< T > const & buffer )const;
		template< typename T >
		inline void downloadBufferData( Queue const & queue
			, CommandPool const & commandPool
			, std::vector< T > & data
			, uint32_t offset
			, Buffer< T > const & buffer )const;
		template< typename T >
		inline void downloadBufferData( Queue const & queue
			, CommandPool const & commandPool
			, ByteArray & data
			, uint32_t offset
			, Buffer< T > const & buffer )const;
		template< typename T >
		void downloadBufferData( Queue const & queue
			, CommandPool const & commandPool
			, uint8_t * data
			, uint32_t size
			, uint32_t offset
			, Buffer< T > const & buffer )const;
		/**@}*/
		/**
		*\name
		*	Vertex buffer.
		**/
		/**@{*/
		template< typename T >
		inline void downloadVertexData( Queue const & queue
			, CommandPool const & commandPool
			, std::vector< T > & data
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void downloadVertexData( Queue const & queue
			, CommandPool const & commandPool
			, ByteArray & data
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void downloadVertexData( Queue const & queue
			, CommandPool const & commandPool
			, uint8_t * data
			, uint32_t size
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void downloadVertexData( Queue const & queue
			, CommandPool const & commandPool
			, std::vector< T > & data
			, uint32_t offset
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void downloadVertexData( Queue const & queue
			, CommandPool const & commandPool
			, ByteArray & data
			, uint32_t offset
			, VertexBuffer< T > const & buffer )const;
		template< typename T >
		inline void downloadVertexData( Queue const & queue
			, CommandPool const & commandPool
			, uint8_t * data
			, uint32_t size
			, uint32_t offset
			, VertexBuffer< T > const & buffer )const;
		/**@}*/
		/**
		*\name
		*	Uniform buffer.
		**/
		/**@{*/
		template< typename T >
		inline void downloadUniformData( Queue const & queue
			, CommandPool const & commandPool
			, std::vector< T > & data
			, UniformBuffer< T > const & buffer
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eVertexShader )const;
		template< typename T >
		inline void downloadUniformData( Queue const & queue
			, CommandPool const & commandPool
			, T * data
			, uint32_t count
			, UniformBuffer< T > const & buffer
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eVertexShader )const;
		template< typename T >
		inline void downloadUniformData( Queue const & queue
			, CommandPool const & commandPool
			, std::vector< T > & data
			, uint32_t offset
			, UniformBuffer< T > const & buffer
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eVertexShader )const;
		template< typename T >
		inline void downloadUniformData( Queue const & queue
			, CommandPool const & commandPool
			, T * data
			, uint32_t count
			, uint32_t offset
			, UniformBuffer< T > const & buffer
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eVertexShader )const;
		/**@}*/
		/**
		*\name
		*	Texture.
		**/
		/**@{*/
		void downloadTextureData( Queue const & queue
			, CommandPool const & commandPool
			, ImageSubresourceLayers const & subresourceLayers
			, Format format
			, Offset3D const & offset
			, Extent2D const & extent
			, uint8_t * data
			, ImageView const & texture
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eFragmentShader )const;
		inline void downloadTextureData( Queue const & queue
			, CommandPool const & commandPool
			, ImageSubresourceLayers const & subresourceLayers
			, Format format
			, Offset3D const & offset
			, Extent2D const & extent
			, ByteArray & data
			, ImageView const & texture
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eFragmentShader )const;
		void downloadTextureData( Queue const & queue
			, CommandPool const & commandPool
			, Format format
			, uint8_t * data
			, ImageView const & texture
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eFragmentShader )const;
		inline void downloadTextureData( Queue const & queue
			, CommandPool const & commandPool
			, Format format
			, ByteArray & data
			, ImageView const & texture
			, PipelineStageFlags dstStageFlags = PipelineStageFlag::eFragmentShader )const;
		/**@}*/
		/**
		*\return
		*	Le tampon GPU.
		*/
		inline BufferBase const & getBuffer()const
		{
			return *m_buffer;
		}

	private:
		/**
		*\name
		*	Upload.
		**/
		/**@{*/
		template< typename T >
		inline void doCopyUniformDataToStagingBuffer( T const * const data
			, uint32_t count
			, uint32_t elemAlignedSize )const;
		void doCopyToStagingBuffer( uint8_t const * const data
			, uint32_t size )const;
		void doCopyFromStagingBuffer( CommandBuffer const & commandBuffer
			, uint32_t size
			, uint32_t offset
			, BufferBase const & buffer )const;
		void doCopyFromStagingBuffer( CommandBuffer const & commandBuffer
			, uint32_t size
			, uint32_t offset
			, VertexBufferBase const & buffer )const;
		void doCopyFromStagingBuffer( CommandBuffer const & commandBuffer
			, uint32_t size
			, uint32_t offset
			, UniformBufferBase const & buffer
			, PipelineStageFlags dstStageFlags )const;
		void doCopyFromStagingBuffer( CommandBuffer const & commandBuffer
			, Extent2D const & size
			, Offset3D const & offset
			, ImageView const & view
			, PipelineStageFlags dstStageFlags
			, ImageSubresourceLayers const & subresourceLayers )const;
		/**@{*/
		/**
		*\name
		*	Download.
		**/
		/**@{*/
		template< typename T >
		inline void doCopyUniformDataFromStagingBuffer( T * data
			, uint32_t count
			, uint32_t elemAlignedSize )const;
		void doCopyFromStagingBuffer( uint8_t * data
			, uint32_t size )const;
		void doCopyToStagingBuffer( CommandBuffer const & commandBuffer
			, uint32_t size
			, uint32_t offset
			, BufferBase const & buffer )const;
		void doCopyToStagingBuffer( CommandBuffer const & commandBuffer
			, uint32_t size
			, uint32_t offset
			, VertexBufferBase const & buffer )const;
		void doCopyToStagingBuffer( CommandBuffer const & commandBuffer
			, uint32_t size
			, uint32_t offset
			, UniformBufferBase const & buffer
			, PipelineStageFlags dstStageFlags )const;
		void doCopyToStagingBuffer( CommandBuffer const & commandBuffer
			, Extent2D const & size
			, Offset3D const & offset
			, ImageView const & view
			, PipelineStageFlags dstStageFlags
			, ImageSubresourceLayers const & subresourceLayers )const;
		/**@}*/

	protected:
		Device const & m_device;
		AccessFlags m_currentAccessMask{ AccessFlag::eMemoryWrite };
		BufferBasePtr m_buffer;
		DeviceMemoryPtr m_storage;
	};
}

#include "Ashes/Buffer/StagingBuffer.inl"

#endif
