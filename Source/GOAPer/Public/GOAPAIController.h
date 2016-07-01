// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GOAPer.h"
#include "AIController.h"
#include "GOAPFSMState.h"
#include "GOAPState.h"
#include "GOAPAction.h"
#include "GOAPGoal.h"
#include "GOAPerCharacter.h"
#include "GOAPAICharacter.h"
#include "GameFramework/Actor.h"
#include "Actors/ResourceActor.h"
#include "GOAPAIController.generated.h"

UCLASS()
class GOAPER_API AGOAPAIController : public AAIController
{
	GENERATED_BODY()
private:
	bool LoadGOAPDefaults();

public:
	TSharedPtr<GOAPFSMState> state;
	AGOAPAICharacter* character;

	TQueue<TSharedPtr<GOAPAction>>	ActionQueue;
	TSharedPtr<GOAPAction>			CurrentAction;
	TSharedPtr<GOAPGoal>			CurrentGoal;
	TArray<TSharedPtr<GOAPState>>	GOAPAgentStates;
	TArray<TSharedPtr<GOAPAction>>	GOAPActions;
	TArray<TSharedPtr<GOAPGoal>>	GOAPGoals;


	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SetNewState(TSharedPtr<GOAPFSMState> newState);
	void SetMoveToStateWithTarget(FVector targetLocation);
	bool BuildActionPlanForCurrentGoal();

	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;
	AResourceActor* FindNewResourceActor(EResourceType aResourceType);

	UFUNCTION(BlueprintCallable, Category = "GOAPAIController")
	FString GetCurrentStateString();
	UFUNCTION(BlueprintCallable, Category = "GOAPAIController")
	FString GetCurrentActionString();


	bool UpdateSingleGOAPAgentState(EGOAPState aGOAPState, bool aValue);
	void EvaluateAllGOAPAgentStates();

	bool SelectRandomGoalAndFormPlan();

	bool isStateSatisfied(TSharedPtr<GOAPState> aState);

	TSharedPtr<GOAPAction> FindActionToSatisfyState(TSharedPtr<GOAPState> aState);
};