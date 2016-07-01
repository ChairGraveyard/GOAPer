// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GOAPState.h"
#include "GOAPAction.h"
#include "GOAPGoal.h"
#include "StateDefinition.h"
#include "FloatingTextWidget.h"
#include "GOAPAICharacter.generated.h"

UCLASS()
class GOAPER_API AGOAPAICharacter : public ACharacter
{
	GENERATED_BODY()

		
	float TimeSinceLastDecay = 0.0f;
	UWorld* World;

public:
	// Sets default values for this character's properties
	AGOAPAICharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GOAP Behaviour Config")
	TArray<FStateDefinition> AgentState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GOAP Behaviour Config")
	TArray<EGOAPAction> AvailableActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GOAP Behaviour Config")
	TArray<EGOAPGoal> Goals;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GOAP Character Attributes")
	bool Stat_HasFood;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GOAP Character Attributes")
	int32 Stat_Nutrition_Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GOAP Character Attributes")
	float NutritionDecayRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GOAP UI References")
	TSubclassOf<class UFloatingTextWidget> FloatingTextWidget;

	void DisplayFloatingText(FString textToDisplay, FSlateColor textColor);

	UFloatingTextWidget* MyFloatingTextWidget;
	
};
