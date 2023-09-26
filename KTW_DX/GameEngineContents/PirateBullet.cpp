#include "PreCompile.h"
#include "PirateBullet.h"

#include "BaseCharacter.h"

PirateBullet::PirateBullet()
{
}

PirateBullet::~PirateBullet()
{
}

void PirateBullet::Start()
{
	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Bullet);
	BulletRenderer->CreateAnimation("Pirate_Bullet_Yellow_Move", "Pirate_Bullet_Yellow_Move");
	BulletRenderer->CreateAnimation("Pirate_Bullet_Yellow_Death", "Pirate_Bullet_Yellow_Death");
	BulletRenderer->SetEndEvent("Pirate_Bullet_Yellow_Death",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	BulletRenderer->AutoSpriteSizeOn();
	BulletRenderer->SetPivotType(PivotType::Left);
	BulletRenderer->ChangeAnimation("Pirate_Bullet_Yellow_Move");

	BulletCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::MonsterAttack);
	BulletCollision->Transform.SetLocalScale({ 10.0f, 10.0f });

	PlayerPos = BaseCharacter::MainCharacter->Transform.GetWorldPosition();
	
}

void PirateBullet::Update(float _Delta)
{
	float4 Check = PlayerPos;
	DirVector = PlayerPos - Transform.GetWorldPosition();
	float4 CheckVector = DirVector;

	float4 MovePos = DirVector.NormalizeReturn() * _Delta * Speed;

	if (BulletRenderer->IsCurAnimation("Pirate_Bullet_Yellow_Move"))
	{
		Transform.AddLocalPosition(MovePos);
	}

	BulletCollision->Collision(ECOLLISIONORDER::Player,
		[=](std::vector<std::shared_ptr<GameEngineCollision>>& _ColVector)
		{
			BulletRenderer->ChangeAnimation("Pirate_Bullet_Yellow_Death");
		}
	);
}