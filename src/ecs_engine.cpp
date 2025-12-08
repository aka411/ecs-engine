#include "ecs_engine.h"

namespace TheEngine::ECS
{




	ECSEngine::ECSEngine(IFatalErrorHandler& fatalErrorHandler) :
		m_fatalErrorHandler(fatalErrorHandler),
		m_componentRegistry(),
		m_entityManager(),
		m_archetypeManager(m_componentRegistry, fatalErrorHandler),
		m_commandProcessor(m_entityManager),
		m_querySystem(m_componentRegistry, m_entityManager, m_archetypeManager)
	{

	}

	EntityId ECSEngine::createEntity()
	{
		return m_entityManager.createEntity();
	}


	void ECSEngine::destroyEntity(EntityId& entityId)
	{
		Command command;
		command.commandType = CommandType::DESTROY_ENTITY;
		command.componentId = 0;
		command.ptr = nullptr;

		m_commandBuffer.storeCommand(entityId, command, nullptr);


	}


	void ECSEngine::addComponntDataToEntity(std::vector<EntityAddInfo>& entityAddInfos)
	{


		for (const EntityAddInfo& entityAddInfo : entityAddInfos)
		{

			const std::vector<EntityRecordUpdate> EntityRecordUpdates = m_archetypeManager.addComponentToEntity(entityAddInfo);


			for (const EntityRecordUpdate& entityRecordUpdate : EntityRecordUpdates)
			{
				m_entityManager.updateEntityRecord(entityRecordUpdate);
			}

		}



	}

	void  ECSEngine::processBufferedCommands()
	{
		std::unordered_map<EntityId, std::vector<Command>>& entityIdToCommands = m_commandBuffer.getCommandList();
		m_commandProcessor.process(entityIdToCommands);
		std::vector<EntityAddInfo>& entityAddInfos = m_commandProcessor.getEntityAddInfos();

		addComponntDataToEntity(entityAddInfos);
		m_commandProcessor.reset();
		m_commandBuffer.reset();
	}

	void ECSEngine::processDestructionOfEntities(std::vector<EntityId>& m_entityIdsToBeDestroyed)
	{

		for (const EntityId& entityId : m_entityIdsToBeDestroyed)
		{

			//ToDo : Need to write code here and in Archetype Manager also

		}



	}


	QueryBuilder ECSEngine::createQuery()
	{
		return QueryBuilder(m_componentRegistry, m_archetypeManager);
	}




	EntityChunkView ECSEngine::getEntityChunkView(const EntityId& entityId)
	{
		return m_querySystem.getEntityChunkView(entityId);
	}


}