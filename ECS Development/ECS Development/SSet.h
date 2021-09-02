#pragma once

#include <vector>
#include <type_traits>

namespace CommonUtilities
{
	template<typename T>
	class SSet
	{
	public:
		SSet() = default;
		~SSet() = default;

		using iterator = typename std::vector<T>::const_iterator;
		using const_iterator = typename std::vector<T>::const_iterator;

		iterator begin() { return myDense.begin(); }
		iterator begin() const { return myDense.begin(); }

		iterator end() { return myDense.begin() + mySize; }
		iterator end() const { return myDense.begin() + mySize; }

		const int Size() const { return mySize; }
		const int Capacity() const { return myCapacity; }

		const bool Empty() const { return mySize == 0; }

		void Clear() { mySize = 0; }

		void Reserve(int aSize)
		{
			if (aSize > myCapacity)
			{
				myDense.resize(aSize, 0);
				mySparse.resize(aSize, 0);
				myCapacity = aSize;
			}
		}

		bool Has(const T& aVal)
		{
			return aVal < myCapacity&& mySparse[aVal] < mySize&& myDense[mySparse[aVal]] == aVal;
		}

		void Insert(const T& aVal)
		{
			if (!Has(aVal))
			{
				if (aVal >= myCapacity)
				{
					reserve(aVal + 1);
				}

				myDense[mySize] = aVal;
				mySparse[aVal] = mySize;
				++mySize;
			}
		}

		void Erase(const T& aVal)
		{
			if (Has(aVal))
			{
				myDense[mySparse[aVal]] = myDense[mySize - 1];
				mySparse[myDense[mySize - 1]] = mySparse[aVal];
				--mySize;
			}
		}

	private:
		std::vector<T> myDense;
		std::vector<T> mySparse;
		int mySize = 0;
		int myCapacity = 0;
	};
}

namespace CU = CommonUtilities;