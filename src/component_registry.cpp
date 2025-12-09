#include "component_registry.h"
#include <cassert>

namespace ECS
{


	ComponentTypeInfo* ComponentRegistry::getComponentTypeInfo(ComponentId componentId) const
	{

		ComponentTypeInfo* componentTypeInfo = m_componentIdToTypeInfoMap.at(componentId).get();
		assert(componentTypeInfo != nullptr);
		return componentTypeInfo;
	}

}