#include "PreCompile.h"
#include "BaseCharacter.h"

#include "RunDust.h"
#include "JumpDust.h"
#include "DashDust.h"
#include "ParryEffect.h"
#include "SpecialAttackDust.h"

void BaseCharacter::CreateRunDust()
{
	std::shared_ptr<RunDust> RunEffect = GetLevel()->CreateActor<RunDust>(UpdateOrder::Effect);
	float4 Pos = Transform.GetWorldPosition();
	RunEffect->Transform.SetLocalPosition(Pos);
}

void BaseCharacter::CreateJumpDust()
{
	std::shared_ptr<JumpDust> JumpEffect = GetLevel()->CreateActor<JumpDust>(UpdateOrder::Effect);
	float4 Pos = Transform.GetWorldPosition();
	JumpEffect->Transform.SetLocalPosition(Pos);
}

void BaseCharacter::CreateDashDust(ActorDir _DustDir)
{
	std::shared_ptr<DashDust> DashEffect = GetLevel()->CreateActor<DashDust>(UpdateOrder::Effect);
	DashEffect->SetDashDustDir(_DustDir);
	float4 Pos = Transform.GetWorldPosition();
	DashEffect->Transform.SetLocalPosition(Pos);
}

void BaseCharacter::CreateParryEffect()
{
	std::shared_ptr<ParryEffect> Parry = GetLevel()->CreateActor<ParryEffect>(UpdateOrder::Effect);
	float4 Pos = Transform.GetWorldPosition();
	Parry->Transform.SetLocalPosition(Pos);
}

void BaseCharacter::CreateSpecialDust(Direction8 _DustDirection)
{
	std::shared_ptr<SpecialAttackDust> SpecialAttackEffect = GetLevel()->CreateActor<SpecialAttackDust>(UpdateOrder::Effect);
	SpecialAttackEffect->SetSpecialAttackDustDirection(_DustDirection);
	float4 Pos = Transform.GetWorldPosition();
	SpecialAttackEffect->Transform.SetLocalPosition(Pos);
}