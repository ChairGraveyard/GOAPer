#include "GOAPer.h"
#include "GOAPAIController.h"
#include "IsFoodAvailableState.h"

bool IsFoodAvailableState::Evaluate(AGOAPAIController* controller)
{
	isSatisfied = controller->FindNewResourceActor(EResourceType::Food) != nullptr;
	return isSatisfied;
}

