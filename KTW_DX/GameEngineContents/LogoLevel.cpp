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
	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	
	ContentsSpriteManager::ImageLoad("Resources\\Texture\\Logo\\Logo.png");
	GameEngineSprite::CreateCut("Logo.png", 5, 20);

	Logo = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	Logo->AnimationInit("Logo", "Logo.png", 0.04f, false);
}

void LogoLevel::Update(float _Delta)
{
	if (true == Logo->AnimationEndCheck())
	{
		Logo->BackGroundDeath();
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

	GameEngineSprite::Release("Logo.png");
	GameEngineTexture::Release("Logo.png");
}