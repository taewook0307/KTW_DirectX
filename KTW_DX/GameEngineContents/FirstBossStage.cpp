#include "PreCompile.h"
#include "FirstBossStage.h"
#include "ContentsCore.h"

#include "BaseCharacter.h"
#include "FirstBoss.h"
#include "FirstBossPhase3.h"
#include "Map.h"
#include "UpperObject.h"
#include "StageStartUI.h"
#include "StageFailUI.h"
#include "StageClearUI.h"

FirstBossStage::FirstBossStage()
{
}

FirstBossStage::~FirstBossStage()
{
}

void FirstBossStage::LevelStart(GameEngineLevel* _PrevLevel)
{
	StageResult = ESTAGERESULT::None;

	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, -500 });
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
		Dir.MoveChild("Resources\\Texture\\FirstBossStage\\Map\\FirstBossMap");
		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\FirstBossStage\\Map\\FirstBossParryObject");
		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	}

	{
		GameEnginePath Path;
		Path.MoveParentToExistsChild("Resources");
		Path.MoveChild("Resources\\Texture\\FirstBossStage\\Map\\FirstBossBitMap.png");
		GameEngineTexture::Load(Path.GetStringPath());
		GameEngineSprite::CreateSingle("FirstBossBitMap.Png");
	}

	{
		GameEnginePath Path;
		Path.MoveParentToExistsChild("Resources");
		Path.MoveChild("Resources\\Texture\\FirstBossStage\\Map\\FirstBossMap_Upper.png");
		GameEngineTexture::Load(Path.GetStringPath());
		GameEngineSprite::CreateSingle("FirstBossMap_Upper.Png");
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\FirstBossStage\\FirstBoss");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	Player = CreateActor<BaseCharacter>(EUPDATEORDER::Player);
	Player->Transform.SetLocalPosition({ 230.0f, -677.0f });

	Boss = CreateActor<FirstBoss>(EUPDATEORDER::Monster);
	Boss->Transform.SetLocalPosition({ 1000.0f, -677.0f });

	StageMap = CreateActor<Map>(EUPDATEORDER::Map);
	StageMap->MapAnimationInit("FirstBossMapAni", "FirstBossMap", 0.05f);
	StageMap->PixelMapInit("FirstBossBitMap.Png");
	StageMap->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });

	StageMapUpper = CreateActor<UpperObject>(EUPDATEORDER::Map);
	StageMapUpper->UpperObjectInit("FirstBossMap_Upper.png");
	StageMapUpper->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });

	StageLevel::LevelStart(_PrevLevel);
}

void FirstBossStage::Update(float _Delta)
{
	StageLevel::Update(_Delta);

	if (true == Boss->GetPhase2End())
	{
		Phase3Timer -= _Delta;
	}
	if (false == Phase3Start && 0.0f > Phase3Timer)
	{
		BossPhase3 = CreateActor<FirstBossPhase3>(EUPDATEORDER::Monster);
		float SpawnX = Boss->Transform.GetWorldPosition().X;
		BossPhase3->Transform.SetLocalPosition({ SpawnX, 0.0f });

		Phase3Start = true;
	}

	if (true == GameEngineInput::IsDown(VK_ESCAPE))
	{
		GameEngineCore::ChangeLevel("MiniMapLevel");
	}
}

void FirstBossStage::LevelEnd(GameEngineLevel* _NextLevel)
{
	StageLevel::LevelEnd(_NextLevel);

	if (nullptr != StageMap)
	{
		StageMap->Death();
		StageMap = nullptr;
	}

	if (nullptr != StageMapUpper)
	{
		StageMapUpper->Death();
		StageMapUpper = nullptr;
	}

	if (nullptr != Player)
	{
		Player->Death();
		Player = nullptr;
	}

	if (nullptr != Boss)
	{
		Boss->Death();
		Boss = nullptr;
	}

	if (nullptr != BossPhase3)
	{
		BossPhase3->Death();
		BossPhase3 = nullptr;
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\FirstBossStage\\FirstBoss");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			std::vector<GameEngineFile> Files = Dir.GetAllFile();

			for (size_t i = 0; i < Files.size(); i++)
			{
				std::string FileName = Files[i].GetFileName();
				GameEngineTexture::Release(FileName);
			}
		}
	}
}