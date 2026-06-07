#include "BTT_ShootZombieDeWolfJorn.h"

#include "AIController.h"
#include "HLSLMathAliases.h"
#include "StudentPerceptorDeWolfJorn.h"
#include "Survivor/SurvivorPawn.h"

inline EBTNodeResult::Type UBTT_ShootZombieDeWolfJorn::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	ASurvivorPawn* myPawn = Cast<ASurvivorPawn>(root.GetAIOwner()->GetPawn());
	if (!myPawn) return EBTNodeResult::Failed;
	UStudentPerceptorDeWolfJorn* perceptor = myPawn->GetComponentByClass<UStudentPerceptorDeWolfJorn>();
	if (!perceptor) return EBTNodeResult::Failed;
		
	
	
	FVector myLocation = myPawn->GetActorLocation();
	
	// Get closest zombie
	AActor* closestZombie = nullptr;
	float closestZombieRange = 999999999.f;
	for (auto zombie : perceptor->GetVisibleZombies())
	{
		if (!zombie) continue;
		
		float distance = FVector::Dist(myLocation, zombie->GetActorLocation());
		if (distance < closestZombieRange)
		{
			closestZombie = zombie;
			closestZombieRange = distance;			
		}
	}
	
	FRotator lookAtRotation = (closestZombie->GetActorLocation() - myLocation).Rotation();
	lookAtRotation.Pitch = 0;
	lookAtRotation.Roll = 0;
	
	myPawn->SetActorRotation(lookAtRotation);
	
	perceptor->ShootGun();
	
	if (auto health = closestZombie->GetComponentByClass<UHealthComponent>())
	{
		if (health->IsDead())
			perceptor->RemoveZombie(closestZombie);
	}
	
	return EBTNodeResult::Succeeded;
}
