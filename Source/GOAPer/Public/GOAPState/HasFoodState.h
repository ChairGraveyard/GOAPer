#pragma once
#include "GOAPer.h"
#include "GameFramework/Actor.h"
#include "Object.h"

class AGOAPAIController;


class HasFoodState : public GOAPState
{	
public:
	HasFoodState(bool bValue) : GOAPState(EGOAPState::HasFood, bValue) {};
	virtual bool Evaluate(AGOAPAIController* controller) override;
};
