﻿#include "PreCompile.h"
#include "SummonAttackObject.h"

#include "SummonAttackObject_Effect.h"
#include "SummonAttackObject_Effect_Parry.h"

SummonAttackObject::SummonAttackObject()
{
}

SummonAttackObject::~SummonAttackObject()
{
}

void SummonAttackObject::CreateSummonEffect(const float4& _Pos)
{
	std::shared_ptr<SummonAttackObject_Effect> Effect = GetLevel()->CreateActor<SummonAttackObject_Effect>(EUPDATEORDER::Effect);
	Effect->Transform.SetLocalPosition(_Pos);
}

void SummonAttackObject::CreateSummonEffectParry(const float4& _Pos)
{
	std::shared_ptr<SummonAttackObject_Effect_Parry> Effect = GetLevel()->CreateActor<SummonAttackObject_Effect_Parry>(EUPDATEORDER::Effect);
	Effect->Transform.SetLocalPosition(_Pos);
}

bool SummonAttackObject::CameraOutCheck(const float4& _Pos)
{
	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 WinHalfScale = GameEngineCore::MainWindow.GetScale().Half();

	float MinX = CameraPos.X - WinHalfScale.X;
	float MaxX = CameraPos.X + WinHalfScale.X;
	float MinY = CameraPos.Y + WinHalfScale.Y;
	float MaxY = CameraPos.Y - WinHalfScale.Y;

	float4 Pos = _Pos;

	if (MinX > Pos.X
		|| MaxX < Pos.X
		|| MinY < Pos.Y
		|| MaxY > Pos.Y)
	{
		return true;
	}

	return false;
}

bool SummonAttackObject::CameraOutCheck()
{
	float4 Pos = Transform.GetWorldPosition();
	return CameraOutCheck(Pos);
}

void SummonAttackObject::AttackSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 3);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_DLC_Graveyard_Devil_Shoot_01.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_DLC_Graveyard_Devil_Shoot_02.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_DLC_Graveyard_Devil_Shoot_03.wav");
		break;
	default:
		GameEngineSound::SoundPlay("sfx_DLC_Graveyard_Devil_Shoot_04.wav");
		break;
	}
}