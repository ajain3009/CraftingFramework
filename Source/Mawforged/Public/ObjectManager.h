// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Mawforged/Public/UItemDataAsset.h"
#include "ObjectManager.generated.h"

UCLASS()
class MAWFORGED_API UObjectManager : public UObject
{
    GENERATED_BODY()

public:
    static UObjectManager& Get();

    void RegisterItem(UItemDataAsset* Item);
    UItemDataAsset* GetItemByID(uint64 ObjectID) const;
    uint64 GenerateUniqueID();

private:
    TMap<uint64, UItemDataAsset*> RegisteredItems;
};