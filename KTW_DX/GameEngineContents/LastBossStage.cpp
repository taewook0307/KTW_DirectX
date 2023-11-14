#include "PreCompile.h"
#include "LastBossStage.h"

#include "BackGround.h"
#include "Map.h"
#include "DevilChair.h"
#include "Devil.h"
#include "SummonDevil.h"
#include "BaseCharacter.h"

LastBossStage::LastBossStage()
{
}

LastBossStage::~LastBossStage()
{
}

void LastBossStage::LevelStart(GameEngineLevel* _PrevLevel)
{
	EACTORDIR SummonDir = EACTORDIR::Left;

	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\BackGround\\LastStageBackGround.png");
	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStageMap.png");
	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStagePixelMap.png");
	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStageChair.png");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\Devil");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\SpiderHead");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\SummonDevil");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\FireBall");

	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find("LastStagePixelMap.png");
	MapScale = MapTexture->GetScale();
	float4 WinScale = GameEngineCore::MainWindow.GetScale();

	GetMainCamera()->Transform.SetLocalPosition({ MapScale.Half().X, -WinScale.Half().Y });

	StageBackGround = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	StageBackGround->BackGroundInitAuto("LastStageBackGround.png");
	StageBackGround->Transform.SetLocalPosition({ MapScale.Half().X, -WinScale.Half().Y });

	StageMap = CreateActor<Map>(EUPDATEORDER::Map);
	StageMap->MapInit("LastStageMap.Png");
	StageMap->PixelMapInit("LastStagePixelMap.Png");
	StageMap->Transform.SetLocalPosition({ MapScale.Half().X, -MapScale.Half().Y });

	BossChair = CreateActor<DevilChair>(EUPDATEORDER::Map);
	BossChair->Transform.SetLocalPosition({ MapScale.Half().X, -WinScale.Y + 80.0f });

	Boss = CreateActor<Devil>(EUPDATEORDER::Monster);
	Boss->Transform.SetLocalPosition({ MapScale.Half().X, -WinScale.Y });

	StageLevel::LevelStart(_PrevLevel);

	GameEngineInput::AddInputObject(this);
}

void LastBossStage::Update(float _Delta)
{
	CameraMove(_Delta);

	if (true == GameEngineInput::IsDown(VK_RETURN, this))
	{
		StageLevel::StageClear();
	}

	StageLevel::LastLevelEnd(_Delta);

	if (0.0f > SummonTimer)
	{
		CreateSummonDevil();
		SummonTimer = SUMMONTIMER;
	}

	SummonTimer -= _Delta;
}

void LastBossStage::LevelEnd(GameEngineLevel* _NextLevel)
{
	StageLevel::LevelEnd(_NextLevel);

	Boss->AllSummonDeath();
	AllRemainActorDeath<SummonDevil>(EUPDATEORDER::Monster);

	if (nullptr != StageBackGround)
	{
		StageBackGround->Death();
		StageBackGround = nullptr;
	}

	if (nullptr != StageMap)
	{
		StageMap->Death();
		StageMap = nullptr;
	}

	if (nullptr != BossChair)
	{
		BossChair->Death();
		BossChair = nullptr;
	}

	if (nullptr != Boss)
	{
		Boss->Death();
		Boss = nullptr;
	}

	ContentsSpriteManager::SingleSpriteRelease("LastStageBackGround.png");
	ContentsSpriteManager::SingleSpriteRelease("LastStageMap.png");
	ContentsSpriteManager::SingleSpriteRelease("LastStagePixelMap.png");
	ContentsSpriteManager::SingleSpriteRelease("LastStageChair.png");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\LastBossStage\\Devil");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\LastBossStage\\SpiderHead");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\LastBossStage\\FireBall");
}

void LastBossStage::CreateSummonDevil()
{
	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find("LastStagePixelMap.png");
	float4 MapScale = MapTexture->GetScale();
	float4 WinScale = GameEngineCore::MainWindow.GetScale();

	std::shared_ptr<SummonDevil> NewDevil = CreateActor<SummonDevil>(EUPDATEORDER::Monster);

	if (nullptr == NewDevil)
	{
		MsgBoxAssert("작은 악마 소환에 실패했습니다.");
		return;
	}

	if (EACTORDIR::Left == SummonDir)
	{
		NewDevil->Transform.SetLocalPosition({ MapScale.Half().X - 180.0f, -WinScale.Y + 150.0f });
		SummonDir = EACTORDIR::Right;
	}
	else
	{
		NewDevil->SetStartDirRight();
		NewDevil->Transform.SetLocalPosition({ MapScale.Half().X + 180.0f, -WinScale.Y + 150.0f });
		SummonDir = EACTORDIR::Left;
	}
}