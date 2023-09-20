#include "PreCompile.h"
#include "SpecialAttackDust.h"

SpecialAttackDust::SpecialAttackDust()
{
}

SpecialAttackDust::~SpecialAttackDust()
{
}

void SpecialAttackDust::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PlayEffect);
	Renderer->CreateAnimation("SpecialAttackDust", "Special_Dust", 0.05f);
	Renderer->SetEndEvent("SpecialAttackDust",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	Renderer->SetAutoScaleRatio(0.8f);
	Renderer->AutoSpriteSizeOn();

	Renderer->ChangeAnimation("SpecialAttackDust");
}

void SpecialAttackDust::Update(float _Delta)
{

}