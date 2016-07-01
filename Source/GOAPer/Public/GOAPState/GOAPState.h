#pragma once
#include "GOAPer.h"

class AGOAPAIController;
class GOAPAction;

UENUM()		
enum class EGOAPState : uint8
{
	HasFood			UMETA(DisplayName = "Has Food"),
	IsHungry		UMETA(DisplayName = "Is Hungry"),
	FoodAvailableState UMETA(DisplayName = "Food Available")
};

class GOAPState
{
public:
	GOAPState() {};
	GOAPState(EGOAPState eKey, bool bValue) : Key{ eKey }, Value{ bValue } {};
	virtual bool Evaluate(AGOAPAIController* controller) = 0;

	bool isSatisfied;
	EGOAPState Key;
	bool Value;
};
