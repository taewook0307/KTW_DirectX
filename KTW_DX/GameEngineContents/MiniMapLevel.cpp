#include "PreCompile.h"
#include "MiniMapLevel.h"

#include "Map.h"
#include "UpperObject.h"
#include "MiniMapEnter.h"
#include "MiniMapFlag.h"
#include "MiniMapPortal.h"
#include "MiniMapCharacter.h"
#include "Trigger.h"

bool MiniMapLevel::Stage1Clear = false;
bool MiniMapLevel::Stage2Clear = false;
bool MiniMapLevel::CreateStage1Flag = false;
bool MiniMapLevel::CreateStage2Flag = false;
bool MiniMapLevel::PortalSpawnDone = false;
float4 MiniMapLevel::CharacterSavePos = CHARACTERSTARTPOS;

MiniMapLevel::MiniMapLevel()
{
}

MiniMapLevel::~MiniMapLevel()
{
}

void MiniMapLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	// 리소스 Load
	ContentsSpriteManager::CreateSingleSpriteDir("Resources\\Texture\\MiniMapLevel\\Map");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\MiniMapLevel\\MiniMapEnter");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\MiniMapLevel\\MiniMapFlag");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\MiniMapLevel\\MiniMapPortal");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\MiniMapLevel\\MiniMapCharacter");

	// 미니맵 생성
	MiniMap = CreateActor<Map>(EUPDATEORDER::Map);
	MiniMap->MapInit("CupHead_MiniMap.png");
	MiniMap->PixelMapInit("CupHead_MiniMap_BitMap.png");

	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find("CupHead_MiniMap.png");
	MapScale = MapTexture->GetScale();
	float4 MapHalfScale = MapScale.Half();
	MiniMap->Transform.SetLocalPosition({ MapHalfScale.X, -MapHalfScale.Y });

	MiniMapUpper = CreateActor<UpperObject>(EUPDATEORDER::Map);
	MiniMapUpper->UpperObjectInit("CupHead_MiniMap_Upper.png", 0, false);
	MiniMapUpper->Transform.SetLocalPosition({ MapHalfScale.X, -MapHalfScale.Y });

	// 플레이 입구 생성
	TutorialEnter = CreateActor<MiniMapEnter>(EUPDATEORDER::Map);
	TutorialEnter->EnterAnimationInit("Tutorial_Enter_Ani", "TutorialEnter");
	TutorialEnter->Transform.SetLocalPosition(TUTORIALENTERPOS);
	TutorialEnter->SetEnterLevel("0.Tutorial_Stage");
	TutorialEnter->SetCollisionScaleAndPosition(TUTORIALENTERCOLLISIONSCALE, TUTORIALENTERCOLLISIONSPOSITION);

	FirstBossEnter = CreateActor<MiniMapEnter>(EUPDATEORDER::Map);
	FirstBossEnter->EnterAnimationInit("FirstBossMap_Enter_Ani", "FirstBossMapEnter");
	FirstBossEnter->Transform.SetLocalPosition(FIRSTBOSSENTERPOS);
	FirstBossEnter->SetEnterLevel("1.FirstBoss_Stage");
	FirstBossEnter->SetCollisionScaleAndPosition(FIRSTBOSSENTERCOLLISIONSCALE, FIRSTBOSSENTERCOLLISIONSPOSITION);

	SecondBossEnter = CreateActor<MiniMapEnter>(EUPDATEORDER::Map);
	SecondBossEnter->EnterAnimationInit("Tutorial_Enter_Ani", "SecondBossMapEnter");
	SecondBossEnter->Transform.SetLocalPosition(SECONDBOSSENTERPOS);
	SecondBossEnter->SetEnterLevel("2.SecondBoss_Stage");
	SecondBossEnter->SetCollisionScaleAndPosition(SECONDBOSSENTERCOLLISIONSCALE);

	LastBossEnter = CreateActor<Trigger>(EUPDATEORDER::Map);
	LastBossEnter->TriggerInit(ECOLLISIONORDER::Trigger, LASTBOSSENTERSCALE, LASTBOSSENTERPOSITION);

	if (true == Stage1Clear)
	{
		FirstBossFlag = CreateActor<MiniMapFlag>(EUPDATEORDER::Map);
		FirstBossFlag->Transform.SetLocalPosition(FIRSTFLAGPOSITION);
		FirstBossFlag->ChangeStayStateFlag();
	}

	if (true == Stage2Clear)
	{
		SecondBossFlag = CreateActor<MiniMapFlag>(EUPDATEORDER::Map);
		SecondBossFlag->Transform.SetLocalPosition(SECONDFLAGPOSITION);
		SecondBossFlag->ChangeStayStateFlag();
	}

	// 
	if (true == PortalSpawnDone)
	{
		IslandPortal = CreateActor<MiniMapPortal>(EUPDATEORDER::Map);
		IslandPortal->Transform.SetLocalPosition(ISLANDPORTALPOS);

		DevilIslandPortal = CreateActor<MiniMapPortal>(EUPDATEORDER::Map);
		DevilIslandPortal->Transform.SetLocalPosition(DEVILISLANDPORTALPOS);
		IslandPortal->SetDestination(DevilIslandPortal->Transform.GetLocalPosition());
		DevilIslandPortal->SetDestination(IslandPortal->Transform.GetLocalPosition());
	}

	// 캐릭터 생성
	Character = CreateActor<MiniMapCharacter>(EUPDATEORDER::Player);
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
					FirstBossFlag = CreateActor<MiniMapFlag>(EUPDATEORDER::Map);
					FirstBossFlag->Transform.SetLocalPosition(FIRSTFLAGPOSITION);
				}

				if (true == CreateStage2Flag && nullptr == SecondBossFlag)
				{
					Stage2Clear = true;
					Character->ChangeClearState();
					SecondBossFlag = CreateActor<MiniMapFlag>(EUPDATEORDER::Map);
					SecondBossFlag->Transform.SetLocalPosition(SECONDFLAGPOSITION);
				}

				if (true == Stage1Clear && true == Stage2Clear && nullptr == IslandPortal && nullptr == DevilIslandPortal)
				{
					MiniMapState.ChangeState(EWORLDMAPSTATE::IslandPortalCreate);
				}
			};

		MiniMapState.CreateState(EWORLDMAPSTATE::Idle, Para);
	}

	{
		CreateStateParameter Para;
		Para.Stay = [&](float _DeltaTime, GameEngineState* _Parent)
			{
				IslandPortalSpawn(_DeltaTime);

				if (true == IslandPortalAnimationEndCheck())
				{
					MiniMapState.ChangeState(EWORLDMAPSTATE::DevilIslandPortalCreate);
				}
			};

		MiniMapState.CreateState(EWORLDMAPSTATE::IslandPortalCreate, Para);
	}

	{
		CreateStateParameter Para;
		Para.Stay = [&](float _DeltaTime, GameEngineState* _Parent)
			{
				DevilIslandPortalSpawn(_DeltaTime);

				if (true == DevilIslandPortalAnimationEndCheck())
				{
					MiniMapState.ChangeState(EWORLDMAPSTATE::ToIdle);
				}
			};

		MiniMapState.CreateState(EWORLDMAPSTATE::DevilIslandPortalCreate, Para);
	}

	{
		CreateStateParameter Para;
		Para.Stay = [&](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == CameraMoveToCharacterPos(_DeltaTime))
				{
					MiniMapState.ChangeState(EWORLDMAPSTATE::Idle);
				}
			};

		MiniMapState.CreateState(EWORLDMAPSTATE::ToIdle, Para);
	}

	MiniMapState.ChangeState(EWORLDMAPSTATE::Idle);

	GameEngineInput::AddInputObject(this);
}

