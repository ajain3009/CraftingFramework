// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FItemStats.generated.h"

USTRUCT(BlueprintType)
struct FItemStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CritChance = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Durability = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Weight = 1.0f;
};
