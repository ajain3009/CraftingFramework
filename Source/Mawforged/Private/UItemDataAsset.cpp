#include "UItemDataAsset.h"
#include "Mawforged/Public/ObjectManager.h"

void UItemDataAsset::PostInitProperties()
{
    Super::PostInitProperties();

#if WITH_EDITOR
    UObjectManager::Get().RegisterItem(this);
#endif
}