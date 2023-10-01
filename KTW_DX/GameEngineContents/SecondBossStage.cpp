#include "PreCompile.h"
#include "SecondBossStage.h"

#include "BaseCharacter.h"
#include "PirateBoss.h"
#include "ShipBoss.h"
#include "Map.h"

SecondBossStage::SecondBossStage()
{
}

SecondBossStage::~SecondBossStage()
{
}

void SecondBossStage::LevelStart(GameEngineLevel* _PrevLevel)
{
	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, -500 });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Texture\\Global\\Character");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Dir = Directorys[i];

		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\SecondBossStage\\SecondBoss");
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
		Dir.MoveChild("Resources\\Texture\\SecondBossStage\\Map");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];

			std::string PathCheck = File.GetStringPath();
			std::string FileNameCheck = File.GetFileName();

			GameEngineTexture::Load(File.GetStringPath());
			GameEngineSprite::CreateSingle(File.GetFileName());
		}
	}

	float4 WinScale = GameEngineCore::MainWindow.GetScale();

	PirateBossActor = CreateActor<PirateBoss>(EUPDATEORDER::Monster);
	PirateBossActor->Transform.SetLocalPosition({ WinScale.X - 80.0f, -500.0f });

	ShipBossActor = CreateActor<ShipBoss>(EUPDATEORDER::Monster);
	ShipBossActor->Transform.SetLocalPosition({ WinScale.X + 60.0f, -WinScale.Y - 50.0f });

	Player = CreateActor<BaseCharacter>(EUPDATEORDER::Player);
	Player->Transform.SetLocalPosition({ 230.0f, -677.0f });

	// 테스트용 맵
	SecondStageMap = CreateActor<Map>(EUPDATEORDER::Map);
	SecondStageMap->MapInit("SecondTestMap.Png");
	SecondStageMap->PixelMapInit("SecondStagePixelMap.Png");
	SecondStageMap->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });

	StageLevel::LevelStart(_PrevLevel);
}

void SecondBossStage::Update(float _Delta)
{
	StageLevel::Update(_Delta);

	if (true == GameEngineInput::IsDown(VK_ESCAPE))
	{
		GameEngineCore::ChangeLevel("MiniMapLevel");
	}
}

void SecondBossStage::LevelEnd(GameEngineLevel* _NextLevel)
{

}