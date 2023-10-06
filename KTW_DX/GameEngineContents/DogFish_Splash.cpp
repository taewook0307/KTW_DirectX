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
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PlayEffect);
	Renderer->CreateAnimation("DogFish_SplashEffect", "DogFish_SplashEffect", 0.05f, -1, -1, false);
	Renderer->SetEndEvent("DogFish_SplashEffect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Renderer = nullptr;
			Death();
		}
	);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::RightBottom);

	Renderer->ChangeAnimation("DogFish_SplashEffect");
}