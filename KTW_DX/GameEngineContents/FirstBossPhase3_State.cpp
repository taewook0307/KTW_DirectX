#include "PreCompile.h"
#include "FirstBossPhase3.h"

#include "Map.h"
#include "BaseCharacter.h"
#include "FirstBossPhase3Effect.h"
#include "StageLevel.h"

void FirstBossPhase3::FallStart()
{
	IsIntroState = true;
	GameEngineSound::SoundPlay("sfx_slime_tombstone_drop_onto_slime.wav");
	ChangeAnimation("Fall");
}

void FirstBossPhase3::FallUpdate(float _Delta)
{
	GameEngineColor CurColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (FLOORCOLOR == CurColor)
	{
		ChangeState(EBOSSSTATE::Intro);
		return;
	}

	ActorGravity(_Delta, Transform.GetWorldPosition());
}

void FirstBossPhase3::IntroStart()
{
	IsIntroState = true;
	ChangeAnimation("Intro");
	CreateEffect(EBOSSSTATE::Intro);
}

void FirstBossPhase3::IntroUpdate(float _Delta)
{
	if (IntroTimer < 0.0f)
	{
		IsIntroState = false;
		ChangeState(EBOSSSTATE::Idle);
		return;
	}
	
	IntroTimer -= _Delta;
}

void FirstBossPhase3::IdleStart()
{
	IdleSoundPlay();
	ChangeAnimation("Idle");
}

void FirstBossPhase3::IdleUpdate(float _Delta)
{
	ActorGravity(_Delta, Transform.GetWorldPosition());
}

void FirstBossPhase3::MoveStart()
{
	MoveSoundPlay();
	MoveVoiceSoundPlay();
	ChangeAnimation("Move");
}

void FirstBossPhase3::MoveUpdate(float _Delta)
{
	if (nullptr != Effect)
	{
		float4 Pos = Transform.GetWorldPosition();
		Effect->Transform.SetLocalPosition(Pos);
	}
	
	if (2 < DirChangeCount)
	{
		float4 CharacterPos = BaseCharacter::MainCharacter->Transform.GetWorldPosition();
		float4 BossPos = Transform.GetWorldPosition();
		float DirSize = fabs(BossPos.X - CharacterPos.X);

		if (DirSize < 30.0f)
		{
			MoveSound.Stop();
			ChangeState(EBOSSSTATE::Attack);
			return;
		}
	}

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (EACTORDIR::Left == FirstBossDir)
	{
		MovePos = float4::LEFT * Speed * _Delta;
		CheckPos = { -60.0f, 70.0f };
	}
	else
	{
		MovePos = float4::RIGHT * Speed * _Delta;
		CheckPos = { 60.0f, 70.0f };
	}

	CheckPos += Transform.GetWorldPosition();

	GameEngineColor CheckColor = Map::MainMap->GetColor(CheckPos, FLOORCOLOR);

	if (FLOORCOLOR == CheckColor)
	{
		ChangeState(EBOSSSTATE::Turn);
		return;
	}
	else
	{
		Transform.AddLocalPosition(MovePos);
	}
}

void FirstBossPhase3::TurnStart()
{
	ChangeAnimation("Turn");
}

void FirstBossPhase3::TurnUpdate(float _Delta)
{
	if (true == FirstBossRenderer->IsCurAnimationEnd())
	{
		DirChange();
		ChangeState(EBOSSSTATE::Move);
		return;
	}
}

void FirstBossPhase3::AttackStart()
{
	FirstBossRenderer->SetPivotType(PivotType::Center);
	ChangeAnimation("Attack");
	DirChangeCount = 0;
}

void FirstBossPhase3::DeathStart()
{
	MoveSound.Stop();
	GameEngineSound::SoundPlay("sfx_slime_tombstone_death.wav");
	ChangeAnimation("Death");
	StageLevel::StageClear();
}