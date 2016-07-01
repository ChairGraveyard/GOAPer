#pragma once
#include "GOAPer.h"

class AGOAPAIController;


class IsFoodAvailableState : public GOAPState
{
public:
	IsFoodAvailableState(bool bValue) : GOAPState(EGOAPState::FoodAvailableState, bValue) {};
	virtual bool Evaluate(AGOAPAIController* controller) override;
};
