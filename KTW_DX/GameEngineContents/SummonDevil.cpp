#include "PreCompile.h"
#include "SummonDevil.h"

#include "Map.h"
#include "BaseCharacter.h"

SummonDevil::SummonDevil()
{
}

SummonDevil::~SummonDevil()
{
}

void SummonDevil::Start()
{
	SummonDevilEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss1);
	SummonDevilEffectRenderer->CreateAnimation("SummonDevil_Death_Effect", "SummonDevil_Death_Effect", 0.1f, -1, -1, false);
	SummonDevilEffectRenderer->AutoSpriteSizeOn();
	SummonDevilEffectRenderer->ChangeAnimation("SummonDevil_Death_Effect");
	SummonDevilEffectRenderer->Off();

	SummonDevilRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperMap1);
	SummonDevilRenderer->AutoSpriteSizeOn();
	SummonDevilRenderer->SetAutoScaleRatio(0.7f);
	SummonDevilRenderer->SetPivotType(PivotType::RightBottom);

	SummonDevilRenderer->CreateAnimation("SummonDevil_Intro", "SummonDevil_Intro", 0.1f, -1, -1, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { SummonDevilRenderer->ChangeAnimation("SummonDevil_Intro"); };
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if(true == SummonDevilRenderer->IsCurAnimationEnd())
				{
					SummonDevilState.ChangeState(ESUMMONDEVILSTATE::Appear);
					return;
				}
			};
		SummonDevilState.CreateState(ESUMMONDEVILSTATE::Intro, Para);
	}
	
	SummonDevilRenderer->CreateAnimation("SummonDevil_Appear", "SummonDevil_Appear", 0.1f, -1, -1, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				SpawnSoundPlay();
				SummonDevilRenderer->ChangeAnimation("SummonDevil_Appear");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == SummonDevilRenderer->IsCurAnimationEnd())
				{
					SummonDevilState.ChangeState(ESUMMONDEVILSTATE::Move);
					return;
				}
			};
		SummonDevilState.CreateState(ESUMMONDEVILSTATE::Appear, Para);
	}

	SummonDevilRenderer->CreateAnimation("SummonDevil_Move", "SummonDevil_Move", 0.1f);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { SummonDevilRenderer->ChangeAnimation("SummonDevil_Move"); };
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				SummonDevilMove(_DeltaTime);
				if (true == CameraOutCheck())
				{
					DirChange();
					SummonDevilState.ChangeState(ESUMMONDEVILSTATE::ComeBack);
					return;
				}
			};
		SummonDevilState.CreateState(ESUMMONDEVILSTATE::Move, Para);
	}

	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				SummonDevilRenderer->SetRenderOrder(ERENDERORDER::UpperBoss);
				SummonDevilRenderer->SetAutoScaleRatio(1.0f);
				SummonDevilCollision->On();
				PosSetting();

				if (EACTORDIR::Left == Dir)
				{
					SummonDevilRenderer->RightFlip();
					SummonDevilCollision->Transform.SetLocalPosition(SUMMONDEVILCOLLISIONPOSITIONRIGHT);
					SummonDevilEffectRenderer->Transform.SetLocalPosition(SUMMONDEVILCOLLISIONPOSITIONRIGHT);
				}
				else
				{
					SummonDevilRenderer->LeftFlip();
					SummonDevilCollision->Transform.SetLocalPosition(SUMMONDEVILCOLLISIONPOSITIONLEFT);
					SummonDevilEffectRenderer->Transform.SetLocalPosition(SUMMONDEVILCOLLISIONPOSITIONLEFT);
				}

				
			};
		Para.Stay = [&](float _DeltaTime, GameEngineState* _Parent)
			{
				SummonDevilMove(_DeltaTime);
				
				HitCheck();

				if (true == CameraOutCheck())
				{
					Death();
				}
			};
		SummonDevilState.CreateState(ESUMMONDEVILSTATE::ComeBack, Para);
	}

	SummonDevilRenderer->CreateAnimation("SummonDevil_Death", "SummonDevil_Death", 0.1f, -1, -1, false);
	
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				DeathSoundPlay();
				SummonDevilCollision->Off();
				SummonDevilEffectRenderer->On();
				SummonDevilRenderer->ChangeAnimation("SummonDevil_Death");
			};

		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == SummonDevilRenderer->IsCurAnimationEnd())
				{
					Death();
				}
			};

		SummonDevilState.CreateState(ESUMMONDEVILSTATE::Death, Para);
	}

	SummonDevilCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::MonsterBody);
	SummonDevilCollision->SetCollisionType(ColType::AABBBOX2D);
	SummonDevilCollision->Transform.SetLocalScale(SUMMONDEVILCOLLISIONSCALE);
	SummonDevilCollision->Off();

	SummonDevilState.ChangeState(ESUMMONDEVILSTATE::Intro);

	GameEngineInput::AddInputObject(this);
}

