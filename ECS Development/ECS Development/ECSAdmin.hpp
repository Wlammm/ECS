#pragma once

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

class ECSAdmin
{
public:
	static ECSAdmin* GetInstance()
	{
		return ourInstance;
	}

	ECSAdmin()
	{
		ourInstance = this;
	}

	~ECSAdmin()
	{
		delete myComponentManager;
		myComponentManager = nullptr;

		delete myEntityManager;
		myEntityManager = nullptr;

		delete mySystemManager;
		mySystemManager = nullptr;
	}

	void Init()
	{
		myComponentManager = new ComponentManager();
		myEntityManager = new EntityManager();
		mySystemManager = new SystemManager();

		ourInstance = this;
	}

	Entity CreateEntity()
	{
		return myEntityManager->CreateEntity();
	}

	void DestroyEntity(Entity anEntity)
	{
		myEntityManager->DestroyEntity(anEntity);

		myComponentManager->EntityDestroyed(anEntity);
	}


	template<typename T>
	void RegisterComponent()
	{
		myComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(Entity anEntity, T aComponent)
	{
		myComponentManager->AddComponent<T>(anEntity, aComponent);

		auto signature = myEntityManager->GetSignature(anEntity);
		signature.set(myComponentManager->GetComponentType<T>(), true);
		myEntityManager->SetSignature(anEntity, signature);

		mySystemManager->EntitySignatureChanged(anEntity, signature);
	}

	template<typename T>
	void RemoveComponent(Entity anEntity)
	{
		myComponentManager->RemoveComponent<T>(anEntity);

		auto signature = myEntityManager->GetSignature(anEntity);
		signature.set(myComponentManager->GetComponentType<T>(), false);
		myEntityManager->SetSignature(anEntity, signature);

		mySystemManager->EntitySignatureChanged(anEntity, signature);
	}

	template<typename T>
	T& GetComponent(Entity anEntity)
	{
		return myComponentManager->GetComponent<T>(anEntity);
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		return myComponentManager->GetComponentType<T>();
	}

	template<typename T>
	T* RegisterSystem()
	{
		return mySystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature aSignature)
	{
		mySystemManager->SetSignature<T>(aSignature);
	}

private:
	static ECSAdmin* ourInstance;

	ComponentManager* myComponentManager = nullptr;
	EntityManager* myEntityManager = nullptr;
	SystemManager* mySystemManager = nullptr;
};