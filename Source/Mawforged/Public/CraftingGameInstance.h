// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Mawforged/Public/CraftingRecipeDataAsset.h"
#include "CraftingGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FQualityModifierData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EQualityModifier QualityModifier;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 QualityPercentage;
};

UCLASS()
class MAWFORGED_API UCraftingGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FQualityModifierData> FQualityModifierDataList;
};
