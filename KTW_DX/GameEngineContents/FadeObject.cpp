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
	FadeRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Fade);
}

void FadeObject::SetFadeType(bool _FadeIn)
{
	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	FadeRenderer->Transform.SetLocalScale(WinScale);

	if (true == _FadeIn)
	{
		FadeRenderer->CreateAnimation("Fade_In", "FadeIn", 0.2f, -1, -1, false);
		FadeRenderer->ChangeAnimation("Fade_In");
	}
	else
	{
		FadeRenderer->CreateAnimation("Fade_Out", "FadeOut", 0.2f, -1, -1, false);
		FadeRenderer->ChangeAnimation("Fade_Out");
	}	
}