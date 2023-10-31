﻿#include "PreCompile.h"
#include "TestStage.h"

#include "BaseCharacter.h"
#include "ParryObject.h"
//#include "Spider_Head.h"
//#include "SummonDevil.h"
//#include "Ram_Arm.h"
//#include "Serpent_Head.h"
#include "Devil.h"
#include "TestActor.h"
#include "Map.h"

TestStage::TestStage()
{
}

TestStage::~TestStage()
{
}

void TestStage::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineInput::AddInputObject(this);

	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, 0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	/*ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Global\\Character\\CupHead");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Global\\Character\\Bullet");
	ContentsSpriteManager::CreateSingleSpriteDir("Resources\\Texture\\Tutorial");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Tutorial\\Parry");*/

	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStagePixelMap.png");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\Devil");
	// ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\SummonDevil");

	/*Player = CreateActor<BaseCharacter>(EUPDATEORDER::Player);
	Player->Transform.SetLocalPosition(PLAYERSTARTPOS);

	TestParry = CreateActor<ParryObject>(EUPDATEORDER::Bullet);
	TestParry->Transform.SetLocalPosition({ 640.0f, -360.0f });

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("TutorialMap.Png");
	float4 SpriteHalfScale = Sprite->GetSpriteData(0).GetScale().Half();*/

	TestMap = CreateActor<Map>(EUPDATEORDER::Map);
	TestMap->MapInit("LastStagePixelMap.Png");
	TestMap->PixelMapInit("LastStagePixelMap.Png");
	TestMap->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });

	/*std::shared_ptr<Ram_Arm_Right> RightCheck = CreateActor<Ram_Arm_Right>(EUPDATEORDER::Monster);
	RightCheck->Transform.SetLocalPosition({ 0.0f, -360.0f });*/

	/*std::shared_ptr<Ram_Arm_Left> LeftCheck = CreateActor<Ram_Arm_Left>(EUPDATEORDER::Monster);
	LeftCheck->Transform.SetLocalPosition({ 1280.0f, -360.0f });*/

	std::shared_ptr<Devil> Check = CreateActor<Devil>(EUPDATEORDER::Monster);
	Check->Transform.SetLocalPosition({ 640.0f, -720.0f });

	/*std::shared_ptr<Ram_Arm> RightCheck = CreateActor<Ram_Arm>(EUPDATEORDER::Monster);
	RightCheck->Transform.SetLocalPosition({ 0.0f, -360.0f });

	std::shared_ptr<Ram_Arm> Check = CreateActor<Ram_Arm>(EUPDATEORDER::Monster);
	Check->ChangeLeftDir();
	Check->Transform.SetLocalPosition({ 1280.0f, -360.0f });*/
}

void TestStage::LevelEnd(GameEngineLevel* _NextLevel)
{
	//ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\LastBossStage\\SummonDevil");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\LastBossStage\\Devil");

	/*if (nullptr != Player)
	{
		Player->Death();
		Player = nullptr;
	}

	if (nullptr != TestParry)
	{
		TestParry->Death();
		TestParry = nullptr;
	}

	if (nullptr != TestMap)
	{
		TestMap->Death();
		TestMap = nullptr;
	}

	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Global\\Character\\CupHead");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Global\\Character\\Bullet");
	ContentsSpriteManager::SingleSpriteInDirRelease("Resources\\Texture\\Tutorial");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Tutorial\\Parry");*/
}

void TestStage::Update(float _Delta)
{
	/*if (true == GameEngineInput::IsDown('R', this))
	{
		std::shared_ptr<Ram_Arm_Right> RightCheck = CreateActor<Ram_Arm_Right>(EUPDATEORDER::Monster);
		RightCheck->Transform.SetLocalPosition({ 0.0f, -360.0f });

		std::shared_ptr<Ram_Arm_Left> LeftCheck = CreateActor<Ram_Arm_Left>(EUPDATEORDER::Monster);
		LeftCheck->Transform.SetLocalPosition({ 1280.0f, -360.0f });
	}*/

	/*if (true == GameEngineInput::IsDown('R', this))
	{
		TestParry->ParryActive();
	}

	if (0.0f > StopTimer)
	{
		StopTimer = 0.3f;
		LevelStopToParry = false;
		BaseCharacter::MainCharacter->ParrySuccessReset();
		GameEngineCore::MainTime.SetAllTimeScale(1.0f);
	}

	if (true == BaseCharacter::MainCharacter->GetParrySuccess())
	{
		LevelStopToParry = true;
		GameEngineCore::MainTime.SetAllTimeScale(0.0f);
	}

	if (true == LevelStopToParry)
	{
		StopTimer -= _Delta;
	}*/
}