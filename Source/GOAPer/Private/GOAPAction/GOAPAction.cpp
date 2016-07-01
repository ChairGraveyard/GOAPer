#include "GOAPer.h"
#include "GOAPAIController.h"
#include "GameFramework/Actor.h"
#include "GOAPAction.h"

GOAPAction::GOAPAction()
{

}

bool GOAPAction::ArePreconditionsSatisfied(AGOAPAIController& controller)
{
	bool result = true;

	if (PreConditions.Num() == 0)
	{
		return true;
	}

	for (auto& condition : PreConditions)
	{
		bool isThisConditionSatisfied = false;

		// If result is false then we've already failed a precondition, return false
		if (!result) {
			return false;
		}

		// Check all agent states for key and value matches
		// TODO: Optimisation target
		for (auto& agentState : (&controller)->GOAPAgentStates)
		{
			if (agentState->Key == condition->Key
					&& agentState->Value == condition->Value)
			{
				isThisConditionSatisfied = true;
				break;
			}
		}
		result = isThisConditionSatisfied;
	}

	// If we get here and result is still true, then all preconditions are met
	return result;
}

void GOAPAction::ApplyEffectsToState(AGOAPAIController& controller)
{
	for (auto& effect : Effects)
	{
		for (auto& agentState : (&controller)->GOAPAgentStates)
		{
			if (agentState->Key == effect->Key)
			{
				agentState->Value = effect->Value;
			}
		}
	}
}

// Checks if the Agent is within the Interaction Range of the TargetActor
bool GOAPAction::IsInRange(AGOAPAIController& controller)
{
	// If there's no target, we're always in range
	if (ActionTarget == nullptr)
	{
		return true;
	}

	// Otherwise, check the distance against the interaction range
	return ((&controller)->character->GetActorLocation() - ActionTarget->GetActorLocation()).Size() < InteractionRange;
}

bool GOAPAction::AreEffectsSatisfied(AGOAPAIController& controller)
{
	bool result = true;

	for (auto& condition : Effects)
	{
		bool isThisEffectSatisfied = false;

		// If result is false then we've already failed a precondition, return false
		if (!result) {
			return false;
		}

		// Check all agent states for key and value matches
		// TODO: Optimisation target
		for (auto& agentState : (&controller)->GOAPAgentStates)
		{
			if (agentState->Key == condition->Key
				&& agentState->Value == condition->Value)
			{
				isThisEffectSatisfied = true;
				break;
			}
		}
		result = isThisEffectSatisfied;
	}

	// If we get here and result is still true, then all effects are already satisfied
	return result;
}