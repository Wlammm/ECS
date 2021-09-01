#pragma once

#include <vector>
#include <array>
#include <typeindex>
#include <map>
#include <iostream>
#include "SSet.h"

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
	void AddComponent(const Entity& anEntity, T& aComponent);

	template<typename T>
	T* GetComponent(const Entity& anEntity);

private:
	std::vector<Entity> myActiveEntities;
	//std::map<std::type_index, std::pair<int, void*>> myComponents;
	std::map<std::type_index, CU::SSet<void*>> myComponents;

	Entity myNextEntityID = 0;
};

template<typename T>
inline void ECSAdmin::AddComponent(const Entity& anEntity, T& aComponent)
{
	std::type_index typeID = typeid(T);

	if (myComponents[typeID].Empty())
	{
		myComponents[typeID] = CU::SSet<void*>();
	}

	myComponents[typeID].Insert(static_cast<void*>(&aComponent));
	// .Insert(aComponent);
}