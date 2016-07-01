#pragma once
#include "GOAPer.h"
#include "GOAPState.h"

class AGOAPAIController;

UENUM()
enum class EGOAPGoal : uint8
{
	BeNourished		UMETA(DisplayName = "Be Nourished"),
	MakeFoodAvailable UMETA(DisplaName = "Make Food Available")
};

class GOAPGoal
{
public:
	TArray<TSharedPtr<GOAPState>> TargetState;

	bool IsTargetStateSatisfied(AGOAPAIController& controller);
};
