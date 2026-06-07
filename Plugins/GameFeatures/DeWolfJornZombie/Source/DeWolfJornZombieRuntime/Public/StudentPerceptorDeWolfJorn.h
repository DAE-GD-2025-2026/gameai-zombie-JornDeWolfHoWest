// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Damage.h"
#include "GameAI_Zombie/Survivor/SurvivorPawn.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "AIController.h"
#include "Common/InventoryComponent.h"

#include "StudentPerceptorDeWolfJorn.generated.h"

UENUM()
enum class EInventorySlot : uint8
{
	WeaponSlot = 0,
	MedkitSlot = 1,
	FoodSlot = 2
};

UENUM()
enum class ESurvivorState : uint8
{
	Explore,
	Loot,
	Flee
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEWOLFJORNZOMBIERUNTIME_API UStudentPerceptorDeWolfJorn : public UActorComponent
{
	GENERATED_BODY()

public:
	UStudentPerceptorDeWolfJorn();

	virtual void BeginPlay() override;

	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
	UPROPERTY()
	UInventoryComponent* Inventory;
	UBlackboardComponent* BB;
	ASurvivorPawn* SurvivorPawn;

	UPROPERTY()
	TArray<AActor*> VisibleZombies;

	UPROPERTY()
	TArray<AActor*> VisibleHouses;
	UPROPERTY()
	TArray<AActor*> SeenHouses;
	
	UPROPERTY()
	TArray<AActor*> SeenWeapons;

	UPROPERTY()
	TArray<AActor*> VisibleItems;

	ESurvivorState CurrentState = ESurvivorState::Explore;

	
	
public:
	const TArray<AActor*>& GetVisibleZombies() const
	{
		return VisibleZombies;
	}

	const TArray<AActor*>& GetVisibleHouses() const
	{
		return VisibleHouses;
	}
	
	const TArray<AActor*>& GetSeenWeapons() const
	{
		return SeenWeapons;
	}
	
	void MarkHouseAsSeen();
	void GetNextHouseToCheck();
	bool HasWeapon();

	void PickupItem(AActor* Actor);
};
