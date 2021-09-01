#pragma once

#include "ComponentArray.h"
#include "Types.h"
#include <any>
#include <memory>
#include <unordered_map>

class ComponentManager
{
public:
	template<typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();

		assert(myComponentTypes.find(typeName) == myComponentTypes.end() && "Registering component type more than once.");

		myComponentTypes.insert({ typeName, myNextComponentType });
		myComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		++myNextComponentType;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();

		assert(myComponentTypes.find(typeName) != myComponentTypes.end() && "Component not registered before use.");

		return myComponentTypes[typeName];
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return GetComponentArray<T>()->GetData(entity);
	}

	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : myComponentArrays)
		{
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}

private:
	std::unordered_map<const char*, ComponentType> myComponentTypes{};
	std::unordered_map<const char*, IComponentArray*> myComponentArrays{};
	ComponentType myNextComponentType{};

	template<typename T>
	ComponentArray<T>* GetComponentArray()
	{
		const char* typeName = typeid(T).name();

		assert(myComponentTypes.find(typeName) != myComponentTypes.end() && "Component not registered before use.");

		return myComponentArrays[typeName];
	}
};