#include "PreCompile.h"
#include "MenuLevel.h"

#include "BackGround.h"
#include "SelectMenu.h"

MenuLevel::MenuLevel()
{
}

MenuLevel::~MenuLevel()
{
}

void MenuLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineDirectory MenuDir;
	MenuDir.MoveParentToExistsChild("Resources");
	MenuDir.MoveChild("Resources\\Texture\\Level\\MainMenu");
	std::vector<GameEngineFile> AllFiles = MenuDir.GetAllFile();

	for (size_t i = 0; i < AllFiles.size(); i++)
	{
		GameEngineFile& File = AllFiles[i];
		GameEngineTexture::Load(File.GetStringPath());
	}

	GameEngineSprite::CreateSingle("MainMenu.png");
	GameEngineSprite::CreateSingle("Start_Select.png");
	GameEngineSprite::CreateSingle("Start_UnSelect.png");
	GameEngineSprite::CreateSingle("Exit_Select.png");
	GameEngineSprite::CreateSingle("Exit_UnSelect.png");

	Back = CreateActor<BackGround>(UpdateOrder::BackGround);
	Back->BackGroundInit("MainMenu.png");

	StartMenu = CreateActor<SelectMenu>(UpdateOrder::Menu);
	StartMenu->SelectMenuInit("Start_Select.png", "Start_UnSelect.png");
	StartMenu->Transform.SetLocalPosition({ 0.0f, 30.0f });

	ExitMenu = CreateActor<SelectMenu>(UpdateOrder::Menu);
	ExitMenu->SelectMenuInit("Exit_Select.png", "Exit_UnSelect.png");
	ExitMenu->Transform.SetLocalPosition({ 0.0f, -30.0f });

	StartMenu->SelectOn();
}

void MenuLevel::Update(float _Delta)
{
	if (MainMenuSelect::Start == CurSelect && GameEngineInput::IsDown(VK_DOWN))
	{
		CurSelect = MainMenuSelect::Exit;
		MenuChange();
	}

	if (MainMenuSelect::Exit == CurSelect && GameEngineInput::IsDown(VK_UP))
	{
		CurSelect = MainMenuSelect::Start;
		MenuChange();
	}

	if (MainMenuSelect::Start == CurSelect && GameEngineInput::IsDown(VK_RETURN)
		|| MainMenuSelect::Start == CurSelect && GameEngineInput::IsDown('Z'))
	{
		GameEngineCore::ChangeLevel("IntroLevel");
	}

	if (MainMenuSelect::Exit == CurSelect && GameEngineInput::IsDown(VK_RETURN)
		|| MainMenuSelect::Exit == CurSelect && GameEngineInput::IsDown('Z'))
	{
		GameEngineWindow::WindowLoopOff();
	}
}

void MenuLevel::MenuChange()
{
	if (MainMenuSelect::Start == CurSelect)
	{
		StartMenu->SelectOn();
		ExitMenu->SelectOff();
	}
	else if (MainMenuSelect::Exit == CurSelect)
	{
		StartMenu->SelectOff();
		ExitMenu->SelectOn();
	}
}

void MenuLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Back)
	{
		Back->Death();
		Back = nullptr;
	}

	if (nullptr != StartMenu)
	{
		StartMenu->Death();
		StartMenu = nullptr;
	}

	if (nullptr != ExitMenu)
	{
		ExitMenu->Death();
		ExitMenu = nullptr;
	}
}