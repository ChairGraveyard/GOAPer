
#include "GOAPer.h"
#include "MoveToState.h"

MoveToState::MoveToState()
{
	eState = EGOAPFSMState::MoveTo;
}

MoveToState::~MoveToState()
{

}

TSharedPtr<GOAPFSMState> MoveToState::Tick(AGOAPAIController& controller, float DeltaTime)
{
	TSharedPtr<GOAPFSMState> retVal;
	return retVal;
}

void MoveToState::Enter(AGOAPAIController& controller)
{

}

FString MoveToState::ToString()
{
	return TEXT("MoveTo");
}

