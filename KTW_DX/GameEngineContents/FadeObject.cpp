#include "PreCompile.h"
#include "FadeObject.h"

FadeObject::FadeObject()
{
}

FadeObject::~FadeObject()
{
}

void FadeObject::Start()
{
	FadeRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Fade);
}

void FadeObject::SetFadeType(bool _FadeIn)
{
	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	FadeRenderer->SetImageScale(WinScale);

	if (true == _FadeIn)
	{
		FadeRenderer->CreateAnimation("Fade_In", "FadeOut", FADEANIMATIONINTER, 16, 0, false);
		FadeRenderer->ChangeAnimation("Fade_In");
	}
	else
	{
		FadeRenderer->CreateAnimation("Fade_Out", "FadeOut", FADEANIMATIONINTER, -1, -1, false);
		FadeRenderer->ChangeAnimation("Fade_Out");
	}	
}