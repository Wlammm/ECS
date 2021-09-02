#pragma once

#include "Types.hpp"
#include <array>
#include <cassert>
#include <queue>

class EntityManager
{
public:
	EntityManager()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			myAvailableEntities.push(entity);
		}
	}

	Entity CreateEntity()
	{
		assert(myLivingEntityCount < MAX_ENTITIES && "Entity limit exceeded.");

		Entity id = myAvailableEntities.front();
		myAvailableEntities.pop();
		++myLivingEntityCount;

		return id;
	}

	void DestroyEntity(Entity anEntity)
	{
		assert(anEntity < MAX_ENTITIES && "Entity out of range.");

		mySignatures[anEntity].reset();
		myAvailableEntities.push(anEntity);
		--myLivingEntityCount;
	}

	void SetSignature(Entity anEntity, Signature aSignature)
	{
		assert(anEntity < MAX_ENTITIES && "Entity out of range.");

		mySignatures[anEntity] = aSignature;
	}

	Signature GetSignature(Entity anEntity)
	{
		assert(anEntity < MAX_ENTITIES && "Entity out of range.");

		return mySignatures[anEntity];
	}

private:
	std::queue<Entity> myAvailableEntities{};
	std::array<Signature, MAX_ENTITIES> mySignatures{};
	int myLivingEntityCount{};

};