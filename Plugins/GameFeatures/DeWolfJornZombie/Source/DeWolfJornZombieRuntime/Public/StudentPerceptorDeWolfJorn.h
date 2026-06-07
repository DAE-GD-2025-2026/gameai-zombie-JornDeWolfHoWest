// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameAI_Zombie/Survivor/SurvivorPawn.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "StudentPerceptorDeWolfJorn.generated.h"

UENUM()
enum class EInventorySlot : uint8
{
	WeaponSlot = 0,
	MedkitSlot = 1,
	FoodSlot = 2
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
	UHealthComponent* Health;
	UPROPERTY()
	UInventoryComponent* Inventory;
	UPROPERTY()
	UStaminaComponent* Stamina;
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
	TArray<AActor*> SeenFood;
	UPROPERTY()
	TArray<AActor*> SeenMedkits;


	
	
public:
	void PickupItem(AActor* Actor);
	
	
	const TArray<AActor*>& GetVisibleZombies() const
	{
		return VisibleZombies;
	}
	void ShootGun();
	void RemoveZombie(AActor* Actor);
	
	const TArray<AActor*>& GetVisibleHouses() const
	{
		return VisibleHouses;
	}
	void MarkHouseAsSeen();
	void GetNextHouseToCheck();
	
	const TArray<AActor*>& GetSeenWeapons() const
	{
		return SeenWeapons;
	}
	bool HasWeapon();
	
	const TArray<AActor*>& GetSeenFood() const
	{
		return SeenFood;
	}
	int GetCurrentFoodValue();
	bool HasFood();
	void Eat();
	
	const TArray<AActor*>& GetSeenMedkit() const
	{
		return SeenMedkits;
	}
	int GetCurrentMedkitHealingValue();
	bool HasMedkit();
	void Heal();

	const UHealthComponent* GetHealthComponent() const
	{
		return Health;
	}
	const UStaminaComponent* GetStaminaComponent() const	
	{
		return Stamina;
	}
};
