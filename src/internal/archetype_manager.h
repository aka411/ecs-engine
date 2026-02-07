#pragma once
#include <vector>
#include <unordered_map>
#include <memory>


#include "common_data_types.h"
#include "i_fatal_error_handler.h"


namespace ECS
{


	


	struct ChunkList
	{
		//owner of memory region is allocator
		//full chunks will be full of data
		//availableChunks is the one being filled
		std::vector<ArchetypeChunkHeader*> fullChunks;
		std::vector<ArchetypeChunkHeader*>  availableChunks;
	};


	class IComponentRegistry;

	class ArchetypeManager
	{

		
	private:


		IFatalErrorHandler& m_fatalErrorHandler;


		static const size_t MAX_NUM_OF_ENTITIES_PER_CHUNK = 256; // adjust based on performance testing


		std::unordered_map<ArchetypeSignature, std::unique_ptr<ArchetypeDefinition>> m_archetypeDefinitions;
		std::unordered_map<ArchetypeSignature, ChunkList> m_archetypeChunksMap;

		IComponentRegistry& m_componentRegistry;



		//Methods:
		void* allocateAlignedMemory(const size_t size, const int alignment);
		void deallocateAlignedMemory(void* ptr);


		bool moveArchetypeHeaderChunkToCorrectList(std::vector<ArchetypeChunkHeader*>& destChunkList, std::vector<ArchetypeChunkHeader*>& srcChunkList, ArchetypeChunkHeader* archetypeChunkHeader);
		

		bool moveArchetypeChunkHeaderToAvailableList(ArchetypeChunkHeader* archetypeChunkHeader);
		bool moveArchetypeChunkHeaderToFullList(ArchetypeChunkHeader* archetypeChunkHeader);



		struct MoveResult
		{
			bool moveResult = false;
			EntityRecordUpdate movedEntityRecordUpdate;

			bool entityMovedToFillGap = false;
			EntityRecordUpdate entityMovedToFillGapRecordUpdate;
		};

		MoveResult moveEntityData(ArchetypeChunkHeader* destArchetypeChunkHeader, ArchetypeChunkHeader* srcArchetypeChunkHeader, EntityRecord* entityToBeMovedRecord);


		std::vector<EntityRecordUpdate>  transferAndAddEntityDataToArchetypeChunk(ArchetypeChunkHeader* destArchetypeChunkHeader, ArchetypeChunkHeader* srcArchetypeChunkHeader, EntityAddInfo entityAddInfo);

		EntityRecordUpdate addInitialComponentDataToArchetypeChunk(ArchetypeChunkHeader* archetypeChunkHeader,EntityAddInfo entityAddInfo);


		ArchetypeDefinition* createNewArchetypeDefinition(const ArchetypeSignature& archetypeSignature);

		ArchetypeChunkHeader* createArchetypeChunkHeader(ArchetypeDefinition* archetypeDefinition);

		ArchetypeChunkHeader* createOrGetArchetypeChunk(ArchetypeSignature archetypeSignature);



	public:


		ArchetypeManager(IComponentRegistry& componentRegistry, IFatalErrorHandler& fatalErrorHandler);
		~ArchetypeManager();



		std::vector<EntityRecordUpdate> addComponentToEntity(EntityAddInfo entityAddInfo);




		const std::unordered_map<ArchetypeSignature, std::unique_ptr<ArchetypeDefinition>>& getArchetypeDefinitions() const;
		std::vector<ArchetypeChunkHeader*>  getArchetypeChunksWithEntityData(ArchetypeSignature archetypeSignature);




	};

}