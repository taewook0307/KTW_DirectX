#include "PreCompile.h"
#include "LogoLevel.h"

#include "BackGround.h"

LogoLevel::LogoLevel()
{
}

LogoLevel::~LogoLevel()
{
}

void LogoLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentsResourcesManager::SoundLoad("Resources\\Sound\\Logo\\MDHR_LOGO_STING.wav");
	ContentsResourcesManager::ImageLoad("Resources\\Texture\\Logo\\Logo.png");
	GameEngineSprite::CreateCut("Logo.png", 5, 20);

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	Logo = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	Logo->AnimationInit("Logo", "Logo.png", 0.04f, false);
	GameEngineSound::SoundPlay("MDHR_LOGO_STING.wav");
}

void LogoLevel::Update(float _Delta)
{
	if (true == Logo->AnimationEndCheck())
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}
}

void LogoLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Logo)
	{
		Logo->Death();
		Logo = nullptr;
	}

	ContentsResourcesManager::SingleSpriteRelease("Logo.png");
}