#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SetTargetAwayFromZombieDeWolfJorn.generated.h"

UCLASS()
class DEWOLFJORNZOMBIERUNTIME_API UBTT_SetTargetAwayFromZombieDeWolfJorn : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;
public:	
	UPROPERTY(EditAnywhere, Category = "Task")
	float Distance = 100.f;
};