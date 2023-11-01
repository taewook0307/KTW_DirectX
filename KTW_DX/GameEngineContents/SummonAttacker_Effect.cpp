#include "PreCompile.h"
#include "SummonAttacker_Effect.h"

SummonAttacker_Effect::SummonAttacker_Effect()
{
}

SummonAttacker_Effect::~SummonAttacker_Effect()
{
}

void SummonAttacker_Effect::Start()
{
	EffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	EffectRenderer->CreateAnimation("DevilAttacker_SpawnEffect", "DevilAttacker_SpawnEffect", 0.1f, -1, -1, false);
	EffectRenderer->SetEndEvent("DevilAttacker_SpawnEffect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	EffectRenderer->AutoSpriteSizeOn();

	EffectRenderer->ChangeAnimation("DevilAttacker_SpawnEffect");
}