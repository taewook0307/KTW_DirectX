#include "PreCompile.h"
#include "DashDust.h"

DashDust::DashDust()
{
}

DashDust::~DashDust()
{
}

void DashDust::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PlayEffect);
	Renderer->CreateAnimation("DashDust", "Dash_Dust", DASHEFFECTANIMATIONINTER);
	Renderer->SetEndEvent("DashDust",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(0.8f);
	Renderer->SetPivotType(PivotType::Right);

	Renderer->ChangeAnimation("DashDust");
}

void DashDust::Update(float _Delta)
{
	if (EACTORDIR::Left == DashDustDir)
	{
		Renderer->LeftFlip();
	}
	else
	{
		Renderer->RightFlip();
	}
}