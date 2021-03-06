#include "D3D11RendererPrerequisites.hpp"

namespace d3d11_renderer
{
	DXGI_FORMAT getDxgiFormat( ashes::Format const & format )noexcept
	{
		switch ( format )
		{
		case ashes::Format::eUndefined: return DXGI_FORMAT_UNKNOWN;
		case ashes::Format::eR4G4B4A4_UNORM_PACK16: return DXGI_FORMAT_B4G4R4A4_UNORM;
		case ashes::Format::eB4G4R4A4_UNORM_PACK16: return DXGI_FORMAT_B4G4R4A4_UNORM;
		case ashes::Format::eR5G6B5_UNORM_PACK16: return DXGI_FORMAT_B5G6R5_UNORM;
		case ashes::Format::eB5G6R5_UNORM_PACK16: return DXGI_FORMAT_B5G6R5_UNORM;
		case ashes::Format::eR5G5B5A1_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case ashes::Format::eB5G5R5A1_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case ashes::Format::eA1R5G5B5_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case ashes::Format::eR8_UNORM: return DXGI_FORMAT_R8_UNORM;
		case ashes::Format::eR8_SNORM: return DXGI_FORMAT_R8_SNORM;
		case ashes::Format::eR8_USCALED: return DXGI_FORMAT_R8_UNORM;
		case ashes::Format::eR8_SSCALED: return DXGI_FORMAT_R8_SNORM;
		case ashes::Format::eR8_UINT: return DXGI_FORMAT_R8_UINT;
		case ashes::Format::eR8_SINT: return DXGI_FORMAT_R8_SINT;
		case ashes::Format::eR8_SRGB: return DXGI_FORMAT_R8_SINT;
		case ashes::Format::eR8G8_UNORM: return DXGI_FORMAT_R8G8_UNORM;
		case ashes::Format::eR8G8_SNORM: return DXGI_FORMAT_R8G8_SNORM;
		case ashes::Format::eR8G8_USCALED: return DXGI_FORMAT_R8G8_UNORM;
		case ashes::Format::eR8G8_SSCALED: return DXGI_FORMAT_R8G8_SNORM;
		case ashes::Format::eR8G8_UINT: return DXGI_FORMAT_R8G8_UINT;
		case ashes::Format::eR8G8_SINT: return DXGI_FORMAT_R8G8_SINT;
		case ashes::Format::eR8G8_SRGB: return DXGI_FORMAT_R8G8_SINT;
		case ashes::Format::eR8G8B8_UNORM: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eR8G8B8_SNORM: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eR8G8B8_USCALED: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eR8G8B8_SSCALED: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eR8G8B8_UINT: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eR8G8B8_SINT: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eR8G8B8_SRGB: return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		case ashes::Format::eB8G8R8_UNORM: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eB8G8R8_SNORM: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eB8G8R8_USCALED: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eB8G8R8_SSCALED: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eB8G8R8_UINT: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eB8G8R8_SINT: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eB8G8R8_SRGB: return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		case ashes::Format::eR8G8B8A8_UNORM: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eR8G8B8A8_SNORM: return DXGI_FORMAT_R8G8B8A8_SNORM;
		case ashes::Format::eR8G8B8A8_USCALED: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eR8G8B8A8_SSCALED: return DXGI_FORMAT_R8G8B8A8_SNORM;
		case ashes::Format::eR8G8B8A8_UINT: return DXGI_FORMAT_R8G8B8A8_UINT;
		case ashes::Format::eR8G8B8A8_SINT: return DXGI_FORMAT_R8G8B8A8_SINT;
		case ashes::Format::eR8G8B8A8_SRGB: return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		case ashes::Format::eB8G8R8A8_UNORM: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case ashes::Format::eB8G8R8A8_SNORM: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case ashes::Format::eB8G8R8A8_USCALED: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case ashes::Format::eB8G8R8A8_SSCALED: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case ashes::Format::eB8G8R8A8_UINT: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case ashes::Format::eB8G8R8A8_SINT: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case ashes::Format::eB8G8R8A8_SRGB: return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		case ashes::Format::eA2R10G10B10_UNORM_PACK32: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case ashes::Format::eA2R10G10B10_SNORM_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case ashes::Format::eA2R10G10B10_USCALED_PACK32: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case ashes::Format::eA2R10G10B10_SSCALED_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case ashes::Format::eA2R10G10B10_UINT_PACK32: return DXGI_FORMAT_R10G10B10A2_UINT;
		case ashes::Format::eA2R10G10B10_SINT_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case ashes::Format::eR16_UNORM: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eR16_SNORM: return DXGI_FORMAT_R16_SNORM;
		case ashes::Format::eR16_USCALED: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eR16_SSCALED: return DXGI_FORMAT_R16_SNORM;
		case ashes::Format::eR16_UINT: return DXGI_FORMAT_R16_UINT;
		case ashes::Format::eR16_SINT: return DXGI_FORMAT_R16_SINT;
		case ashes::Format::eR16_SFLOAT: return DXGI_FORMAT_R16_FLOAT;
		case ashes::Format::eR16G16_UNORM: return DXGI_FORMAT_R16G16_UNORM;
		case ashes::Format::eR16G16_SNORM: return DXGI_FORMAT_R16G16_SNORM;
		case ashes::Format::eR16G16_USCALED: return DXGI_FORMAT_R16G16_UNORM;
		case ashes::Format::eR16G16_SSCALED: return DXGI_FORMAT_R16G16_SNORM;
		case ashes::Format::eR16G16_UINT: return DXGI_FORMAT_R16G16_UINT;
		case ashes::Format::eR16G16_SINT: return DXGI_FORMAT_R16G16_SINT;
		case ashes::Format::eR16G16_SFLOAT: return DXGI_FORMAT_R16G16_FLOAT;
		case ashes::Format::eR16G16B16A16_UNORM: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eR16G16B16A16_SNORM: return DXGI_FORMAT_R16G16B16A16_SNORM;
		case ashes::Format::eR16G16B16A16_USCALED: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eR16G16B16A16_SSCALED: return DXGI_FORMAT_R16G16B16A16_SNORM;
		case ashes::Format::eR16G16B16A16_UINT: return DXGI_FORMAT_R16G16B16A16_UINT;
		case ashes::Format::eR16G16B16A16_SINT: return DXGI_FORMAT_R16G16B16A16_SINT;
		case ashes::Format::eR16G16B16A16_SFLOAT: return DXGI_FORMAT_R16G16B16A16_FLOAT;
		case ashes::Format::eR32_UINT: return DXGI_FORMAT_R32_UINT;
		case ashes::Format::eR32_SINT: return DXGI_FORMAT_R32_SINT;
		case ashes::Format::eR32_SFLOAT: return DXGI_FORMAT_R32_FLOAT;
		case ashes::Format::eR32G32_UINT: return DXGI_FORMAT_R32G32_UINT;
		case ashes::Format::eR32G32_SINT: return DXGI_FORMAT_R32G32_SINT;
		case ashes::Format::eR32G32_SFLOAT: return DXGI_FORMAT_R32G32_FLOAT;
		case ashes::Format::eR32G32B32_UINT: return DXGI_FORMAT_R32G32B32_UINT;
		case ashes::Format::eR32G32B32_SINT: return DXGI_FORMAT_R32G32B32_SINT;
		case ashes::Format::eR32G32B32_SFLOAT: return DXGI_FORMAT_R32G32B32_FLOAT;
		case ashes::Format::eR32G32B32A32_UINT: return DXGI_FORMAT_R32G32B32A32_UINT;
		case ashes::Format::eR32G32B32A32_SINT: return DXGI_FORMAT_R32G32B32A32_SINT;
		case ashes::Format::eR32G32B32A32_SFLOAT: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case ashes::Format::eB10G11R11_UFLOAT_PACK32: return DXGI_FORMAT_R11G11B10_FLOAT;
		case ashes::Format::eE5B9G9R9_UFLOAT_PACK32: return DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
		case ashes::Format::eD16_UNORM: return DXGI_FORMAT_D16_UNORM;
		case ashes::Format::eX8_D24_UNORM_PACK32: return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		case ashes::Format::eD32_SFLOAT: return DXGI_FORMAT_D32_FLOAT;
		case ashes::Format::eD24_UNORM_S8_UINT: return DXGI_FORMAT_D24_UNORM_S8_UINT;
		case ashes::Format::eD32_SFLOAT_S8_UINT: return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
		case ashes::Format::eBC1_RGB_UNORM_BLOCK: return DXGI_FORMAT_BC1_UNORM;
		case ashes::Format::eBC1_RGB_SRGB_BLOCK: return DXGI_FORMAT_BC1_UNORM_SRGB;
		case ashes::Format::eBC2_UNORM_BLOCK: return DXGI_FORMAT_BC2_UNORM;
		case ashes::Format::eBC2_SRGB_BLOCK: return DXGI_FORMAT_BC2_UNORM_SRGB;
		case ashes::Format::eBC3_UNORM_BLOCK: return DXGI_FORMAT_BC3_UNORM;
		case ashes::Format::eBC3_SRGB_BLOCK: return DXGI_FORMAT_BC3_UNORM_SRGB;
		case ashes::Format::eBC4_UNORM_BLOCK: return DXGI_FORMAT_BC4_UNORM;
		case ashes::Format::eBC4_SNORM_BLOCK: return DXGI_FORMAT_BC4_SNORM;
		case ashes::Format::eBC5_UNORM_BLOCK: return DXGI_FORMAT_BC5_UNORM;
		case ashes::Format::eBC5_SNORM_BLOCK: return DXGI_FORMAT_BC5_SNORM;
		case ashes::Format::eBC7_UNORM_BLOCK: return DXGI_FORMAT_BC7_UNORM;
		case ashes::Format::eBC7_SRGB_BLOCK: return DXGI_FORMAT_BC7_UNORM_SRGB;
		case ashes::Format::eG8_B8_R8_3PLANE_444_UNORM: return DXGI_FORMAT_AYUV;
		case ashes::Format::eG10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16: return DXGI_FORMAT_Y410;
		case ashes::Format::eG16_B16_R16_3PLANE_444_UNORM: return DXGI_FORMAT_Y416;
		case ashes::Format::eG8_B8_R8_3PLANE_420_UNORM: return DXGI_FORMAT_NV12;
		case ashes::Format::eG10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16: return DXGI_FORMAT_P010;
		case ashes::Format::eG16_B16_R16_3PLANE_420_UNORM: return DXGI_FORMAT_P016;
		case ashes::Format::eG8_B8_R8_3PLANE_422_UNORM: return DXGI_FORMAT_YUY2;
		case ashes::Format::eG10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16: return DXGI_FORMAT_Y210;
		case ashes::Format::eG16_B16_R16_3PLANE_422_UNORM: return DXGI_FORMAT_Y216;
		default: return DXGI_FORMAT_UNKNOWN;
		}
	}
	
