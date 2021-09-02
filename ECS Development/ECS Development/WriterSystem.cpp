#include <iostream>
#include "WriterComponent.h"
#include "WriterSystem.h"
#include "ECSAdmin.hpp"

void WriterSystem::Init()
{

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
