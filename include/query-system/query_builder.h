#pragma once
#include "query-system/query.h"



namespace ECS
{
	class ComponentRegistry;
	class ArchetypeManager;

	class QueryBuilder
	{

	private:

		ComponentRegistry& m_componentRegistry;
		ArchetypeManager& m_archetypeManager;

	
		ArchetypeSignature m_mustHaveMask = 0;
		ArchetypeSignature m_mustNotHaveMask = 0;

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
		(m_mustHaveMask.set(m_componentRegistry.getComponentIdFromComponent<ComponentType>()), ...);

		return *this;
	}



	template<typename ...ComponentType>
	inline QueryBuilder& QueryBuilder::without()
	{
		(m_mustNotHaveMask.set(m_componentRegistry.getComponentIdFromComponent<ComponentType>()), ...);

		return *this;
	}

}
