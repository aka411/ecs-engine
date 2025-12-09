#pragma once
#include <vector>

#include "chunk_array_view.h"




namespace ECS
{
	struct ArchetypeChunkHeader;
	class ComponentRegistry;


	class Query
	{
	private:

		std::vector<ArchetypeChunkHeader*> m_archetypeChunkHeaders;
		std::vector<ChunkArrayView> m_chunkArrayViews;

	public:


		Query();

		
		void addArchetypeChunkHeaders(std::vector<ArchetypeChunkHeader*> archetypeChunkHeaders,const ComponentRegistry& componentRegistry);

		std::vector<ChunkArrayView>& getChunkArrayViews();


	};
}