#pragma once
#include <vector>
#include "chunk_array_view.h"

namespace TheEngine::ECS
{
	class Query
	{
	private:

		std::vector<ArchetypeChunkHeader*> m_archetypeChunkHeaders;
		std::vector<ChunkArrayView> m_chunkArrayViews;

	public:
		//may be i should keep it in query builder?
		ArchetypeSignature mustHaveMask = 0;
		ArchetypeSignature mustNotHaveMask = 0;

		Query();

		
		void addArchetypeChunkHeaders(std::vector<ArchetypeChunkHeader*> archetypeChunkHeaders,const ComponentRegistry& componentRegistry);

		std::vector<ChunkArrayView>& getChunkArrayViews();


	};
}