#include "PreCompile.h"
#include "TitleLevel.h"

#include "BackGround.h"
#include "FadeObject.h"


TitleLevel::TitleLevel()
{
	GameEngineInput::AddInputObject(this);
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentsResourcesManager::SoundLoad("Resources\\Sound\\Global\\LevelMove\\sfx_WorldMap_LevelSelect_DiffucultySettings_Appear.wav");
	ContentsResourcesManager::CreateFolderSpriteDir("Resources\\Texture\\Title\\TitleAnimation");
	ContentsResourcesManager::CreateSingleSpriteImage("Resources\\Texture\\Title\\Title_BackGround.Png");

	BGMPlayer = GameEngineSound::SoundPlay("01 Don't Deal With The Devil.mp3");

	TitleBackGround = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	TitleBackGround->BackGroundInit("Title_BackGround.Png");

	TitleAnimation = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	TitleAnimation->AnimationInit("Title_Animation", "TitleAnimation", 0.04f, true, false);
	TitleAnimation->Transform.SetLocalPosition({ 0.0f, -GameEngineCore::MainWindow.GetScale().Half().Y });
	TitleAnimation->SetBackGroundRendererPivotType(PivotType::Bottom);
}

void TitleLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RETURN, this)
		|| true == GameEngineInput::IsDown('Z', this))
	{
		GameEngineSound::SoundPlay("sfx_WorldMap_LevelSelect_DiffucultySettings_Appear.wav");
		FadeEffect = CreateActor<FadeObject>(EUPDATEORDER::UI);
		FadeEffect->SetFadeType();
	}

	if (true == GameEngineInput::IsDown('P', this))
	{
		BGMPlayer.Stop();
	}

	if (nullptr != FadeEffect && true == FadeEffect->GetFadeAnimationEnd())
	{
		GameEngineCore::ChangeLevel("MenuLevel");
	}
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != TitleBackGround)
	{
		TitleBackGround->Death();
		TitleBackGround = nullptr;
	}

	if (nullptr != TitleAnimation)
	{
		TitleAnimation->Death();
		TitleAnimation = nullptr;
	}

	if (nullptr != FadeEffect)
	{
		FadeEffect->Death();
		FadeEffect = nullptr;
	}

	ContentsResourcesManager::SingleSpriteRelease("Title_BackGround.Png");
	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Title");
}