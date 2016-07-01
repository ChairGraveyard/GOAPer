#pragma once
#include "GOAPGoal.h"
#include "IsHungryState.h"

class GOAPGoalFactory
{
public:
	static TSharedPtr<GOAPGoal> Create(EGOAPGoal aGoal);
};


TSharedPtr<GOAPGoal> GOAPGoalFactory::Create(EGOAPGoal aGoal)
{
	TSharedPtr<GOAPGoal> _goal = MakeShareable<GOAPGoal>(new GOAPGoal());

	switch (aGoal)
	{
	case EGOAPGoal::BeNourished:
		_goal->TargetState.Add(MakeShareable<GOAPState>(new IsHungryState(false)));
		return _goal;
	case EGOAPGoal::MakeFoodAvailable:
		_goal->TargetState.Add(MakeShareable<GOAPState>(new IsFoodAvailableState(true)));
		return _goal;
	default:
		return nullptr;
	}
}