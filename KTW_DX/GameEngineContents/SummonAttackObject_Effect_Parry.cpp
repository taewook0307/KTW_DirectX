#include "PreCompile.h"
#include "SummonAttackObject_Effect_Parry.h"

SummonAttackObject_Effect_Parry::SummonAttackObject_Effect_Parry()
{
}

SummonAttackObject_Effect_Parry::~SummonAttackObject_Effect_Parry()
{
}

void SummonAttackObject_Effect_Parry::Start()
{
	EffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	EffectRenderer->CreateAnimation("DevilAttackObject_Parry_SpawnEffect", "DevilAttackObject_Parry_SpawnEffect", 0.1f, -1, -1, false);
	EffectRenderer->SetEndEvent("DevilAttackObject_Parry_SpawnEffect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	EffectRenderer->AutoSpriteSizeOn();

	EffectRenderer->ChangeAnimation("DevilAttackObject_Parry_SpawnEffect");
}