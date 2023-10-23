#include "PreCompile.h"
#include "MiniMapLevel.h"

#include "Map.h"
#include "UpperObject.h"
#include "MiniMapEnter.h"
#include "MiniMapFlag.h"
#include "MiniMapCharacter.h"

bool MiniMapLevel::Stage1Clear = false;
bool MiniMapLevel::Stage2Clear = false;
bool MiniMapLevel::CreateStage1Flag = false;
bool MiniMapLevel::CreateStage2Flag = false;
float4 MiniMapLevel::CharacterPos = CHARACTERSTARTPOS;

MiniMapLevel::MiniMapLevel()
{
}

MiniMapLevel::~MiniMapLevel()
{
}

void MiniMapLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, 0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	// 리소스 Load

	ContentsSpriteManager::CreateSingleSpriteDir("Resources\\Texture\\MiniMapLevel\\Map");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\MiniMapLevel\\MiniMapEnter");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\MiniMapLevel\\MiniMapFlag");

	// 미니맵 생성
	MiniMap = CreateActor<Map>(EUPDATEORDER::Map);
	MiniMap->MapInit("CupHead_MiniMap.png");
	MiniMap->PixelMapInit("CupHead_MiniMap_BitMap.png");

	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find("CupHead_MiniMap.png");
	float4 MapTextureHalfScale = MapTexture->GetScale().Half();
	MiniMap->Transform.SetLocalPosition({ MapTextureHalfScale.X, -MapTextureHalfScale.Y });

	MiniMapUpper = CreateActor<UpperObject>(EUPDATEORDER::Map);
	MiniMapUpper->UpperObjectInit("CupHead_MiniMap_Upper.png", 0, false);
	MiniMapUpper->Transform.SetLocalPosition({ MapTextureHalfScale.X, -MapTextureHalfScale.Y });

	// 플레이 입구 생성
	TutorialEnter = CreateActor<MiniMapEnter>(EUPDATEORDER::Map);
	TutorialEnter->EnterAnimationInit("Tutorial_Enter_Ani", "TutorialEnter");
	TutorialEnter->Transform.SetLocalPosition(TUTORIALENTERPOS);
	TutorialEnter->SetEnterLevel("Tutorial_Stage");
	TutorialEnter->SetCollisionScaleAndPosition(TUTORIALENTERCOLLISIONSCALE, TUTORIALENTERCOLLISIONSPOSITION);

	FirstBossEnter = CreateActor<MiniMapEnter>(EUPDATEORDER::Map);
	FirstBossEnter->EnterAnimationInit("FirstBossMap_Enter_Ani", "FirstBossMapEnter");
	FirstBossEnter->Transform.SetLocalPosition(FIRSTBOSSENTERPOS);
	FirstBossEnter->SetEnterLevel("FirstBoss_Stage");
	FirstBossEnter->SetCollisionScaleAndPosition(FIRSTBOSSENTERCOLLISIONSCALE, FIRSTBOSSENTERCOLLISIONSPOSITION);

	SecondBossEnter = CreateActor<MiniMapEnter>(EUPDATEORDER::Map);
	SecondBossEnter->EnterAnimationInit("Tutorial_Enter_Ani", "SecondBossMapEnter");
	SecondBossEnter->Transform.SetLocalPosition(SECONDBOSSENTERPOS);
	SecondBossEnter->SetEnterLevel("SecondBoss_Stage");
	SecondBossEnter->SetCollisionScaleAndPosition(SECONDBOSSENTERCOLLISIONSCALE);

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

	// 캐릭터 생성
	Character = CreateActor<MiniMapCharacter>(EUPDATEORDER::Player);
	Character->Transform.SetLocalPosition(CharacterPos);
}

void MiniMapLevel::Update(float _Delta)
{
	float4 CharacterPos = Character->Transform.GetWorldPosition();
	GetMainCamera()->Transform.SetLocalPosition(CharacterPos);

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
}

void MiniMapLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	CharacterPos = Character->Transform.GetWorldPosition();

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

	ContentsSpriteManager::CreateSingleSpriteDir("Resources\\Texture\\MiniMapLevel\\Map");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\MiniMapLevel\\MiniMapEnter");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\MiniMapLevel\\MiniMapFlag");
}