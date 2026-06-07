#include "BTD_NeedsMedkitDeWolfJorn.h"

#include "AIController.h"
#include "GameAI_Zombie/Survivor/SurvivorPawn.h"
#include "StudentPerceptorDeWolfJorn.h"

bool UBTD_NeedsMedkitDeWolfJorn::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ASurvivorPawn* MyPawn =
		Cast<ASurvivorPawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (!MyPawn)
	{
		return false;
	}

	UStudentPerceptorDeWolfJorn* Perceptor =
		MyPawn->GetComponentByClass<UStudentPerceptorDeWolfJorn>();

	if (!Perceptor)
	{
		return false;
	}
	// Check for any food needed in our inv
	if (Perceptor->HasMedkit())
		return false;
	
	// Check if any on the map
	auto medkitList = Perceptor->GetSeenMedkit();
	if (medkitList.IsEmpty())
		return false;

	AActor* closestMedkit = nullptr;
	float closestDistance = 9999999.f;
	for (AActor* medkit : medkitList)
	{
		if (!medkit) continue;
		
		float distance = FVector::Dist(medkit->GetActorLocation(), MyPawn->GetActorLocation());
		if (distance < closestDistance)
		{
			closestMedkit = medkit;
			closestDistance = distance;
		}
	}
	
	OwnerComp.GetBlackboardComponent()->SetValueAsObject("ItemTarget", closestMedkit);
	
	return true;
}
