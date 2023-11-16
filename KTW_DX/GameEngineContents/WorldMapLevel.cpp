#include "PreCompile.h"
#include "WorldMapLevel.h"

#include "Map.h"
#include "UpperObject.h"
#include "WorldMapEnter.h"
#include "WorldMapFlag.h"
#include "WorldMapPortal.h"
#include "WorldMapCharacter.h"
#include "Trigger.h"
#include "FadeObject.h"

bool WorldMapLevel::Stage1Clear = false;
bool WorldMapLevel::Stage2Clear = false;
bool WorldMapLevel::CreateStage1Flag = false;
bool WorldMapLevel::CreateStage2Flag = false;
bool WorldMapLevel::PortalSpawnDone = false;
float4 WorldMapLevel::CharacterSavePos = CHARACTERSTARTPOS;

WorldMapLevel::WorldMapLevel()
{
}

WorldMapLevel::~WorldMapLevel()
{
}

void WorldMapLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	// 리소스 Load
	ContentsResourcesManager::CreateSingleSpriteDir("Resources\\Texture\\WorldMapLevel\\Map");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\WorldMapLevel\\WorldMapEnter");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\WorldMapLevel\\WorldMapFlag");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\WorldMapLevel\\WorldMapPortal");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\WorldMapLevel\\WorldMapCharacter");

	// 미니맵 생성
	WorldMap = CreateActor<Map>(EUPDATEORDER::Map);
	WorldMap->MapInit("CupHead_WorldMap.png");
	WorldMap->PixelMapInit("CupHead_WorldMap_BitMap.png");

	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find("CupHead_WorldMap.png");
	MapScale = MapTexture->GetScale();
	float4 MapHalfScale = MapScale.Half();
	WorldMap->Transform.SetLocalPosition({ MapHalfScale.X, -MapHalfScale.Y });

	WorldMapUpper = CreateActor<UpperObject>(EUPDATEORDER::Map);
	WorldMapUpper->UpperObjectInit("CupHead_WorldMap_Upper.png", 0, false);
	WorldMapUpper->Transform.SetLocalPosition({ MapHalfScale.X, -MapHalfScale.Y });

	// 플레이 입구 생성
	TutorialEnter = CreateActor<WorldMapEnter>(EUPDATEORDER::Map);
	TutorialEnter->EnterAnimationInit("Tutorial_Enter_Ani", "TutorialEnter");
	TutorialEnter->Transform.SetLocalPosition(TUTORIALENTERPOS);
	TutorialEnter->SetEnterLevel("0.Tutorial_Stage");
	TutorialEnter->SetCollisionScaleAndPosition(TUTORIALENTERCOLLISIONSCALE, TUTORIALENTERCOLLISIONSPOSITION);

	FirstBossEnter = CreateActor<WorldMapEnter>(EUPDATEORDER::Map);
	FirstBossEnter->EnterAnimationInit("FirstBossMap_Enter_Ani", "FirstBossMapEnter");
	FirstBossEnter->Transform.SetLocalPosition(FIRSTBOSSENTERPOS);
	FirstBossEnter->SetEnterLevel("1.FirstBoss_Stage");
	FirstBossEnter->SetCollisionScaleAndPosition(FIRSTBOSSENTERCOLLISIONSCALE, FIRSTBOSSENTERCOLLISIONSPOSITION);

	SecondBossEnter = CreateActor<WorldMapEnter>(EUPDATEORDER::Map);
	SecondBossEnter->EnterAnimationInit("Tutorial_Enter_Ani", "SecondBossMapEnter");
	SecondBossEnter->Transform.SetLocalPosition(SECONDBOSSENTERPOS);
	SecondBossEnter->SetEnterLevel("2.SecondBoss_Stage");
	SecondBossEnter->SetCollisionScaleAndPosition(SECONDBOSSENTERCOLLISIONSCALE);

	LastBossEnter = CreateActor<Trigger>(EUPDATEORDER::Map);
	LastBossEnter->TriggerInit(ECOLLISIONORDER::Trigger, LASTBOSSENTERSCALE, LASTBOSSENTERPOSITION);

	if (true == Stage1Clear)
	{
		FirstBossFlag = CreateActor<WorldMapFlag>(EUPDATEORDER::Map);
		FirstBossFlag->Transform.SetLocalPosition(FIRSTFLAGPOSITION);
		FirstBossFlag->ChangeStayStateFlag();
	}

	if (true == Stage2Clear)
	{
		SecondBossFlag = CreateActor<WorldMapFlag>(EUPDATEORDER::Map);
		SecondBossFlag->Transform.SetLocalPosition(SECONDFLAGPOSITION);
		SecondBossFlag->ChangeStayStateFlag();
	}

	// 
	if (true == PortalSpawnDone)
	{
		IslandPortal = CreateActor<WorldMapPortal>(EUPDATEORDER::Map);
		IslandPortal->Transform.SetLocalPosition(ISLANDPORTALPOS);

		DevilIslandPortal = CreateActor<WorldMapPortal>(EUPDATEORDER::Map);
		DevilIslandPortal->Transform.SetLocalPosition(DEVILISLANDPORTALPOS);
		IslandPortal->SetDestination(DevilIslandPortal->Transform.GetLocalPosition());
		DevilIslandPortal->SetDestination(IslandPortal->Transform.GetLocalPosition());
	}

	// 캐릭터 생성
	Character = CreateActor<WorldMapCharacter>(EUPDATEORDER::Player);
	Character->Transform.SetLocalPosition(CharacterSavePos);
	// Character->Transform.SetLocalPosition({5580.0f, -900.0f});

	GetMainCamera()->Transform.SetLocalPosition(Character->Transform.GetWorldPosition());

	{
		CreateStateParameter Para;
		Para.Stay = [&](float _DeltaTime, GameEngineState* _Parent)
			{
				float4 CameraSettingPos = CalCameraPos(Character->Transform.GetWorldPosition());
				GetMainCamera()->Transform.SetLocalPosition(CameraSettingPos);

				if (true == CreateStage1Flag && nullptr == FirstBossFlag)
				{
					Stage1Clear = true;
					Character->ChangeClearState();
					FirstBossFlag = CreateActor<WorldMapFlag>(EUPDATEORDER::Map);
					FirstBossFlag->Transform.SetLocalPosition(FIRSTFLAGPOSITION);
				}

				if (true == CreateStage2Flag && nullptr == SecondBossFlag)
				{
					Stage2Clear = true;
					Character->ChangeClearState();
					SecondBossFlag = CreateActor<WorldMapFlag>(EUPDATEORDER::Map);
					SecondBossFlag->Transform.SetLocalPosition(SECONDFLAGPOSITION);
				}

				if (true == Stage1Clear
					&& true == FirstBossFlag->IsCurAnimation("Flag_Stay")
					&& true == Stage2Clear
					&& true == SecondBossFlag->IsCurAnimation("Flag_Stay")
					&& nullptr == IslandPortal
					&& nullptr == DevilIslandPortal)
				{
					WorldMapState.ChangeState(EWORLDMAPSTATE::IslandPortalCreate);
				}
			};

		WorldMapState.CreateState(EWORLDMAPSTATE::Idle, Para);
	}

	{
		CreateStateParameter Para;
		Para.Stay = [&](float _DeltaTime, GameEngineState* _Parent)
			{
				IslandPortalSpawn(_DeltaTime);

				if (true == IslandPortalAnimationEndCheck())
				{
					WorldMapState.ChangeState(EWORLDMAPSTATE::DevilIslandPortalCreate);
				}
			};

		WorldMapState.CreateState(EWORLDMAPSTATE::IslandPortalCreate, Para);
	}

	{
		CreateStateParameter Para;
		Para.Stay = [&](float _DeltaTime, GameEngineState* _Parent)
			{
				DevilIslandPortalSpawn(_DeltaTime);

				if (true == DevilIslandPortalAnimationEndCheck())
				{
					WorldMapState.ChangeState(EWORLDMAPSTATE::ToIdle);
				}
			};

		WorldMapState.CreateState(EWORLDMAPSTATE::DevilIslandPortalCreate, Para);
	}

	{
		CreateStateParameter Para;
		Para.Stay = [&](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == CameraMoveToCharacterPos(_DeltaTime))
				{
					WorldMapState.ChangeState(EWORLDMAPSTATE::Idle);
				}
			};

		WorldMapState.CreateState(EWORLDMAPSTATE::ToIdle, Para);
	}

	WorldMapState.ChangeState(EWORLDMAPSTATE::Idle);

	GameEngineInput::AddInputObject(this);
}