	DXGI_FORMAT getTextureFormat( ashes::Format const & format )noexcept
	{
		switch ( format )
		{
		case ashes::Format::eUndefined: return DXGI_FORMAT_UNKNOWN;
		case ashes::Format::eR4G4B4A4_UNORM_PACK16: return DXGI_FORMAT_B4G4R4A4_UNORM;
		case ashes::Format::eB4G4R4A4_UNORM_PACK16: return DXGI_FORMAT_B4G4R4A4_UNORM;
		case ashes::Format::eR5G6B5_UNORM_PACK16: return DXGI_FORMAT_B5G6R5_UNORM;
		case ashes::Format::eB5G6R5_UNORM_PACK16: return DXGI_FORMAT_B5G6R5_UNORM;
		case ashes::Format::eR5G5B5A1_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case ashes::Format::eB5G5R5A1_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case ashes::Format::eA1R5G5B5_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case ashes::Format::eR8_UNORM: return DXGI_FORMAT_R8_UNORM;
		case ashes::Format::eR8_SNORM: return DXGI_FORMAT_R8_SNORM;
		case ashes::Format::eR8_USCALED: return DXGI_FORMAT_R8_UNORM;
		case ashes::Format::eR8_SSCALED: return DXGI_FORMAT_R8_SNORM;
		case ashes::Format::eR8_UINT: return DXGI_FORMAT_R8_UINT;
		case ashes::Format::eR8_SINT: return DXGI_FORMAT_R8_SINT;
		case ashes::Format::eR8_SRGB: return DXGI_FORMAT_R8_SINT;
		case ashes::Format::eR8G8_UNORM: return DXGI_FORMAT_R8G8_UNORM;
		case ashes::Format::eR8G8_SNORM: return DXGI_FORMAT_R8G8_SNORM;
		case ashes::Format::eR8G8_USCALED: return DXGI_FORMAT_R8G8_UNORM;
		case ashes::Format::eR8G8_SSCALED: return DXGI_FORMAT_R8G8_SNORM;
		case ashes::Format::eR8G8_UINT: return DXGI_FORMAT_R8G8_UINT;
		case ashes::Format::eR8G8_SINT: return DXGI_FORMAT_R8G8_SINT;
		case ashes::Format::eR8G8_SRGB: return DXGI_FORMAT_R8G8_SINT;
		case ashes::Format::eR8G8B8_UNORM: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eR8G8B8_SNORM: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eR8G8B8_USCALED: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eR8G8B8_SSCALED: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eR8G8B8_UINT: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eR8G8B8_SINT: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eR8G8B8_SRGB: return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		case ashes::Format::eB8G8R8_UNORM: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eB8G8R8_SNORM: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eB8G8R8_USCALED: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eB8G8R8_SSCALED: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eB8G8R8_UINT: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eB8G8R8_SINT: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eB8G8R8_SRGB: return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		case ashes::Format::eR8G8B8A8_UNORM: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eR8G8B8A8_SNORM: return DXGI_FORMAT_R8G8B8A8_SNORM;
		case ashes::Format::eR8G8B8A8_USCALED: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eR8G8B8A8_SSCALED: return DXGI_FORMAT_R8G8B8A8_SNORM;
		case ashes::Format::eR8G8B8A8_UINT: return DXGI_FORMAT_R8G8B8A8_UINT;
		case ashes::Format::eR8G8B8A8_SINT: return DXGI_FORMAT_R8G8B8A8_SINT;
		case ashes::Format::eR8G8B8A8_SRGB: return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		case ashes::Format::eB8G8R8A8_UNORM: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case ashes::Format::eB8G8R8A8_SNORM: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case ashes::Format::eB8G8R8A8_USCALED: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case ashes::Format::eB8G8R8A8_SSCALED: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case ashes::Format::eB8G8R8A8_UINT: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case ashes::Format::eB8G8R8A8_SINT: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case ashes::Format::eB8G8R8A8_SRGB: return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		case ashes::Format::eA2R10G10B10_UNORM_PACK32: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case ashes::Format::eA2R10G10B10_SNORM_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case ashes::Format::eA2R10G10B10_USCALED_PACK32: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case ashes::Format::eA2R10G10B10_SSCALED_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case ashes::Format::eA2R10G10B10_UINT_PACK32: return DXGI_FORMAT_R10G10B10A2_UINT;
		case ashes::Format::eA2R10G10B10_SINT_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case ashes::Format::eR16_UNORM: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eR16_SNORM: return DXGI_FORMAT_R16_SNORM;
		case ashes::Format::eR16_USCALED: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eR16_SSCALED: return DXGI_FORMAT_R16_SNORM;
		case ashes::Format::eR16_UINT: return DXGI_FORMAT_R16_UINT;
		case ashes::Format::eR16_SINT: return DXGI_FORMAT_R16_SINT;
		case ashes::Format::eR16_SFLOAT: return DXGI_FORMAT_R16_FLOAT;
		case ashes::Format::eR16G16_UNORM: return DXGI_FORMAT_R16G16_UNORM;
		case ashes::Format::eR16G16_SNORM: return DXGI_FORMAT_R16G16_SNORM;
		case ashes::Format::eR16G16_USCALED: return DXGI_FORMAT_R16G16_UNORM;
		case ashes::Format::eR16G16_SSCALED: return DXGI_FORMAT_R16G16_SNORM;
		case ashes::Format::eR16G16_UINT: return DXGI_FORMAT_R16G16_UINT;
		case ashes::Format::eR16G16_SINT: return DXGI_FORMAT_R16G16_SINT;
		case ashes::Format::eR16G16_SFLOAT: return DXGI_FORMAT_R16G16_FLOAT;
		case ashes::Format::eR16G16B16A16_UNORM: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eR16G16B16A16_SNORM: return DXGI_FORMAT_R16G16B16A16_SNORM;
		case ashes::Format::eR16G16B16A16_USCALED: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eR16G16B16A16_SSCALED: return DXGI_FORMAT_R16G16B16A16_SNORM;
		case ashes::Format::eR16G16B16A16_UINT: return DXGI_FORMAT_R16G16B16A16_UINT;
		case ashes::Format::eR16G16B16A16_SINT: return DXGI_FORMAT_R16G16B16A16_SINT;
		case ashes::Format::eR16G16B16A16_SFLOAT: return DXGI_FORMAT_R16G16B16A16_FLOAT;
		case ashes::Format::eR32_UINT: return DXGI_FORMAT_R32_UINT;
		case ashes::Format::eR32_SINT: return DXGI_FORMAT_R32_SINT;
		case ashes::Format::eR32_SFLOAT: return DXGI_FORMAT_R32_FLOAT;
		case ashes::Format::eR32G32_UINT: return DXGI_FORMAT_R32G32_UINT;
		case ashes::Format::eR32G32_SINT: return DXGI_FORMAT_R32G32_SINT;
		case ashes::Format::eR32G32_SFLOAT: return DXGI_FORMAT_R32G32_FLOAT;
		case ashes::Format::eR32G32B32_UINT: return DXGI_FORMAT_R32G32B32_UINT;
		case ashes::Format::eR32G32B32_SINT: return DXGI_FORMAT_R32G32B32_SINT;
		case ashes::Format::eR32G32B32_SFLOAT: return DXGI_FORMAT_R32G32B32_FLOAT;
		case ashes::Format::eR32G32B32A32_UINT: return DXGI_FORMAT_R32G32B32A32_UINT;
		case ashes::Format::eR32G32B32A32_SINT: return DXGI_FORMAT_R32G32B32A32_SINT;
		case ashes::Format::eR32G32B32A32_SFLOAT: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case ashes::Format::eB10G11R11_UFLOAT_PACK32: return DXGI_FORMAT_R11G11B10_FLOAT;
		case ashes::Format::eE5B9G9R9_UFLOAT_PACK32: return DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
		case ashes::Format::eD16_UNORM: return DXGI_FORMAT_D16_UNORM;
		case ashes::Format::eX8_D24_UNORM_PACK32: return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		case ashes::Format::eD32_SFLOAT: return DXGI_FORMAT_D32_FLOAT;
		case ashes::Format::eD24_UNORM_S8_UINT: return DXGI_FORMAT_R24G8_TYPELESS;
		case ashes::Format::eD32_SFLOAT_S8_UINT: return DXGI_FORMAT_R32G8X24_TYPELESS;
		case ashes::Format::eBC1_RGB_UNORM_BLOCK: return DXGI_FORMAT_BC1_UNORM;
		case ashes::Format::eBC1_RGB_SRGB_BLOCK: return DXGI_FORMAT_BC1_UNORM_SRGB;
		case ashes::Format::eBC2_UNORM_BLOCK: return DXGI_FORMAT_BC2_UNORM;
		case ashes::Format::eBC2_SRGB_BLOCK: return DXGI_FORMAT_BC2_UNORM_SRGB;
		case ashes::Format::eBC3_UNORM_BLOCK: return DXGI_FORMAT_BC3_UNORM;
		case ashes::Format::eBC3_SRGB_BLOCK: return DXGI_FORMAT_BC3_UNORM_SRGB;
		case ashes::Format::eBC4_UNORM_BLOCK: return DXGI_FORMAT_BC4_UNORM;
		case ashes::Format::eBC4_SNORM_BLOCK: return DXGI_FORMAT_BC4_SNORM;
		case ashes::Format::eBC5_UNORM_BLOCK: return DXGI_FORMAT_BC5_UNORM;
		case ashes::Format::eBC5_SNORM_BLOCK: return DXGI_FORMAT_BC5_SNORM;
		case ashes::Format::eBC7_UNORM_BLOCK: return DXGI_FORMAT_BC7_UNORM;
		case ashes::Format::eBC7_SRGB_BLOCK: return DXGI_FORMAT_BC7_UNORM_SRGB;
		case ashes::Format::eG8_B8_R8_3PLANE_444_UNORM: return DXGI_FORMAT_AYUV;
		case ashes::Format::eG10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16: return DXGI_FORMAT_Y410;
		case ashes::Format::eG16_B16_R16_3PLANE_444_UNORM: return DXGI_FORMAT_Y416;
		case ashes::Format::eG8_B8_R8_3PLANE_420_UNORM: return DXGI_FORMAT_NV12;
		case ashes::Format::eG10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16: return DXGI_FORMAT_P010;
		case ashes::Format::eG16_B16_R16_3PLANE_420_UNORM: return DXGI_FORMAT_P016;
		case ashes::Format::eG8_B8_R8_3PLANE_422_UNORM: return DXGI_FORMAT_YUY2;
		case ashes::Format::eG10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16: return DXGI_FORMAT_Y210;
		case ashes::Format::eG16_B16_R16_3PLANE_422_UNORM: return DXGI_FORMAT_Y216;

		default:
			assert( false && "Unsupported pixel format." );
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	DXGI_FORMAT getSRVFormat( ashes::Format const & format )noexcept
	{
		switch ( format )
		{
		case ashes::Format::eUndefined: return DXGI_FORMAT_UNKNOWN;
		case ashes::Format::eR4G4B4A4_UNORM_PACK16: return DXGI_FORMAT_B4G4R4A4_UNORM;
		case ashes::Format::eB4G4R4A4_UNORM_PACK16: return DXGI_FORMAT_B4G4R4A4_UNORM;
		case ashes::Format::eR5G6B5_UNORM_PACK16: return DXGI_FORMAT_B5G6R5_UNORM;
		case ashes::Format::eB5G6R5_UNORM_PACK16: return DXGI_FORMAT_B5G6R5_UNORM;
		case ashes::Format::eR5G5B5A1_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case ashes::Format::eB5G5R5A1_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case ashes::Format::eA1R5G5B5_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case ashes::Format::eR8_UNORM: return DXGI_FORMAT_R8_UNORM;
		case ashes::Format::eR8_SNORM: return DXGI_FORMAT_R8_SNORM;
		case ashes::Format::eR8_USCALED: return DXGI_FORMAT_R8_UNORM;
		case ashes::Format::eR8_SSCALED: return DXGI_FORMAT_R8_SNORM;
		case ashes::Format::eR8_UINT: return DXGI_FORMAT_R8_UINT;
		case ashes::Format::eR8_SINT: return DXGI_FORMAT_R8_SINT;
		case ashes::Format::eR8_SRGB: return DXGI_FORMAT_R8_SINT;
		case ashes::Format::eR8G8_UNORM: return DXGI_FORMAT_R8G8_UNORM;
		case ashes::Format::eR8G8_SNORM: return DXGI_FORMAT_R8G8_SNORM;
		case ashes::Format::eR8G8_USCALED: return DXGI_FORMAT_R8G8_UNORM;
		case ashes::Format::eR8G8_SSCALED: return DXGI_FORMAT_R8G8_SNORM;
		case ashes::Format::eR8G8_UINT: return DXGI_FORMAT_R8G8_UINT;
		case ashes::Format::eR8G8_SINT: return DXGI_FORMAT_R8G8_SINT;
		case ashes::Format::eR8G8_SRGB: return DXGI_FORMAT_R8G8_SINT;
		case ashes::Format::eR8G8B8_UNORM: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eR8G8B8_SNORM: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eR8G8B8_USCALED: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eR8G8B8_SSCALED: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eR8G8B8_UINT: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eR8G8B8_SINT: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eR8G8B8_SRGB: return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		case ashes::Format::eB8G8R8_UNORM: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eB8G8R8_SNORM: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eB8G8R8_USCALED: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eB8G8R8_SSCALED: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eB8G8R8_UINT: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eB8G8R8_SINT: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eB8G8R8_SRGB: return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		case ashes::Format::eR8G8B8A8_UNORM: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eR8G8B8A8_SNORM: return DXGI_FORMAT_R8G8B8A8_SNORM;
		case ashes::Format::eR8G8B8A8_USCALED: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eR8G8B8A8_SSCALED: return DXGI_FORMAT_R8G8B8A8_SNORM;
		case ashes::Format::eR8G8B8A8_UINT: return DXGI_FORMAT_R8G8B8A8_UINT;
		case ashes::Format::eR8G8B8A8_SINT: return DXGI_FORMAT_R8G8B8A8_SINT;
		case ashes::Format::eR8G8B8A8_SRGB: return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		case ashes::Format::eB8G8R8A8_UNORM: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case ashes::Format::eB8G8R8A8_SNORM: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case ashes::Format::eB8G8R8A8_USCALED: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case ashes::Format::eB8G8R8A8_SSCALED: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case ashes::Format::eB8G8R8A8_UINT: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case ashes::Format::eB8G8R8A8_SINT: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case ashes::Format::eB8G8R8A8_SRGB: return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		case ashes::Format::eA2R10G10B10_UNORM_PACK32: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case ashes::Format::eA2R10G10B10_SNORM_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case ashes::Format::eA2R10G10B10_USCALED_PACK32: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case ashes::Format::eA2R10G10B10_SSCALED_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case ashes::Format::eA2R10G10B10_UINT_PACK32: return DXGI_FORMAT_R10G10B10A2_UINT;
		case ashes::Format::eA2R10G10B10_SINT_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case ashes::Format::eR16_UNORM: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eR16_SNORM: return DXGI_FORMAT_R16_SNORM;
		case ashes::Format::eR16_USCALED: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eR16_SSCALED: return DXGI_FORMAT_R16_SNORM;
		case ashes::Format::eR16_UINT: return DXGI_FORMAT_R16_UINT;
		case ashes::Format::eR16_SINT: return DXGI_FORMAT_R16_SINT;
		case ashes::Format::eR16_SFLOAT: return DXGI_FORMAT_R16_FLOAT;
		case ashes::Format::eR16G16_UNORM: return DXGI_FORMAT_R16G16_UNORM;
		case ashes::Format::eR16G16_SNORM: return DXGI_FORMAT_R16G16_SNORM;
		case ashes::Format::eR16G16_USCALED: return DXGI_FORMAT_R16G16_UNORM;
		case ashes::Format::eR16G16_SSCALED: return DXGI_FORMAT_R16G16_SNORM;
		case ashes::Format::eR16G16_UINT: return DXGI_FORMAT_R16G16_UINT;
		case ashes::Format::eR16G16_SINT: return DXGI_FORMAT_R16G16_SINT;
		case ashes::Format::eR16G16_SFLOAT: return DXGI_FORMAT_R16G16_FLOAT;
		case ashes::Format::eR16G16B16A16_UNORM: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eR16G16B16A16_SNORM: return DXGI_FORMAT_R16G16B16A16_SNORM;
		case ashes::Format::eR16G16B16A16_USCALED: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eR16G16B16A16_SSCALED: return DXGI_FORMAT_R16G16B16A16_SNORM;
		case ashes::Format::eR16G16B16A16_UINT: return DXGI_FORMAT_R16G16B16A16_UINT;
		case ashes::Format::eR16G16B16A16_SINT: return DXGI_FORMAT_R16G16B16A16_SINT;
		case ashes::Format::eR16G16B16A16_SFLOAT: return DXGI_FORMAT_R16G16B16A16_FLOAT;
		case ashes::Format::eR32_UINT: return DXGI_FORMAT_R32_UINT;
		case ashes::Format::eR32_SINT: return DXGI_FORMAT_R32_SINT;
		case ashes::Format::eR32_SFLOAT: return DXGI_FORMAT_R32_FLOAT;
		case ashes::Format::eR32G32_UINT: return DXGI_FORMAT_R32G32_UINT;
		case ashes::Format::eR32G32_SINT: return DXGI_FORMAT_R32G32_SINT;
		case ashes::Format::eR32G32_SFLOAT: return DXGI_FORMAT_R32G32_FLOAT;
		case ashes::Format::eR32G32B32_UINT: return DXGI_FORMAT_R32G32B32_UINT;
		case ashes::Format::eR32G32B32_SINT: return DXGI_FORMAT_R32G32B32_SINT;
		case ashes::Format::eR32G32B32_SFLOAT: return DXGI_FORMAT_R32G32B32_FLOAT;
		case ashes::Format::eR32G32B32A32_UINT: return DXGI_FORMAT_R32G32B32A32_UINT;
		case ashes::Format::eR32G32B32A32_SINT: return DXGI_FORMAT_R32G32B32A32_SINT;
		case ashes::Format::eR32G32B32A32_SFLOAT: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case ashes::Format::eB10G11R11_UFLOAT_PACK32: return DXGI_FORMAT_R11G11B10_FLOAT;
		case ashes::Format::eE5B9G9R9_UFLOAT_PACK32: return DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
		case ashes::Format::eD16_UNORM: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eX8_D24_UNORM_PACK32: return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		case ashes::Format::eD32_SFLOAT: return DXGI_FORMAT_R32_FLOAT;
		case ashes::Format::eD24_UNORM_S8_UINT: return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		case ashes::Format::eD32_SFLOAT_S8_UINT: return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
		case ashes::Format::eBC1_RGB_UNORM_BLOCK: return DXGI_FORMAT_BC1_UNORM;
		case ashes::Format::eBC1_RGB_SRGB_BLOCK: return DXGI_FORMAT_BC1_UNORM_SRGB;
		case ashes::Format::eBC2_UNORM_BLOCK: return DXGI_FORMAT_BC2_UNORM;
		case ashes::Format::eBC2_SRGB_BLOCK: return DXGI_FORMAT_BC2_UNORM_SRGB;
		case ashes::Format::eBC3_UNORM_BLOCK: return DXGI_FORMAT_BC3_UNORM;
		case ashes::Format::eBC3_SRGB_BLOCK: return DXGI_FORMAT_BC3_UNORM_SRGB;
		case ashes::Format::eBC4_UNORM_BLOCK: return DXGI_FORMAT_BC4_UNORM;
		case ashes::Format::eBC4_SNORM_BLOCK: return DXGI_FORMAT_BC4_SNORM;
		case ashes::Format::eBC5_UNORM_BLOCK: return DXGI_FORMAT_BC5_UNORM;
		case ashes::Format::eBC5_SNORM_BLOCK: return DXGI_FORMAT_BC5_SNORM;
		case ashes::Format::eBC7_UNORM_BLOCK: return DXGI_FORMAT_BC7_UNORM;
		case ashes::Format::eBC7_SRGB_BLOCK: return DXGI_FORMAT_BC7_UNORM_SRGB;
		case ashes::Format::eG8_B8_R8_3PLANE_444_UNORM: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eG10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case ashes::Format::eG16_B16_R16_3PLANE_444_UNORM: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eG8_B8_R8_3PLANE_420_UNORM: return DXGI_FORMAT_R8_UNORM;
		case ashes::Format::eG10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eG16_B16_R16_3PLANE_420_UNORM: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eG8_B8_R8_3PLANE_422_UNORM: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eG10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eG16_B16_R16_3PLANE_422_UNORM: return DXGI_FORMAT_R16G16B16A16_UNORM;

		default:
			assert( false && "Unsupported pixel format." );
			return DXGI_FORMAT_UNKNOWN;
		}
	}
	
	DXGI_FORMAT getRTVFormat( ashes::Format const & format )noexcept
	{
		switch ( format )
		{
		case ashes::Format::eUndefined: return DXGI_FORMAT_UNKNOWN;
		case ashes::Format::eR4G4B4A4_UNORM_PACK16: return DXGI_FORMAT_B4G4R4A4_UNORM;
		case ashes::Format::eB4G4R4A4_UNORM_PACK16: return DXGI_FORMAT_B4G4R4A4_UNORM;
		case ashes::Format::eR5G6B5_UNORM_PACK16: return DXGI_FORMAT_B5G6R5_UNORM;
		case ashes::Format::eB5G6R5_UNORM_PACK16: return DXGI_FORMAT_B5G6R5_UNORM;
		case ashes::Format::eR5G5B5A1_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case ashes::Format::eB5G5R5A1_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case ashes::Format::eA1R5G5B5_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case ashes::Format::eR8_UNORM: return DXGI_FORMAT_R8_UNORM;
		case ashes::Format::eR8_SNORM: return DXGI_FORMAT_R8_SNORM;
		case ashes::Format::eR8_USCALED: return DXGI_FORMAT_R8_UNORM;
		case ashes::Format::eR8_SSCALED: return DXGI_FORMAT_R8_SNORM;
		case ashes::Format::eR8_UINT: return DXGI_FORMAT_R8_UINT;
		case ashes::Format::eR8_SINT: return DXGI_FORMAT_R8_SINT;
		case ashes::Format::eR8_SRGB: return DXGI_FORMAT_R8_SINT;
		case ashes::Format::eR8G8_UNORM: return DXGI_FORMAT_R8G8_UNORM;
		case ashes::Format::eR8G8_SNORM: return DXGI_FORMAT_R8G8_SNORM;
		case ashes::Format::eR8G8_USCALED: return DXGI_FORMAT_R8G8_UNORM;
		case ashes::Format::eR8G8_SSCALED: return DXGI_FORMAT_R8G8_SNORM;
		case ashes::Format::eR8G8_UINT: return DXGI_FORMAT_R8G8_UINT;
		case ashes::Format::eR8G8_SINT: return DXGI_FORMAT_R8G8_SINT;
		case ashes::Format::eR8G8_SRGB: return DXGI_FORMAT_R8G8_SINT;
		case ashes::Format::eR8G8B8_UNORM: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eR8G8B8_SNORM: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eR8G8B8_USCALED: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eR8G8B8_SSCALED: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eR8G8B8_UINT: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eR8G8B8_SINT: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eR8G8B8_SRGB: return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		case ashes::Format::eB8G8R8_UNORM: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eB8G8R8_SNORM: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eB8G8R8_USCALED: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eB8G8R8_SSCALED: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eB8G8R8_UINT: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eB8G8R8_SINT: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eB8G8R8_SRGB: return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		case ashes::Format::eR8G8B8A8_UNORM: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eR8G8B8A8_SNORM: return DXGI_FORMAT_R8G8B8A8_SNORM;
		case ashes::Format::eR8G8B8A8_USCALED: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eR8G8B8A8_SSCALED: return DXGI_FORMAT_R8G8B8A8_SNORM;
		case ashes::Format::eR8G8B8A8_UINT: return DXGI_FORMAT_R8G8B8A8_UINT;
		case ashes::Format::eR8G8B8A8_SINT: return DXGI_FORMAT_R8G8B8A8_SINT;
		case ashes::Format::eR8G8B8A8_SRGB: return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		case ashes::Format::eB8G8R8A8_UNORM: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case ashes::Format::eB8G8R8A8_SNORM: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case ashes::Format::eB8G8R8A8_USCALED: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case ashes::Format::eB8G8R8A8_SSCALED: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case ashes::Format::eB8G8R8A8_UINT: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case ashes::Format::eB8G8R8A8_SINT: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case ashes::Format::eB8G8R8A8_SRGB: return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		case ashes::Format::eA2R10G10B10_UNORM_PACK32: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case ashes::Format::eA2R10G10B10_SNORM_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case ashes::Format::eA2R10G10B10_USCALED_PACK32: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case ashes::Format::eA2R10G10B10_SSCALED_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case ashes::Format::eA2R10G10B10_UINT_PACK32: return DXGI_FORMAT_R10G10B10A2_UINT;
		case ashes::Format::eA2R10G10B10_SINT_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case ashes::Format::eR16_UNORM: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eR16_SNORM: return DXGI_FORMAT_R16_SNORM;
		case ashes::Format::eR16_USCALED: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eR16_SSCALED: return DXGI_FORMAT_R16_SNORM;
		case ashes::Format::eR16_UINT: return DXGI_FORMAT_R16_UINT;
		case ashes::Format::eR16_SINT: return DXGI_FORMAT_R16_SINT;
		case ashes::Format::eR16_SFLOAT: return DXGI_FORMAT_R16_FLOAT;
		case ashes::Format::eR16G16_UNORM: return DXGI_FORMAT_R16G16_UNORM;
		case ashes::Format::eR16G16_SNORM: return DXGI_FORMAT_R16G16_SNORM;
		case ashes::Format::eR16G16_USCALED: return DXGI_FORMAT_R16G16_UNORM;
		case ashes::Format::eR16G16_SSCALED: return DXGI_FORMAT_R16G16_SNORM;
		case ashes::Format::eR16G16_UINT: return DXGI_FORMAT_R16G16_UINT;
		case ashes::Format::eR16G16_SINT: return DXGI_FORMAT_R16G16_SINT;
		case ashes::Format::eR16G16_SFLOAT: return DXGI_FORMAT_R16G16_FLOAT;
		case ashes::Format::eR16G16B16A16_UNORM: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eR16G16B16A16_SNORM: return DXGI_FORMAT_R16G16B16A16_SNORM;
		case ashes::Format::eR16G16B16A16_USCALED: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eR16G16B16A16_SSCALED: return DXGI_FORMAT_R16G16B16A16_SNORM;
		case ashes::Format::eR16G16B16A16_UINT: return DXGI_FORMAT_R16G16B16A16_UINT;
		case ashes::Format::eR16G16B16A16_SINT: return DXGI_FORMAT_R16G16B16A16_SINT;
		case ashes::Format::eR16G16B16A16_SFLOAT: return DXGI_FORMAT_R16G16B16A16_FLOAT;
		case ashes::Format::eR32_UINT: return DXGI_FORMAT_R32_UINT;
		case ashes::Format::eR32_SINT: return DXGI_FORMAT_R32_SINT;
		case ashes::Format::eR32_SFLOAT: return DXGI_FORMAT_R32_FLOAT;
		case ashes::Format::eR32G32_UINT: return DXGI_FORMAT_R32G32_UINT;
		case ashes::Format::eR32G32_SINT: return DXGI_FORMAT_R32G32_SINT;
		case ashes::Format::eR32G32_SFLOAT: return DXGI_FORMAT_R32G32_FLOAT;
		case ashes::Format::eR32G32B32_UINT: return DXGI_FORMAT_R32G32B32_UINT;
		case ashes::Format::eR32G32B32_SINT: return DXGI_FORMAT_R32G32B32_SINT;
		case ashes::Format::eR32G32B32_SFLOAT: return DXGI_FORMAT_R32G32B32_FLOAT;
		case ashes::Format::eR32G32B32A32_UINT: return DXGI_FORMAT_R32G32B32A32_UINT;
		case ashes::Format::eR32G32B32A32_SINT: return DXGI_FORMAT_R32G32B32A32_SINT;
		case ashes::Format::eR32G32B32A32_SFLOAT: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case ashes::Format::eB10G11R11_UFLOAT_PACK32: return DXGI_FORMAT_R11G11B10_FLOAT;
		case ashes::Format::eE5B9G9R9_UFLOAT_PACK32: return DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
		case ashes::Format::eD16_UNORM: return DXGI_FORMAT_D16_UNORM;
		case ashes::Format::eX8_D24_UNORM_PACK32: return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		case ashes::Format::eD32_SFLOAT: return DXGI_FORMAT_D32_FLOAT;
		case ashes::Format::eD24_UNORM_S8_UINT: return DXGI_FORMAT_D24_UNORM_S8_UINT;
		case ashes::Format::eD32_SFLOAT_S8_UINT: return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
		case ashes::Format::eBC1_RGB_UNORM_BLOCK: return DXGI_FORMAT_BC1_UNORM;
		case ashes::Format::eBC1_RGB_SRGB_BLOCK: return DXGI_FORMAT_BC1_UNORM_SRGB;
		case ashes::Format::eBC2_UNORM_BLOCK: return DXGI_FORMAT_BC2_UNORM;
		case ashes::Format::eBC2_SRGB_BLOCK: return DXGI_FORMAT_BC2_UNORM_SRGB;
		case ashes::Format::eBC3_UNORM_BLOCK: return DXGI_FORMAT_BC3_UNORM;
		case ashes::Format::eBC3_SRGB_BLOCK: return DXGI_FORMAT_BC3_UNORM_SRGB;
		case ashes::Format::eBC4_UNORM_BLOCK: return DXGI_FORMAT_BC4_UNORM;
		case ashes::Format::eBC4_SNORM_BLOCK: return DXGI_FORMAT_BC4_SNORM;
		case ashes::Format::eBC5_UNORM_BLOCK: return DXGI_FORMAT_BC5_UNORM;
		case ashes::Format::eBC5_SNORM_BLOCK: return DXGI_FORMAT_BC5_SNORM;
		case ashes::Format::eBC7_UNORM_BLOCK: return DXGI_FORMAT_BC7_UNORM;
		case ashes::Format::eBC7_SRGB_BLOCK: return DXGI_FORMAT_BC7_UNORM_SRGB;
		case ashes::Format::eG8_B8_R8_3PLANE_444_UNORM: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eG10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case ashes::Format::eG16_B16_R16_3PLANE_444_UNORM: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eG8_B8_R8_3PLANE_420_UNORM: return DXGI_FORMAT_R8_UNORM;
		case ashes::Format::eG10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eG16_B16_R16_3PLANE_420_UNORM: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eG8_B8_R8_3PLANE_422_UNORM: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eG10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eG16_B16_R16_3PLANE_422_UNORM: return DXGI_FORMAT_R16G16B16A16_UNORM;

		default:
			assert( false && "Unsupported pixel format." );
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	DXGI_FORMAT getUAVFormat( ashes::Format const & format )noexcept
	{
		switch ( format )
		{
		case ashes::Format::eUndefined: return DXGI_FORMAT_UNKNOWN;
		case ashes::Format::eR4G4B4A4_UNORM_PACK16: return DXGI_FORMAT_B4G4R4A4_UNORM;
		case ashes::Format::eB4G4R4A4_UNORM_PACK16: return DXGI_FORMAT_B4G4R4A4_UNORM;
		case ashes::Format::eR5G6B5_UNORM_PACK16: return DXGI_FORMAT_B5G6R5_UNORM;
		case ashes::Format::eB5G6R5_UNORM_PACK16: return DXGI_FORMAT_B5G6R5_UNORM;
		case ashes::Format::eR5G5B5A1_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case ashes::Format::eB5G5R5A1_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case ashes::Format::eA1R5G5B5_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case ashes::Format::eR8_UNORM: return DXGI_FORMAT_R8_UNORM;
		case ashes::Format::eR8_SNORM: return DXGI_FORMAT_R8_SNORM;
		case ashes::Format::eR8_USCALED: return DXGI_FORMAT_R8_UNORM;
		case ashes::Format::eR8_SSCALED: return DXGI_FORMAT_R8_SNORM;
		case ashes::Format::eR8_UINT: return DXGI_FORMAT_R8_UINT;
		case ashes::Format::eR8_SINT: return DXGI_FORMAT_R8_SINT;
		case ashes::Format::eR8_SRGB: return DXGI_FORMAT_R8_SINT;
		case ashes::Format::eR8G8_UNORM: return DXGI_FORMAT_R8G8_UNORM;
		case ashes::Format::eR8G8_SNORM: return DXGI_FORMAT_R8G8_SNORM;
		case ashes::Format::eR8G8_USCALED: return DXGI_FORMAT_R8G8_UNORM;
		case ashes::Format::eR8G8_SSCALED: return DXGI_FORMAT_R8G8_SNORM;
		case ashes::Format::eR8G8_UINT: return DXGI_FORMAT_R8G8_UINT;
		case ashes::Format::eR8G8_SINT: return DXGI_FORMAT_R8G8_SINT;
		case ashes::Format::eR8G8_SRGB: return DXGI_FORMAT_R8G8_SINT;
		case ashes::Format::eR8G8B8_UNORM: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eR8G8B8_SNORM: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eR8G8B8_USCALED: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eR8G8B8_SSCALED: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eR8G8B8_UINT: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eR8G8B8_SINT: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eR8G8B8_SRGB: return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		case ashes::Format::eB8G8R8_UNORM: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eB8G8R8_SNORM: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eB8G8R8_USCALED: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eB8G8R8_SSCALED: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eB8G8R8_UINT: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case ashes::Format::eB8G8R8_SINT: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case ashes::Format::eB8G8R8_SRGB: return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		case ashes::Format::eR8G8B8A8_UNORM: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eR8G8B8A8_SNORM: return DXGI_FORMAT_R8G8B8A8_SNORM;
		case ashes::Format::eR8G8B8A8_USCALED: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eR8G8B8A8_SSCALED: return DXGI_FORMAT_R8G8B8A8_SNORM;
		case ashes::Format::eR8G8B8A8_UINT: return DXGI_FORMAT_R8G8B8A8_UINT;
		case ashes::Format::eR8G8B8A8_SINT: return DXGI_FORMAT_R8G8B8A8_SINT;
		case ashes::Format::eR8G8B8A8_SRGB: return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		case ashes::Format::eB8G8R8A8_UNORM: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case ashes::Format::eB8G8R8A8_SNORM: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case ashes::Format::eB8G8R8A8_USCALED: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case ashes::Format::eB8G8R8A8_SSCALED: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case ashes::Format::eB8G8R8A8_UINT: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case ashes::Format::eB8G8R8A8_SINT: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case ashes::Format::eB8G8R8A8_SRGB: return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		case ashes::Format::eA2R10G10B10_UNORM_PACK32: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case ashes::Format::eA2R10G10B10_SNORM_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case ashes::Format::eA2R10G10B10_USCALED_PACK32: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case ashes::Format::eA2R10G10B10_SSCALED_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case ashes::Format::eA2R10G10B10_UINT_PACK32: return DXGI_FORMAT_R10G10B10A2_UINT;
		case ashes::Format::eA2R10G10B10_SINT_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case ashes::Format::eR16_UNORM: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eR16_SNORM: return DXGI_FORMAT_R16_SNORM;
		case ashes::Format::eR16_USCALED: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eR16_SSCALED: return DXGI_FORMAT_R16_SNORM;
		case ashes::Format::eR16_UINT: return DXGI_FORMAT_R16_UINT;
		case ashes::Format::eR16_SINT: return DXGI_FORMAT_R16_SINT;
		case ashes::Format::eR16_SFLOAT: return DXGI_FORMAT_R16_FLOAT;
		case ashes::Format::eR16G16_UNORM: return DXGI_FORMAT_R16G16_UNORM;
		case ashes::Format::eR16G16_SNORM: return DXGI_FORMAT_R16G16_SNORM;
		case ashes::Format::eR16G16_USCALED: return DXGI_FORMAT_R16G16_UNORM;
		case ashes::Format::eR16G16_SSCALED: return DXGI_FORMAT_R16G16_SNORM;
		case ashes::Format::eR16G16_UINT: return DXGI_FORMAT_R16G16_UINT;
		case ashes::Format::eR16G16_SINT: return DXGI_FORMAT_R16G16_SINT;
		case ashes::Format::eR16G16_SFLOAT: return DXGI_FORMAT_R16G16_FLOAT;
		case ashes::Format::eR16G16B16A16_UNORM: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eR16G16B16A16_SNORM: return DXGI_FORMAT_R16G16B16A16_SNORM;
		case ashes::Format::eR16G16B16A16_USCALED: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eR16G16B16A16_SSCALED: return DXGI_FORMAT_R16G16B16A16_SNORM;
		case ashes::Format::eR16G16B16A16_UINT: return DXGI_FORMAT_R16G16B16A16_UINT;
		case ashes::Format::eR16G16B16A16_SINT: return DXGI_FORMAT_R16G16B16A16_SINT;
		case ashes::Format::eR16G16B16A16_SFLOAT: return DXGI_FORMAT_R16G16B16A16_FLOAT;
		case ashes::Format::eR32_UINT: return DXGI_FORMAT_R32_UINT;
		case ashes::Format::eR32_SINT: return DXGI_FORMAT_R32_SINT;
		case ashes::Format::eR32_SFLOAT: return DXGI_FORMAT_R32_FLOAT;
		case ashes::Format::eR32G32_UINT: return DXGI_FORMAT_R32G32_UINT;
		case ashes::Format::eR32G32_SINT: return DXGI_FORMAT_R32G32_SINT;
		case ashes::Format::eR32G32_SFLOAT: return DXGI_FORMAT_R32G32_FLOAT;
		case ashes::Format::eR32G32B32_UINT: return DXGI_FORMAT_R32G32B32_UINT;
		case ashes::Format::eR32G32B32_SINT: return DXGI_FORMAT_R32G32B32_SINT;
		case ashes::Format::eR32G32B32_SFLOAT: return DXGI_FORMAT_R32G32B32_FLOAT;
		case ashes::Format::eR32G32B32A32_UINT: return DXGI_FORMAT_R32G32B32A32_UINT;
		case ashes::Format::eR32G32B32A32_SINT: return DXGI_FORMAT_R32G32B32A32_SINT;
		case ashes::Format::eR32G32B32A32_SFLOAT: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case ashes::Format::eB10G11R11_UFLOAT_PACK32: return DXGI_FORMAT_R11G11B10_FLOAT;
		case ashes::Format::eE5B9G9R9_UFLOAT_PACK32: return DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
		case ashes::Format::eD16_UNORM: return DXGI_FORMAT_D16_UNORM;
		case ashes::Format::eX8_D24_UNORM_PACK32: return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		case ashes::Format::eD32_SFLOAT: return DXGI_FORMAT_D32_FLOAT;
		case ashes::Format::eD24_UNORM_S8_UINT: return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		case ashes::Format::eD32_SFLOAT_S8_UINT: return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
		case ashes::Format::eBC1_RGB_UNORM_BLOCK: return DXGI_FORMAT_BC1_UNORM;
		case ashes::Format::eBC1_RGB_SRGB_BLOCK: return DXGI_FORMAT_BC1_UNORM_SRGB;
		case ashes::Format::eBC2_UNORM_BLOCK: return DXGI_FORMAT_BC2_UNORM;
		case ashes::Format::eBC2_SRGB_BLOCK: return DXGI_FORMAT_BC2_UNORM_SRGB;
		case ashes::Format::eBC3_UNORM_BLOCK: return DXGI_FORMAT_BC3_UNORM;
		case ashes::Format::eBC3_SRGB_BLOCK: return DXGI_FORMAT_BC3_UNORM_SRGB;
		case ashes::Format::eBC4_UNORM_BLOCK: return DXGI_FORMAT_BC4_UNORM;
		case ashes::Format::eBC4_SNORM_BLOCK: return DXGI_FORMAT_BC4_SNORM;
		case ashes::Format::eBC5_UNORM_BLOCK: return DXGI_FORMAT_BC5_UNORM;
		case ashes::Format::eBC5_SNORM_BLOCK: return DXGI_FORMAT_BC5_SNORM;
		case ashes::Format::eBC7_UNORM_BLOCK: return DXGI_FORMAT_BC7_UNORM;
		case ashes::Format::eBC7_SRGB_BLOCK: return DXGI_FORMAT_BC7_UNORM_SRGB;
		case ashes::Format::eG8_B8_R8_3PLANE_444_UNORM: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eG10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case ashes::Format::eG16_B16_R16_3PLANE_444_UNORM: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eG8_B8_R8_3PLANE_420_UNORM: return DXGI_FORMAT_R8_UNORM;
		case ashes::Format::eG10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eG16_B16_R16_3PLANE_420_UNORM: return DXGI_FORMAT_R16_UNORM;
		case ashes::Format::eG8_B8_R8_3PLANE_422_UNORM: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ashes::Format::eG10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case ashes::Format::eG16_B16_R16_3PLANE_422_UNORM: return DXGI_FORMAT_R16G16B16A16_UNORM;

		default:
			assert( false && "Unsupported pixel format." );
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	DXGI_FORMAT getBufferFormat( ashes::Format const & format )noexcept
	{
		return getTextureFormat( format );
	}

	ashes::Format convert( DXGI_FORMAT const & format )noexcept
	{
		switch ( format )
		{
		case DXGI_FORMAT_UNKNOWN: return ashes::Format::eUndefined;
		case DXGI_FORMAT_B4G4R4A4_UNORM: return ashes::Format::eB4G4R4A4_UNORM_PACK16;
		case DXGI_FORMAT_B5G6R5_UNORM: return ashes::Format::eB5G6R5_UNORM_PACK16;
		case DXGI_FORMAT_B5G5R5A1_UNORM: return ashes::Format::eB5G5R5A1_UNORM_PACK16;
		case DXGI_FORMAT_R8_UNORM: return ashes::Format::eR8_UNORM;
		case DXGI_FORMAT_R8_SNORM: return ashes::Format::eR8_SNORM;
		case DXGI_FORMAT_R8_UINT: return ashes::Format::eR8_UINT;
		case DXGI_FORMAT_R8_SINT: return ashes::Format::eR8_SINT;
		case DXGI_FORMAT_R8G8_UNORM: return ashes::Format::eR8G8_UNORM;
		case DXGI_FORMAT_R8G8_SNORM: return ashes::Format::eR8G8_SNORM;
		case DXGI_FORMAT_R8G8_UINT: return ashes::Format::eR8G8_UINT;
		case DXGI_FORMAT_R8G8_SINT: return ashes::Format::eR8G8_SINT;
		case DXGI_FORMAT_B8G8R8X8_UNORM: return ashes::Format::eB8G8R8_UNORM;
		case DXGI_FORMAT_B8G8R8X8_TYPELESS: return ashes::Format::eB8G8R8_SNORM;
		case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB: return ashes::Format::eB8G8R8_SRGB;
		case DXGI_FORMAT_R8G8B8A8_UNORM: return ashes::Format::eR8G8B8A8_UNORM;
		case DXGI_FORMAT_R8G8B8A8_SNORM: return ashes::Format::eR8G8B8A8_SNORM;
		case DXGI_FORMAT_R8G8B8A8_UINT: return ashes::Format::eR8G8B8A8_UINT;
		case DXGI_FORMAT_R8G8B8A8_SINT: return ashes::Format::eR8G8B8A8_SINT;
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB: return ashes::Format::eR8G8B8A8_SRGB;
		case DXGI_FORMAT_B8G8R8A8_UNORM: return ashes::Format::eB8G8R8A8_UNORM;
		case DXGI_FORMAT_B8G8R8A8_TYPELESS: return ashes::Format::eB8G8R8A8_SNORM;
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB: return ashes::Format::eB8G8R8A8_SRGB;
		case DXGI_FORMAT_R10G10B10A2_UNORM: return ashes::Format::eA2R10G10B10_UNORM_PACK32;
		case DXGI_FORMAT_R10G10B10A2_TYPELESS: return ashes::Format::eA2R10G10B10_SNORM_PACK32;
		case DXGI_FORMAT_R10G10B10A2_UINT: return ashes::Format::eA2R10G10B10_UINT_PACK32;
		case DXGI_FORMAT_R16_UNORM: return ashes::Format::eR16_UNORM;
		case DXGI_FORMAT_R16_SNORM: return ashes::Format::eR16_SNORM;
		case DXGI_FORMAT_R16_UINT: return ashes::Format::eR16_UINT;
		case DXGI_FORMAT_R16_SINT: return ashes::Format::eR16_SINT;
		case DXGI_FORMAT_R16_FLOAT: return ashes::Format::eR16_SFLOAT;
		case DXGI_FORMAT_R16G16_UNORM: return ashes::Format::eR16G16_UNORM;
		case DXGI_FORMAT_R16G16_SNORM: return ashes::Format::eR16G16_SNORM;
		case DXGI_FORMAT_R16G16_UINT: return ashes::Format::eR16G16_UINT;
		case DXGI_FORMAT_R16G16_SINT: return ashes::Format::eR16G16_SINT;
		case DXGI_FORMAT_R16G16_FLOAT: return ashes::Format::eR16G16_SFLOAT;
		case DXGI_FORMAT_R16G16B16A16_UNORM: return ashes::Format::eR16G16B16A16_UNORM;
		case DXGI_FORMAT_R16G16B16A16_SNORM: return ashes::Format::eR16G16B16A16_SNORM;
		case DXGI_FORMAT_R16G16B16A16_UINT: return ashes::Format::eR16G16B16A16_UINT;
		case DXGI_FORMAT_R16G16B16A16_SINT: return ashes::Format::eR16G16B16A16_SINT;
		case DXGI_FORMAT_R16G16B16A16_FLOAT: return ashes::Format::eR16G16B16A16_SFLOAT;
		case DXGI_FORMAT_R32_UINT: return ashes::Format::eR32_UINT;
		case DXGI_FORMAT_R32_SINT: return ashes::Format::eR32_SINT;
		case DXGI_FORMAT_R32_FLOAT: return ashes::Format::eR32_SFLOAT;
		case DXGI_FORMAT_R32G32_UINT: return ashes::Format::eR32G32_UINT;
		case DXGI_FORMAT_R32G32_SINT: return ashes::Format::eR32G32_SINT;
		case DXGI_FORMAT_R32G32_FLOAT: return ashes::Format::eR32G32_SFLOAT;
		case DXGI_FORMAT_R32G32B32_UINT: return ashes::Format::eR32G32B32_UINT;
		case DXGI_FORMAT_R32G32B32_SINT: return ashes::Format::eR32G32B32_SINT;
		case DXGI_FORMAT_R32G32B32_FLOAT: return ashes::Format::eR32G32B32_SFLOAT;
		case DXGI_FORMAT_R32G32B32A32_UINT: return ashes::Format::eR32G32B32A32_UINT;
		case DXGI_FORMAT_R32G32B32A32_SINT: return ashes::Format::eR32G32B32A32_SINT;
		case DXGI_FORMAT_R32G32B32A32_FLOAT: return ashes::Format::eR32G32B32A32_SFLOAT;
		case DXGI_FORMAT_R11G11B10_FLOAT: return ashes::Format::eB10G11R11_UFLOAT_PACK32;
		case DXGI_FORMAT_R9G9B9E5_SHAREDEXP: return ashes::Format::eE5B9G9R9_UFLOAT_PACK32;
		case DXGI_FORMAT_D16_UNORM: return ashes::Format::eD16_UNORM;
		case DXGI_FORMAT_R24_UNORM_X8_TYPELESS: return ashes::Format::eX8_D24_UNORM_PACK32;
		case DXGI_FORMAT_D32_FLOAT: return ashes::Format::eD32_SFLOAT;
		case DXGI_FORMAT_D24_UNORM_S8_UINT: return ashes::Format::eD24_UNORM_S8_UINT;
		case DXGI_FORMAT_D32_FLOAT_S8X24_UINT: return ashes::Format::eD32_SFLOAT_S8_UINT;
		case DXGI_FORMAT_BC1_UNORM: return ashes::Format::eBC1_RGB_UNORM_BLOCK;
		case DXGI_FORMAT_BC1_UNORM_SRGB: return ashes::Format::eBC1_RGB_SRGB_BLOCK;
		case DXGI_FORMAT_BC2_UNORM: return ashes::Format::eBC2_UNORM_BLOCK;
		case DXGI_FORMAT_BC2_UNORM_SRGB: return ashes::Format::eBC2_SRGB_BLOCK;
		case DXGI_FORMAT_BC3_UNORM: return ashes::Format::eBC3_UNORM_BLOCK;
		case DXGI_FORMAT_BC3_UNORM_SRGB: return ashes::Format::eBC3_SRGB_BLOCK;
		case DXGI_FORMAT_BC4_UNORM: return ashes::Format::eBC4_UNORM_BLOCK;
		case DXGI_FORMAT_BC4_SNORM: return ashes::Format::eBC4_SNORM_BLOCK;
		case DXGI_FORMAT_BC5_UNORM: return ashes::Format::eBC5_UNORM_BLOCK;
		case DXGI_FORMAT_BC5_SNORM: return ashes::Format::eBC5_SNORM_BLOCK;
		case DXGI_FORMAT_BC7_UNORM: return ashes::Format::eBC7_UNORM_BLOCK;
		case DXGI_FORMAT_BC7_UNORM_SRGB: return ashes::Format::eBC7_SRGB_BLOCK;
		case DXGI_FORMAT_AYUV: return ashes::Format::eG8_B8_R8_3PLANE_444_UNORM;
		case DXGI_FORMAT_Y410: return ashes::Format::eG10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16;
		case DXGI_FORMAT_Y416: return ashes::Format::eG16_B16_R16_3PLANE_444_UNORM;
		case DXGI_FORMAT_NV12: return ashes::Format::eG8_B8_R8_3PLANE_420_UNORM;
		case DXGI_FORMAT_P010: return ashes::Format::eG10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16;
		case DXGI_FORMAT_P016: return ashes::Format::eG16_B16_R16_3PLANE_420_UNORM;
		case DXGI_FORMAT_YUY2: return ashes::Format::eG8_B8_R8_3PLANE_422_UNORM;
		case DXGI_FORMAT_Y210: return ashes::Format::eG10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16;
		case DXGI_FORMAT_Y216: return ashes::Format::eG16_B16_R16_3PLANE_422_UNORM;
		default:
			assert( false && "Unsupported pixel format." );
			return ashes::Format::eR8G8B8A8_UNORM;
		}
	}

	BlockSize getBlockSize( ashes::Format format )
	{
		BlockSize result{ { 1u, 1u }, 0u };

		if ( isCompressedFormat( format ) )
		{
			if ( format >= ashes::Format::eBCCompressed_BEGIN
				&& format <= ashes::Format::eEACCompressed_END )
			{
				result.block.width = 4u;
				result.block.height = 4u;
			}
			else
			{
				switch ( format )
				{
				case ashes::Format::eASTC_4x4_UNORM_BLOCK:
				case ashes::Format::eASTC_4x4_SRGB_BLOCK:
					result.block.width = 4u;
					result.block.height = 4u;
					break;
				case ashes::Format::eASTC_5x4_UNORM_BLOCK:
				case ashes::Format::eASTC_5x4_SRGB_BLOCK:
					result.block.width = 5u;
					result.block.height = 4u;
					break;
				case ashes::Format::eASTC_5x5_UNORM_BLOCK:
				case ashes::Format::eASTC_5x5_SRGB_BLOCK:
					result.block.width = 5u;
					result.block.height = 5u;
					break;
				case ashes::Format::eASTC_6x5_UNORM_BLOCK:
				case ashes::Format::eASTC_6x5_SRGB_BLOCK:
					result.block.width = 6u;
					result.block.height = 5u;
					break;
				case ashes::Format::eASTC_6x6_UNORM_BLOCK:
				case ashes::Format::eASTC_6x6_SRGB_BLOCK:
					result.block.width = 6u;
					result.block.height = 6u;
					break;
				case ashes::Format::eASTC_8x5_UNORM_BLOCK:
				case ashes::Format::eASTC_8x5_SRGB_BLOCK:
					result.block.width = 8u;
					result.block.height = 5u;
					break;
				case ashes::Format::eASTC_8x6_UNORM_BLOCK:
				case ashes::Format::eASTC_8x6_SRGB_BLOCK:
					result.block.width = 8u;
					result.block.height = 6u;
					break;
				case ashes::Format::eASTC_8x8_UNORM_BLOCK:
				case ashes::Format::eASTC_8x8_SRGB_BLOCK:
					result.block.width = 8u;
					result.block.height = 8u;
					break;
				case ashes::Format::eASTC_10x5_UNORM_BLOCK:
				case ashes::Format::eASTC_10x5_SRGB_BLOCK:
					result.block.width = 10u;
					result.block.height = 5u;
					break;
				case ashes::Format::eASTC_10x6_UNORM_BLOCK:
				case ashes::Format::eASTC_10x6_SRGB_BLOCK:
					result.block.width = 10u;
					result.block.height = 6u;
					break;
				case ashes::Format::eASTC_10x8_UNORM_BLOCK:
				case ashes::Format::eASTC_10x8_SRGB_BLOCK:
					result.block.width = 10u;
					result.block.height = 8u;
					break;
				case ashes::Format::eASTC_10x10_UNORM_BLOCK:
				case ashes::Format::eASTC_10x10_SRGB_BLOCK:
					result.block.width = 10u;
					result.block.height = 10u;
					break;
				case ashes::Format::eASTC_12x10_UNORM_BLOCK:
				case ashes::Format::eASTC_12x10_SRGB_BLOCK:
					result.block.width = 12u;
					result.block.height = 10u;
					break;
				case ashes::Format::eASTC_12x12_UNORM_BLOCK:
				case ashes::Format::eASTC_12x12_SRGB_BLOCK:
					result.block.width = 12u;
					result.block.height = 12u;
					break;
				default:
					assert( false && "Unsupported pixel format." );
					break;
				}
			}
		}

		result.size = getSize( result.block, format );
		return result;
	}
}
