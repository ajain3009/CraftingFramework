// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UItemDataAsset.generated.h"

UCLASS(BlueprintType)
class MAWFORGED_API UItemDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool Stackable = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTexture2D* Thumbnail;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UStaticMesh* MeshData;
};