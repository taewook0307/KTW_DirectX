#include "PreCompile.h"
#include "IntroBook.h"

#include <GameEngineCore/FadePostEffect.h>

IntroBook::IntroBook()
{
}

IntroBook::~IntroBook()
{
}

void IntroBook::Start()
{
	BookRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::BackGround);

	BookRenderer->CreateAnimation("StoryPage_1", "Page_1", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_1",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_2");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_2", "Page_2", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_2",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_3");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_3", "Page_3", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_3",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_4");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_4", "Page_4", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_4",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_5");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_5", "Page_5", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_5",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_6");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_6", "Page_6", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_6",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_7");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_7", "Page_7", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_7",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_8");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_8", "Page_8", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_8",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_9");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_9", "Page_9", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_9",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_10");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_10", "Page_10", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_10",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_11");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_11", "Page_11", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_11",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			// std::shared_ptr<FadePostEffect> Effect = GetLevel()->GetLevelRenderTarget()->CreateEffect<FadePostEffect>();
			Death();
			GameEngineCore::ChangeLevel("0.Tutorial_Stage");
		}
	);

	BookRenderer->ChangeAnimation("StoryPage_1");

	BookRenderer->SetImageScale(GameEngineCore::MainWindow.GetScale());

	GameEngineInput::AddInputObject(this);
}

void IntroBook::Update(float _Delta)
{
	// 확인용
	if (true == GameEngineInput::IsDown(VK_RETURN, this))
	{
		Death();
		GameEngineCore::ChangeLevel("0.Tutorial_Stage");
	}
}