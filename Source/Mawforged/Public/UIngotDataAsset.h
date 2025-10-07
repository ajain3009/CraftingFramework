// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Mawforged/Public/FItemStats.h"
#include "Mawforged/Public/UItemDataAsset.h"
#include "UIngotDataAsset.generated.h"

UCLASS(BlueprintType)
class MAWFORGED_API UIngotDataAsset : public UItemDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FItemStats ItemStats;
};

