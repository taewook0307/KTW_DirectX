#include "PreCompile.h"
#include "FirstBossStage.h"
#include "ContentsCore.h"

#include "FirstBoss.h"
#include "FirstBossMoveDust.h"
#include "FirstMapParryObject.h"

#include "FirstBossPhase3.h"
#include "FirstBossPhase3Effect.h"

#include "Map.h"
#include "UpperObject.h"
#include "StageStartUI.h"
#include "StageFailUI.h"
#include "StageClearUI.h"
#include "WorldMapLevel.h"

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
	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, 0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	ContentsSpriteManager::CreateFolderSpriteDir("Resources\\Texture\\FirstBossStage\\Map\\FirstBossMap");
	ContentsSpriteManager::CreateFolderSpriteDir("Resources\\Texture\\FirstBossStage\\Map\\FirstBossParryObject");
	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\FirstBossStage\\Map\\FirstBossBitMap.png");
	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\FirstBossStage\\Map\\FirstBossMap_Upper.png");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\FirstBossStage\\FirstBoss");

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

	GameEngineInput::AddInputObject(this);
}

void FirstBossStage::Update(float _Delta)
{
	if(true == GameEngineInput::IsDown(VK_RETURN, this))
	{
		StageLevel::StageClear();
	}

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

	if (true == GameEngineInput::IsDown(VK_ESCAPE, this))
	{
		GameEngineCore::ChangeLevel("WorldMapLevel");
	}

	if (ESTAGERESULT::Success == StageResult)
	{
		WorldMapLevel::IsCreateStage1Flag();
	}
}

void FirstBossStage::LevelEnd(GameEngineLevel* _NextLevel)
{
	Phase3Timer = PHASE3TIMER;
	Phase3Start = false;

	StageLevel::LevelEnd(_NextLevel);

	AllRemainActorDeath<FirstMapParryObject>(EUPDATEORDER::Effect);
	AllRemainActorDeath<FirstBossMoveDust>(EUPDATEORDER::Effect);
	AllRemainActorDeath<FirstBossPhase3Effect>(EUPDATEORDER::Effect);

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

	ContentsSpriteManager::FolderSpriteRelease("Resources\\Texture\\FirstBossStage\\Map\\FirstBossMap");
	ContentsSpriteManager::FolderSpriteRelease("Resources\\Texture\\FirstBossStage\\Map\\FirstBossParryObject");
	ContentsSpriteManager::SingleSpriteRelease("FirstBossBitMap.png");
	ContentsSpriteManager::SingleSpriteRelease("FirstBossMap_Upper.png");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\FirstBossStage\\FirstBoss");
}