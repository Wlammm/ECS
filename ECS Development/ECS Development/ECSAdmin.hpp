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

	ECSAdmin() = default;

	~ECSAdmin();

	void Init();

	Entity CreateEntity();

	void DestroyEntity(Entity anEntity);

	void Update();

	template<typename T>
	void RegisterComponent()
	{
		myComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	T* RegisterSingletonComponent()
	{
		return myComponentManager->RegisterSingletonComponent<T>();
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
	void AddSingletonComponent(Entity anEntity)
	{
		if (myComponentManager->IsSingletonComponent<T>())
		{
			auto signature = myEntityManager->GetSignature(anEntity);
			signature.set(myComponentManager->GetComponentType<T>(), true);
			myEntityManager->SetSignature(anEntity, signature);

			mySystemManager->EntitySignatureChanged(anEntity, signature);
		}

		assert(false && "Component is not a singleton component or not yet registered!");
	}

	template<typename T>
	void RemoveComponent(Entity anEntity)
	{
		if (!myComponentManager->IsSingletonComponent<T>())
		{
			myComponentManager->RemoveComponent<T>(anEntity);
		}

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