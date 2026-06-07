#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTD_CheckIfZombieInRangeDeWolfJorn.generated.h"

UCLASS()
class DEWOLFJORNZOMBIERUNTIME_API UBTD_CheckIfZombieInRangeDeWolfJorn : public UBTDecorator
{
	GENERATED_BODY()

public:

protected:
	virtual bool CalculateRawConditionValue(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) const override;

public:
	UPROPERTY(EditAnywhere, Category="Condition")
	float Range = 1000.f;
};