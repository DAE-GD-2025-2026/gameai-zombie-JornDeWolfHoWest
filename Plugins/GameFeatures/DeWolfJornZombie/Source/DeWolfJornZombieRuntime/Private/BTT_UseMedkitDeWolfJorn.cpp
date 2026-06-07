#include "BTT_UseMedkitDeWolfJorn.h"

#include "AIController.h"
#include "StudentPerceptorDeWolfJorn.h"
#include "Survivor/SurvivorPawn.h"


EBTNodeResult::Type UBTT_UseMedkitDeWolfJorn::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	ASurvivorPawn* myPawn = Cast<ASurvivorPawn>(root.GetAIOwner()->GetPawn());
	if (!myPawn) return EBTNodeResult::Failed;
	UStudentPerceptorDeWolfJorn* perceptor = myPawn->GetComponentByClass<UStudentPerceptorDeWolfJorn>();
	if (!perceptor) return EBTNodeResult::Failed;
	
	
	// Do we have a medkit to heal?
	if (!perceptor->HasMedkit()) return EBTNodeResult::Failed;

	perceptor->Heal();
	
	return EBTNodeResult::Succeeded;
}
