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
	T& RegisterSingletonComponent()
	{
		std::string typeName = typeid(T).name();

		assert(myComponentTypes.find(typeName) == myComponentTypes.end() && "Component type already registered.");

		myComponentTypes.insert({ typeName, myNextComponentType });
		myComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		mySingletonComponents.emplace_back(myNextComponentType);
		++myNextComponentType;

		T t = T{};
		AddComponent(SINGLETON_COMPONENT_INDEX, t);

		return GetComponent<T>(SINGLETON_COMPONENT_INDEX);
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
	bool IsSingletonComponent()
	{
		ComponentType type = GetComponentType<T>();
		return (std::find(mySingletonComponents.begin(), mySingletonComponents.end(), type) != mySingletonComponents.end());
	}

	template<typename T>
	void RemoveComponent(Entity anEntity)
	{
		GetComponentArray<T>()->Removedata(anEntity);
	}

	template<typename T>
	T& GetComponent(Entity anEntity)
	{
		ComponentType type = GetComponentType<T>();
		if (std::find(mySingletonComponents.begin(), mySingletonComponents.end(), type) != mySingletonComponents.end())
		{
			return GetComponentArray<T>()->GetData(SINGLETON_COMPONENT_INDEX);
		}

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
	std::vector<ComponentType> mySingletonComponents;
	ComponentType myNextComponentType{ 1 };

	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		std::string typeName = typeid(T).name();

		assert(myComponentTypes.find(typeName) != myComponentTypes.end() && "COmponent not registered.");

		return std::static_pointer_cast<ComponentArray<T>>(myComponentArrays[typeName]);
	}
};
