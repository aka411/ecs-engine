#pragma once
#include <cstdint>
#include <functional>
#include <bitset>

namespace ECS
{


	using ComponentId = int16_t;



	struct EntityId
	{

		size_t id = 0; // unique identifier for the entity
		uint16_t generation = 0; // generation number to handle entity reuse

		bool operator==(const EntityId& other) const
		{
			// Two EntityIds are the same ONLY if both their ID and generation match.
			return id == other.id && generation == other.generation;
		}
	};





	struct ComponentTypeInfo
	{




		ComponentId componentId = 0;

		size_t size = 0;
		size_t alignment = 0;

		std::function<void(void*)> constructor = nullptr; // Function to construct the component
		std::function<void(void*)> destructor = nullptr; // Function to destruct the component

		//dest , src
		std::function<void(void*, const void*)> copyConstructor = nullptr; // Function to copy construct the component
		std::function<void(void*, void*)> moveConstructor = nullptr; // Function to move construct the component

	};



	constexpr size_t MAX_COMPONENTS = 100;
	using ComponentFilter = std::bitset<MAX_COMPONENTS>;
	using ArchetypeSignature = std::bitset<MAX_COMPONENTS>;
}