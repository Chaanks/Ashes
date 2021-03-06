#include "Descriptor/VkDescriptorPool.hpp"

#include "Descriptor/VkDescriptorSet.hpp"
#include "Descriptor/VkDescriptorSetLayout.hpp"
#include "Descriptor/VkDescriptorSetLayoutBinding.hpp"
#include "Core/VkDevice.hpp"

namespace vk_renderer
{
	DescriptorPool::DescriptorPool( Device const & device
		, ashes::DescriptorPoolCreateFlags flags
		, uint32_t maxSets
		, ashes::DescriptorPoolSizeArray poolSizes )
		: ashes::DescriptorPool{ device, flags }
		, m_device{ device }
	{
		std::vector< VkDescriptorPoolSize > vkpoolSizes;

		for ( auto const & poolSize : poolSizes )
		{
			vkpoolSizes.push_back(
			{
				convert( poolSize.type ),
				poolSize.descriptorCount
			} );
		}

		VkDescriptorPoolCreateInfo createInfo
		{
			VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,      // sType
			nullptr,                                            // pNext
			convert( flags ),                                   // flags
			maxSets,                                            // maxSets
			uint32_t( vkpoolSizes.size() ),                     // poolSizeCount
			vkpoolSizes.data()                                  // pPoolSizes
		};
		DEBUG_DUMP( createInfo );
		auto res = m_device.vkCreateDescriptorPool( m_device
			, &createInfo
			, nullptr
			, &m_pool );
		checkError( res, "DescriptorPool creation" );
	}

	DescriptorPool::~DescriptorPool()
	{
		m_device.vkDestroyDescriptorPool( m_device, m_pool, nullptr );
	}

	ashes::DescriptorSetPtr DescriptorPool::createDescriptorSet( ashes::DescriptorSetLayout const & layout
		, uint32_t bindingPoint )const
	{
		return std::make_unique< DescriptorSet >( m_device
			, *this
			, static_cast< DescriptorSetLayout const & >( layout )
			, bindingPoint );
	}
}
