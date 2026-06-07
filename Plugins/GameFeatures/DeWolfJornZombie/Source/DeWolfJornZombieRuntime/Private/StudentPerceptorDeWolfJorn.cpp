// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptorDeWolfJorn.h"
#include "GameAI_Zombie/Zombies/BaseZombie.h"
#include "GameAI_Zombie/Village/House/House.h"
#include "GameAI_Zombie/Items/BaseItem.h"
#include "GameAI_Zombie/Items/Medkit.h"
#include "GameAI_Zombie/Items/Food.h"
#include "GameAI_Zombie/Items/Weapon.h"
#include "GameAI_Zombie/Items/ItemType.h"
#include "GameAI_Zombie/PurgeZones/PurgeZone.h"


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
}

static AActor* GetClosest(const TArray<AActor*>& List, const FVector& Origin)
{
	AActor* Best = nullptr;
	float BestDist = FLT_MAX;

	for (AActor* A : List)
	{
		if (!A) continue;

		float Dist = FVector::Dist(A->GetActorLocation(), Origin);

		if (Dist < BestDist)
		{
			BestDist = Dist;
			Best = A;
		}
	}

	return Best;
}

void UStudentPerceptorDeWolfJorn::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!SurvivorPawn)
		return;

	AAIController* AIController =
		Cast<AAIController>(SurvivorPawn->GetController());

	if (!AIController)
		return;

	UBlackboardComponent* BB = AIController->GetBlackboardComponent();

	if (!BB)
		return;

	FVector Origin = SurvivorPawn->GetActorLocation();

	// 1. ZOMBIE PRIORITY
	AActor* Zombie = GetClosest(VisibleZombies, Origin);
	BB->SetValueAsObject(TEXT("ZombieTarget"), Zombie);

	// 2. ITEM PRIORITY
	AActor* Item = GetClosest(VisibleItems, Origin);
	BB->SetValueAsObject(TEXT("ItemTarget"), Item);

	// 3. HOUSE PRIORITY
	AActor* House = GetClosest(VisibleHouses, Origin);
	BB->SetValueAsObject(TEXT("HouseTarget"), House);

	// 4. STATE DECISION (simple logic for now)
	if (Zombie)
	{
		BB->SetValueAsName(TEXT("CurrentState"), TEXT("FLEE"));
	}
	else if (Item)
	{
		BB->SetValueAsName(TEXT("CurrentState"), TEXT("LOOT"));
	}
	else
	{
		BB->SetValueAsName(TEXT("CurrentState"), TEXT("EXPLORE"));
	}
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
		if (!VisibleHouses.Contains(house))
		{
			VisibleHouses.Add(house);
		}
		return;
	}
}
