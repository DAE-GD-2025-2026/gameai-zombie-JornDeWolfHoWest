// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptorDeWolfJorn.h"

#include "AIController.h"
#include "Common/InventoryComponent.h"
#include "GameAI_Zombie/Zombies/BaseZombie.h"
#include "GameAI_Zombie/Village/House/House.h"
#include "GameAI_Zombie/Items/BaseItem.h"
#include "GameAI_Zombie/Items/Medkit.h"
#include "GameAI_Zombie/Items/Food.h"
#include "GameAI_Zombie/Items/Weapon.h"
#include "GameAI_Zombie/Items/ItemType.h"
#include "GameAI_Zombie/PurgeZones/PurgeZone.h"

#include "GameAI_Zombie/Common/InventoryComponent.h"

#include "Elements/Framework/TypedElementSorter.h"


UStudentPerceptorDeWolfJorn::UStudentPerceptorDeWolfJorn()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStudentPerceptorDeWolfJorn::BeginPlay()
{
	Super::BeginPlay();

	SurvivorPawn = Cast<ASurvivorPawn>(GetOwner());

	if (auto PerceptionComp =
		GetOwner()->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(
			this,
			&UStudentPerceptorDeWolfJorn::OnPerceptionUpdated);
	}


	AAIController* AIController =
		Cast<AAIController>(SurvivorPawn->GetController());

	if (!AIController)
		return;

	BB = AIController->GetBlackboardComponent();


	Inventory = SurvivorPawn->GetComponentByClass<UInventoryComponent>();
}

void UStudentPerceptorDeWolfJorn::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UStudentPerceptorDeWolfJorn::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	auto name = Actor->GetName();
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, name);

	// If actor is enemy zombie, add him to visible zombies
	if (auto enemy = Cast<ABaseZombie>(Actor))
	{
		if (!VisibleZombies.Contains(enemy))
		{
			VisibleZombies.Add(enemy);
		}
		return;
	}
	// If actor is house, add him to visible houses (to explore later)
	if (auto house = Cast<AHouse>(Actor))
	{
		if (!VisibleHouses.Contains(house) and !SeenHouses.Contains(house))
		{
			VisibleHouses.Add(house);
			GetNextHouseToCheck();
		}
		return;
	}
	// If Item
	if (auto item = Cast<ABaseItem>(Actor))
	{
		switch (item->GetItemType()) {
		case EItemType::Food:
			if (!SeenFood.Contains(item))
			{
				SeenFood.Add(item);
			}
			break;
		case EItemType::Medkit:
			if (!SeenMedkits.Contains(item))
			{
				SeenMedkits.Add(item);
			}
			break;
		case EItemType::Shotgun:
		case EItemType::Pistol:
			if (!SeenWeapons.Contains(item))
			{
				SeenWeapons.Add(item);
			}
			break;
		case EItemType::Garbage:
			break;
		}
	}
}

void UStudentPerceptorDeWolfJorn::ShootGun()
{
	Inventory->UseItem(static_cast<int>(EInventorySlot::WeaponSlot));

	ABaseItem* item = Inventory->GetInventory()[static_cast<int>(EInventorySlot::WeaponSlot)];

	if (item->GetValue() <= 0)
	{
		Inventory->RemoveItem(static_cast<int>(EInventorySlot::WeaponSlot));
	}
}

void UStudentPerceptorDeWolfJorn::RemoveZombie(AActor* Actor)
{
	if (VisibleZombies.Contains(Actor))
		VisibleZombies.Remove(Actor);
}

void UStudentPerceptorDeWolfJorn::GetNextHouseToCheck()
{
	if (VisibleHouses.Num() <= 0)
	{
		BB->SetValueAsObject("HouseTarget", nullptr);
		return;
	}

	// More houses to check!


	AActor* closestHouse = nullptr;
	float closestDistance = TNumericLimits<float>::Max();

	const FVector Location = GetOwner()->GetActorLocation();

	for (AActor* House : VisibleHouses)
	{
		if (!IsValid(House))
		{
			continue;
		}

		const float DistanceSq =
			FVector::DistSquared(Location, House->GetActorLocation());

		if (DistanceSq < closestDistance)
		{
			closestDistance = DistanceSq;
			closestHouse = House;
		}
	}

	BB->SetValueAsObject("HouseTarget", closestHouse);
}

bool UStudentPerceptorDeWolfJorn::HasWeapon()
{
	return Inventory->GetInventory()[static_cast<int>(EInventorySlot::WeaponSlot)] != nullptr;
}

int UStudentPerceptorDeWolfJorn::GetCurrentFoodValue()
{
	return Inventory->GetInventory()[static_cast<int>(EInventorySlot::FoodSlot)]->GetValue();
}

bool UStudentPerceptorDeWolfJorn::HasFood()
{
	return Inventory->GetInventory()[static_cast<int>(EInventorySlot::FoodSlot)] != nullptr;
}

void UStudentPerceptorDeWolfJorn::Eat()
{
	Inventory->UseItem(static_cast<int>(EInventorySlot::FoodSlot));

	ABaseItem* item = Inventory->GetInventory()[static_cast<int>(EInventorySlot::FoodSlot)];

	if (item->GetValue() <= 0)
	{
		Inventory->RemoveItem(static_cast<int>(EInventorySlot::FoodSlot));
	}
}

int UStudentPerceptorDeWolfJorn::GetCurrentMedkitHealingValue()
{
	return Inventory->GetInventory()[static_cast<int>(EInventorySlot::MedkitSlot)]->GetValue();
}

bool UStudentPerceptorDeWolfJorn::HasMedkit()
{
	return Inventory->GetInventory()[static_cast<int>(EInventorySlot::MedkitSlot)] != nullptr;
}

void UStudentPerceptorDeWolfJorn::Heal()
{
	Inventory->UseItem(static_cast<int>(EInventorySlot::MedkitSlot));

	ABaseItem* item = Inventory->GetInventory()[static_cast<int>(EInventorySlot::MedkitSlot)];

	if (item->GetValue() <= 0)
	{
		Inventory->RemoveItem(static_cast<int>(EInventorySlot::MedkitSlot));
	}
}

void UStudentPerceptorDeWolfJorn::PickupItem(AActor* Actor)
{
	if (!IsValid(Actor)) return;

	auto item = Cast<ABaseItem>(Actor);
	switch (item->GetItemType())
	{
	case EItemType::Food:
		Inventory->GrabItem(static_cast<int>(EInventorySlot::FoodSlot), item);
		break;


	case EItemType::Medkit:
		Inventory->GrabItem(static_cast<int>(EInventorySlot::MedkitSlot), item);
		break;


	case EItemType::Shotgun:
	case EItemType::Pistol:
		Inventory->GrabItem(static_cast<int>(EInventorySlot::WeaponSlot), item);
		break;


	default:
	case EItemType::Garbage:
		// Useless-, why even grab it?
		break;
	}
}

void UStudentPerceptorDeWolfJorn::MarkHouseAsSeen()
{
	AHouse* house = Cast<AHouse>(BB->GetValueAsObject("HouseTarget"));

	SeenHouses.Add(house);
	VisibleHouses.Remove(house);
}
