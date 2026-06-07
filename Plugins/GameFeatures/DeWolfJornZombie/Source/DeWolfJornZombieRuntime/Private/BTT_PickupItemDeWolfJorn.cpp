#include "BTT_PickupItemDeWolfJorn.h"

#include "AIController.h"
#include "StudentPerceptorDeWolfJorn.h"
#include "Survivor/SurvivorPawn.h"
#include "Items/BaseItem.h"

inline EBTNodeResult::Type UBTT_PickupItemDeWolfJorn::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	ASurvivorPawn* myPawn = Cast<ASurvivorPawn>(root.GetAIOwner()->GetPawn());
	if (!myPawn) return EBTNodeResult::Failed;
	UStudentPerceptorDeWolfJorn* perceptor = myPawn->GetComponentByClass<UStudentPerceptorDeWolfJorn>();
	if (!perceptor) return EBTNodeResult::Failed;
	
	auto itemObject = root.GetBlackboardComponent()->GetValueAsObject("ItemTarget");
	
	if (!itemObject) return EBTNodeResult::Failed;
	if (auto item = Cast<ABaseItem>(itemObject))
	{
		// Pickup item	
		perceptor->PickupItem(item);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
