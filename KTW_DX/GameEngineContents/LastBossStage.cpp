#include "PreCompile.h"
#include "LastBossStage.h"

#include "BackGround.h"
#include "Map.h"
#include "DevilChair.h"
#include "Devil.h"
#include "BaseCharacter.h"

LastBossStage::LastBossStage()
{
}

LastBossStage::~LastBossStage()
{
}

void LastBossStage::Start()
{
	//StageLevel::Start();

	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\BackGround\\LastStageBackGround.png");
	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStageMap.png");
	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStagePixelMap.png");
	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStageChair.png");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\Devil");

	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find("LastStagePixelMap.png");
	float4 MapScale = MapTexture->GetScale();
	float4 WinScale = GameEngineCore::MainWindow.GetScale();

	GetMainCamera()->Transform.SetLocalPosition({ MapScale.Half().X, -MapScale.Half().Y });

	StageBackGround = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	StageBackGround->BackGroundInit("LastStageBackGround.png");
	StageBackGround->Transform.SetLocalPosition({ MapScale.Half().X, -WinScale.Half().Y });

	StageMap = CreateActor<Map>(EUPDATEORDER::Map);
	StageMap->MapInit("LastStageMap.Png");
	StageMap->PixelMapInit("LastStagePixelMap.Png");
	StageMap->Transform.SetLocalPosition({ MapScale.Half().X, -MapScale.Half().Y });

	BossChair = CreateActor<DevilChair>(EUPDATEORDER::Map);
	BossChair->Transform.SetLocalPosition({ MapScale.Half().X, -WinScale.Y + 80.0f });

	Boss = CreateActor<Devil>(EUPDATEORDER::Monster);
	Boss->Transform.SetLocalPosition({ MapScale.Half().X, -WinScale.Y });
	
	GameEngineInput::AddInputObject(this);
}

void LastBossStage::Update(float _Delta)
{
	// LastStageCameraMove(_Delta);
}

void LastBossStage::LevelStart(GameEngineLevel* _PrevLevel)
{
	StageLevel::LevelStart(_PrevLevel);
}

void LastBossStage::LevelEnd(GameEngineLevel* _NextLevel)
{
	StageLevel::LevelEnd(_NextLevel);
}

void LastBossStage::LastStageCameraMove(float _Delta)
{
	float4 CameraPos = GetMainCamera()->Transform.GetWorldPosition();
	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find("LastStagePixelMap.png");
	float4 MapScale = MapTexture->GetScale();

	float MovableValue = MapScale.X - WinScale.X;
	float CameraMinPosX = MapScale.Half().X - MovableValue / 2.0f;
	float CameraMaxPosX = MapScale.Half().X + MovableValue / 2.0f;

	float4 CharacterPos = Player->Transform.GetWorldPosition();

	float Ratio = MovableValue / MapScale.X;

	float CameraPosX = CharacterPos.X * Ratio;

	CameraPos.X = CameraPosX;

	GetMainCamera()->Transform.SetLocalPosition(CameraPos);
}