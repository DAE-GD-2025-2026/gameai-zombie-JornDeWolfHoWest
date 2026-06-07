#include "BTT_MarkHouseAsCheckedDeWolfJorn.h"

#include "AIController.h"
#include "StudentPerceptorDeWolfJorn.h"
#include "Survivor/SurvivorPawn.h"

EBTNodeResult::Type UBTT_MarkHouseAsCheckedDeWolfJorn::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	ASurvivorPawn* myPawn = Cast<ASurvivorPawn>(root.GetAIOwner()->GetPawn());
	if (!myPawn) return EBTNodeResult::Failed;
	UStudentPerceptorDeWolfJorn* perceptor = myPawn->GetComponentByClass<UStudentPerceptorDeWolfJorn>();
	if (!perceptor) return EBTNodeResult::Failed;
	
	perceptor->MarkHouseAsSeen();
	perceptor->GetNextHouseToCheck();
	
	return  EBTNodeResult::Succeeded;	
}