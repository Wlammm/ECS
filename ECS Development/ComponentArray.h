#pragma once

#include "Types.h"
#include <array>
#include <cassert>
#include <unordered_map>

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
	void InsertData(Entity anEntity, T aComponent)
	{
		assert(myEntityToIndexMap.find(anEntity) == myEntityToIndexMap.end() && "Multiple components on same entity.");

		size_t newIndex = mySize;
		myEntityToIndexMap[anEntity] = newIndex;
		myIndexToEntityMap[newIndex] = anEntity;
		myComponentArray[newIndex] = aComponent;
		++mySize;
	}

	void RemoveData(Entity anEntity)
	{
		assert(myEntityToIndexMap.find(anEntity) != myEntityToIndexMap.end() && "Component does not exists..");

		size_t indexOfRemovedEntity = myEntityToIndexMap[anEntity];
		size_t indexOfLastElement = mySize - 1;
		myComponentArray[indexOfRemovedEntity] = myComponentArray[indexOfLastElement];

		Entity entityOfLastElement = myIndexToEntityMap[indexOfLastElement];
		myEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		myIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		myEntityToIndexMap.erase(anEntity);
		myIndexToEntityMap.erase(indexOfLastElement);

		--mySize;
	}

	T& GetData(Entity anEntity)
	{
		assert(myEntityToIndexMap.find(anEntity) != myEntityToIndexMap.end() && "Retrieving non-existent component.");

		return myComponentArray[myEntityToIndexMap[anEntity]];
	}

	void EntityDestroyed(Entity anEntity) override
	{
		if (myEntityToIndexMap.find(anEntity) != myEntityToIndexMap.end())
		{
			RemoveData(anEntity);
		}
	}

private:
	std::array<T, MAX_ENTITIES> myComponentArray{};
	std::unordered_map<Entity, size_t> myEntityToIndexMap{};
	std::unordered_map<size_t, Entity> myIndexToEntityMap{};
	size_t mySize{};
};