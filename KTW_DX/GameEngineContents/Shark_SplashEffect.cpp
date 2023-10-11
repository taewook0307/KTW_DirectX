#include "PreCompile.h"
#include "Shark_SplashEffect.h"

Shark_SplashEffect::Shark_SplashEffect()
{
}

Shark_SplashEffect::~Shark_SplashEffect()
{
}

void Shark_SplashEffect::Start()
{
	EffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PlayEffect);
	EffectRenderer->CreateAnimation("Shark_Splash", "Shark_Splash", 0.05f, -1, -1, false);
	EffectRenderer->SetEndEvent("Shark_Splash",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			EffectRenderer = nullptr;
			Death();
		}
	);
	EffectRenderer->AutoSpriteSizeOn();
	EffectRenderer->SetPivotType(PivotType::LeftBottom);

	EffectRenderer->ChangeAnimation("Shark_Splash");
}