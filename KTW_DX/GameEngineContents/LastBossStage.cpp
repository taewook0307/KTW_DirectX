﻿#include "PreCompile.h"
#include "LastBossStage.h"

#include "BackGround.h"
#include "Lava.h"
#include "UpperObject.h"
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

	ContentsResourcesManager::SoundLoadDir("Resources\\Sound\\LastStage\\Devil");
	ContentsResourcesManager::SoundLoadDir("Resources\\Sound\\LastStage\\Devil_Ram");
	ContentsResourcesManager::SoundLoadDir("Resources\\Sound\\LastStage\\Devil_Spider");
	ContentsResourcesManager::SoundLoadDir("Resources\\Sound\\LastStage\\Devil_AttackObject");
	ContentsResourcesManager::SoundLoadDir("Resources\\Sound\\LastStage\\SummonDevil");
	ContentsResourcesManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\BackGround\\LastStageBackGround.png");
	ContentsResourcesManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\BackGround\\devil_bg_ph_1_foreground.png");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\BackGround\\Lava");
	ContentsResourcesManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStageMap.png");
	ContentsResourcesManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStagePixelMap.png");
	ContentsResourcesManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStageChair.png");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\Devil");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\SpiderHead");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\SummonDevil");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\DevilAttackObject");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\DevilAttackObject_Parry");

	BGMPlayer = GameEngineSound::SoundPlay("53 One Hell Of A Time.mp3");

	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find("LastStagePixelMap.png");
	MapScale = MapTexture->GetScale();
	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	float4 WinScaleHalf = WinScale.Half();

	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });

	StageBackGround = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	StageBackGround->BackGroundInitAuto("LastStageBackGround.png");
	StageBackGround->Transform.SetLocalPosition({ MapScale.Half().X, -WinScaleHalf.Y });

	LavaA = CreateActor<Lava>(EUPDATEORDER::BackGround);
	LavaA->Transform.SetLocalPosition({ 265.0f, -255.0f });

	LavaB = CreateActor<Lava>(EUPDATEORDER::BackGround);
	LavaB->ChagneLavaType();
	LavaB->Transform.SetLocalPosition({ 1155.0f, -215.0f });

	StageMap = CreateActor<Map>(EUPDATEORDER::Map);
	StageMap->MapInit("LastStageMap.Png");
	StageMap->PixelMapInit("LastStagePixelMap.Png");
	StageMap->Transform.SetLocalPosition({ MapScale.Half().X, -MapScale.Half().Y });

	StageUpper = CreateActor<UpperObject>(EUPDATEORDER::BackGround);
	StageUpper->UpperObjectInit("devil_bg_ph_1_foreground.png", 0, false);
	StageUpper->Transform.SetLocalPosition({ MapScale.Half().X, -MapScale.Half().Y });

	BossChair = CreateActor<DevilChair>(EUPDATEORDER::Map);
	BossChair->Transform.SetLocalPosition({ MapScale.Half().X, -WinScale.Y + 80.0f });

	Boss = CreateActor<Devil>(EUPDATEORDER::Monster);
	Boss->Transform.SetLocalPosition({ MapScale.Half().X, -WinScale.Y + 10.0f });

	StageLevel::LevelStart(_PrevLevel);

	Player->ChangeDevilStageIntro();

	GameEngineInput::AddInputObject(this);
}

void LastBossStage::Update(float _Delta)
{
	CameraMove(_Delta);
	StageLevel::ParryUpdate(_Delta);

	if (true == GameEngineInput::IsDown(VK_RETURN, this))
	{
		StageLevel::StageClear();
	}

	StageLevel::LastLevelEnd(_Delta);

	if (ESTAGERESULT::None == StageResult)
	{
		if (0.0f > SummonTimer)
		{
			CreateSummonDevil();
			SummonTimer = SUMMONTIMER;
		}

		SummonTimer -= _Delta;
	}
}

void LastBossStage::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();

	StageLevel::LevelEnd(_NextLevel);

	Boss->AllSummonDeath();
	AllRemainActorDeath<SummonDevil>(EUPDATEORDER::Monster);

	if (nullptr != StageBackGround)
	{
		StageBackGround->Death();
		StageBackGround = nullptr;
	}

	if (nullptr != LavaA)
	{
		LavaA->Death();
		LavaA = nullptr;
	}

	if (nullptr != LavaB)
	{
		LavaB->Death();
		LavaB = nullptr;
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

	ContentsResourcesManager::SingleSpriteRelease("LastStageBackGround.png");
	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\LastBossStage\\BackGround\\Lava");
	ContentsResourcesManager::SingleSpriteRelease("LastStageMap.png");
	ContentsResourcesManager::SingleSpriteRelease("LastStagePixelMap.png");
	ContentsResourcesManager::SingleSpriteRelease("LastStageChair.png");
	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\LastBossStage\\Devil");
	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\LastBossStage\\SpiderHead");
	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\LastBossStage\\DevilAttackObject");
	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\LastBossStage\\DevilAttackObject_Parry");
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