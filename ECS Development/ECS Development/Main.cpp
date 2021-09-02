#include "Types.hpp"
#include <iostream>
#include "ECSAdmin.hpp"
#include "WriterSystem.h"
#include "WriterComponent.h"
#include "PlayerComponent.h"
#include "PlayerSystem.h"

int main()
{
	ECSAdmin* admin = new ECSAdmin();
	admin->Init();

	admin->RegisterComponent<Writer>();
	admin->RegisterComponent<Player>();

	auto writerSystem = admin->RegisterSystem<WriterSystem>();
	{
		Signature signature;
		signature.set(admin->GetComponentType<Writer>());
		admin->SetSystemSignature<WriterSystem>(signature);
	}
	writerSystem->Init();

	auto playerSystem = admin->RegisterSystem<PlayerSystem>();
	{
		Signature signature;
		signature.set(admin->GetComponentType<Player>());
		signature.set(admin->GetComponentType<Writer>());
		admin->SetSystemSignature<PlayerSystem>(signature);
	}


	Entity e = admin->CreateEntity();
	admin->AddComponent(e, Writer{"weewjkfdls"});
	
	e = admin->CreateEntity();
	admin->AddComponent(e, Writer{ "Hello." });
	admin->AddComponent(e, Player{ "Pontus" });

	while (true)
	{
		writerSystem->Update();
		playerSystem->Update();
	}

	return 0;
}