#include "ecs_internal_manager.h"
#include "component_registry.h"


namespace ECS
{


	void ECSInternalManager::processDestructionOfEntities(std::vector<EntityId>& m_entityIdsToBeDestroyed)
	{

		for (const EntityId& entityId : m_entityIdsToBeDestroyed)
		{

			//ToDo : Need to write code here and in Archetype Manager also

		}



	}

	void ECSInternalManager::addComponntDataToEntity(std::vector<EntityAddInfo>& entityAddInfos)
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





	ECS::ECSInternalManager::ECSInternalManager(IFatalErrorHandler& fatalErrorHandler, ComponentRegistry& componentRegistry) :
		m_componentRegistry(componentRegistry),
		m_entityManager(),
		m_archetypeManager(m_componentRegistry, fatalErrorHandler),
		m_commandProcessor(m_entityManager),
		m_querySystem(m_componentRegistry, m_entityManager, m_archetypeManager)
	{



	}
	
	void ECSInternalManager::processBufferedCommands()
	{

		std::unordered_map<EntityId, std::vector<Command>>& entityIdToCommands = m_commandBuffer.getCommandList();
		m_commandProcessor.process(entityIdToCommands);
		std::vector<EntityAddInfo>& entityAddInfos = m_commandProcessor.getEntityAddInfos();

		addComponntDataToEntity(entityAddInfos);
		m_commandProcessor.reset();
		m_commandBuffer.reset();
	}

	EntityId ECSInternalManager::createEntity()
	{
		return m_entityManager.createEntity();
	}

	CommandBuffer& ECSInternalManager::getCommandBuffer()
	{
		return m_commandBuffer;
	}

	CommandProcessor& ECSInternalManager::getCommandProcessor()
	{
		return m_commandProcessor;
	}



	QueryBuilder ECSInternalManager::createQueryBuilder()
	{
		return QueryBuilder(m_componentRegistry, m_archetypeManager);
	}

	EntityChunkView ECSInternalManager::getEntityChunkView(const EntityId& entityId)
	{
		return m_querySystem.getEntityChunkView(entityId);

	}



}