#include "Descriptor/D3D11DescriptorSetLayout.hpp"

#include "Core/D3D11Device.hpp"

namespace d3d11_renderer
{
	DescriptorSetLayout::DescriptorSetLayout( Device const & device
		, ashes::DescriptorSetLayoutBindingArray bindings )
		: ashes::DescriptorSetLayout{ device, std::move( bindings ) }
	{
	}

	DescriptorSetLayout::~DescriptorSetLayout()
	{
	}
}
