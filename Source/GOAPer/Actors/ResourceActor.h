// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ResourceActor.generated.h"

UENUM()
enum class EResourceType : uint8
{
	Food			UMETA(DisplayName = "Food"),
	Tool			UMETA(DisplayName = "Tool")
};

UCLASS()
class GOAPER_API AResourceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceActor();
	AResourceActor(const FObjectInitializer& ObjectInitializer) {
		auto box = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, FName("ResourceBox"));
		box->bHiddenInGame = false;
		box->Mobility = EComponentMobility::Movable;
		RootComponent = box;
	}

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Type")
	EResourceType ResourceType;
	
};
