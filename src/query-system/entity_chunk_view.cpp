#include <cassert>

#include "query-system/entity_chunk_view.h"
#include "common_data_types.h"


namespace ECS
{

	bool EntityChunkView::archetypeDefinitionHasComponent(const ComponentId componentId) const
	{
		return m_archetypeDefinition->hasComponent(componentId);
	}

	size_t EntityChunkView::getComponentOffset(const ComponentId componentTypeId) const
	{
		return m_archetypeDefinition->getComponentOffset(componentTypeId);
	}

	EntityChunkView::EntityChunkView(const EntityRecord& entityRecord, const ComponentRegistry& componentRegistry) : m_componentRegistry(componentRegistry)
	{
		assert(entityRecord.archetypeChunkHeader != nullptr);
		assert(entityRecord.archetypeChunkHeader->archetypeDefinition != nullptr);


		m_archetypeDefinition = entityRecord.archetypeChunkHeader->archetypeDefinition;
		m_offsetIndex = entityRecord.indexInArchetypeChunkRecordList;

		m_chunkBaseAddress = reinterpret_cast<std::uintptr_t>(entityRecord.archetypeChunkHeader->archetypeChunk);
		m_archetypeChunkSize = entityRecord.archetypeChunkHeader->archetypeDefinition->chunkRawSize;

	};



}