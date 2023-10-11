#include "PreCompile.h"
#include "DogFish_DeathEffect.h"

DogFish_DeathEffect::DogFish_DeathEffect()
{
}

DogFish_DeathEffect::~DogFish_DeathEffect()
{
}

void DogFish_DeathEffect::Start()
{
	EffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PlayEffect);
	EffectRenderer->CreateAnimation("DogFish_DeathEffect", "DogFish_DeathEffect", 0.05f, -1, -1, false);
	EffectRenderer->SetEndEvent("DogFish_DeathEffect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			EffectRenderer = nullptr;
			Death();
		}
	);
	EffectRenderer->AutoSpriteSizeOn();

	EffectRenderer->ChangeAnimation("DogFish_DeathEffect");
}