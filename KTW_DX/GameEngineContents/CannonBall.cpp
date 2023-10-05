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
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Bullet);
	Renderer->CreateAnimation("Cannon_Move", "Ship_Cannon");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::LeftBottom);

	Renderer->ChangeAnimation("Cannon_Move");

	Collision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::MonsterAttack);
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