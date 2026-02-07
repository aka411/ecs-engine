#include "ecs_engine.h"
#include "command_buffer.h"
#include "ecs_internal_manager.h"

namespace ECS
{





	void ECSEngine::storeAddComponentCommand(const EntityId& entityId, const ComponentId componentId, void* ptr)
	{

		Command command;
		command.commandType = CommandType::ADD_COMPONENT;
		command.componentId = componentId;
		command.ptr = ptr;

		//owner if the data the pointer points to is Component Registry and is managed by unique pointer so no dangling pointers
		ComponentTypeInfo* componentTypeInfo = m_componentRegistry.getComponentTypeInfo(command.componentId);
		
		m_ecsInternalManager.get()->getCommandBuffer().storeCommand(entityId, command, componentTypeInfo);

	}


	ECSEngine::ECSEngine(IFatalErrorHandler& fatalErrorHandler) :
		m_fatalErrorHandler(fatalErrorHandler)
	{
		m_ecsInternalManager = std::make_unique<ECSInternalManager>(fatalErrorHandler,m_componentRegistry);
	}




	EntityId ECSEngine::createEntity()
	{
		return m_ecsInternalManager.get()->createEntity();
	}


	void ECSEngine::destroyEntity(EntityId& entityId)
	{
		Command command;
		command.commandType = CommandType::DESTROY_ENTITY;
		command.componentId = 0;// Might need to consider a null component Id.
		command.ptr = nullptr;

		m_ecsInternalManager.get()->getCommandBuffer().storeCommand(entityId, command, nullptr);


	}



	void  ECSEngine::processBufferedCommands()
	{

			m_ecsInternalManager.get()->processBufferedCommands();


	}





	QueryBuilder ECSEngine::createQuery()
	{
		
		return m_ecsInternalManager.get()->createQueryBuilder();
	}




	EntityChunkView ECSEngine::getEntityChunkView(const EntityId& entityId)
	{
		return m_ecsInternalManager.get()->getEntityChunkView(entityId);

	}


	ECSEngine::~ECSEngine()
	{

	}

}