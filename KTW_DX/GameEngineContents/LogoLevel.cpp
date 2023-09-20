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
	GetMainCamera()->Transform.SetLocalPosition({ 0, 0, -500 });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	
	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild("Resources\\Texture\\Level\\Logo\\Logo.png");
	GameEngineTexture::Load(Path.GetStringPath());

	GameEngineSprite::CreateCut("Logo.png", 5, 20);

	Logo = CreateActor<BackGround>(UpdateOrder::BackGround);
	Logo->AnimationInit("Logo", "Logo.png", 0.04f, false);
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
}