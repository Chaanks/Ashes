/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#include "Ashes/Descriptor/DescriptorSetLayout.hpp"

#include "Ashes/Core/Device.hpp"
#include "Ashes/Core/Exception.hpp"
#include "Ashes/Core/Instance.hpp"
#include "Ashes/Descriptor/DescriptorSetPool.hpp"

#include <algorithm>

namespace ashes
{
	DescriptorSetLayout::DescriptorSetLayout( Device const & device
		, DescriptorSetLayoutBindingArray bindings )
		: m_device{ device }
		, m_bindings{ std::move( bindings ) }
	{
		auto it = std::find_if( m_bindings.begin()
			, m_bindings.end()
			, []( DescriptorSetLayoutBinding const & lookup )
			{
				return lookup.getDescriptorType() == DescriptorType::eStorageImage
					|| lookup.getDescriptorType() == DescriptorType::eStorageTexelBuffer;
			} );

		if ( it != m_bindings.end()
			&& !device.getInstance().getFeatures().hasImageTexture )
		{
			throw Exception{ Result::eErrorFeatureNotPresent, "Image storage" };
		}

		registerObject( m_device, "DescriptorSetLayout", this );
	}

	DescriptorSetLayout::~DescriptorSetLayout()
	{
		unregisterObject( m_device, this );
	}

	DescriptorSetLayoutBinding const & DescriptorSetLayout::getBinding( uint32_t bindingPoint
		, uint32_t index )const
	{
		auto it = std::find_if( m_bindings.begin()
			, m_bindings.end()
			, [bindingPoint, index]( DescriptorSetLayoutBinding const & lookup )
		{
			return lookup.getBindingPoint() == bindingPoint
				&& index < lookup.getDescriptorsCount();
		} );

		if ( it == m_bindings.end() )
		{
			throw std::range_error{ "Descriptor set layout binding was not found." };
		}

		return *it;
	}

	ashes::DescriptorSetPoolPtr DescriptorSetLayout::createPool( uint32_t maxSets
		, bool automaticFree )const
	{
		return std::make_unique< DescriptorSetPool >( m_device
			, *this
			, maxSets
			, automaticFree );
	}
}
