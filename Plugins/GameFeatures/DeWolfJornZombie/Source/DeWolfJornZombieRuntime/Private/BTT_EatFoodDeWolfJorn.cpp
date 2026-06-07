#include "BTT_EatFoodDeWolfJorn.h"

#include "AIController.h"
#include "StudentPerceptorDeWolfJorn.h"
#include "Survivor/SurvivorPawn.h"

EBTNodeResult::Type UBTT_EatFoodDeWolfJorn::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	ASurvivorPawn* myPawn = Cast<ASurvivorPawn>(root.GetAIOwner()->GetPawn());
	if (!myPawn) return EBTNodeResult::Failed;
	UStudentPerceptorDeWolfJorn* perceptor = myPawn->GetComponentByClass<UStudentPerceptorDeWolfJorn>();
	if (!perceptor) return EBTNodeResult::Failed;
	
	// Do we have a food to eat?
	if (!perceptor->HasFood()) return EBTNodeResult::Failed;
	
	perceptor->Eat();
	
	return EBTNodeResult::Succeeded;
}
