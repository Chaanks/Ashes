/**
*\file
*	Instance.h
*\author
*	Sylvain Doremus
*/
#pragma once

#include "D3D11Renderer/Core/D3D11Layer.hpp"

#include <Ashes/Core/Instance.hpp>
#include <Utils/DynamicLibrary.hpp>

namespace d3d11_renderer
{
	class Instance
		: public ashes::Instance
	{
	public:
		/**
		*\brief
		*	Constructeur, initialise l'instance de Vulkan.
		*/
		Instance( ashes::InstanceCreateInfo createInfo );
		/**
		*\brief
		*	Destructeur.
		*/
		~Instance();
		/**
		*\copydoc	ashes::Instance::enumerateLayerProperties
		*/
		ashes::PhysicalDevicePtrArray enumeratePhysicalDevices()const override;
		/**
		*\copydoc	ashes::Instance::createDevice
		*/
		ashes::DevicePtr createDevice( ashes::PhysicalDevice const & physicalDevice
			, ashes::DeviceCreateInfo createInfos )const override;
		/**
		*\copydoc	ashes::Instance::createSurface
		*/
		ashes::SurfacePtr createSurface( ashes::PhysicalDevice const & gpu
			, ashes::WindowHandle handle )const override;
		/**
		*\copydoc	ashes::Instance::createDebugReportCallback
		*/
		ashes::DebugReportCallbackPtr createDebugReportCallback( ashes::DebugReportCallbackCreateInfo createInfo )const override;
		/**
		*\copydoc	ashes::Instance::frustum
		*/
		std::array< float, 16 > frustum( float left
			, float right
			, float bottom
			, float top
			, float zNear
			, float zFar )const override;
		/**
		*\copydoc	ashes::Instance::perspective
		*/
		std::array< float, 16 > perspective( float radiansFovY
			, float aspect
			, float zNear
			, float zFar )const override;
		/**
		*\copydoc	ashes::Instance::ortho
		*/
		std::array< float, 16 > ortho( float left
			, float right
			, float bottom
			, float top
			, float zNear
			, float zFar )const override;
		/**
		*\~english
		*name
		*	Layers delegation.
		*\~french
		*name
		*	D�l�gation aux layers.
		*/
		/**@{*/
		void registerLayer( Layer * layer )const;
		void unregisterLayer( Layer * layer )const;
		bool onCopyToImageCommand( ashes::CommandBuffer const & cmd
			, ashes::BufferImageCopyArray const & copyInfo
			, ashes::BufferBase const & src
			, ashes::Image const & dst )const;
		bool onCheckHResultCommand( HRESULT hresult
			, std::string message )const;
		/**@}*/

		inline IDXGIFactory * getDXGIFactory()const
		{
			return m_factory;
		}

		static inline ashes::PhysicalDeviceMemoryProperties const & getMemoryProperties()
		{
			return m_memoryProperties;
		}

	private:
		void doCreateDXGIFactory();
		void doLoadAdapters();

	private:
		IDXGIFactory * m_factory;
		std::vector< AdapterInfo > m_adapters;
		D3D_FEATURE_LEVEL m_maxFeatureLevel;
		mutable std::vector< Layer * > m_layers;
		static ashes::PhysicalDeviceMemoryProperties const m_memoryProperties;
	};
}
