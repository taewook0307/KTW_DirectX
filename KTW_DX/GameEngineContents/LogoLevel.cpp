#include "PreCompile.h"
#include "LogoLevel.h"

#include "BackGround.h"

LogoLevel::LogoLevel()
{
}

LogoLevel::~LogoLevel()
{
}

void LogoLevel::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\Level\\Logo");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		size_t FileSize = Files.size();

		for (size_t i = 0; i < FileSize; i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateCut("Logo.png", 5, 20);
	}

	/*GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);*/

	Logo = CreateActor<BackGround>(UpdateOrder::BackGround);
	Logo->AnimationInit("Logo", "Logo.png", 0.05f, true, -1, -1, false);
}

void LogoLevel::Update(float _Delta)
{
	// 강제 이동
	if (true == GameEngineInput::IsPress('P'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}
}