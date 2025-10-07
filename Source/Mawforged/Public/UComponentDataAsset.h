// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Mawforged/Public/UItemDataAsset.h"
#include "UComponentDataAsset.generated.h"

UCLASS(BlueprintType)
class MAWFORGED_API UComponentDataAsset : public UItemDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Weight = 0.0f;
};
