#include "BTT_SetTargetAwayFromZombie.h"

#include "AIController.h"
#include "EditorReimportHandler.h"
#include "Survivor/SurvivorPawn.h"
#include "StudentPerceptorDeWolfJorn.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTT_SetTargetAwayFromZombie::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
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
		float distance = FVector::Dist(myLocation, zombie->GetActorLocation());
		if (distance < closestZombieRange)
		{
			closestZombie = zombie;
			closestZombieRange = distance;			
		}
	}
	
	auto fleeDirection = myLocation - closestZombie->GetActorLocation();
	
	FVector targetLocation = fleeDirection * 100;
	
	root.GetBlackboardComponent()->SetValueAsVector("WanderSpot", targetLocation);
	
	return EBTNodeResult::Succeeded;
}
