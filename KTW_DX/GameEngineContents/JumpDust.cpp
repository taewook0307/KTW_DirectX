#include "PreCompile.h"
#include "JumpDust.h"

JumpDust::JumpDust()
{
}

JumpDust::~JumpDust()
{
}

void JumpDust::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PlayEffect);
	Renderer->CreateAnimation("JumpDust", "Jump_Dust", JUMPEFFECTANIMATIONINTER);
	Renderer->SetEndEvent("JumpDust",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::Bottom);

	Renderer->ChangeAnimation("JumpDust");
}