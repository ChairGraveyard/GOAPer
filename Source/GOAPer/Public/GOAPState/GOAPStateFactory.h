#pragma once
#include "GOAPState.h"
#include "HasFoodState.h"
#include "IsHungryState.h"
#include "IsFoodAvailableState.h"

class GOAPStateFactory
{
public:
	static TSharedPtr<GOAPState> Create(EGOAPState aState, bool aValue);
};


TSharedPtr<GOAPState> GOAPStateFactory::Create(EGOAPState aState, bool aValue)
{
	switch (aState)
	{
	case EGOAPState::HasFood:
		return MakeShareable<GOAPState>(new HasFoodState(aValue));
	case EGOAPState::IsHungry:
		return MakeShareable<GOAPState>(new IsHungryState(aValue));
	case EGOAPState::FoodAvailableState:
		return MakeShareable<GOAPState>(new IsFoodAvailableState(aValue));
	default:
		return nullptr;
	}
}