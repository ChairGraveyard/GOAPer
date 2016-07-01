#pragma once
#include "GOAPer.h"
#include "GOAPAction.h"

class AGOAPAIController;

class GatherFoodAction : public GOAPAction
{
	

public:
	GatherFoodAction();
	// Called each frame while this is the active action, returns true when complete
	virtual bool Execute(AGOAPAIController& controller) override;
	virtual FString GetTextDescription() override;

};
