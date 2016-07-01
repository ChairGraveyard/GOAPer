#pragma once
#include "GOAPer.h"
#include "GOAPState.h"
#include "StateDefinition.generated.h"

USTRUCT()
struct FStateDefinition
{
	GENERATED_USTRUCT_BODY()

	FStateDefinition() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateDefinition")
	EGOAPState Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateDefinition")
	bool Value;
};
