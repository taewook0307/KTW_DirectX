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
	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Bullet);
	BulletRenderer->CreateAnimation("EXBullet_Spawn", "EXBulletSpawn", 0.02f);
	BulletRenderer->CreateAnimation("EXBullet_Move", "EXBulletMove", 0.02f);
	BulletRenderer->CreateAnimation("EXBullet_Death", "EXBulletDeath", 0.02f);
	BulletRenderer->AutoSpriteSizeOn();
	BulletRenderer->SetAutoScaleRatio(BULLETRATIO);

	ChangeBulletState(BulletState::Spawn);

	BulletCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Bullet);
	BulletCollision->Transform.SetLocalScale({ 27.0f, 18.0f });
}

void SpecialBullet::ChangeBulletAnimation(std::string_view _State)
{
	std::string AnimationName = "EXBullet_";

	AnimationName += _State;

	State = _State;

	BulletRenderer->ChangeAnimation(AnimationName);
}