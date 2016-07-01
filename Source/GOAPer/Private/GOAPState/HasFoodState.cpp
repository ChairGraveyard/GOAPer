#include "GOAPer.h"
#include "GOAPAIController.h"
#include "HasFoodState.h"

bool HasFoodState::Evaluate(AGOAPAIController* controller)
{
	isSatisfied = controller->character->Stat_HasFood;
	return isSatisfied;
}

