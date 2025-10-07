// Fill out your copyright notice in the Description page of Project Settings.

#include "CraftingResolver.h"
#include "Mawforged/Public/CraftingGameInstance.h"

UIngotDataAsset* UCraftingResolver::Resolve(UObject* WorldContextObject, UCraftingRecipeDataAsset* Recipe, UUInventoryComponent* Inventory, EQualityModifier Quality)
{
    UIngotDataAsset* CraftedItem = nullptr;

    if (!Recipe || !Recipe->Output)
    {
        UE_LOG(LogTemp, Warning, TEXT("CraftingResolver: Invalid recipe or result item"));
        return CraftedItem;
    }

    CraftedItem = DuplicateObject<UIngotDataAsset>(Recipe->Output, WorldContextObject);

    FString ItemName;
    FItemStats newStats = PreviewStats(WorldContextObject, Recipe, Quality, ItemName);
    CraftedItem->ItemStats = newStats;

    return CraftedItem;
}

FItemStats UCraftingResolver::PreviewStats(UObject* WorldContextObject, UCraftingRecipeDataAsset* Recipe, EQualityModifier Quality, FString& ItemName)
{
    FItemStats Stats;
    if (Recipe == nullptr || Quality == EQualityModifier::Fail || !Recipe->Output)
    {
        return Stats;
    }

    ItemName = Recipe->Output->Name;

    UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
    UCraftingGameInstance* CraftingData = Cast<UCraftingGameInstance>(World->GetGameInstance());
    if (CraftingData == nullptr)
    {
        return Stats;
    }

    for (FRecipeIngot& ingot : Recipe->RequiredIngots)
    {
        FItemStats ingotItemStats = ingot.Ingot->ItemStats;
        int ingotQuantity = ingot.Quantity;
        Stats.Damage = ingotItemStats.Damage * ingotQuantity;
        Stats.CritChance = ingotItemStats.CritChance * ingotQuantity;
    }

    for (FQualityModifierData& modiferData : CraftingData->FQualityModifierDataList)
    {
        if (modiferData.QualityModifier == Quality)
        {
            float itemQuality = modiferData.QualityPercentage / 100;
            Stats.Damage = Stats.Damage * itemQuality;
            Stats.CritChance = Stats.CritChance * itemQuality;
        }
    }

    return Stats;
}
