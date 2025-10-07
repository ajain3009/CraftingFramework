// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mawforged/Public/UItemDataAsset.h"
#include "UInventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemDataAsset* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAWFORGED_API UUInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddItem(UItemDataAsset* NewItem);
	
	UFUNCTION(BlueprintCallable)
	void RemoveItem(UItemDataAsset* NewItem, int Quantity = 1);

	bool HasRequiredItem(const UItemDataAsset* Item) const;

	bool HasRequiredItemWithQuantity(const UItemDataAsset* Item, int Quantity) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventoryItem> Items;
};
