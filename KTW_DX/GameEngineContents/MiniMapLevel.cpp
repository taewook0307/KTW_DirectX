#include "PreCompile.h"
#include "MiniMapLevel.h"

#include "Map.h"
#include "UpperObject.h"
#include "MiniMapEnter.h"
#include "MiniMapCharacter.h"

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
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\MiniMapLevel\\Map");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		size_t FileSize = Files.size();

		for (size_t i = 0; i < FileSize; i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
			GameEngineSprite::CreateSingle(File.GetFileName());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\MiniMapLevel\\MiniMapEnter");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}


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
	TutorialEnter->SetEnterLevel("TutorialStage");
	TutorialEnter->SetCollisionScaleAndPosition(TUTORIALENTERCOLLISIONSCALE, TUTORIALENTERCOLLISIONSPOSITION);

	FirstEnter = CreateActor<MiniMapEnter>(EUPDATEORDER::Map);
	FirstEnter->EnterAnimationInit("FirstBossMap_Enter_Ani", "FirstBossMapEnter");
	FirstEnter->Transform.SetLocalPosition(FIRSTBOSSENTERPOS);
	FirstEnter->SetEnterLevel("FirstBossStage");
	FirstEnter->SetCollisionScaleAndPosition(FIRSTBOSSENTERCOLLISIONSCALE, FIRSTBOSSENTERCOLLISIONSPOSITION);

	SecondEnter = CreateActor<MiniMapEnter>(EUPDATEORDER::Map);
	SecondEnter->EnterAnimationInit("Tutorial_Enter_Ani", "SecondBossMapEnter");
	SecondEnter->Transform.SetLocalPosition(SECONDBOSSENTERPOS);
	SecondEnter->SetEnterLevel("SecondBossStage");
	SecondEnter->SetCollisionScaleAndPosition(SECONDBOSSENTERCOLLISIONSCALE);

	// 캐릭터 생성
	Character = CreateActor<MiniMapCharacter>(EUPDATEORDER::Player);
	Character->Transform.SetLocalPosition(CharacterPos);
}

void MiniMapLevel::Update(float _Delta)
{
	float4 CharacterPos = Character->Transform.GetWorldPosition();
	GetMainCamera()->Transform.SetLocalPosition(CharacterPos);
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

	if (nullptr != FirstEnter)
	{
		FirstEnter->Death();
		FirstEnter = nullptr;
	}
}