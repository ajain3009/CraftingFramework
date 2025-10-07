// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Mawforged/Public/UItemDataAsset.h"
#include "Mawforged/Public/UIngotDataAsset.h"
#include "Mawforged/Public/UComponentDataAsset.h"
#include "CraftingRecipeDataAsset.generated.h"

UENUM(BlueprintType)
enum class ERecipeType : uint8
{
    Fixed,
    Mixable
};

UENUM(BlueprintType)
enum class EProfession : uint8
{
    Blacksmith,
    Alchemist,
    Tailor
};

UENUM(BlueprintType)
enum class EStationType : uint8
{
    Forge,
    AlchemyTable,
    Loom
};

UENUM(BlueprintType)
enum class EMessageType : uint8
{
    ItemNotFound,
    RecipeNotFound,
    Craft,
    None
};

UENUM(BlueprintType)
enum class EQualityModifier : uint8
{
    Good,
    Great,
    Perfect,
    Fail
};

USTRUCT(BlueprintType)
struct FRecipeComponent
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UComponentDataAsset* Component;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 Quantity;
};

USTRUCT(BlueprintType)
struct FRecipeIngot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UIngotDataAsset* Ingot;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 Quantity;
};

UCLASS(BlueprintType)
class MAWFORGED_API UCraftingRecipeDataAsset : public UItemDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    ERecipeType RecipeType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EProfession Profession;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EStationType Station;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FRecipeComponent> RequiredComponents;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FRecipeIngot> RequiredIngots;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UIngotDataAsset* Output;
};
