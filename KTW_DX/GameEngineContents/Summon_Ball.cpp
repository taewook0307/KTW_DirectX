#include "PreCompile.h"
#include "Summon_Ball.h"

#include "Map.h"

Summon_Ball::Summon_Ball()
{
}

Summon_Ball::~Summon_Ball()
{
}

void Summon_Ball::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	Renderer->CreateAnimation("Ball_Spawn", "DevilAttackObject_Spawn", 0.1f, -1, -1, false);
	Renderer->SetStartEvent("Ball_Spawn",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			float4 Pos = Transform.GetWorldPosition();
			CreateSummonEffect(Pos);
		}
	);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent) { Renderer->ChangeAnimation("Ball_Spawn"); };
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == Renderer->IsCurAnimationEnd())
				{
					BallState.ChangeState(ESUMMONATTACKOBJECTSTATE::Idle);
				}
			};
		BallState.CreateState(ESUMMONATTACKOBJECTSTATE::Spawn, Para);
	}

	Renderer->CreateAnimation("Ball_Idle", "FireBall_Idle");
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { Renderer->ChangeAnimation("Ball_Idle"); };
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				DeathConditionCheck();
			};
		BallState.CreateState(ESUMMONATTACKOBJECTSTATE::Idle, Para);
	}

	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { DirPosSetting(); };
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				BallMove(_DeltaTime);
				DeathConditionCheck();
			};
		BallState.CreateState(ESUMMONATTACKOBJECTSTATE::Move, Para);
	}

	Renderer->CreateAnimation("Ball_Death", "DevilAttackObject_Death", 0.1f, -1, -1, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				BallCollision->Off();
				Renderer->ChangeAnimation("Ball_Death");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == Renderer->IsCurAnimationEnd())
				{
					Death();
				}
			};
		BallState.CreateState(ESUMMONATTACKOBJECTSTATE::Death, Para);
	}

	Renderer->AutoSpriteSizeOn();

	BallCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	BallCollision->Transform.SetLocalScale(BALLCOLLISIONSCALE);

	BallState.ChangeState(ESUMMONATTACKOBJECTSTATE::Spawn);
}

void Summon_Ball::Update(float _Delta)
{
	BallState.Update(_Delta);
}

void Summon_Ball::BallMove(float _Delta)
{
	float4 MovePos = DirPos * Speed * _Delta;

	float4 CheckPos = Transform.GetWorldPosition() + (DirPos * 20.0f);

	if (Count > 5)
	{
		Death();
	}
	else if (true == CameraOutCheck(CheckPos))
	{
		AttackSoundPlay();
		ChangeDirPos(CheckPos);
	}
	else
	{
		Transform.AddLocalPosition(MovePos);
	}
}

void Summon_Ball::DirPosSetting()
{
	GameEngineRandom Random;
	Random.SetSeed(reinterpret_cast<long long>(this));

	float RandomDeg = Random.RandomFloat(0.0f, 360.0f);
	float4 Dir = float4::GetUnitVectorFromDeg(RandomDeg);
	
	DirPos = Dir.NormalizeReturn();
}

void Summon_Ball::ChangeDirPos(const float4& _Pos)
{
	++Count;

	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 WinHalfScale = GameEngineCore::MainWindow.GetScale().Half();

	float MinX = CameraPos.X - WinHalfScale.X;
	float MaxX = CameraPos.X + WinHalfScale.X;
	float MinY = CameraPos.Y + WinHalfScale.Y;
	float MaxY = CameraPos.Y - WinHalfScale.Y;

	float4 Pos = _Pos;

	if (Pos.X < MinX)
	{
		DirPos.X *= -1;
	}
	else if (Pos.X > MaxX)
	{
		DirPos.X *= -1;
	}
	else if (Pos.Y > MinY)
	{
		DirPos.Y *= -1;
	}
	else if (Pos.Y < MaxY)
	{
		DirPos.Y *= -1;
	}
	else
	{
		return;
	}
	return;
}

void Summon_Ball::ChangeStateReq()
{
	if (true == BallState.IsCurState(ESUMMONATTACKOBJECTSTATE::Death))
	{
		return;
	}

	BallState.ChangeState(ESUMMONATTACKOBJECTSTATE::Move);
}

void Summon_Ball::DeathConditionCheck()
{
	if (true == BallCollision->Collision(ECOLLISIONORDER::Player))
	{
		BallState.ChangeState(ESUMMONATTACKOBJECTSTATE::Death);
		return;
	}
}