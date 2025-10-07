// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Mawforged/Public/CraftingRecipeDataAsset.h"
#include "Mawforged/Public/UInventoryComponent.h"
#include "Mawforged/Public/FItemStats.h"
#include "CraftingResolver.generated.h"

UCLASS()
class MAWFORGED_API UCraftingResolver : public UObject
{
	GENERATED_BODY()

public:
    //Resolves a recipe into a final inventory item, applying stat blending and quality modifiers
    UFUNCTION(BlueprintCallable, Category = "Crafting")
    static UIngotDataAsset* Resolve(UObject* WorldContextObjectt, UCraftingRecipeDataAsset* Recipe, UUInventoryComponent* Inventory, EQualityModifier Quality);

    // Previews the stat block of a crafted item based on quality, without consuming resources
    UFUNCTION(BlueprintCallable, Category = "Crafting")
    static FItemStats PreviewStats(UObject* WorldContextObject, UCraftingRecipeDataAsset* Recipe, EQualityModifier Quality, FString& ItemName);
};
