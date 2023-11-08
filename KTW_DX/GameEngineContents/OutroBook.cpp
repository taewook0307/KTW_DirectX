#include "PreCompile.h"
#include "OutroBook.h"

OutroBook::OutroBook()
{
}

OutroBook::~OutroBook()
{
}

void OutroBook::Start()
{
	BookRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::BackGround);

	BookRenderer->CreateAnimation("StoryPage_12", "Page_12", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_12",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_13");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_13", "Page_13", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_13",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_14");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_14", "Page_14", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_14",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_15");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_15", "Page_15", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_15",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_16");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_16", "Page_16", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_16",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_17");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_17", "Page_17", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_17",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("StoryPage_18");
			return;
		}
	);

	BookRenderer->CreateAnimation("StoryPage_18", "Page_18", BOOKANIMATIONINTER, -1, -1, false);
	BookRenderer->SetEndEvent("StoryPage_18",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
			GameEngineCore::ChangeLevel("MenuLevel");
		}
	);

	BookRenderer->ChangeAnimation("StoryPage_12");

	BookRenderer->SetImageScale(GameEngineCore::MainWindow.GetScale());

	GameEngineInput::AddInputObject(this);
}

void OutroBook::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_F1, this))
	{
		Death();
		GameEngineCore::ChangeLevel("MenuLevel");
	}
}