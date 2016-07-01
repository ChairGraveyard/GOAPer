#include "GOAPer.h"
#include "DoActionState.h"
#include "IdleState.h"
#include "GOAPAction.h"
#include "GOAPAIController.h"

DoActionState::DoActionState()
{
	eState = EGOAPFSMState::DoAction;
}

DoActionState::~DoActionState()
{

}

TSharedPtr<GOAPFSMState> DoActionState::Tick(AGOAPAIController& controller, float DeltaTime)
{
	// Check if the preconditions are still valid, we need to invalidate the plan
	if (!(&controller)->CurrentAction->ArePreconditionsSatisfied(controller))
	{
		(&controller)->ActionQueue.Empty();
		(&controller)->CurrentAction.Reset();
		// Then return to idle
		return MakeShareable(new IdleState());
	}
	// Otherwise, crack on with it
	else if ((&controller)->CurrentAction->Execute(controller))
	{
		// If it's complete, apply the effects
		(&controller)->CurrentAction->ApplyEffectsToState(controller);
		// And clear the action
		(&controller)->CurrentAction.Reset();
		// Then return to idle
		return MakeShareable(new IdleState());
	}
	return nullptr;
}

void DoActionState::Enter(AGOAPAIController& controller)
{
	
}

FString DoActionState::ToString()
{
	return TEXT("DoAction");
}

