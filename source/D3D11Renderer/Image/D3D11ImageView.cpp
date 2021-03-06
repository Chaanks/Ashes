#include "Image/D3D11ImageView.hpp"

#include "Core/D3D11Device.hpp"
#include "Image/D3D11Image.hpp"

namespace d3d11_renderer
{
	ImageView::ImageView( Device const & device
		, Image const & image
		, ashes::ImageViewCreateInfo const & createInfo )
		: ashes::ImageView{ device
			, image
			, createInfo }
		, m_device{ device }
		, m_image{ image }
	{
		switch ( createInfo.viewType )
		{
		case ashes::ImageViewType::e1D:
			if ( m_image.getLayerCount() > 1 )
			{
				doCreate1DArray();
			}
			else
			{
				doCreate1D();
			}
			break;

		case ashes::ImageViewType::e1DArray:
			doCreate1DArray();
			break;

		case ashes::ImageViewType::e2D:
			if ( m_image.getLayerCount() > 1 )
			{
				doCreate2DArray();
			}
			else
			{
				doCreate2D();
			}
			break;

		case ashes::ImageViewType::e2DArray:
			doCreate2DArray();
			break;

		case ashes::ImageViewType::e3D:
			doCreate3D();
			break;

		case ashes::ImageViewType::eCube:
			if ( m_image.getLayerCount() > 1 )
			{
				doCreateCubeArray();
			}
			else
			{
				doCreateCube();
			}
			break;

		case ashes::ImageViewType::eCubeArray:
			doCreateCubeArray();
			break;
		}
	}

	ImageView::~ImageView()
	{
		safeRelease( m_renderTargetView );
		safeRelease( m_depthStencilView );
		safeRelease( m_unorderedAccessView );
		safeRelease( m_shaderView );
	}

	void ImageView::doCreate1D()
	{
		auto device = m_device.getDevice();

		if ( m_image.isRenderTarget() )
		{
			D3D11_RENDER_TARGET_VIEW_DESC desc{};
			desc.Format = getRTVFormat( getFormat() );
			desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1D;
			desc.Texture1D.MipSlice = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateRenderTargetView( m_image.getTexture1D()
				, &desc
				, &m_renderTargetView );
			checkError( m_device, hr, "CreateRenderTargetView1D" );
			dxDebugName( m_renderTargetView, RenderTargetView1D );
		}

		if ( m_image.isSamplable() )
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC desc{};
			desc.Format = getSRVFormat( getFormat() );
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
			desc.Texture1D.MipLevels = getSubResourceRange().levelCount;
			desc.Texture1D.MostDetailedMip = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateShaderResourceView( m_image.getTexture1D()
				, &desc
				, &m_shaderView );
			checkError( m_device, hr, "CreateShaderResourceView1D" );
			dxDebugName( m_shaderView, ShaderResourceView1D );
		}

