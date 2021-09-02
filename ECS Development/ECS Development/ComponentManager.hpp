#pragma once

#include "ComponentArray.hpp"
#include "Types.hpp"
#include <any>
#include <memory>
#include <unordered_map>
#include <string>

class ComponentManager
{
public:
	template<typename T>
	void RegisterComponent()
	{
		std::string typeName = typeid(T).name();

		assert(myComponentTypes.find(typeName) == myComponentTypes.end() && "Component type already registered.");

		myComponentTypes.insert({ typeName, myNextComponentType });
		myComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		++myNextComponentType;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		std::string typeName = typeid(T).name();

		assert(myComponentTypes.find(typeName) != myComponentTypes.end() && "Component is not registered.");

		return myComponentTypes[typeName];
	}

	template<typename T>
	void AddComponent(Entity anEntity, T aComponent)
	{
		GetComponentArray<T>()->InsertData(anEntity, aComponent);
	}

	template<typename T>
	void RemoveComponent(Entity anEntity)
	{
		GetComponentArray<T>()->Removedata(anEntity);
	}

	template<typename T>
	T& GetComponent(Entity anEntity)
	{
		return GetComponentArray<T>()->GetData(anEntity);
	}

	void EntityDestroyed(Entity anEntity)
	{
		for (auto const& pair : myComponentArrays)
		{
			auto const& component = pair.second;

			component->EntityDestroyed(anEntity);
		}
	}

private:
	std::unordered_map<std::string, ComponentType> myComponentTypes{};
	std::unordered_map<std::string, std::shared_ptr<IComponentArray>> myComponentArrays{};
	ComponentType myNextComponentType{};

	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		std::string typeName = typeid(T).name();

		assert(myComponentTypes.find(typeName) != myComponentTypes.end() && "COmponent not registered.");

		return std::static_pointer_cast<ComponentArray<T>>(myComponentArrays[typeName]);
	}
};
