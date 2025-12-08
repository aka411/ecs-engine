#pragma once
#include "query.h"
#include "archetype_manager.h"


namespace TheEngine::ECS
{

	class QueryBuilder
	{

	private:

		ComponentRegistry& m_componentRegistry;
		ArchetypeManager& m_archetypeManager;

		Query m_query;


	public:


		QueryBuilder(ComponentRegistry& componentRegistry, ArchetypeManager& archetypeManager);

		template<typename... ComponentType>
		QueryBuilder& with();

		template<typename... ComponentType>
		QueryBuilder& without();


		Query build();
	};





	template<typename ...ComponentType>
	inline QueryBuilder& QueryBuilder::with()
	{
		(m_query.mustHaveMask.set(m_componentRegistry.getComponentIdFromComponent<ComponentType>()), ...);

		return *this;
	}



	template<typename ...ComponentType>
	inline QueryBuilder& QueryBuilder::without()
	{
		(m_query.mustNotHaveMask.set(m_componentRegistry.getComponentIdFromComponent<ComponentType>()), ...);

		return *this;
	}

}
