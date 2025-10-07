// Fill out your copyright notice in the Description page of Project Settings.

#include "Mawforged/Public/UInventoryComponent.h"
#include "Mawforged/Mawforged.h"

// Sets default values for this component's properties
UUInventoryComponent::UUInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UUInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UUInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUInventoryComponent::AddItem(UItemDataAsset* NewItem)
{
	for (FInventoryItem& item : Items)
	{
		if (item.ItemData == NewItem)
		{
			if (item.ItemData->Stackable)
			{
				item.Quantity += 1;
				return;
			}
		}
		else if(item.Quantity == 0)
		{
			item.ItemData = NewItem;
			item.Quantity = 1;
			return;
		}
	}
}

void UUInventoryComponent::RemoveItem(UItemDataAsset* NewItem, int Quantity)
{
	for (FInventoryItem& item : Items)
	{
		if (item.ItemData == NewItem)
		{
			item.Quantity -= Quantity;
			if (item.Quantity == 0)
			{
				item.ItemData = nullptr;
				break;
			}
		}
	}

	TArray<FInventoryItem> TempsItems;
	TempsItems.Init(FInventoryItem(), Items.Num());
	int index = 0;

	for (FInventoryItem& item : Items)
	{
		if (item.Quantity != 0)
		{
			TempsItems[index] = item;
			index++;
		}
	}

	Items = TempsItems;
}

bool UUInventoryComponent::HasRequiredItem(const UItemDataAsset* Item) const
{
	for (FInventoryItem item : Items)
	{
		if (item.ItemData == Item)
		{
			return true;
		}
	}

	return false;
}

bool UUInventoryComponent::HasRequiredItemWithQuantity(const UItemDataAsset* Item, int Quantity) const
{
	for (FInventoryItem item : Items)
	{
		if (item.ItemData == Item)
		{
			if (item.Quantity >= Quantity)
			{
				return true;
			}
			return true;
		}
	}

	return false;
}