void WorldMapLevel::Update(float _Delta)
{
	WorldMapState.Update(_Delta);

	if (true == GameEngineInput::IsDown('0', this))
	{
		Stage2Clear = true;
		Character->ChangeClearState();
		SecondBossFlag = CreateActor<WorldMapFlag>(EUPDATEORDER::Map);
		SecondBossFlag->Transform.SetLocalPosition(SECONDFLAGPOSITION);
	}

	if (true == GameEngineInput::IsDown('9', this))
	{
		Stage1Clear = true;
		Character->ChangeClearState();
		FirstBossFlag = CreateActor<WorldMapFlag>(EUPDATEORDER::Map);
		FirstBossFlag->Transform.SetLocalPosition(FIRSTFLAGPOSITION);
	}
}

void WorldMapLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	CharacterSavePos = Character->Transform.GetWorldPosition();

	AllRemainActorDeath<FadeObject>(EUPDATEORDER::UI);

	if (nullptr != WorldMap)
	{
		WorldMap->Death();
		WorldMap = nullptr;
	}

	if (nullptr != WorldMapUpper)
	{
		WorldMapUpper->Death();
		WorldMapUpper = nullptr;
	}

	if (nullptr != Character)
	{
		Character->Death();
		Character = nullptr;
	}

	if (nullptr != TutorialEnter)
	{
		TutorialEnter->Death();
		TutorialEnter = nullptr;
	}

	if (nullptr != FirstBossEnter)
	{
		FirstBossEnter->Death();
		FirstBossEnter = nullptr;
	}

	if (nullptr != SecondBossEnter)
	{
		SecondBossEnter->Death();
		SecondBossEnter = nullptr;
	}

	if (nullptr != LastBossEnter)
	{
		LastBossEnter->Death();
		LastBossEnter = nullptr;
	}

	if (nullptr != FirstBossFlag)
	{
		FirstBossFlag->Death();
		FirstBossFlag = nullptr;
	}

	if (nullptr != SecondBossFlag)
	{
		SecondBossFlag->Death();
		SecondBossFlag = nullptr;
	}

	if (nullptr != IslandPortal)
	{
		IslandPortal->Death();
		IslandPortal = nullptr;
	}

	if (nullptr != DevilIslandPortal)
	{
		DevilIslandPortal->Death();
		DevilIslandPortal = nullptr;
	}

	ContentsResourcesManager::CreateSingleSpriteDir("Resources\\Texture\\WorldMapLevel\\Map");
	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\WorldMapLevel\\WorldMapEnter");
	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\WorldMapLevel\\WorldMapFlag");
	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\WorldMapLevel\\WorldMapPortal");
	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\WorldMapLevel\\WorldMapCharacter");
}

