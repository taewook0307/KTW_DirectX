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
	BallRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	BallRenderer->CreateAnimation("Ball_Spawn", "DevilAttacker_Spawn", 0.1f, -1, -1, false);
	BallRenderer->SetStartEvent("Ball_Spawn",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			float4 Pos = Transform.GetWorldPosition();
			CreateSummonEffect(Pos);
		}
	);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent) { BallRenderer->ChangeAnimation("Ball_Spawn"); };
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == BallRenderer->IsCurAnimationEnd())
				{
					BallState.ChangeState(ESUMMONATTACKOBJECTSTATE::Idle);
				}
			};
		BallState.CreateState(ESUMMONATTACKOBJECTSTATE::Spawn, Para);
	}

	BallRenderer->CreateAnimation("FireBall_Idle", "FireBall_Idle");
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { BallRenderer->ChangeAnimation("FireBall_Idle"); };
		BallState.CreateState(ESUMMONATTACKOBJECTSTATE::Idle, Para);
	}

	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { DirPosSetting(); };
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				BallMove(_DeltaTime);
			};
		BallState.CreateState(ESUMMONATTACKOBJECTSTATE::Move, Para);
	}

	BallRenderer->AutoSpriteSizeOn();

	BallState.ChangeState(ESUMMONATTACKOBJECTSTATE::Spawn);

	GameEngineInput::AddInputObject(this);
}

void Summon_Ball::Update(float _Delta)
{
	BallState.Update(_Delta);

	if (true == GameEngineInput::IsDown('P', this))
	{
		BallState.ChangeState(ESUMMONATTACKOBJECTSTATE::Move);
		return;
	}
}

void Summon_Ball::BallMove(float _Delta)
{
	float4 MovePos = DirPos * Speed * _Delta;

	float4 CheckPos = MovePos + Transform.GetWorldPosition() + DirPos;

	GameEngineColor CheckColor = Map::MainMap->GetColor(CheckPos, FLOORCOLOR);

	if (FLOORCOLOR == CheckColor || true == CameraOutCheck())
	{
		ChangeDirPos();
	}
	else
	{
		Transform.AddLocalPosition(MovePos);
	}
	// 벽에 부딪히면 반사각으로 Dirpos전환
}

void Summon_Ball::DirPosSetting()
{
	GameEngineRandom Random;
	Random.SetSeed(reinterpret_cast<long long>(this));

	float RandomDeg = Random.RandomFloat(0.0f, 360.0f);
	float4 Dir = float4::GetUnitVectorFromDeg(RandomDeg);
	
	DirPos = Dir.NormalizeReturn();
	DirPos = float4::LEFT + float4::DOWN;
}

void Summon_Ball::ChangeDirPos()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 WinHalfScale = GameEngineCore::MainWindow.GetScale().Half();

	float MinX = CameraPos.X - WinHalfScale.X;
	float MaxX = CameraPos.X + WinHalfScale.X;
	float MinY = CameraPos.Y + WinHalfScale.Y;
	float MaxY = CameraPos.Y - WinHalfScale.Y;

	float4 Pos = Transform.GetWorldPosition();

	float4 StandardVector = float4::ZERO;

	if (fabsf(MinX - Pos.X) < 10.0f
		|| MinX > Pos.X)
	{
		DirPos.X *= -1.0f;
	}
	else if (fabsf(MaxX - Pos.X) < 10.0f
		|| MaxX < Pos.X)
	{
		DirPos.X *= -1.0f;
	}
	/*else if (fabsf(MaxY - Pos.Y) < 10.0f
		|| MaxY < Pos.Y)
	{
		DirPos.Y *= -1.0f;
	}*/
	else
	{
		DirPos.Y *= -1.0f;
	}
}