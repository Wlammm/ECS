#include "Types.hpp"
#include <iostream>
#include "ECSAdmin.hpp"
#include "WriterSystem.h"
#include "WriterComponent.h"
#include "PlayerComponent.h"
#include "PlayerSystem.h"

void RegisterSystems()
{
	ECSAdmin* admin = ECSAdmin::GetInstance();
	admin->RegisterSystem<PlayerSystem>();
	admin->RegisterSystem<WriterSystem>();
}

void RegisterComponents()
{
	ECSAdmin* admin = ECSAdmin::GetInstance();
	admin->RegisterComponent<Writer>();
	admin->RegisterComponent<Player>();
}

int main()
{
	ECSAdmin* admin = new ECSAdmin();
	admin->Init();

	RegisterComponents();
	RegisterSystems();

	Entity e = admin->CreateEntity();
	admin->AddComponent(e, Writer{"weewjkfdls"});
	
	e = admin->CreateEntity();
	admin->AddComponent(e, Writer{ "Hello." });
	admin->AddComponent(e, Player{ "Pontus" });

	while (true)
	{
		admin->Update();
	}

	return 0;
}