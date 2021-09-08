#include "ECSAdmin.hpp"
#define USE_PIX
#include "pix3.h"
#include <string>

ECSAdmin* ECSAdmin::ourInstance = nullptr;

void ECSAdmin::Update()
{
	for (auto& sys : mySystemManager->GetSystems())
	{
		PIXScopedEvent(PIX_COLOR(0, 255, 255), sys.first.c_str());
		sys.second->Update();
	}
}
