#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTD_CheckHasWeaponDeWolfJorn.generated.h"

UCLASS()
class DEWOLFJORNZOMBIERUNTIME_API UBTD_CheckHasWeaponDeWolfJorn : public UBTDecorator
{
	GENERATED_BODY()
protected:
	virtual bool CalculateRawConditionValue(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) const override;
};