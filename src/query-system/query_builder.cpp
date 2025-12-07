#include <query-system/query_builder.h>






namespace TheEngine::ECS
{



	QueryBuilder::QueryBuilder(ComponentRegistry& componentRegistry, ArchetypeManager& archetypeManager):
		m_componentRegistry(componentRegistry),
		m_archetypeManager(archetypeManager)
	{

	}

	Query QueryBuilder::build()
	{
		const std::unordered_map<ArchetypeSignature, std::unique_ptr<ArchetypeDefinition>>& archetypeDefinitions = m_archetypeManager.getArchetypeDefinitions();

		//std::unordered_map<ArchetypeDefinition*, std::vector<ArchetypeChunkHeader*>> archetypeDefintionsToArchetypeChunkHeaders;
		


		for (const auto& it : archetypeDefinitions)
		{
			ArchetypeSignature archetypeSignature = it.first;


			if ((archetypeSignature & m_query.mustHaveMask) != m_query.mustHaveMask)
			{
				continue;
			}

			//need to look into this
			if ((archetypeSignature & m_query.mustNotHaveMask).any())
			{
				continue;
			}



			m_query.addArchetypeChunkHeaders(m_archetypeManager.getArchetypeChunksWithEntityData(archetypeSignature), m_componentRegistry);

		}

		return m_query;



	}

}