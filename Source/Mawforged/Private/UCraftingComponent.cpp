// Fill out your copyright notice in the Description page of Project Settings.


#include "Mawforged/Public/UCraftingComponent.h"
#include "Mawforged/Public/UCraftingStationComponent.h"
#include "Mawforged/Public/CraftingResolver.h"

// Sets default values for this component's properties
UUCraftingComponent::UUCraftingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UUCraftingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UUCraftingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UUCraftingComponent::CanCraft(UCraftingRecipeDataAsset* Recipe, AActor* Station, EMessageType& messageType, FString& outError)
{
    outError = "Recipe is invalid";
    messageType = EMessageType::RecipeNotFound;

    if (!Recipe || !Station)
    {
        return false;
    }

    // Check station type
    UUCraftingStationComponent* StationComp = Station->FindComponentByClass<UUCraftingStationComponent>();
    if (!StationComp || StationComp->StationType != Recipe->Station)
    {
        return false;
    }

    // Check inventory for recipe
    UUInventoryComponent* Inventory = GetInventory();
    if (!Inventory || !Inventory->HasRequiredItem(Recipe))
    {
        outError = "You don't have reciepy";
        messageType = EMessageType::RecipeNotFound;
        return false;
    }

    //check inventory for components
    if (!CheckInventoryForRecipeItems(Recipe))
    {
        outError = "You don't have components/Ingots to craft";
        messageType = EMessageType::ItemNotFound;
        return false;
    }

    outError = "Press Tab to craft";
    messageType = EMessageType::Craft;

    return true;
}

bool UUCraftingComponent::Craft(UCraftingRecipeDataAsset* Recipe, AActor* Station, EQualityModifier Quality, FString& Error, EMessageType& messageType)
{
    if (!CanCraft(Recipe, Station, messageType, Error))
    {
        UE_LOG(LogTemp, Warning, TEXT("Crafting failed: %s"), *Error);
        return false;
    }

    UUInventoryComponent* Inventory = GetInventory();
    if (!Inventory) return false;

    // Consume items
    if (!ConsumeItems(Recipe))
    {
        return false;
    }

    // Resolve final item

    UIngotDataAsset* CraftedItem = UCraftingResolver::Resolve(this, Recipe, Inventory, Quality);

    // Add to inventory
    Inventory->AddItem(CraftedItem);

    return true;
}

bool UUCraftingComponent::GetQualityModifier(float barPosition, float barBound, EQualityModifier& quality, FString& ModifierStatus)
{
    int scalePosition = 100 * barPosition / barBound;
    
    if (scalePosition < 20 || scalePosition > 80)
    {
        ModifierStatus = "Fail";
        quality = EQualityModifier::Fail;
        return false;
    }
    else if (scalePosition < 40)
    {
        ModifierStatus = "Good";
        quality = EQualityModifier::Good;
    }
    else if (scalePosition < 60)
    {
        ModifierStatus = "Perfect!";
        quality = EQualityModifier::Perfect;
    }
    else
    {
        ModifierStatus = "Great";
        quality = EQualityModifier::Great;
    }

    return true;
}

bool UUCraftingComponent::CheckInventoryForRecipeItems(UCraftingRecipeDataAsset* Recipe) const
{
    if (!Recipe)
    {
        return false;
    }

    UUInventoryComponent* inventory = GetInventory();
    if (!inventory)
    {
        return false;
    }

    for (FRecipeIngot& ingot : Recipe->RequiredIngots)
    {
        if (!inventory->HasRequiredItemWithQuantity(ingot.Ingot, ingot.Quantity))
        {
            return false;
        }
    }

    for (FRecipeComponent& component : Recipe->RequiredComponents)
    {
        if (!inventory->HasRequiredItemWithQuantity(component.Component, component.Quantity))
        {
            return false;
        }
    }

    return true;
}

UUInventoryComponent* UUCraftingComponent::GetInventory() const
{
    if (AActor* Owner = GetOwner())
    {
        return Owner->FindComponentByClass<UUInventoryComponent>();
    }
    return nullptr;
}

bool UUCraftingComponent::ConsumeItems(UCraftingRecipeDataAsset* Recipe)
{
    UUInventoryComponent* inventory = GetInventory();
    if (!inventory)
    {
        return false;
    }

    for (FRecipeIngot& ingot : Recipe->RequiredIngots)
    {
        inventory->RemoveItem(ingot.Ingot, ingot.Quantity);
    }

    for (FRecipeComponent& component : Recipe->RequiredComponents)
    {
        inventory->RemoveItem(component.Component, component.Quantity);
    }

    return true;
}


