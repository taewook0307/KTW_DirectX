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
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PlayEffect);
	Renderer->CreateAnimation("DogFish_DeathEffect", "DogFish_DeathEffect", 0.05f, -1, -1, false);
	Renderer->SetEndEvent("DogFish_DeathEffect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Renderer = nullptr;
			Death();
		}
	);
	Renderer->AutoSpriteSizeOn();

	Renderer->ChangeAnimation("DogFish_DeathEffect");
}