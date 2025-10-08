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

	ItemMap.Empty();
	for (const FInventoryItem& Item : Items)
	{
		if (Item.ItemData)
		{
			ItemMap.Add(Item.ItemData->ObjectID, Item);
		}
	}
}

// Called every frame
void UUInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUInventoryComponent::AddItem(UItemDataAsset* NewItem)
{
	if (!NewItem) return;

	uint64 ID = NewItem->ObjectID;
	FInventoryItem* Existing = ItemMap.Find(ID);

	if (Existing)
	{
		if (NewItem->Stackable)
		{
			Existing->Quantity += 1;
			for (FInventoryItem& Item : Items)
			{
				if (Item.ItemData && Item.ItemData->ObjectID == ID)
				{
					Item = *Existing;
					break;
				}
			}
		}
		return;
	}

	FInventoryItem NewEntry;
	NewEntry.ItemData = NewItem;
	NewEntry.Quantity = 1;

	ItemMap.Add(ID, NewEntry);

	for (FInventoryItem& itemslot : Items)
	{
		if (!itemslot.ItemData)
		{
			itemslot = NewEntry;
			break;
		}
	}
}

void UUInventoryComponent::RemoveItem(UItemDataAsset* Item, int Quantity /*= 1*/)
{
	if (!Item || Quantity <= 0) return;

	uint64 ID = Item->ObjectID;
	FInventoryItem* Existing = ItemMap.Find(ID);

	if (!Existing) return;

	Existing->Quantity -= Quantity;
	if (Existing->Quantity <= 0)
	{
		ItemMap.Remove(ID);

		// Remove from Items array
		Items.RemoveAll([ID](const FInventoryItem& Item)
			{
				return Item.ItemData && Item.ItemData->ObjectID == ID;
			});

		Items.Add(FInventoryItem());
	}
	else
	{
		// Sync array quantity
		for (FInventoryItem& Item : Items)
		{
			if (Item.ItemData && Item.ItemData->ObjectID == ID)
			{
				Item.Quantity = Existing->Quantity;
				break;
			}
		}
	}
}

bool UUInventoryComponent::HasRequiredItem(const UItemDataAsset* Item) const
{
	if (!Item) return false;
	return ItemMap.Contains(Item->ObjectID);
}

bool UUInventoryComponent::HasRequiredItemWithQuantity(const UItemDataAsset* Item, int Quantity) const
{
	if (!Item || Quantity <= 0) return false;

	const FInventoryItem* Existing = ItemMap.Find(Item->ObjectID);
	return Existing && Existing->Quantity >= Quantity;
}



