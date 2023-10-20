#include "PreCompile.h"
#include "TargetExplosionEffect.h"

TargetExplosionEffect::TargetExplosionEffect()
{
}

TargetExplosionEffect::~TargetExplosionEffect()
{
}

void TargetExplosionEffect::Start()
{
	MainRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperMap1);
	MainRenderer->CreateAnimation("Explosion_Main", "Explosion_Main", 0.05f, -1, -1, false);
	MainRenderer->AutoSpriteSizeOn();
	MainRenderer->ChangeAnimation("Explosion_Main");

	EffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperMap2);
	EffectRenderer->CreateAnimation("Explosion_Effect", "Explosion_Effect", 0.05f, -1, -1, false);
	EffectRenderer->AutoSpriteSizeOn();
	EffectRenderer->ChangeAnimation("Explosion_Effect");
}

void TargetExplosionEffect::Update(float _Delta)
{
	if (true == MainRenderer->IsCurAnimationEnd() && true == EffectRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}