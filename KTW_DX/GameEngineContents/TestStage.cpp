#include "PreCompile.h"
#include "TestStage.h"

#include "BaseCharacter.h"
#include "ParryObject.h"
#include "Map.h"

TestStage::TestStage()
{
}

TestStage::~TestStage()
{
}

void TestStage::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineInput::AddInputObject(this);

	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, 0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\Global\\Character");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\Tutorial");
		std::vector<GameEngineFile> AllFiles = Dir.GetAllFile();

		size_t FileCount = AllFiles.size();

		for (size_t i = 0; i < FileCount; i++)
		{
			GameEngineFile File = AllFiles[i];
			GameEngineTexture::Load(File.GetStringPath());
			GameEngineSprite::CreateSingle(File.GetFileName());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\Tutorial\\Parry");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	Player = CreateActor<BaseCharacter>(EUPDATEORDER::Player);
	Player->Transform.SetLocalPosition(PLAYERSTARTPOS);

	TestParry = CreateActor<ParryObject>(EUPDATEORDER::Map);
	TestParry->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("TutorialMap.Png");
	float4 SpriteHalfScale = Sprite->GetSpriteData(0).GetScale().Half();

	TestMap = CreateActor<Map>(EUPDATEORDER::Map);
	TestMap->MapInit("TutorialMap.Png");
	TestMap->PixelMapInit("TutorialBitMap.Png");
	TestMap->Transform.SetLocalPosition({ SpriteHalfScale.X, -SpriteHalfScale.Y });
}

void TestStage::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Player)
	{
		Player->Death();
		Player = nullptr;
	}

	if (nullptr != TestParry)
	{
		TestParry->Death();
		TestParry = nullptr;
	}

	if (nullptr != TestMap)
	{
		TestMap->Death();
		TestMap = nullptr;
	}
}

void TestStage::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('R', this))
	{
		TestParry->ParryActive();
	}

	if (true == GameEngineInput::IsDown(VK_NUMPAD0, this))
	{
		GameEngineCore::MainTime.SetAllTimeScale(0.0f);
	}

	if (true == GameEngineInput::IsDown(VK_NUMPAD1, this))
	{
		GameEngineCore::MainTime.SetAllTimeScale(1.0f);
	}
}