#include "ECSAdmin.h"

void ECSAdmin::Update()
{
}

Entity ECSAdmin::CreateEntity()
{
	myActiveEntities.push_back(myNextEntityID);

	Entity retEnt = myNextEntityID;
	myNextEntityID++;
	return retEnt;
}
