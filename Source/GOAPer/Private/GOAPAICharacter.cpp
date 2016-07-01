// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAPer.h"
#include "GOAPAICharacter.h"
#include "FloatingTextWidget.h"


// Sets default values
AGOAPAICharacter::AGOAPAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGOAPAICharacter::BeginPlay()
{
	Super::BeginPlay();

	Stat_HasFood = false;
	Stat_Nutrition_Value = 100;
	
	World = GetWorld();
}

// Called every frame
void AGOAPAICharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	TimeSinceLastDecay += DeltaTime;

	if (TimeSinceLastDecay > NutritionDecayRate && Stat_Nutrition_Value > 0)
	{
		--Stat_Nutrition_Value;
		TimeSinceLastDecay = 0.0f;
	}
}

// Called to bind functionality to input
void AGOAPAICharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AGOAPAICharacter::DisplayFloatingText(FString textToDisplay, FSlateColor textColor)
{
	APlayerController* pc = World->GetFirstPlayerController();

	if (FloatingTextWidget && pc)
	{
		MyFloatingTextWidget = CreateWidget<UFloatingTextWidget>(World->GetFirstPlayerController(), FloatingTextWidget);
	}
	if (MyFloatingTextWidget)
	{
		MyFloatingTextWidget->ActorRef = this;
		MyFloatingTextWidget->TextColor = textColor;
		MyFloatingTextWidget->DisplayText = textToDisplay;

		MyFloatingTextWidget->AddToViewport();
	}
}

