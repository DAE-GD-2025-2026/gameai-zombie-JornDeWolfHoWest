#include "BTD_NeedsFood.h"

#include "AIController.h"
#include "GameAI_Zombie/Survivor/SurvivorPawn.h"
#include "StudentPerceptorDeWolfJorn.h"

bool UBTD_NeedsFood::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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
	if (Perceptor->HasFood())
		return false;
	
	// Check if any on the map
	auto foodList = Perceptor->GetSeenFood();
	if (foodList.IsEmpty())
		return false;

	AActor* closestFood = nullptr;
	float closestDistance = 9999999.f;
	for (AActor* food : foodList)
	{
		if (!food) continue;
		
		float distance = FVector::Dist(food->GetActorLocation(), MyPawn->GetActorLocation());
		if (distance < closestDistance)
		{
			closestFood = food;
			closestDistance = distance;
		}
	}
	
	OwnerComp.GetBlackboardComponent()->SetValueAsObject("ItemTarget", closestFood);
	
	return true;
}
