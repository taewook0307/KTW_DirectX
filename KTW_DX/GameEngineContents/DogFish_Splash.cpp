#include "PreCompile.h"
#include "DogFish_Splash.h"

DogFish_Splash::DogFish_Splash()
{
}

DogFish_Splash::~DogFish_Splash()
{
}

void DogFish_Splash::Start()
{
	EffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PlayEffect);
	EffectRenderer->CreateAnimation("DogFish_SplashEffect", "DogFish_SplashEffect", 0.05f, -1, -1, false);
	EffectRenderer->SetEndEvent("DogFish_SplashEffect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			EffectRenderer = nullptr;
			Death();
		}
	);
	EffectRenderer->AutoSpriteSizeOn();
	EffectRenderer->SetPivotType(PivotType::RightBottom);

	EffectRenderer->ChangeAnimation("DogFish_SplashEffect");
}