float4 WorldMapLevel::CalCameraPos(const float4& _SetPos)
{
	float4 SettingPos = _SetPos;
	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();

	float SetLeft = SettingPos.X - WinScaleHalf.X;
	float SetRight = SettingPos.X + WinScaleHalf.X;
	float SetTop = SettingPos.Y + WinScaleHalf.Y;
	float SetBot = SettingPos.Y - WinScaleHalf.Y;

	if (0.0f > SetLeft)
	{
		SettingPos.X = WinScaleHalf.X;
	}

	if (MapScale.X < SetRight)
	{
		SettingPos.X = MapScale.X - WinScaleHalf.X;
	}

	if (0.0f < SetTop)
	{
		SettingPos.Y = -WinScaleHalf.Y;
	}

	if (-MapScale.Y > SetBot)
	{
		SettingPos.Y = WinScaleHalf.Y - MapScale.Y;
	}

	return SettingPos;
}

void WorldMapLevel::IslandPortalSpawn(float _Delta)
{
	if (nullptr != IslandPortal)
	{
		return;
	}

	float4 CameraPos = GetMainCamera()->Transform.GetWorldPosition();
	float4 PortalPos = ISLANDPORTALPOS;

	float4 MovePos = PortalPos - CameraPos;

	if (nullptr == IslandPortal)
	{
		if (MovePos.Size() < 5.0f)
		{
			IslandPortal = CreateActor<WorldMapPortal>(EUPDATEORDER::Map);
			IslandPortal->Transform.SetLocalPosition(ISLANDPORTALPOS);
		}
		else
		{
			MovePos.Normalize();
			GetMainCamera()->Transform.AddLocalPosition(MovePos * _Delta * CameraMoveSpeed);
		}
	}
}

bool WorldMapLevel::IslandPortalAnimationEndCheck()
{
	if (nullptr != IslandPortal && true == IslandPortal->IsCurAnimation("Portal_Idle"))
	{
		return true;
	}

	return false;
}

void WorldMapLevel::DevilIslandPortalSpawn(float _Delta)
{
	if (nullptr != DevilIslandPortal)
	{
		return;
	}

	float4 CameraPos = GetMainCamera()->Transform.GetWorldPosition();
	float4 PortalPos = DEVILISLANDPORTALPOS;

	float4 MovePos = PortalPos - CameraPos;

	if (nullptr != IslandPortal)
	{
		if (MovePos.Size() < 5.0f)
		{
			DevilIslandPortal = CreateActor<WorldMapPortal>(EUPDATEORDER::Map);
			DevilIslandPortal->Transform.SetLocalPosition(DEVILISLANDPORTALPOS);
			IslandPortal->SetDestination(DevilIslandPortal->Transform.GetLocalPosition());
			DevilIslandPortal->SetDestination(IslandPortal->Transform.GetLocalPosition());
			PortalSpawnDone = true;
		}
		else
		{
			MovePos.Normalize();
			GetMainCamera()->Transform.AddLocalPosition(MovePos * _Delta * CameraMoveSpeed);
		}
	}
}

bool WorldMapLevel::DevilIslandPortalAnimationEndCheck()
{
	if (nullptr != DevilIslandPortal && true == DevilIslandPortal->IsCurAnimation("Portal_Idle"))
	{
		return true;
	}

	return false;
}

bool WorldMapLevel::CameraMoveToCharacterPos(float _Delta)
{
	float4 CameraPos = GetMainCamera()->Transform.GetWorldPosition();
	float4 CharacterPos = Character->Transform.GetWorldPosition();

	float4 MovePos = CharacterPos - CameraPos;

	if (MovePos.Size() < 5.0f)
	{
		return true;
	}

	MovePos.Normalize();
	GetMainCamera()->Transform.AddLocalPosition(MovePos * _Delta * CameraMoveSpeed);
	return false;
}