#include "PlayerSystem.h"
#include <iostream>
#include "ECSAdmin.hpp"
#include "WriterComponent.h"
#include "PlayerComponent.h"

void PlayerSystem::Update()
{
	ECSAdmin* admin = ECSAdmin::GetInstance();

	for (auto& entity : myEntities)
	{
		auto writer = admin->GetComponent<Writer>(entity);
		auto player = admin->GetComponent<Player>(entity);

		std::cout << player.name << ": " << writer.text << std::endl;
		
	}
}