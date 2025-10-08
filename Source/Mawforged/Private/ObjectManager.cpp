#include "ObjectManager.h"
#include "Misc/Guid.h"
#include "Misc/MessageDialog.h"

UObjectManager& UObjectManager::Get()
{
    static UObjectManager* Singleton = NewObject<UObjectManager>();
    Singleton->AddToRoot();
    return *Singleton;
}

uint64 UObjectManager::GenerateUniqueID()
{
    uint64 NewID = 0;
    do
    {
        FGuid Guid = FGuid::NewGuid();
        NewID = FCrc::MemCrc32(&Guid, sizeof(Guid));
    } while (RegisteredItems.Contains(NewID));

    return NewID;
}

void UObjectManager::RegisterItem(UItemDataAsset* Item)
{
    if (!Item) return;

    if (Item->ObjectID == 0)
    {
        Item->ObjectID = GenerateUniqueID();
        Item->Modify();
    }

    RegisteredItems.FindOrAdd(Item->ObjectID) = Item;
}

UItemDataAsset* UObjectManager::GetItemByID(uint64 ObjectID) const
{
    if (RegisteredItems.Contains(ObjectID))
    {
        return RegisteredItems[ObjectID];
    }
    return nullptr;
}