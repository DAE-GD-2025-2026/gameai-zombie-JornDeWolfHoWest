#pragma once 

#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SetRandomWanderPointDeWolfJorn.generated.h"

UCLASS()
class DEWOLFJORNZOMBIERUNTIME_API UBTT_SetRandomWanderPointDeWolfJorn : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;
	
public:
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector TargetKey;
	
	UPROPERTY(EditAnywhere, Category = "Task")
	float MinimumRange = 100.f;
	
	
	UPROPERTY(EditAnywhere, Category = "Task")
	float MaximumRange = 1000.f;
	
	UPROPERTY(EditAnywhere, Category = "Task")
	float MaxAngleDeviation = 5.f;
};