#include "PreCompile.h"
#include "LogoActor.h"

LogoActor::LogoActor()
{
}

LogoActor::~LogoActor()
{
}

void LogoActor::Start()
{
	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	LogoRenderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::UI);
	LogoRenderer->CreateAnimation("Logo", "Logo.png", 0.04f, -1, -1, false);
	std::shared_ptr<GameEngineFrameAnimation> LogoAni = LogoRenderer->FindAnimation("Logo");
	LogoAni->Inter[0] = 1.2f;

	LogoRenderer->SetEndEvent("Logo",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			GameEngineCore::ChangeLevel("TitleLevel");
		}
	);
	LogoRenderer->SetImageScale(WinScale);
	LogoRenderer->ChangeAnimation("Logo");
}