#pragma once

#include <vector>

#include "i_fatal_error_handler.h"

#include "component_registry.h"


#include "query-system/entity_chunk_view.h"
#include "query-system/query.h"
#include "query-system/query_builder.h"
#include "ecs_data_types.h"
#include <memory>



namespace ECS
{
	class ECSInternalManager;
	class ECSEngine
	{
	private:


		
		IFatalErrorHandler& m_fatalErrorHandler;// passed by user of ecs system

		ComponentRegistry	 m_componentRegistry;//Owner


		std::unique_ptr<ECSInternalManager> m_ecsInternalManager;//Owner

		void storeAddComponentCommand(const EntityId& entityId, const ComponentId componentId, void* ptr);

	public:

		ECSEngine(IFatalErrorHandler& fatalErrorHandler);
		~ECSEngine();

		EntityId createEntity();

		void destroyEntity(EntityId& entityId);

		template<typename ComponentType>
		void addComponentToEntity(const EntityId& entityId, ComponentType& component);


		void processBufferedCommands();

		template<typename DataType>
		ComponentId registerComponent();




		/*** Query System Area ***/

		//For bulk iteration
		QueryBuilder createQuery();

		//For single Entity
		EntityChunkView getEntityChunkView(const EntityId& entityId);


	};




	template<typename DataType>
	ComponentId ECSEngine::registerComponent()
	{
		return m_componentRegistry.registerComponent<DataType>();
	}



	template<typename ComponentType>
	void ECSEngine::addComponentToEntity(const EntityId& entityId, ComponentType& component)
	{
		const ComponentId componentId = m_componentRegistry.getComponentIdFromComponent<ComponentType>();

		storeAddComponentCommand(entityId, componentId, &component);

	}



}