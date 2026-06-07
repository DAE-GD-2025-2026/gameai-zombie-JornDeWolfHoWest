#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTT_TurnDegreesDeWolfJorn.generated.h"

UCLASS()
class DEWOLFJORNZOMBIERUNTIME_API UBTT_TurnDegreesDeWolfJorn : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;
	
public:	
	UPROPERTY(EditAnywhere, Category = "Task")
	float TurnAngle = 45.f;
};