// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mawforged/Public/CraftingRecipeDataAsset.h"
#include "UCraftingStationComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAWFORGED_API UUCraftingStationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUCraftingStationComponent() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	EStationType StationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UCraftingRecipeDataAsset* Recipe;
};
