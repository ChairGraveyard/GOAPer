#include "GOAPer.h"
#include "GOAPAIController.h"
#include "IsHungryState.h"

bool IsHungryState::Evaluate(AGOAPAIController* controller)
{
	isSatisfied = controller->character->Stat_Nutrition_Value < 100;
	return isSatisfied;
}

