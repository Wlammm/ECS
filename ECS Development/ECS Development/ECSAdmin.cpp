#include "ECSAdmin.h"
#define USE_PIX
#include "pix3.h"
#include <string>
#include "ECSRegistration.h"

ECSAdmin* ECSAdmin::ourInstance = nullptr;

ECSAdmin::~ECSAdmin()
{
	delete myComponentManager;
	myComponentManager = nullptr;

	delete myEntityManager;
	myEntityManager = nullptr;

	delete mySystemManager;
	mySystemManager = nullptr;
}

void ECSAdmin::Init()
{
	myComponentManager = new ComponentManager();
	myEntityManager = new EntityManager();
	mySystemManager = new SystemManager();

	ECS::RegisterComponents();
	ECS::RegisterSystems();
}

Entity ECSAdmin::CreateEntity()
{
	return myEntityManager->CreateEntity();
}

void ECSAdmin::DestroyEntity(Entity anEntity)
{
	myEntityManager->DestroyEntity(anEntity);

	myComponentManager->EntityDestroyed(anEntity);
}

void ECSAdmin::Update()
{
	for (auto& sys : mySystemManager->GetSystems())
	{
		PIXScopedEvent(PIX_COLOR(0, 255, 255), sys.first.c_str());
		sys.second->Update();
	}
}
