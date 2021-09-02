#pragma once

#include <assert.h>
#include <array>
#include <unordered_map>
#include "Types.hpp"

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity anEntity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
	void InsertData(Entity anEntity, T aComponent)
	{
		assert(myEntityToIndexMap.find(anEntity) == myEntityToIndexMap.end() && "Component already exists on entity.");

		int newIndex = mySize;
		myEntityToIndexMap[anEntity] = newIndex;
		myIndexToEntityMap[newIndex] = anEntity;
		myComponentArray[newIndex] = aComponent;
		mySize++;
	}

	void RemoveData(Entity anEntity)
	{
		assert(myEntityToIndexMap.find(anEntity) != myEntityToIndexMap.end() && "Entity does not exists.");

		int indexOfRemovedEntity = myEntityToIndexMap[anEntity];
		int indexOfLastElement = mySize - 1;
		myComponentArray[indexOfRemovedEntity] = myComponentArray[indexOfLastElement];

		Entity entityOfLastElement = myIndexToEntityMap[indexOfLastElement];
		myEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		myIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		myEntityToIndexMap.erase(anEntity);
		myIndexToEntityMap.erase(indexOfLastElement);
	}

	T& GetData(Entity anEntity)
	{
		assert(myEntityToIndexMap.find(anEntity) != myEntityToIndexMap.end() && "Component does not exist on entity.");

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
	std::unordered_map<Entity, int> myEntityToIndexMap{};
	std::unordered_map<int, Entity> myIndexToEntityMap{};
	int mySize{};
};