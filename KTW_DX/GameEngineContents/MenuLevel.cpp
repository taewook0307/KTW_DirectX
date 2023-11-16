#include "PreCompile.h"
#include "MenuLevel.h"

#include "BackGround.h"
#include "SelectMenu.h"

#include <GameEngineCore/FadePostEffect.h>

MenuLevel::MenuLevel()
{
}

MenuLevel::~MenuLevel()
{
}

void MenuLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineInput::AddInputObject(this);

	//리소스 Load
	ContentsResourcesManager::SoundLoad("Resources\\Sound\\Global\\LevelMove\\sfx_WorldMap_LevelSelect_DiffucultySettings_Appear.wav");
	ContentsResourcesManager::SoundLoad("Resources\\Sound\\Menu\\Menu_Equipment_Move.wav");
	ContentsResourcesManager::CreateSingleSpriteDir("Resources\\Texture\\MainMenu");

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
	if (EMAINMENUSELECT::Start == CurSelect && GameEngineInput::IsDown(VK_DOWN, this))
	{
		GameEngineSound::SoundPlay("Menu_Equipment_Move.wav");
		CurSelect = EMAINMENUSELECT::Exit;
		MenuChange();
	}

	if (EMAINMENUSELECT::Exit == CurSelect && GameEngineInput::IsDown(VK_UP, this))
	{
		GameEngineSound::SoundPlay("Menu_Equipment_Move.wav");
		CurSelect = EMAINMENUSELECT::Start;
		MenuChange();
	}

	if (EMAINMENUSELECT::Start == CurSelect && GameEngineInput::IsDown(VK_RETURN, this)
		|| EMAINMENUSELECT::Start == CurSelect && GameEngineInput::IsDown('Z', this))
	{
		GameEngineSound::SoundPlay("sfx_WorldMap_LevelSelect_DiffucultySettings_Appear.wav");
		FadeEffect = GetLevelRenderTarget()->CreateEffect<FadePostEffect>();
		IsFade = true;
	}

	if (true == IsFade)
	{
		LevelChangeTimer -= _Delta;
	}

	if (0.0f > LevelChangeTimer)
	{
		LevelChangeTimer = 3.0f;
		IsFade = false;
		GameEngineCore::ChangeLevel("IntroLevel");
	}

	if (EMAINMENUSELECT::Exit == CurSelect && GameEngineInput::IsDown(VK_RETURN, this)
		|| EMAINMENUSELECT::Exit == CurSelect && GameEngineInput::IsDown('Z', this))
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

	if (nullptr != FadeEffect)
	{
		FadeEffect->Death();
		FadeEffect = nullptr;
	}

	ContentsResourcesManager::SingleSpriteInDirRelease("Resources\\Texture\\MainMenu");
}