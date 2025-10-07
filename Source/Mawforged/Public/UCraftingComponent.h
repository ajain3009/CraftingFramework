// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mawforged/Public/CraftingRecipeDataAsset.h"
#include "Mawforged/Public/UInventoryComponent.h"
#include "UCraftingComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAWFORGED_API UUCraftingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUCraftingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	bool CanCraft(UCraftingRecipeDataAsset* Recipe, AActor* Station, EMessageType& messageType, FString& outError);

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	bool Craft(UCraftingRecipeDataAsset* Recipe, AActor* Station, EQualityModifier Quality, FString& Error, EMessageType& messageType);

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	bool GetQualityModifier(float barPosition, float barBound, EQualityModifier& quality, FString& ModifierStatus) const;

public:
	UUInventoryComponent* GetInventory() const;

	bool CheckInventoryForRecipeItems(UCraftingRecipeDataAsset* Recipe) const;

	bool ConsumeItems(UCraftingRecipeDataAsset* Recipe);
};
