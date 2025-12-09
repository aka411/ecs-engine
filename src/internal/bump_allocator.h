#pragma once
#include <vector>
#include <cstdint>


namespace ECS
{



	// This is not fully implemented and currently it just uses aligned_malloc internally

	struct AllocatedBlockInfo
	{
		size_t sizeOfAllocatedMemory = 0;
		void* basePtr = nullptr;

	};

	class BumpAllocator
	{

	private:
		std::vector<AllocatedBlockInfo> m_usedUpAllocatedMemoryBlocks;

		std::vector<void*> m_allocatedBlocks;

		AllocatedBlockInfo m_currentAllocatedBlockInfo;

		size_t m_currentUsedSize = 0;


		AllocatedBlockInfo getNewFreeBlock(); // affects m_currentAllocatedBlockInfo
		void setNextFreeBlock();
		size_t getRequiredPadding(const std::uintptr_t address, const size_t alignment);

	public:
		void* allocateAligned(size_t size, size_t alignment);
		void reset();

	};
}