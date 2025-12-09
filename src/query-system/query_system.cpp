#include "query-system/query_system.h"

#include "entity_manager.h"


namespace ECS
{
	QuerySystem::QuerySystem(ComponentRegistry& componentRegistry,EntityManager& entityManager, ArchetypeManager& archetypeManager) : m_componentRegistry(componentRegistry),m_entityManager(entityManager), m_archetypeManager(archetypeManager)
	{

	};

	QueryBuilder QuerySystem::createQuery()
	{

		return QueryBuilder(m_componentRegistry, m_archetypeManager);
	}

	EntityChunkView QuerySystem::getEntityChunkView(const EntityId& entityId)
	{
		return EntityChunkView(m_entityManager.getEntityRecord(entityId),m_componentRegistry);

	}



};

