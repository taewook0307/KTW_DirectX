#include "PreCompile.h"
#include "ParryEffect.h"

ParryEffect::ParryEffect()
{
}

ParryEffect::~ParryEffect()
{
}

void ParryEffect::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PlayEffect);
	Renderer->CreateAnimation("ParryEffect", "Parry_Effect", PARRYEFFECTANIMATIONINTER);
	Renderer->SetEndEvent("ParryEffect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(0.8f);
	Renderer->SetPivotType(PivotType::Bottom);

	Renderer->ChangeAnimation("ParryEffect");
}