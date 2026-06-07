#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTT_EatFoodDeWolfJorn.generated.h"

UCLASS()
class DEWOLFJORNZOMBIERUNTIME_API UBTT_EatFoodDeWolfJorn : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;
};