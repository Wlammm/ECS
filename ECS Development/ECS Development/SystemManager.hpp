#pragma once

#include "System.hpp"
#include "Types.hpp"
#include <cassert>
#include <memory>
#include <unordered_map>
#include <string>

class SystemManager
{
public:

	template<typename T>
	T* RegisterSystem()
	{
		std::string typeName = typeid(T).name();

		assert(mySystems.find(typeName) == mySystems.end() && "System already registered.");

		T* system = new T();
		mySystems.insert({ typeName, system });
		return system;
	}

	template<typename T>
	void SetSignature(Signature aSignature)
	{
		std::string typeName = typeid(T).name();

		assert(mySystems.find(typeName) != mySystems.end() && "System is not registered.");

		mySignatures.insert({ typeName, aSignature });
	}

	void EntityDestroyed(Entity anEntity)
	{
		for (auto const& pair : mySystems)
		{
			auto const& system = pair.second;
			system->myEntities.erase(anEntity);
		}
	}

	void EntitySignatureChanged(Entity anEntity, Signature aEntitySignature)
	{
		for (auto const& pair : mySystems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = mySignatures[type];

			if ((aEntitySignature & systemSignature) == systemSignature)
			{
				system->myEntities.insert(anEntity);
			}
			else
			{
				system->myEntities.erase(anEntity);
			}
		}
	}

private:
	std::unordered_map<std::string, Signature> mySignatures;
	std::unordered_map<std::string, System*> mySystems;

};