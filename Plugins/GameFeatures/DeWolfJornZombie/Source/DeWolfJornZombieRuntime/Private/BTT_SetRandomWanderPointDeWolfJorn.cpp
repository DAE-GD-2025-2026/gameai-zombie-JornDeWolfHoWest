#include "BTT_SetRandomWanderPointDeWolfJorn.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTT_SetRandomWanderPointDeWolfJorn::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	UBlackboardComponent* BlackboardComponent = root.GetBlackboardComponent();
	if (!BlackboardComponent) return EBTNodeResult::Failed;
	
	AAIController* AIController = root.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;
	
	APawn* pawn = AIController->GetPawn();
	if (!pawn) return EBTNodeResult::Failed;
	
	// Set angle offset first
	float angleOffset = FMath::FRandRange(-MaxAngleDeviation, MaxAngleDeviation);
	
	FVector direction = pawn->GetActorForwardVector();
	direction = direction.RotateAngleAxis(angleOffset, FVector::UpVector);
	
	// Set random distance
	float distance = FMath::FRandRange(MinimumRange, MaximumRange);
	
	FVector wanderPoint = pawn->GetActorLocation() + direction * distance;
	
	BlackboardComponent->SetValueAsVector(TargetKey.SelectedKeyName, wanderPoint);
	
	return  EBTNodeResult::Succeeded;
}