void SummonDevil::Update(float _Delta)
{
	SummonDevilState.Update(_Delta);
}

void SummonDevil::DirChange()
{
	if (EACTORDIR::Left == Dir)
	{
		Dir = EACTORDIR::Right;
		SummonDevilRenderer->SetPivotType(PivotType::LeftBottom);
	}
	else
	{
		Dir = EACTORDIR::Left;
		SummonDevilRenderer->SetPivotType(PivotType::RightBottom);
	}
}

bool SummonDevil::CameraOutCheck()
{
	float4 Pos = Transform.GetWorldPosition();

	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();

	if (EACTORDIR::Left == Dir
		&& CameraPos.X - WinScaleHalf.X - 300.0f > Pos.X)
	{
		return true;
	}
	
	if (EACTORDIR::Right == Dir
		&& CameraPos.X + WinScaleHalf.X + 300.0f < Pos.X)
	{
		return true;
	}

	return false;
}

void SummonDevil::SummonDevilMove(float _Delta)
{
	float4 MovePos = float4::ZERO;

	if (EACTORDIR::Left == Dir)
	{
		MovePos = float4::LEFT * Speed * _Delta;
	}
	else
	{
		MovePos = float4::RIGHT * Speed * _Delta;
	}

	Transform.AddLocalPosition(MovePos);
}

void SummonDevil::SetStartDirRight()
{
	Dir = EACTORDIR::Right;
	SummonDevilRenderer->SetPivotType(PivotType::LeftBottom);
	SummonDevilRenderer->LeftFlip();
}

void SummonDevil::PosSetting()
{
	float4 Pos = Transform.GetWorldPosition();

	Transform.SetWorldPosition({ Pos.X, -670.0f });
}

void SummonDevil::HitCheck()
{
	if (true == SummonDevilCollision->Collision(ECOLLISIONORDER::Bullet))
	{
		SummonDevilState.ChangeState(ESUMMONDEVILSTATE::Death);
		return;
	}
}

void SummonDevil::SpawnSoundPlay()
{
	GameEngineRandom Random;
	unsigned int Time = static_cast<unsigned int>(time(NULL));
	Random.SetSeed(static_cast<long long>(Time));

	int SoundNum = Random.RandomInt(0, 2);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_devil_imp_spawn_01.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_devil_imp_spawn_02.wav");
		break;
	default:
		GameEngineSound::SoundPlay("sfx_devil_imp_spawn_03.wav");
		break;
	}
}

void SummonDevil::DeathSoundPlay()
{
	GameEngineRandom Random;
	unsigned int Time = static_cast<unsigned int>(time(NULL));
	Random.SetSeed(static_cast<long long>(Time));

	int SoundNum = Random.RandomInt(0, 3);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_devil_imp_death_01.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_devil_imp_death_02.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_devil_imp_death_03.wav");
		break;
	default:
		GameEngineSound::SoundPlay("sfx_devil_imp_death_04.wav");
		break;
	}
}