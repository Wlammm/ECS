#include <iostream>
#include "WriterComponent.h"
#include "WriterSystem.h"
#include "ECSAdmin.hpp"

void WriterSystem::Init()
{
	ECSAdmin* admin = ECSAdmin::GetInstance();
	Signature signature;
	signature.set(admin->GetComponentType<Writer>());
	admin->SetSystemSignature<WriterSystem>(signature);
}

void WriterSystem::Update()
{
	ECSAdmin* admin = ECSAdmin::GetInstance();

	for (auto const& entity : myEntities)
	{
		auto& w = admin->GetComponent<Writer>(entity);

		std::cout << w.text << std::endl;
	}
}