void MiniMapLevel::Update(float _Delta)
{
	MiniMapState.Update(_Delta);

	if (true == GameEngineInput::IsDown('0', this))
	{
		Stage2Clear = true;
		Character->ChangeClearState();
		SecondBossFlag = CreateActor<MiniMapFlag>(EUPDATEORDER::Map);
		SecondBossFlag->Transform.SetLocalPosition(SECONDFLAGPOSITION);
	}

	if (true == GameEngineInput::IsDown('9', this))
	{
		Stage1Clear = true;
		Character->ChangeClearState();
		FirstBossFlag = CreateActor<MiniMapFlag>(EUPDATEORDER::Map);
		FirstBossFlag->Transform.SetLocalPosition(FIRSTFLAGPOSITION);
	}
}

void MiniMapLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	CharacterSavePos = Character->Transform.GetWorldPosition();

	if (nullptr != MiniMap)
	{
		MiniMap->Death();
		MiniMap = nullptr;
	}

	if (nullptr != MiniMapUpper)
	{
		MiniMapUpper->Death();
		MiniMapUpper = nullptr;
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

	ContentsSpriteManager::CreateSingleSpriteDir("Resources\\Texture\\MiniMapLevel\\Map");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\MiniMapLevel\\MiniMapEnter");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\MiniMapLevel\\MiniMapFlag");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\MiniMapLevel\\MiniMapPortal");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\MiniMapLevel\\MiniMapCharacter");
}

float4 MiniMapLevel::CalCameraPos(const float4& _SetPos)
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

void MiniMapLevel::IslandPortalSpawn(float _Delta)
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
			IslandPortal = CreateActor<MiniMapPortal>(EUPDATEORDER::Map);
			IslandPortal->Transform.SetLocalPosition(ISLANDPORTALPOS);
		}
		else
		{
			MovePos.Normalize();
			GetMainCamera()->Transform.AddLocalPosition(MovePos * _Delta * CameraMoveSpeed);
		}
	}
}

bool MiniMapLevel::IslandPortalAnimationEndCheck()
{
	if (nullptr != IslandPortal && true == IslandPortal->PortalRenderer->IsCurAnimation("Portal_Idle"))
	{
		return true;
	}

	return false;
}

void MiniMapLevel::DevilIslandPortalSpawn(float _Delta)
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
			DevilIslandPortal = CreateActor<MiniMapPortal>(EUPDATEORDER::Map);
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

bool MiniMapLevel::DevilIslandPortalAnimationEndCheck()
{
	if (nullptr != DevilIslandPortal && true == DevilIslandPortal->PortalRenderer->IsCurAnimation("Portal_Idle"))
	{
		return true;
	}

	return false;
}

bool MiniMapLevel::CameraMoveToCharacterPos(float _Delta)
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