#pragma once
#include <stdint.h>


#include "query-system/query_builder.h"
#include "component_registry.h"


#include "query-system/entity_chunk_view.h"


namespace ECS
{

	class ComponentRegistry;
	class EntityManager;
	class ArchetypeManager;


	class QuerySystem
	{

	private:

		 ComponentRegistry& m_componentRegistry;
		 EntityManager& m_entityManager;
		 ArchetypeManager& m_archetypeManager;

	public:

		QuerySystem(ComponentRegistry& componentRegistry, EntityManager& entityManager, ArchetypeManager& archetypeManager);
		
		/* Depreciated Method */
		//template<typename... ComponentType>
		//inline Query getQuery();


		QueryBuilder createQuery();

		EntityChunkView getEntityChunkView(const EntityId& entityId);

	
	
	};



	/*

	template<typename... ComponentType>
	inline Query QuerySystem::getQuery()
	{

		//process here 
		ArchetypeSignature neededArchtypeSignatureMask;

		(neededArchtypeSignatureMask.set(m_componentRegistry.getComponentIdFromComponent<ComponentType>()), ...);

		const std::unordered_map<ArchetypeSignature, std::unique_ptr<ArchetypeDefinition>>& archetypeDefinitions = m_archetypeManager.getArchetypeDefinitions();

		//std::unordered_map<ArchetypeDefinition*, std::vector<ArchetypeChunkHeader*>> archetypeDefintionsToArchetypeChunkHeaders;
		Query query;


		for (const auto& it : archetypeDefinitions)
		{
			ArchetypeSignature archetypeSignature = it.first;

			
			if ((archetypeSignature & neededArchtypeSignatureMask) == neededArchtypeSignatureMask)
			{
				query.addArchetypeChunkHeaders(m_archetypeManager.getArchetypeChunksWithEntityData(archetypeSignature),m_componentRegistry);
			}

		}

		return query;
	}
	*/
}
