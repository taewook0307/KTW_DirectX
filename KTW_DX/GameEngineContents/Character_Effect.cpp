#include "PreCompile.h"
#include "BaseCharacter.h"

#include "JumpDust.h"
#include "DashDust.h"
#include "SpecialAttackDust.h"

void BaseCharacter::CreateJumpDust()
{
	std::shared_ptr<JumpDust> JumpEffect = GetLevel()->CreateActor<JumpDust>(UpdateOrder::UI);
	float4 Pos = Transform.GetWorldPosition();
	JumpEffect->Transform.SetLocalPosition(Pos);
}

void BaseCharacter::CreateDashDust()
{
	std::shared_ptr<DashDust> DashEffect = GetLevel()->CreateActor<DashDust>(UpdateOrder::UI);
	float4 Pos = Transform.GetWorldPosition();
	DashEffect->Transform.SetLocalPosition(Pos);
}

void BaseCharacter::CreateParryEffect()
{

}

void BaseCharacter::CreateSpecialDust()
{
	std::shared_ptr<SpecialAttackDust> SpecialAttackEffect = GetLevel()->CreateActor<SpecialAttackDust>(UpdateOrder::UI);
	float4 Pos = Transform.GetWorldPosition();
	SpecialAttackEffect->Transform.SetLocalPosition(Pos);
}