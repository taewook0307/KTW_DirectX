#include "PreCompile.h"
#include "BaseCharacter.h"

#include "RunDust.h"
#include "JumpDust.h"
#include "DashDust.h"
#include "ParryEffect.h"
#include "SpecialAttackDust.h"

void BaseCharacter::CreateRunDust()
{
	std::shared_ptr<RunDust> RunEffect = GetLevel()->CreateActor<RunDust>(EUPDATEORDER::Effect);
	float4 Pos = Transform.GetWorldPosition();
	RunEffect->Transform.SetLocalPosition(Pos);
}

void BaseCharacter::CreateJumpDust()
{
	GameEngineSound::SoundPlay("sfx_player_land_ground_01.wav");
	std::shared_ptr<JumpDust> JumpEffect = GetLevel()->CreateActor<JumpDust>(EUPDATEORDER::Effect);
	float4 Pos = Transform.GetWorldPosition();
	JumpEffect->Transform.SetLocalPosition(Pos);
}

void BaseCharacter::CreateDashDust(EACTORDIR _DustDir)
{
	std::shared_ptr<DashDust> DashEffect = GetLevel()->CreateActor<DashDust>(EUPDATEORDER::Effect);
	DashEffect->SetDashDustDir(_DustDir);
	float4 Pos = Transform.GetWorldPosition();
	DashEffect->Transform.SetLocalPosition(Pos);
}

void BaseCharacter::CreateParryEffect()
{
	GameEngineSound::SoundPlay("sfx_player_parry_slap_01.wav");
	std::shared_ptr<ParryEffect> Parry = GetLevel()->CreateActor<ParryEffect>(EUPDATEORDER::Effect);
	float4 Pos = Transform.GetWorldPosition();
	Parry->Transform.SetLocalPosition(Pos);
	PlusHitSuccessParry();
}

void BaseCharacter::CreateSpecialDust(EDIRECTION8 _DustDirection)
{
	std::shared_ptr<SpecialAttackDust> SpecialAttackEffect = GetLevel()->CreateActor<SpecialAttackDust>(EUPDATEORDER::Effect);
	SpecialAttackEffect->SetSpecialAttackDustDirection(_DustDirection);
	float4 Pos = Transform.GetWorldPosition();
	SpecialAttackEffect->Transform.SetLocalPosition(Pos);
}