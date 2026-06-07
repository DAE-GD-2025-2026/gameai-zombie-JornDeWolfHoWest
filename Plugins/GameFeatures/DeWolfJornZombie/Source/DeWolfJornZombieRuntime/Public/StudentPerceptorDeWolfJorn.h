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

#include "StudentPerceptorDeWolfJorn.generated.h"

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
	UBlackboardComponent* BB;
	ASurvivorPawn* SurvivorPawn;

	UPROPERTY()
	TArray<AActor*> VisibleZombies;

	UPROPERTY()
	TArray<AActor*> VisibleHouses;
	UPROPERTY()
	TArray<AActor*> SeenHouses;

	UPROPERTY()
	TArray<AActor*> VisibleItems;

	ESurvivorState CurrentState = ESurvivorState::Explore;

	
	
public:

	bool HasZombie() const
	{
		return VisibleZombies.Num() > 0;
	}

	bool HasHouse() const
	{
		return VisibleHouses.Num() > 0;
	}

	bool HasItem() const
	{
		return VisibleItems.Num() > 0;
	}

	const TArray<AActor*>& GetVisibleZombies() const
	{
		return VisibleZombies;
	}

	const TArray<AActor*>& GetVisibleHouses() const
	{
		return VisibleHouses;
	}
	
	void MarkHouseAsSeen();
	void GetNextHouseToCheck();

	const TArray<AActor*>& GetVisibleItems() const
	{
		return VisibleItems;
	}
};
