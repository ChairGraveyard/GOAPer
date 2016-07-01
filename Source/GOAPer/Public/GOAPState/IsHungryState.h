#pragma once
#include "GOAPer.h"
#include "GameFramework/Actor.h"
#include "Object.h"

class AGOAPAIController;


class IsHungryState : public GOAPState
{
public:
	IsHungryState(bool bValue) : GOAPState(EGOAPState::IsHungry, bValue) {};
	virtual bool Evaluate(AGOAPAIController* controller) override;
};
