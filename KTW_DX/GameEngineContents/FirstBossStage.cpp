#include "PreCompile.h"
#include "FirstBossStage.h"
#include "ContentsCore.h"

#include "FirstBoss.h"
#include "FirstBossMoveDust.h"
#include "FirstMapParryObject.h"

#include "FirstBossPhase3.h"
#include "FirstBossPhase3Effect.h"

#include "BackGround.h"
#include "FarForest.h"
#include "NearForest.h"
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

	ContentsResourcesManager::SoundLoadDir("Resources\\Sound\\FirstStage\\Slime_Big");
	ContentsResourcesManager::SoundLoadDir("Resources\\Sound\\FirstStage\\Slime_Small");
	ContentsResourcesManager::SoundLoadDir("Resources\\Sound\\FirstStage\\Slime_Tombstone");
	ContentsResourcesManager::CreateFolderSpriteDir("Resources\\Texture\\FirstBossStage\\Map\\FirstBossBackGroundAnimation");
	ContentsResourcesManager::CreateSingleSpriteImage("Resources\\Texture\\FirstBossStage\\Map\\FirstBossBackGround_1.png");
	ContentsResourcesManager::CreateSingleSpriteImage("Resources\\Texture\\FirstBossStage\\Map\\FirstBossBackGround_2.png");
	ContentsResourcesManager::CreateFolderSpriteDir("Resources\\Texture\\FirstBossStage\\Map\\FirstBossParryObject");
	ContentsResourcesManager::CreateSingleSpriteImage("Resources\\Texture\\FirstBossStage\\Map\\FirstBossMap.png");
	ContentsResourcesManager::CreateSingleSpriteImage("Resources\\Texture\\FirstBossStage\\Map\\FirstBossBitMap.png");
	ContentsResourcesManager::CreateSingleSpriteImage("Resources\\Texture\\FirstBossStage\\Map\\FirstBossMap_Upper.png");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\FirstBossStage\\FirstBoss");

	BGMPlayer = GameEngineSound::SoundPlay("12 Ruse Of An Ooze.mp3");

	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find("FirstBossBitMap.png");
	MapScale = MapTexture.get()->GetScale();

	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	float4 WinScaleHalf = WinScale.Half();

	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -MapScale.Y + WinScaleHalf.Y, 0.0f});
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	Boss = CreateActor<FirstBoss>(EUPDATEORDER::Monster);
	Boss->Transform.SetLocalPosition(FIRSTBOSSSPAWNPOSITION);

	StageBackGroundFarForest = CreateActor<FarForest>(EUPDATEORDER::BackGround);
	StageBackGroundFarForest->Transform.SetLocalPosition({ MapScale.Half().X, -MapScale.Y + WinScale.Y });

	StageBackGroundNearForest = CreateActor<NearForest>(EUPDATEORDER::BackGround);
	StageBackGroundNearForest->Transform.SetLocalPosition({ MapScale.Half().X, -MapScale.Y + WinScaleHalf.Y });

	StageBackGround = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	StageBackGround->AnimationInit("FirstBossBackGroundAnimation", "FirstBossBackGroundAnimation", 0.1f, true, false);
	StageBackGround->Transform.SetLocalPosition({ MapScale.Half().X, -WinScaleHalf.Y });

	StageMap = CreateActor<Map>(EUPDATEORDER::Map);
	StageMap->MapInit("FirstBossMap.png");
	StageMap->PixelMapInit("FirstBossBitMap.png");
	StageMap->Transform.SetLocalPosition({ MapScale.Half().X, -MapScale.Half().Y });

	StageMapUpper = CreateActor<UpperObject>(EUPDATEORDER::Map);
	StageMapUpper->UpperObjectInit("FirstBossMap_Upper.png");
	StageMapUpper->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });

	StageLevel::LevelStart(_PrevLevel);

	GameEngineInput::AddInputObject(this);
}

void FirstBossStage::Update(float _Delta)
{
	CameraMove(_Delta);

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

	BGMPlayer.Stop();

	StageLevel::LevelEnd(_NextLevel);

	AllRemainActorDeath<FirstMapParryObject>(EUPDATEORDER::Effect);
	AllRemainActorDeath<FirstBossMoveDust>(EUPDATEORDER::Effect);
	AllRemainActorDeath<FirstBossPhase3Effect>(EUPDATEORDER::Effect);

	if (nullptr != StageBackGround)
	{
		StageBackGround->Death();
		StageBackGround = nullptr;
	}

	if (nullptr != StageBackGroundFarForest)
	{
		StageBackGroundFarForest->Death();
		StageBackGroundFarForest = nullptr;
	}

	if (nullptr != StageBackGroundNearForest)
	{
		StageBackGroundNearForest->Death();
		StageBackGroundNearForest = nullptr;
	}

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

	ContentsResourcesManager::FolderSpriteRelease("Resources\\Texture\\FirstBossStage\\Map\\FirstBossBackGroundAnimation");
	ContentsResourcesManager::SingleSpriteRelease("FirstBossBackGround_1.png");
	ContentsResourcesManager::SingleSpriteRelease("FirstBossBackGround_2.png");
	ContentsResourcesManager::FolderSpriteRelease("Resources\\Texture\\FirstBossStage\\Map\\FirstBossParryObject");
	ContentsResourcesManager::SingleSpriteRelease("FirstBossMap.png");
	ContentsResourcesManager::SingleSpriteRelease("FirstBossBitMap.png");
	ContentsResourcesManager::SingleSpriteRelease("FirstBossMap_Upper.png");
	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\FirstBossStage\\FirstBoss");
}

float4 FirstBossStage::CameraMove(float _Delta)
{
	float4 MovePos = StageLevel::CameraMove(_Delta);

	MovePos /= CameraSpeed;

	float4 FarForestMovePos = MovePos * 30.0f;
	float4 NearForestMovePos = MovePos * -20.0f;

	StageBackGroundFarForest->Transform.AddLocalPosition(FarForestMovePos);
	StageBackGroundNearForest->Transform.AddLocalPosition(NearForestMovePos);

	float4 CameraPos = GetMainCamera()->Transform.GetWorldPosition();
	StageMapUpper->Transform.SetWorldPosition(CameraPos);

	return MovePos;
}