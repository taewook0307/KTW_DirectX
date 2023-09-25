#include "PreCompile.h"
#include "RunDust.h"

RunDust::RunDust()
{
}

RunDust::~RunDust()
{
}

void RunDust::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PlayEffect);
	Renderer->CreateAnimation("RunDust", "Run_Dust", RUNEFFECTANIMATIONINTER);
	Renderer->SetEndEvent("RunDust",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(0.8f);
	Renderer->SetPivotType(PivotType::Bottom);

	Renderer->ChangeAnimation("RunDust");
}