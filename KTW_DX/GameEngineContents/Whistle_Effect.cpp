#include "PreCompile.h"
#include "Whistle_Effect.h"

Whistle_Effect::Whistle_Effect()
{
}

Whistle_Effect::~Whistle_Effect()
{
}

void Whistle_Effect::Start()
{
	EffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PlayEffect);
	EffectRenderer->CreateAnimation("Whistle_Effect", "Pirate_Whistle_Effect", 0.05f, -1, -1, false);
	EffectRenderer->SetEndEvent("Whistle_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			EffectRenderer = nullptr;
			Death();
		}
	);
	EffectRenderer->AutoSpriteSizeOn();
	EffectRenderer->SetPivotType(PivotType::RightBottom);

	EffectRenderer->ChangeAnimation("Whistle_Effect");
}