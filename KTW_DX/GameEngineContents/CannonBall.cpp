#include "PreCompile.h"
#include "CannonBall.h"

#include "Map.h"

CannonBall::CannonBall()
{
}

CannonBall::~CannonBall()
{
}

void CannonBall::Start()
{
	CannonBallRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Bullet);
	CannonBallRenderer->CreateAnimation("Cannon_Move", "Cannon_Move");
	CannonBallRenderer->AutoSpriteSizeOn();
	CannonBallRenderer->SetPivotType(PivotType::LeftBottom);

	CannonBallRenderer->ChangeAnimation("Cannon_Move");

	Collision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	Collision->Transform.SetLocalScale(CANNONCOLLISIONSCALE);
	Collision->Transform.SetLocalPosition(CANNONCOLLISIONPOSITION);
}

void CannonBall::Update(float _Delta)
{
	float4 CannonPos = Transform.GetWorldPosition();
	
	float4 MovePos = float4::LEFT * Speed * _Delta;
	Transform.AddLocalPosition(MovePos);

	if (-200.0f > CannonPos.X)
	{
		Death();
	}
}