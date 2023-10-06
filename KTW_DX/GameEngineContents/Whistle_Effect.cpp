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
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PlayEffect);
	Renderer->CreateAnimation("Whistle_Effect", "Pirate_Whistle_Effect", 0.05f, -1, -1, false);
	Renderer->SetEndEvent("Whistle_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Renderer = nullptr;
			Death();
		}
	);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::RightBottom);

	Renderer->ChangeAnimation("Whistle_Effect");
}