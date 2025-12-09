#pragma once
#include <functional>
#include <typeindex>

#include "ecs_data_types.h"

namespace ECS
{
	
	class IComponentRegistry
	{

	private:

	public:

		virtual ComponentTypeInfo* getComponentTypeInfo(ComponentId componentId) const = 0;

	
	};

}