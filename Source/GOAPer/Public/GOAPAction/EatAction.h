#pragma once
#pragma once
#include "GOAPer.h"
#include "GOAPAction.h"

class AGOAPAIController;

class EatAction : public GOAPAction
{


public:
	EatAction();
	// Called each frame while this is the active action, returns true when complete
	virtual bool Execute(AGOAPAIController& controller) override;
	virtual FString GetTextDescription() override;

};
