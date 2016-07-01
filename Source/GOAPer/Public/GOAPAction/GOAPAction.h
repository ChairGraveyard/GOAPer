#pragma once
#include "GOAPer.h"
#include "GOAPState.h"

class AGOAPAIController;

UENUM()
enum class EGOAPAction : uint8
{
	GatherFood	UMETA(DisplayName = "Gather Food"),
	Eat			UMETA(DisplayName = "Eat"),
	CreateFood  UMETA(DisplayName = "Create Food")
};


class GOAPAction
{
	

public:
	GOAPAction();
	// Checks if the preconditions are satisfied by the current agent state
	bool ArePreconditionsSatisfied(AGOAPAIController& controller);
	// Called on completion, applies the action effects to the agent state
	void ApplyEffectsToState(AGOAPAIController& controller);
	// Checks if the agent is within range of whatever it needs to be in range of
	bool IsInRange(AGOAPAIController& controller);

	// Checks if the target state (effect) is already satisfied
	bool AreEffectsSatisfied(AGOAPAIController& controller);

	// Called each frame while this is the active action, returns true when complete
	virtual bool Execute(AGOAPAIController& controller) = 0;
	virtual FString GetTextDescription() = 0;

	// Agent State values that must be satisfied to execute the action
	TArray<TSharedPtr<GOAPState>> PreConditions;
	// Agent State values that will be applied upon succesful execution
	TArray<TSharedPtr<GOAPState>> Effects;

	// Type of actor which is the target of the this action (if any)
	AActor* ActionTarget = nullptr;
	// Required range from target to perform action
	float InteractionRange;

	uint8 Cost;
};
