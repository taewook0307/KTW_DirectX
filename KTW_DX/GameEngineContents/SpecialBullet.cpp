#include "PreCompile.h"
#include "SpecialBullet.h"

SpecialBullet::SpecialBullet()
{
	Att = 8;
}

SpecialBullet::~SpecialBullet()
{
}

void SpecialBullet::Start()
{
	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Bullet);
	BulletRenderer->CreateAnimation("EXBullet_Spawn", "EXBulletSpawn", BULLETANIMATIONINTER);
	BulletRenderer->CreateAnimation("EXBullet_Move", "EXBulletMove", BULLETANIMATIONINTER);
	BulletRenderer->CreateAnimation("EXBullet_Death", "EXBulletDeath", BULLETANIMATIONINTER);
	BulletRenderer->AutoSpriteSizeOn();
	BulletRenderer->SetAutoScaleRatio(BULLETRATIO);

	ChangeBulletState(EBULLETSTATE::Spawn);

	BulletCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::Bullet);
	BulletCollision->SetCollisionType(ColType::AABBBOX2D);
	BulletCollision->Transform.SetLocalScale({ 170.0f, 100.0f });
}

void SpecialBullet::ChangeBulletAnimation(std::string_view _State)
{
	std::string AnimationName = "EXBullet_";

	AnimationName += _State;

	State = _State;

	BulletRenderer->ChangeAnimation(AnimationName);
}