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
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PlayEffect);
	Renderer->CreateAnimation("Shark_Splash", "Shark_Splash", 0.05f, -1, -1, false);
	Renderer->SetEndEvent("Shark_Splash",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Renderer = nullptr;
			Death();
		}
	);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::LeftBottom);

	Renderer->ChangeAnimation("Shark_Splash");
}