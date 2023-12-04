#include "PreCompile.h"
#include "SummonAttackObject_Effect.h"

SummonAttackObject_Effect::SummonAttackObject_Effect()
{
}

SummonAttackObject_Effect::~SummonAttackObject_Effect()
{
}

void SummonAttackObject_Effect::Start()
{
	EffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	EffectRenderer->CreateAnimation("DevilAttackObject_SpawnEffect", "DevilAttackObject_SpawnEffect", 0.1f, -1, -1, false);
	EffectRenderer->SetEndEvent("DevilAttackObject_SpawnEffect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	EffectRenderer->AutoSpriteSizeOn();

	EffectRenderer->ChangeAnimation("DevilAttackObject_SpawnEffect");
}