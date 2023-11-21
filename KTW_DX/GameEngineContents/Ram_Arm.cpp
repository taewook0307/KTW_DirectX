#include "PreCompile.h"
#include "Ram_Arm.h"

Ram_Arm::Ram_Arm()
{
}

Ram_Arm::~Ram_Arm()
{
}

void Ram_Arm::Start()
{
	ArmRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	ArmRenderer->SetPivotType(PivotType::Right);
	ArmRenderer->AutoSpriteSizeOn();
	ArmRenderer->CreateAnimation("Ram_Arm_Move", "Ram_Arm", RAMARMANIMATIONINTER, 0, 4, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { ArmRenderer->ChangeAnimation("Ram_Arm_Move"); };
		Para.Stay = [&](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == MoveEndCheck())
				{
					ArmState.ChangeState(EDEVILARMSTATE::Clap);
				}
				else
				{
					ArmMove(_DeltaTime);
				}
			};
		ArmState.CreateState(EDEVILARMSTATE::Move, Para);
	}

	ArmRenderer->CreateAnimation("Ram_Arm_Clap", "Ram_Arm", RAMARMANIMATIONINTER, 5, 9, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				ClapSoundPlay();
				ArmRenderer->ChangeAnimation("Ram_Arm_Clap");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == ArmRenderer->IsCurAnimationEnd())
				{
					ArmState.ChangeState(EDEVILARMSTATE::MoveBack);
				}
			};
		ArmState.CreateState(EDEVILARMSTATE::Clap, Para);
	}

	ArmRenderer->CreateAnimation("Ram_Arm_MoveBack", "Ram_Arm", RAMARMANIMATIONINTER, 10, 14, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { ArmRenderer->ChangeAnimation("Ram_Arm_MoveBack"); };
		Para.Stay = [&](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == DeathPosCheck())
				{
					Death();
				}
				else
				{
					ArmMove(_DeltaTime, true);
				}
			};
		ArmState.CreateState(EDEVILARMSTATE::MoveBack, Para);
	}

	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	MoveEndPoint = CameraPos.X + MOVEENDPOINTERROR;

	ArmCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	ArmCollision->Transform.SetLocalScale(RAMARMCOLLISIONSCALE);
	ArmCollision->Transform.SetLocalPosition(RAMARMCOLLISIONPOSITIONRIGHT);
	ArmCollision->SetCollisionType(ColType::AABBBOX2D);

	ArmState.ChangeState(EDEVILARMSTATE::Move);
}

void Ram_Arm::Update(float _Delta)
{
	ArmState.Update(_Delta);
}

void Ram_Arm::ChangeLeftDir()
{
	ArmDir = EACTORDIR::Left;
	ArmRenderer->SetPivotType(PivotType::Left);
	ArmRenderer->LeftFlip();

	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	MoveEndPoint = CameraPos.X - MOVEENDPOINTERROR;

	ArmCollision->Transform.SetLocalPosition(RAMARMCOLLISIONPOSITIONLEFT);
}

void Ram_Arm::ArmMove(float _Delta, bool _Back /*= false*/)
{
	float4 MovePos = float4::ZERO;

	if (EACTORDIR::Left == ArmDir && false == _Back
		|| EACTORDIR::Right == ArmDir && true == _Back)
	{
		MovePos = float4::LEFT * Speed * _Delta;
	}
	
	if (EACTORDIR::Right == ArmDir && false == _Back
		|| EACTORDIR::Left == ArmDir && true == _Back)
	{
		MovePos = float4::RIGHT * Speed * _Delta;
	}

	Transform.AddLocalPosition(MovePos);
}

bool Ram_Arm::MoveEndCheck()
{
	float4 Pos = Transform.GetWorldPosition();

	if (EACTORDIR::Left == ArmDir && Pos.X <= MoveEndPoint)
	{
		return true;
	}

	if (EACTORDIR::Right == ArmDir && Pos.X >= MoveEndPoint)
	{
		return true;
	}

	return false;
}

bool Ram_Arm::DeathPosCheck()
{
	float4 Pos = Transform.GetWorldPosition();

	if (EACTORDIR::Right == ArmDir && 0.0f > Pos.X)
	{
		return true;
	}

	if (EACTORDIR::Left == ArmDir && 1280.0f < Pos.X)
	{
		return true;
	}

	return false;
}

void Ram_Arm::ClapSoundPlay()
{
	GameEngineRandom Random;
	unsigned int Time = static_cast<unsigned int>(time(NULL));
	Random.SetSeed(static_cast<long long>(Time));

	int SoundNum = Random.RandomInt(0, 3);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_level_devil_ram_hand_clap_01.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_level_devil_ram_hand_clap_02.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_level_devil_ram_hand_clap_03.wav");
		break;
	default:
		GameEngineSound::SoundPlay("sfx_level_devil_ram_hand_clap_04.wav");
		break;
	}
}