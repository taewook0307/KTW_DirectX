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
	MenuDir.MoveChild("Resources\\Texture\\MainMenu");
	std::vector<GameEngineFile> AllFiles = MenuDir.GetAllFile();

	for (size_t i = 0; i < AllFiles.size(); i++)
	{
		GameEngineFile& File = AllFiles[i];
		GameEngineTexture::Load(File.GetStringPath());
		std::string FileName = File.GetFileName();
		GameEngineSprite::CreateSingle(FileName);
	}

	Back = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	Back->BackGroundInit("MainMenu.png");

	StartMenu = CreateActor<SelectMenu>(EUPDATEORDER::Menu);
	StartMenu->SelectMenuInit("Start_Select.png", "Start_UnSelect.png");
	StartMenu->Transform.SetLocalPosition({ 0.0f, 30.0f });

	ExitMenu = CreateActor<SelectMenu>(EUPDATEORDER::Menu);
	ExitMenu->SelectMenuInit("Exit_Select.png", "Exit_UnSelect.png");
	ExitMenu->Transform.SetLocalPosition({ 0.0f, -30.0f });

	StartMenu->SelectOn();
}

void MenuLevel::Update(float _Delta)
{
	if (EMAINMENUSELECT::Start == CurSelect && GameEngineInput::IsDown(VK_DOWN))
	{
		CurSelect = EMAINMENUSELECT::Exit;
		MenuChange();
	}

	if (EMAINMENUSELECT::Exit == CurSelect && GameEngineInput::IsDown(VK_UP))
	{
		CurSelect = EMAINMENUSELECT::Start;
		MenuChange();
	}

	if (EMAINMENUSELECT::Start == CurSelect && GameEngineInput::IsDown(VK_RETURN)
		|| EMAINMENUSELECT::Start == CurSelect && GameEngineInput::IsDown('Z'))
	{
		GameEngineCore::ChangeLevel("IntroLevel");
	}

	if (EMAINMENUSELECT::Exit == CurSelect && GameEngineInput::IsDown(VK_RETURN)
		|| EMAINMENUSELECT::Exit == CurSelect && GameEngineInput::IsDown('Z'))
	{
		GameEngineWindow::WindowLoopOff();
	}
}

void MenuLevel::MenuChange()
{
	if (EMAINMENUSELECT::Start == CurSelect)
	{
		StartMenu->SelectOn();
		ExitMenu->SelectOff();
	}
	else if (EMAINMENUSELECT::Exit == CurSelect)
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