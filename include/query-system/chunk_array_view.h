#pragma once
#include <cstdint>

#include "ecs_data_types.h"
#include "component_registry.h"



namespace ECS
{
	//class ComponentRegistry;
	struct ArchetypeDefinition;
	struct ArchetypeChunkHeader;

	class ChunkArrayView
	{
	private:
		const ComponentRegistry& m_componentRegistry;

		size_t m_entityCount = 0;
		size_t m_archetypeChunkSize = 0;

		ArchetypeDefinition* m_archetypeDefinition = nullptr;

		std::uintptr_t m_chunkBaseAddress = 0;
		std::uintptr_t m_chunkRecordBaseAddress = 0;

		bool archetypeDefinitionHasComponent(const ComponentId componentId) const;
		size_t getComponentOffset(const ComponentId componentTypeId) const;

	public:

	

		ChunkArrayView(ArchetypeChunkHeader* archetypeChunkHeader, const ComponentRegistry& componentRegistry);

		const size_t getCount() const;

		const EntityId* getChunkRecordArray() const;

		template<typename ComponentType>
		ComponentType* getComponentArray();

	};



	template<typename ComponentType>
	ComponentType* ChunkArrayView::getComponentArray()
	{
		ComponentId componentId = m_componentRegistry.getComponentIdFromComponent<ComponentType>();

		//make a function
		if(!archetypeDefinitionHasComponent(componentId))
		{
			return nullptr;
		}

		std::uintptr_t componentAddress = m_chunkBaseAddress + getComponentOffset(componentId);
		assert(componentAddress < m_chunkBaseAddress + m_archetypeChunkSize);
		return reinterpret_cast<ComponentType*>(componentAddress);
	}




}