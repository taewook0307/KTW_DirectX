﻿#include "PreCompile.h"
#include "Bullet.h"

#include "BaseBoss.h"
#include "BaseCharacter.h"
#include "TutorialTarget.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Bullet);
	BulletRenderer->CreateAnimation("Bullet_Spawn", "BulletSpawn", BULLETANIMATIONINTER);
	BulletRenderer->CreateAnimation("Bullet_Move", "BulletMove", BULLETANIMATIONINTER);
	BulletRenderer->CreateAnimation("Bullet_Death", "BulletDeath", BULLETANIMATIONINTER);
	BulletRenderer->AutoSpriteSizeOn();
	BulletRenderer->SetAutoScaleRatio(BULLETRATIO);

	BulletCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::Bullet);
	BulletCollision->SetCollisionType(ColType::AABBBOX2D);
	BulletCollision->Transform.SetLocalScale({ 27.0f, 18.0f });
	BulletCollision->Off();

	ChangeBulletState(EBULLETSTATE::Spawn);
}

void Bullet::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (EDIRECTION8::Left == BulletDir)
	{
		BulletRenderer->LeftFlip();
	}

	else if (EDIRECTION8::Right == BulletDir)
	{
		BulletRenderer->RightFlip();
	}

	else if (EDIRECTION8::Up == BulletDir)
	{
		Transform.SetLocalRotation({0.0f, 0.0f, 90.0f});
	}

	else if (EDIRECTION8::Down == BulletDir)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, -90.0f });
	}

	else if (EDIRECTION8::LeftUp == BulletDir)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, 135.0f });
	}

	else if (EDIRECTION8::LeftDown == BulletDir)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, -135.0f });
	}

	else if (EDIRECTION8::RightUp == BulletDir)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, 45.0f });
	}

	else if (EDIRECTION8::RightDown == BulletDir)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, -45.0f });
	}
}

void Bullet::ChangeBulletState(EBULLETSTATE _CurState)
{
	if (CurState != _CurState)
	{
		switch (_CurState)
		{
		case EBULLETSTATE::Spawn:
			SpawnStart();
			break;
		case EBULLETSTATE::Move:
			MoveStart();
			break;
		case EBULLETSTATE::Death:
			DeathStart();
			break;
		default:
			break;
		}

		CurState = _CurState;
	}
}

void Bullet::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case EBULLETSTATE::Spawn:
		return SpawnUpdate(_Delta);
	case EBULLETSTATE::Move:
		return MoveUpdate(_Delta);
	case EBULLETSTATE::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}

void Bullet::ChangeBulletAnimation(std::string_view _State)
{
	std::string AnimationName = "Bullet_";

	AnimationName += _State;

	State = _State;

	BulletRenderer->ChangeAnimation(AnimationName);
}

void Bullet::PosCheck()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();

	float4 WinHalfScale = GameEngineCore::MainWindow.GetScale().Half();

	float4 WinLeftPos = { CameraPos.X - WinHalfScale.X, CameraPos.Y + WinHalfScale.Y };
	float4 WinRightPos = { CameraPos.X + WinHalfScale.X, CameraPos.Y - WinHalfScale.Y };

	float4 BulletPos = Transform.GetWorldPosition();

	if (BulletPos.X < WinLeftPos.X - 50.0f
		|| BulletPos.X >= WinRightPos.X + 50.0f
		|| BulletPos.Y > WinLeftPos.Y - 50.0f
		|| BulletPos.Y <= WinRightPos.Y + 50.0f)
	{
		Death();
		return;
	}
}

void Bullet::BulletHitSuccess(std::vector<GameEngineCollision*> _Col)
{
	if (EBULLETSTATE::Move == CurState)
	{
		GameEngineCollision* CurCollision = _Col[_Col.size() - 1];
		GameEngineActor* ColMaster = CurCollision->GetActor();
		BaseBoss* ColBoss = dynamic_cast<BaseBoss*>(ColMaster);

		if (nullptr != ColBoss)
		{
			for (int i = 0; i < Att; ++i)
			{
				ColBoss->PlusHitCount();
			}

			BaseCharacter::MainCharacter->PlusHitSuccess();
		}

		ChangeBulletState(EBULLETSTATE::Death);
		return;
	}
}

void Bullet::ColCheck()
{
	BulletCollision->Collision(ECOLLISIONORDER::BossBody,
		[=](std::vector<GameEngineCollision*> _Col)
		{
			BulletHitSuccess(_Col);
		}
	);
	BulletCollision->Collision(ECOLLISIONORDER::UnDamageBoss,
		[=](std::vector<GameEngineCollision*> _Col)
		{
			BulletHitSuccess(_Col);
		}
	);
	BulletCollision->Collision(ECOLLISIONORDER::MonsterBody,
		[=](std::vector<GameEngineCollision*> _Col)
		{
			ChangeBulletState(EBULLETSTATE::Death);
			return;
		}
	);

	BulletCollision->Collision(ECOLLISIONORDER::TutorialTarget,
		[=](std::vector<GameEngineCollision*> _Col)
		{
			if (false == TargetHit)
			{
				GameEngineCollision* CurCol = _Col[_Col.size() - 1];
				GameEngineActor* ColMaster = CurCol->GetActor();
				TutorialTarget* ColTarget = dynamic_cast<TutorialTarget*>(ColMaster);
				ColTarget->PlusHitCount();
				BaseCharacter::MainCharacter->PlusHitSuccessTutorial();
				TargetHit = true;
			}
			ChangeBulletState(EBULLETSTATE::Death);
			return;
		}
	);
}