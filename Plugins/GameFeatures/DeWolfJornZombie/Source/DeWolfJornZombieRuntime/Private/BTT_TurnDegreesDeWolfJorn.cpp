#include "BTT_TurnDegreesDeWolfJorn.h"

#include "AIController.h"
#include "Survivor/SurvivorPawn.h"

EBTNodeResult::Type UBTT_TurnDegreesDeWolfJorn::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{

	ASurvivorPawn* myPawn = Cast<ASurvivorPawn>(root.GetAIOwner()->GetPawn());
	if (!myPawn) return EBTNodeResult::Failed;
	
	auto rotation = myPawn->GetActorRotation();
	rotation.Yaw += TurnAngle;
	myPawn->SetActorRotation(rotation);
	return EBTNodeResult::Succeeded;
}
