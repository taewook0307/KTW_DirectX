#include "PreCompile.h"
#include "SecondBossStage.h"

#include "PirateBoss.h"
#include "ShipBoss.h"

#include "Barrel.h"

#include "Map.h"
#include "Ocean.h"
#include "MiniMapLevel.h"

SecondBossStage::SecondBossStage()
{
}

SecondBossStage::~SecondBossStage()
{
}

void SecondBossStage::LevelStart(GameEngineLevel* _PrevLevel)
{
	Oceans.resize(4);

	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, 0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\SecondBossStage\\SecondBoss");
	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\SecondBossStage\\SecondBoss\\Ship\\pirate_boatMast.Png");
	ContentsSpriteManager::CreateSingleSpriteDir("Resources\\Texture\\SecondBossStage\\Map");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\SecondBossStage\\Map\\Water");

	float4 WinScale = GameEngineCore::MainWindow.GetScale();

	PirateBossActor = CreateActor<PirateBoss>(EUPDATEORDER::Monster);
	PirateBossActor->Transform.SetLocalPosition({ WinScale.X - 80.0f, -450.0f });

	ShipBossActor = CreateActor<ShipBoss>(EUPDATEORDER::Monster);
	ShipBossActor->Transform.SetLocalPosition({ WinScale.X + 80.0f, -WinScale.Y });

	BarrelActor = CreateActor<Barrel>(EUPDATEORDER::Monster);
	BarrelActor->Transform.SetLocalPosition({ WinScale.Half().X, -220.0f });

	Oceans[0] = CreateActor<Ocean>(EUPDATEORDER::BackGround);
	Oceans[0]->SetOceanAnimation(ERENDERORDER::UpperBoss5, "Water_A", "Water_A");
	Oceans[0]->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScale.Y });

	Oceans[1] = CreateActor<Ocean>(EUPDATEORDER::BackGround);
	Oceans[1]->SetOceanAnimation(ERENDERORDER::PrevMap5, "Water_B", "Water_B");
	Oceans[1]->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScale.Y });

	Oceans[2] = CreateActor<Ocean>(EUPDATEORDER::BackGround);
	Oceans[2]->SetOceanAnimation(ERENDERORDER::PrevMap4, "Water_C", "Water_C");
	Oceans[2]->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScale.Y + 190.0f });

	Oceans[3] = CreateActor<Ocean>(EUPDATEORDER::BackGround);
	Oceans[3]->SetOceanAnimation(ERENDERORDER::PrevMap3, "Water_D", "Water_D");
	Oceans[3]->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScale.Y + 260.0f });

	// 테스트용 맵
	SecondStageMap = CreateActor<Map>(EUPDATEORDER::Map);
	SecondStageMap->MapInit("SecondMap.Png");
	SecondStageMap->PixelMapInit("SecondStagePixelMap.Png");
	SecondStageMap->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });

	StageLevel::LevelStart(_PrevLevel);
}

void SecondBossStage::Update(float _Delta)
{
	StageLevel::Update(_Delta);

	if (true == GameEngineInput::IsDown(VK_ESCAPE, this))
	{
		GameEngineCore::ChangeLevel("MiniMapLevel");
	}

	if (ESTAGERESULT::Success == StageResult)
	{
		MiniMapLevel::IsCreateStage2Flag();
	}
}

void SecondBossStage::LevelEnd(GameEngineLevel* _NextLevel)
{
	StageLevel::LevelEnd(_NextLevel);

	if (nullptr != PirateBossActor)
	{
		PirateBossActor->Death();
		PirateBossActor = nullptr;
	}

	if (nullptr != ShipBossActor)
	{
		ShipBossActor->Death();
		ShipBossActor = nullptr;
	}

	if (nullptr != BarrelActor)
	{
		BarrelActor->Death();
		BarrelActor = nullptr;
	}

	for (size_t i = 0; i < Oceans.size(); i++)
	{
		if (nullptr != Oceans[i])
		{
			Oceans[i]->Death();
			Oceans[i] = nullptr;
		}
	}

	Oceans.clear();

	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\SecondBossStage\\SecondBoss");
	ContentsSpriteManager::SingleSpriteRelease("pirate_boatMast.Png");
	ContentsSpriteManager::SingleSpriteInDirRelease("Resources\\Texture\\SecondBossStage\\Map");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\SecondBossStage\\Map\\Water");

}