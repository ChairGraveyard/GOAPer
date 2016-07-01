#include "GOAPer.h"
#include "GOAPAIController.h"
#include "GameFramework/Actor.h"
#include "HasFoodState.h"
#include "IsHungryState.h"
#include "GatherFoodAction.h"
#include "IsFoodAvailableState.h"

GatherFoodAction::GatherFoodAction() 
{
	InteractionRange = 200.0f;

	// No preconditions, we can always try and gather food
	PreConditions.Add(MakeShareable<GOAPState>(new IsFoodAvailableState(true)));

	// Make us have food!
	Effects.Add(MakeShareable<GOAPState>(new HasFoodState(true)));

}

bool GatherFoodAction::Execute(AGOAPAIController& controller)
{
	// Check if the desired effects are already valid, if so, we're done
	if (AreEffectsSatisfied(controller))
	{
		return true;
	}

	// Check if we have a target, if not, find one
	if (ActionTarget == nullptr)
	{
		ActionTarget = (&controller)->FindNewResourceActor(EResourceType::Food);
	}
	if (ActionTarget == nullptr)
	{
		// No targets, we need to abort this action
		// TODO: Abort code
		return false;
	}

	// If we're not in range of the target, change to a move state
	if (!IsInRange(controller))
	{
		(&controller)->SetMoveToStateWithTarget(ActionTarget->GetActorLocation());
		return false;
	}
	// Otherwise, we're in range! Let's nuke the target
	else
	{
		ActionTarget->Destroy();
		ActionTarget = nullptr;
		(&controller)->character->Stat_HasFood = true;
		return true;
	}

	return false;
}

FString GatherFoodAction::GetTextDescription()
{
	return TEXT("Gather Food");
}

