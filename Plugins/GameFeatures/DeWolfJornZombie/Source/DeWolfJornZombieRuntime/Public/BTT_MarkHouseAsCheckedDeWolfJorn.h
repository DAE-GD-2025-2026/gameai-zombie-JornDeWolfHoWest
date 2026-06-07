#pragma once 

#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MarkHouseAsCheckedDeWolfJorn.generated.h"

UCLASS()
class DEWOLFJORNZOMBIERUNTIME_API UBTT_MarkHouseAsCheckedDeWolfJorn : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;
};