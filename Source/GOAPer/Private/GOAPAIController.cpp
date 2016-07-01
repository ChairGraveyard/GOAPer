// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAPer.h"
#include "GOAPAIController.h"
#include "EngineUtils.h"
#include "GOAPState.h"
#include "GOAPAICharacter.h"
#include "Actors/ResourceActor.h"
#include "Engine.h"
#include "IdleState.h"
#include "MoveToState.h"
#include "DoActionState.h"
#include "GOAPStateFactory.h"
#include "GOAPGoalFactory.h"
#include "GOAPActionFactory.h"


bool AGOAPAIController::LoadGOAPDefaults()
{
	// Load state defaults from character
	for (auto& elem : character->AgentState)
	{
		GOAPAgentStates.Add(GOAPStateFactory::Create(elem.Key, elem.Value));
	}

	// Load goals from character defaults
	for (auto& elem : character->Goals)
	{
		GOAPGoals.Add(GOAPGoalFactory::Create(elem));
	}

	for (auto& elem : character->AvailableActions)
	{
		GOAPActions.Add(GOAPActionFactory::Create(elem));
	}


	return true;
}

void AGOAPAIController::BeginPlay()
{
	Super::BeginPlay();

	character = Cast<AGOAPAICharacter>(GetCharacter());

	LoadGOAPDefaults();

	SetNewState(MakeShareable(new IdleState()));
}

void AGOAPAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EvaluateAllGOAPAgentStates();

	// First run the FSM

	TSharedPtr<GOAPFSMState> _possibleNewState = state->Tick(*this, DeltaTime);
	if (_possibleNewState.IsValid())
	{
		SetNewState(_possibleNewState);
	}

	// Then evaluate the Agent State



}

void AGOAPAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	SetNewState(MakeShareable(new IdleState()));
}

void AGOAPAIController::SetNewState(TSharedPtr<GOAPFSMState> newState)
{
	state.Reset();
	state = newState;
	state->Enter(*this);
}

void AGOAPAIController::SetMoveToStateWithTarget(FVector targetLocation)
{
	SetNewState(MakeShareable(new MoveToState()));
	MoveToLocation(targetLocation, -1.0f);
}

bool AGOAPAIController::BuildActionPlanForCurrentGoal()
{
	TArray<TSharedPtr<GOAPAction>> planActions;

	TSharedPtr<GOAPState> targetState = CurrentGoal->TargetState[0];

	// The goal is already satisfied, discard it
	if (isStateSatisfied(targetState))
	{
		character->DisplayFloatingText(TEXT("Goal Already Satisfied"), FSlateColor(FLinearColor::Yellow));
		return false;
	}

	// Search for an action that will satisfy this state

	while (targetState.IsValid())
	{
		TSharedPtr<GOAPAction> currentAction = FindActionToSatisfyState(targetState);

		if (currentAction.IsValid())
		{
			planActions.Add(currentAction);
			targetState = currentAction->PreConditions.Num() == 0 ? nullptr : currentAction->PreConditions[0];
			if (isStateSatisfied(targetState))
			{
				break;
			}
		}
		else
		{
			// We didn't find a plan that meets the goal
			planActions.Empty();
			break;
		}
	}

	if (planActions.Num() > 0)
	{
		for (int i = planActions.Num() - 1; i >= 0; --i)
		{
			ActionQueue.Enqueue(planActions[i]);
		}
	}
	else
	{
		return false;
	}


	return true;
}

// Returns the first ResourceActor in the scene
AResourceActor* AGOAPAIController::FindNewResourceActor(EResourceType aResourceType)
{
	AResourceActor* nearestActor = nullptr;
	float currentClosestDistance = 10000.0f;

	for (TActorIterator<AResourceActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AResourceActor* Target = *ActorItr;
		if (Target->ResourceType == aResourceType
				&& (GetCharacter()->GetActorLocation() - Target->GetActorLocation()).Size() < currentClosestDistance)
		{
			nearestActor = Target;
			currentClosestDistance = (GetCharacter()->GetActorLocation() - Target->GetActorLocation()).Size();
		}
	}
	
	return nearestActor;
}

FString AGOAPAIController::GetCurrentStateString()
{
	if (state.IsValid())
	{
		return state->ToString();
	}
	return TEXT("No Valid State");
}




FString AGOAPAIController::GetCurrentActionString()
{
	if (CurrentAction.IsValid())
	{
		return CurrentAction->GetTextDescription();
	}
	else
	{
		return TEXT("None");
	}
}

bool AGOAPAIController::UpdateSingleGOAPAgentState(EGOAPState aGOAPState, bool aValue)
{
	for (auto& elem : GOAPAgentStates)
	{
		if (elem->Key == aGOAPState)
		{
			elem->Value = aValue;
			return true;
		}
	}
	return false;
}

void AGOAPAIController::EvaluateAllGOAPAgentStates()
{
	for (auto& elem : GOAPAgentStates)
	{
		elem->Value = elem->Evaluate(this);
	}
}

bool AGOAPAIController::SelectRandomGoalAndFormPlan()
{
	if (GOAPGoals.Num() == 0)
	{
		return false;
	}

	CurrentGoal = GOAPGoals[FMath::RandRange(0, GOAPGoals.Num() - 1)];

	if (BuildActionPlanForCurrentGoal())
	{
		character->DisplayFloatingText(TEXT("Planning Successful"), FSlateColor(FLinearColor::Green));
		return true;
	}
	else
	{
		character->DisplayFloatingText(TEXT("Planning Failed"), FSlateColor(FLinearColor::Red));
		return false;
	}

}

bool AGOAPAIController::isStateSatisfied(TSharedPtr<GOAPState> aState)
{
	for (auto agentState : GOAPAgentStates)
	{
		if (agentState->Key == aState->Key && agentState->Value == aState->Value)
		{
			return true;
		}
	}
	return false;
}

TSharedPtr<GOAPAction> AGOAPAIController::FindActionToSatisfyState(TSharedPtr<GOAPState> aState)
{
	for (auto action : GOAPActions)
	{
		for (auto effect : action->Effects)
		{
			if (aState->Key == effect->Key && aState->Value == effect->Value)
			{
				return action;
			}
		}
	}
	return nullptr;
}
