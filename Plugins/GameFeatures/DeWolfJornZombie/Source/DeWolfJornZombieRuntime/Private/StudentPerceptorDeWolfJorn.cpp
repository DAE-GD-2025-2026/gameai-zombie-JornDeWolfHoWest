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
	
	
	
	AAIController* AIController =
		Cast<AAIController>(SurvivorPawn->GetController());

	if (!AIController)
		return;

	BB = AIController->GetBlackboardComponent();
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

void UStudentPerceptorDeWolfJorn::MarkHouseAsSeen()
{	
	AHouse* house = Cast<AHouse>(BB->GetValueAsObject("HouseTarget"));
	
	SeenHouses.Add(house);
	VisibleHouses.Remove(house);
}