		if ( m_image.isStorage()
			&& m_device.getFeatureLevel() >= D3D_FEATURE_LEVEL_11_0 )
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC desc{};
			desc.Format = getUAVFormat( getFormat() );
			desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE1D;
			desc.Texture1D.MipSlice = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateUnorderedAccessView( m_image.getTexture1D()
				, &desc
				, &m_unorderedAccessView );
			checkError( m_device, hr, "CreateUnorderedAccessView1D" );
			dxDebugName( m_unorderedAccessView, UnorderedAccessView1D );
		}
	}

	void ImageView::doCreate1DArray()
	{
		auto device = m_device.getDevice();

		if ( m_image.isRenderTarget() )
		{
			D3D11_RENDER_TARGET_VIEW_DESC desc{};
			desc.Format = getRTVFormat( getFormat() );
			desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1DARRAY;
			desc.Texture1DArray.ArraySize = getSubResourceRange().layerCount;
			desc.Texture1DArray.FirstArraySlice = getSubResourceRange().baseArrayLayer;
			desc.Texture1DArray.MipSlice = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateRenderTargetView( m_image.getTexture1D()
				, &desc
				, &m_renderTargetView );
			checkError( m_device, hr, "CreateRenderTargetView1DArray" );
			dxDebugName( m_renderTargetView, RenderTargetView1DArray );
		}

		if ( m_image.isSamplable() )
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC desc{};
			desc.Format = getSRVFormat( getFormat() );
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1DARRAY;
			desc.Texture1DArray.ArraySize = getSubResourceRange().layerCount;
			desc.Texture1DArray.FirstArraySlice = getSubResourceRange().baseArrayLayer;
			desc.Texture1DArray.MipLevels = getSubResourceRange().levelCount;
			desc.Texture1DArray.MostDetailedMip = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateShaderResourceView( m_image.getTexture1D()
				, &desc
				, &m_shaderView );
			checkError( m_device, hr, "CreateShaderResourceView1DArray" );
			dxDebugName( m_shaderView, ShaderResourceView1DArray );
		}

		if ( m_image.isStorage()
			&& m_device.getFeatureLevel() >= D3D_FEATURE_LEVEL_11_0 )
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC desc{};
			desc.Format = getUAVFormat( getFormat() );
			desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE1DARRAY;
			desc.Texture1DArray.ArraySize = getSubResourceRange().layerCount;
			desc.Texture1DArray.FirstArraySlice = getSubResourceRange().baseArrayLayer;
			desc.Texture1DArray.MipSlice = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateUnorderedAccessView( m_image.getTexture1D()
				, &desc
				, &m_unorderedAccessView );
			checkError( m_device, hr, "CreateUnorderedAccessView1DArray" );
			dxDebugName( m_unorderedAccessView, UnorderedAccessView1DArray );
		}
	}

	void ImageView::doCreate2D()
	{
		auto device = m_device.getDevice();

		if ( m_image.isRenderTarget() )
		{
			if ( isDepthOrStencilFormat( m_image.getFormat() ) )
			{
				D3D11_DEPTH_STENCIL_VIEW_DESC desc{};
				desc.Format = getRTVFormat( getFormat() );
				desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				desc.Texture2D.MipSlice = getSubResourceRange().baseMipLevel;
				auto hr = device->CreateDepthStencilView( m_image.getTexture2D()
					, &desc
					, &m_depthStencilView );
				checkError( m_device, hr, "CreateDepthStencilView2D" );
				dxDebugName( m_depthStencilView, DepthStencilView2D );
			}
			else
			{
				D3D11_RENDER_TARGET_VIEW_DESC desc{};
				desc.Format = getRTVFormat( getFormat() );
				desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
				desc.Texture2D.MipSlice = getSubResourceRange().baseMipLevel;
				auto hr = device->CreateRenderTargetView( m_image.getTexture2D()
					, &desc
					, &m_renderTargetView );
				checkError( m_device, hr, "CreateRenderTargetView2D" );
				dxDebugName( m_renderTargetView, RenderTargetView2D );
			}
		}

		if ( m_image.isSamplable() )
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC desc{};
			desc.Format = getSRVFormat( getFormat() );
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MipLevels = getSubResourceRange().levelCount;
			desc.Texture2D.MostDetailedMip = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateShaderResourceView( m_image.getTexture2D()
				, &desc
				, &m_shaderView );
			checkError( m_device, hr, "CreateShaderResourceView2D" );
			dxDebugName( m_shaderView, ShaderResourceView2D );
		}

		if ( m_image.isStorage()
			&& m_device.getFeatureLevel() >= D3D_FEATURE_LEVEL_11_0 )
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC desc{};
			desc.Format = getUAVFormat( getFormat() );
			desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MipSlice = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateUnorderedAccessView( m_image.getTexture2D()
				, &desc
				, &m_unorderedAccessView );
			checkError( m_device, hr, "CreateUnorderedAccessView2D" );
			dxDebugName( m_unorderedAccessView, UnorderedAccessView2D );
		}
	}

	void ImageView::doCreate2DArray()
	{
		auto device = m_device.getDevice();

		if ( m_image.isRenderTarget() )
		{
			if ( isDepthOrStencilFormat( m_image.getFormat() ) )
			{
				D3D11_DEPTH_STENCIL_VIEW_DESC desc{};
				desc.Format = getRTVFormat( getFormat() );
				desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
				desc.Texture2DArray.ArraySize = getSubResourceRange().layerCount;
				desc.Texture2DArray.FirstArraySlice = getSubResourceRange().baseArrayLayer;
				desc.Texture2DArray.MipSlice = getSubResourceRange().baseMipLevel;
				auto hr = device->CreateDepthStencilView( m_image.getTexture2D()
					, &desc
					, &m_depthStencilView );
				checkError( m_device, hr, "CreateDepthStencilView2D" );
				dxDebugName( m_depthStencilView, DepthStencilView2D );
			}
			else
			{
				D3D11_RENDER_TARGET_VIEW_DESC desc{};
				desc.Format = getRTVFormat( getFormat() );
				desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
				desc.Texture2DArray.ArraySize = getSubResourceRange().layerCount;
				desc.Texture2DArray.FirstArraySlice = getSubResourceRange().baseArrayLayer;
				desc.Texture2DArray.MipSlice = getSubResourceRange().baseMipLevel;
				auto hr = device->CreateRenderTargetView( m_image.getTexture2D()
					, &desc
					, &m_renderTargetView );
				checkError( m_device, hr, "CreateRenderTargetView2DArray" );
				dxDebugName( m_renderTargetView, RenderTargetView2DArray );
			}
		}

		if ( m_image.isSamplable() )
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC desc{};
			desc.Format = getSRVFormat( getFormat() );
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
			desc.Texture2DArray.ArraySize = getSubResourceRange().layerCount;
			desc.Texture2DArray.FirstArraySlice = getSubResourceRange().baseArrayLayer;
			desc.Texture2DArray.MipLevels = getSubResourceRange().levelCount;
			desc.Texture2DArray.MostDetailedMip = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateShaderResourceView( m_image.getTexture2D()
				, &desc
				, &m_shaderView );
			checkError( m_device, hr, "CreateShaderResourceView2DArray" );
			dxDebugName( m_shaderView, ShaderResourceView2DArray );
		}

		if ( m_image.isStorage()
			&& m_device.getFeatureLevel() >= D3D_FEATURE_LEVEL_11_0 )
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC desc{};
			desc.Format = getUAVFormat( getFormat() );
			desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
			desc.Texture2DArray.ArraySize = getSubResourceRange().layerCount;
			desc.Texture2DArray.FirstArraySlice = getSubResourceRange().baseArrayLayer;
			desc.Texture2DArray.MipSlice = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateUnorderedAccessView( m_image.getTexture2D()
				, &desc
				, &m_unorderedAccessView );
			checkError( m_device, hr, "CreateUnorderedAccessView2DArray" );
			dxDebugName( m_unorderedAccessView, UnorderedAccessView2DArray );
		}
	}

	void ImageView::doCreate3D()
	{
		auto device = m_device.getDevice();

		if ( m_image.isRenderTarget() )
		{
			D3D11_RENDER_TARGET_VIEW_DESC desc{};
			desc.Format = getRTVFormat( getFormat() );
			desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE3D;
			desc.Texture3D.MipSlice = getSubResourceRange().baseMipLevel;
			desc.Texture3D.FirstWSlice = getSubResourceRange().baseArrayLayer;
			desc.Texture3D.WSize = getSubResourceRange().layerCount;
			auto hr = device->CreateRenderTargetView( m_image.getTexture3D()
				, &desc
				, &m_renderTargetView );
			checkError( m_device, hr, "CreateRenderTargetView3D" );
			dxDebugName( m_unorderedAccessView, RenderTargetView3D );
		}

		if ( m_image.isSamplable() )
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC desc{};
			desc.Format = getSRVFormat( getFormat() );
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
			desc.Texture3D.MipLevels = getSubResourceRange().levelCount;
			desc.Texture3D.MostDetailedMip = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateShaderResourceView( m_image.getTexture3D()
				, &desc
				, &m_shaderView );
			checkError( m_device, hr, "CreateShaderResourceView3D" );
			dxDebugName( m_unorderedAccessView, UnorderedAccessView3D );
		}

		if ( m_image.isStorage()
			&& m_device.getFeatureLevel() >= D3D_FEATURE_LEVEL_11_0 )
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC desc{};
			desc.Format = getUAVFormat( getFormat() );
			desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE3D;
			desc.Texture3D.MipSlice = getSubResourceRange().baseMipLevel;
			desc.Texture3D.FirstWSlice = getSubResourceRange().baseArrayLayer;
			desc.Texture3D.WSize = getSubResourceRange().layerCount;
			auto hr = device->CreateUnorderedAccessView( m_image.getTexture3D()
				, &desc
				, &m_unorderedAccessView );
			checkError( m_device, hr, "CreateUnorderedAccessView3D" );
			dxDebugName( m_unorderedAccessView, UnorderedAccessView3D );
		}
	}

	void ImageView::doCreateCube()
	{
		auto device = m_device.getDevice();

		if ( m_image.isRenderTarget() )
		{
			D3D11_RENDER_TARGET_VIEW_DESC desc{};
			desc.Format = getRTVFormat( getFormat() );
			desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
			desc.Texture2DArray.ArraySize = getSubResourceRange().layerCount;
			desc.Texture2DArray.FirstArraySlice = getSubResourceRange().baseArrayLayer;
			desc.Texture2DArray.MipSlice = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateRenderTargetView( m_image.getTexture2D()
				, &desc
				, &m_renderTargetView );
			checkError( m_device, hr, "CreateRenderTargetViewCube" );
			dxDebugName( m_unorderedAccessView, RenderTargetViewCube );
		}

		if ( m_image.isSamplable() )
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC desc{};
			desc.Format = getSRVFormat( getFormat() );
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
			desc.TextureCube.MipLevels = getSubResourceRange().levelCount;
			desc.TextureCube.MostDetailedMip = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateShaderResourceView( m_image.getTexture2D()
				, &desc
				, &m_shaderView );
			checkError( m_device, hr, "CreateShaderResourceViewCube" );
			dxDebugName( m_unorderedAccessView, ShaderResourceViewCube );
		}

		if ( m_image.isStorage()
			&& m_device.getFeatureLevel() >= D3D_FEATURE_LEVEL_11_0 )
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC desc{};
			desc.Format = getUAVFormat( getFormat() );
			desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
			desc.Texture2DArray.ArraySize = getSubResourceRange().layerCount;
			desc.Texture2DArray.FirstArraySlice = getSubResourceRange().baseArrayLayer;
			desc.Texture2DArray.MipSlice = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateUnorderedAccessView( m_image.getTexture2D()
				, &desc
				, &m_unorderedAccessView );
			checkError( m_device, hr, "CreateUnorderedAccessViewCube" );
			dxDebugName( m_unorderedAccessView, UnorderedAccessViewCube );
		}
	}

	void ImageView::doCreateCubeArray()
	{
		auto device = m_device.getDevice();

		if ( m_image.isRenderTarget() )
		{
			D3D11_RENDER_TARGET_VIEW_DESC desc{};
			desc.Format = getRTVFormat( getFormat() );
			desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
			desc.Texture2DArray.ArraySize = getSubResourceRange().layerCount;
			desc.Texture2DArray.FirstArraySlice = getSubResourceRange().baseArrayLayer;
			desc.Texture2DArray.MipSlice = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateRenderTargetView( m_image.getTexture2D()
				, &desc
				, &m_renderTargetView );
			checkError( m_device, hr, "CreateRenderTargetViewCubeArray" );
			dxDebugName( m_unorderedAccessView, RenderTargetViewCubeArray );

			if ( checkError( m_device, hr, "CreateRenderTargetViewCubeArray" ) )
			{
				dxDebugName( m_renderTargetView, RenderTargetViewCubeArray );
			}
		}

		if ( m_image.isSamplable() )
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC desc{};
			desc.Format = getSRVFormat( getFormat() );
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
			desc.TextureCubeArray.MipLevels = getSubResourceRange().levelCount;
			desc.TextureCubeArray.MostDetailedMip = getSubResourceRange().baseMipLevel;
			desc.TextureCubeArray.First2DArrayFace = getSubResourceRange().baseArrayLayer;
			desc.TextureCubeArray.NumCubes = getSubResourceRange().layerCount / 6u;
			auto hr = device->CreateShaderResourceView( m_image.getTexture2D()
				, &desc
				, &m_shaderView );
			checkError( m_device, hr, "CreateShaderResourceViewCubeArray" );
			dxDebugName( m_unorderedAccessView, ShaderResourceViewCubeArray );
		}

		if ( m_image.isStorage()
			&& m_device.getFeatureLevel() >= D3D_FEATURE_LEVEL_11_0 )
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC desc{};
			desc.Format = getUAVFormat( getFormat() );
			desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
			desc.Texture2DArray.ArraySize = getSubResourceRange().layerCount;
			desc.Texture2DArray.FirstArraySlice = getSubResourceRange().baseArrayLayer;
			desc.Texture2DArray.MipSlice = getSubResourceRange().baseMipLevel;
			auto hr = device->CreateUnorderedAccessView( m_image.getTexture2D()
				, &desc
				, &m_unorderedAccessView );
			checkError( m_device, hr, "CreateUnorderedAccessViewCubeArray" );
			dxDebugName( m_unorderedAccessView, UnorderedAccessViewCubeArray );
		}
	}
}
