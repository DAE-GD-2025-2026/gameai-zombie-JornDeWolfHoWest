// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptorDeWolfJorn.h"

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