#include "BTT_TurnDegrees.h"

#include "AIController.h"
#include "Survivor/SurvivorPawn.h"

EBTNodeResult::Type UBTT_TurnDegrees::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{

	ASurvivorPawn* myPawn = Cast<ASurvivorPawn>(root.GetAIOwner()->GetPawn());
	auto rotation = myPawn->GetActorRotation();
	rotation.Yaw += TurnAngle;
	myPawn->SetActorRotation(rotation);
	return EBTNodeResult::Succeeded;
}
