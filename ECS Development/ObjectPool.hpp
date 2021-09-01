#pragma once

#include <assert.h>

namespace CommonUtilities
{
	template<typename T>
	class PoolResource
	{
	public:
		PoolResource() = default;
		~PoolResource() = default;

		T& Value() { return myObject; }
		bool IsFree() { return myIsFree; }
		void SetFree(bool aState)
		{
			myIsFree = aState;
		}

	private:
		T myObject;
		bool myIsFree = true;
	};

	template<typename T>
	class ObjectPool
	{
	public:
		ObjectPool()
		{
			myResources = nullptr;
			mySize = 0;
		}

		ObjectPool(int aSize)
		{
			mySize = aSize;
			myResources = new PoolResource<T>[aSize];
		}

		~ObjectPool()
		{
			delete[] myResources;
			myResources = nullptr;
		}

		PoolResource<T>* GetNextFree()
		{
			for (int i = 0; i < mySize; ++i)
			{
				if ((myResources + i)->IsFree())
				{
					myResources[i].SetFree(false);
					return myResources + i;
				}
			}
			assert(false && "Object pool ran out of free resources.");
		}

		void ReturnResource(PoolResource<T>* aResource)
		{
			aResource->SetFree(true);
			aResource->Value() = T();
		}

		bool IsInitialized() { return mySize != 0; }

	private:
		int mySize = 0;
		PoolResource<T>* myResources = nullptr;
	};
}

namespace CU = CommonUtilities;