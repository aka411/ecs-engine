#pragma once
#include "ecs_data_types.h"
#include "archetype_manager.h"
#include "entity_manager.h"
#include "query-system/query_system.h"
#include "command_buffer.h"
#include "command_processor.h"
#include "common_data_types.h"

#include "i_fatal_error_handler.h"



namespace ECS
{
	class ComponentRegistry;
	class IFatalErrorHandler;
	class ECSInternalManager
	{

	private:
	


		ComponentRegistry& m_componentRegistry;

		EntityManager		 m_entityManager;
		ArchetypeManager	 m_archetypeManager;

		CommandBuffer		 m_commandBuffer;
		CommandProcessor	 m_commandProcessor;

		QuerySystem			 m_querySystem;


		void addComponntDataToEntity(std::vector<EntityAddInfo>& m_entityAddInfos);
		void processDestructionOfEntities(std::vector<EntityId>& m_entityIdsToBeDestroyed);

	public:

		ECSInternalManager(IFatalErrorHandler& fatalErrorHandler, ComponentRegistry& componentRegistry);

		EntityId createEntity();

		CommandBuffer& getCommandBuffer();
		CommandProcessor& getCommandProcessor();

		void processBufferedCommands();


		QueryBuilder createQueryBuilder();
		EntityChunkView getEntityChunkView(const EntityId& entityId);

	};



}