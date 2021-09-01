#pragma once

#include <vector>
#include <array>
#include <typeindex>
#include <map>
#include <iostream>
#include "ObjectPool.hpp"
#include "SSet.h"
#include <any>
#include "Component.h"

using Entity = unsigned int;
#define MaxComponentCount 128

class ECSAdmin
{
public:
	ECSAdmin() = default;
	~ECSAdmin() = default;

	void Update();

	Entity CreateEntity();

	template<typename T>
	void AddComponent(const Entity& anEntity, Component* aComponent);

	//template<typename T>
	//T* GetComponent(const Entity& anEntity);

private:
	std::vector<Entity> myActiveEntities;
	std::map<std::type_index, CU::ObjectPool<Component*>> myComponents;

	Entity myNextEntityID = 0;
};

template<typename T>
inline void ECSAdmin::AddComponent(const Entity& anEntity, Component* aComponent)
{
	std::type_index typeID = typeid(T);

	if (!myComponents[typeID].IsInitialized())
	{
		CU::ObjectPool<Component*> pool = CU::ObjectPool<Component*>(MaxComponentCount);
		myComponents[typeID] = pool;
	}

	myComponents[typeID].GetNextFree()->Value() = aComponent;
}