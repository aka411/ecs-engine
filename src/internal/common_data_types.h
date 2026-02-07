#pragma once

#include <cstdint>
#include <bitset>
#include <functional>

#include "ecs_data_types.h"

namespace ECS
{
	










	constexpr ArchetypeSignature EMPTY_ARCHETYPE_SIGNATURE = 0;






	struct ComponentData
	{

		ComponentId componentId;

		void* ptr; //pointer to component data in contiguous memory block

	};




	struct ComponentLayout
	{
		ComponentId componentId = 0;

		uint32_t size = 0; //redundant already in ComponentTypeinfo
		uint32_t alignment = 0;//redundant already in ComponentTypeinfo

		size_t offsetInChunk = 0; //offset in chunk memory region

		ComponentTypeInfo* componentTypeInfo = nullptr;


	};


	struct ArchetypeDefinition
	{
		ArchetypeSignature archetypeSignature;

		//should be sorted by alignment then size
		//A map or unordered map would be better
		std::vector<ComponentLayout> componentLayouts;
		std::unordered_map<ComponentId, size_t>  componentIdToComponentOffset;

		size_t chunkRawSize = 0;//total size of ArchetypeChunk the data is stored in for which the offsets are calculated

		size_t chunkMaxEntityCapacity = 0; //how many entities can be stored for this chunkRawSize

		bool hasComponent(ComponentId componentTypeId) const
		{
			return archetypeSignature.test(componentTypeId);
		}

		size_t getComponentOffset(ComponentId componentTypeId) const
		{
			return componentIdToComponentOffset.at(componentTypeId);
		}
	};

	struct ArchetypeChunk
	{

		//uint8_t data[1]; //raw data block ,hacky way to define a flexible array member in C++
		//Gonna use empty struct cause flexible array member is not allowed in C++


	};


	struct ArchetypeRecordChunk
	{
		
		EntityId id[1];//hacky 

	};

	struct ArchetypeChunkHeader
	{
		ArchetypeDefinition* archetypeDefinition = nullptr;//not the owner

		ArchetypeRecordChunk* archetypeRecordChunk = nullptr;//owner
		ArchetypeChunk* archetypeChunk = nullptr; //owner

		size_t chunkEntityUsed = 0; //how many entities are currently stored in this chunk	


	};



	struct EntityRecord
	{

		EntityId entityId;

		ArchetypeSignature archetypeSignature = EMPTY_ARCHETYPE_SIGNATURE;
		ArchetypeChunkHeader* archetypeChunkHeader = nullptr; //pointer to the chunk where entity data is stored
		uint32_t indexInArchetypeChunkRecordList =  0; //index of the entity within the chunk



	};


	struct EntityAddInfo
	{

		EntityRecord entityRecord;
		ArchetypeSignature newArchetypeSignature = EMPTY_ARCHETYPE_SIGNATURE;
		std::vector<ComponentData> componentDataList;

	};


	struct EntityRecordUpdate
	{
		EntityId entityId;
		ArchetypeChunkHeader* newArchetypeChunkHeader = nullptr;
		uint32_t newIndexInArchetypeChunkRecordList = 0;
	};

}