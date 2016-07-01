#include "GOAPer.h"
#include "GOAPGoal.h"
#include "GOAPAIController.h"

bool GOAPGoal::IsTargetStateSatisfied(AGOAPAIController& controller)
{

	bool result = true;

	for (auto& state : TargetState)
	{
		bool isThisStateSatisfied = false;

		// If result is false then we've already failed a precondition, return false
		if (!result) {
			return false;
		}

		// Check all agent states for key and value matches
		// TODO: Optimisation target
		for (auto& agentState : (&controller)->GOAPAgentStates)
		{
			if (agentState->Key == state->Key
				&& agentState->Value == state->Value)
			{
				isThisStateSatisfied = true;
				break;
			}
		}
		result = isThisStateSatisfied;
	}

	// If we get here and result is still true, then all effects are already satisfied
	return result;
	
}
