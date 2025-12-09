#pragma once
#include <cstdint>

#include "ecs_data_types.h"
#include "component_registry.h"


namespace ECS
{
	
	struct ArchetypeDefinition;
	struct EntityRecord;


	class EntityChunkView
	{
	private:
		const ComponentRegistry& m_componentRegistry;

		size_t m_offsetIndex = 0;

		ArchetypeDefinition* m_archetypeDefinition = nullptr;
		std::uintptr_t m_chunkBaseAddress = 0;
		size_t m_archetypeChunkSize = 0;

		bool archetypeDefinitionHasComponent(const ComponentId componentId) const;
		size_t getComponentOffset(const ComponentId componentTypeId) const;

	public:


		EntityChunkView(const EntityRecord& entityRecord, const ComponentRegistry& componentRegistry);


		template<typename ComponentType>
		ComponentType* getComponent();

	};



	template<typename ComponentType>
	ComponentType* EntityChunkView::getComponent()
	{
		ComponentId componentId = m_componentRegistry.getComponentIdFromComponent<ComponentType>();

		if (!archetypeDefinitionHasComponent(componentId))
		{
			return nullptr;
		}


		std::uintptr_t componentAddress = m_chunkBaseAddress + getComponentOffset(componentId) + sizeof(ComponentType) * m_offsetIndex;
		assert(componentAddress < m_archetypeChunkSize + m_chunkBaseAddress);

		return reinterpret_cast<ComponentType*>(componentAddress);
	}


}