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

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	Logo = CreateActor<BackGround>(UpdateOrder::BackGround);
	Logo->BackGroundInit("Logo.png", Order);
}

void LogoLevel::Update(float _Delta)
{
	// 이미지 체크용
	if (true == GameEngineInput::IsPress('T'))
	{
		if (Order < 99)
		{
			++Order;
		}
		else
		{
			Order = 0;
		}
		Logo->BackGroundInit("Logo.png", Order);
	}

	// 강제 이동
	if (true == GameEngineInput::IsPress('P'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}
}