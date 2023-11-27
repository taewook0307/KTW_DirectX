#include "PreCompile.h"
#include "LogoLevel.h"

#include "LogoActor.h"

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

	Logo = CreateActor<LogoActor>(EUPDATEORDER::BackGround);
	GameEngineSound::SoundPlay("MDHR_LOGO_STING.wav");
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