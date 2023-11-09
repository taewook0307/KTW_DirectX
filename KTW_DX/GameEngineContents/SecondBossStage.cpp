#include "PreCompile.h"
#include "SecondBossStage.h"

#include "PirateBoss.h"
#include "Whistle_Effect.h"
#include "PirateBullet.h"
#include "PirateBulletParry.h"
#include "Shark.h"
#include "Shark_SplashEffect.h"
#include "Periscope.h"
#include "DogFish.h"
#include "DogFish_DeathEffect.h"
#include "DogFish_Splash.h"

#include "ShipBoss.h"
#include "ShipBeam.h"
#include "ShipBubble.h"
#include "CannonBall.h"
#include "CannonBallDust.h"

#include "Barrel.h"

#include "BackGround.h"
#include "Map.h"
#include "Ocean.h"
#include "Cloud.h"
#include "WorldMapLevel.h"

SecondBossStage::SecondBossStage()
{
}

SecondBossStage::~SecondBossStage()
{
}

void SecondBossStage::LevelStart(GameEngineLevel* _PrevLevel)
{
	Oceans.resize(4);
	Clouds.resize(3);

	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, 0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\SecondBossStage\\SecondBoss\\Barrel");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\SecondBossStage\\SecondBoss\\DogFish");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\SecondBossStage\\SecondBoss\\Pirate");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\SecondBossStage\\SecondBoss\\Pirate_Bullet");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\SecondBossStage\\SecondBoss\\Shark");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\SecondBossStage\\SecondBoss\\Ship");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\SecondBossStage\\SecondBoss\\Ship_Bubble");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\SecondBossStage\\SecondBoss\\Ship_Cannon");
	ContentsSpriteManager::CreateFolderSpriteDir("Resources\\Texture\\SecondBossStage\\SecondBoss\\Periscope");
	ContentsSpriteManager::CreateFolderSpriteDir("Resources\\Texture\\SecondBossStage\\SecondBoss\\Ship_Beam");
	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\SecondBossStage\\SecondBoss\\Ship\\pirate_boatMast.Png");
	ContentsSpriteManager::CreateSingleSpriteDir("Resources\\Texture\\SecondBossStage\\Map");
	ContentsSpriteManager::CreateSingleSpriteDir("Resources\\Texture\\SecondBossStage\\Map\\Sky");
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

	Sky = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	Sky->BackGroundInitAuto("pirate_clouds_D.png");
	Sky->SetAutoScaleRatio(1.3f);
	Sky->SetBackGroundRendererPivotType(PivotType::Top);
	Sky->Transform.SetLocalPosition({ WinScaleHalf.X, 0.0f });

	Clouds[0] = CreateActor<Cloud>(EUPDATEORDER::BackGround);
	Clouds[0]->SetCloud(ERENDERORDER::PrevMap2, "pirate_clouds_A.png");
	Clouds[0]->Transform.SetLocalPosition({ 0.0f, -WinScaleHalf.Y });
	Clouds[0]->SetCloudSpeed(0.3f);

	Clouds[1] = CreateActor<Cloud>(EUPDATEORDER::BackGround);
	Clouds[1]->SetCloud(ERENDERORDER::PrevMap, "pirate_clouds_B.png");
	Clouds[1]->Transform.SetLocalPosition({ 0.0f, -WinScaleHalf.Y - 50.0f });
	Clouds[1]->SetCloudSpeed(0.2f);

	Clouds[2] = CreateActor<Cloud>(EUPDATEORDER::BackGround);
	Clouds[2]->SetCloud(ERENDERORDER::PrevMap1, "pirate_clouds_C.png");
	Clouds[2]->Transform.SetLocalPosition({ 0.0f, -WinScaleHalf.Y + 30.0f });
	Clouds[2]->SetCloudSpeed(0.1f);

	// 테스트용 맵
	SecondStageMap = CreateActor<Map>(EUPDATEORDER::Map);
	SecondStageMap->MapInit("SecondMap.Png");
	SecondStageMap->PixelMapInit("SecondStagePixelMap.Png");
	SecondStageMap->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });

	StageLevel::LevelStart(_PrevLevel);

	GameEngineInput::AddInputObject(this);
}

void SecondBossStage::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RETURN, this))
	{
		StageLevel::StageClear();
	}

	StageLevel::Update(_Delta);

	if (true == GameEngineInput::IsDown(VK_ESCAPE, this))
	{
		GameEngineCore::ChangeLevel("WorldMapLevel");
	}

	if (ESTAGERESULT::Success == StageResult)
	{
		WorldMapLevel::IsCreateStage2Flag();
	}
}

void SecondBossStage::LevelEnd(GameEngineLevel* _NextLevel)
{
	StageLevel::LevelEnd(_NextLevel);

	AllRemainActorDeath<PirateBullet>(EUPDATEORDER::Bullet);
	AllRemainActorDeath<PirateBulletParry>(EUPDATEORDER::Bullet);
	AllRemainActorDeath<Whistle_Effect>(EUPDATEORDER::Effect);
	AllRemainActorDeath<Shark>(EUPDATEORDER::Monster);
	AllRemainActorDeath<Shark_SplashEffect>(EUPDATEORDER::Effect);
	AllRemainActorDeath<Periscope>(EUPDATEORDER::Monster);
	AllRemainActorDeath<DogFish>(EUPDATEORDER::Monster);
	AllRemainActorDeath<DogFish_Splash>(EUPDATEORDER::Effect);
	AllRemainActorDeath<DogFish_DeathEffect>(EUPDATEORDER::Effect);

	AllRemainActorDeath<CannonBall>(EUPDATEORDER::Bullet);
	AllRemainActorDeath<CannonBallDust>(EUPDATEORDER::Effect);
	AllRemainActorDeath<ShipBubble>(EUPDATEORDER::Bullet);
	AllRemainActorDeath<ShipBeam>(EUPDATEORDER::Bullet);

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

	for (size_t i = 0; i < Clouds.size(); i++)
	{
		if (nullptr != Clouds[i])
		{
			Clouds[i]->Death();
			Clouds[i] = nullptr;
		}
	}

	Clouds.clear();

	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\SecondBossStage\\SecondBoss\\Barrel");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\SecondBossStage\\SecondBoss\\DogFish");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\SecondBossStage\\SecondBoss\\Pirate");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\SecondBossStage\\SecondBoss\\Pirate_Bullet");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\SecondBossStage\\SecondBoss\\Shark");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\SecondBossStage\\SecondBoss\\Ship");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\SecondBossStage\\SecondBoss\\Ship_Bubble");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\SecondBossStage\\SecondBoss\\Ship_Cannon");
	ContentsSpriteManager::FolderSpriteRelease("Resources\\Texture\\SecondBossStage\\SecondBoss\\Periscope");
	ContentsSpriteManager::FolderSpriteRelease("Resources\\Texture\\SecondBossStage\\SecondBoss\\Ship_Beam");
	ContentsSpriteManager::SingleSpriteRelease("pirate_boatMast.Png");
	ContentsSpriteManager::SingleSpriteInDirRelease("Resources\\Texture\\SecondBossStage\\Map");
	ContentsSpriteManager::SingleSpriteInDirRelease("Resources\\Texture\\SecondBossStage\\Map\\Sky");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\SecondBossStage\\Map\\Water");
}