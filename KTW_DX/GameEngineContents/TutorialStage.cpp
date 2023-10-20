#include "PreCompile.h"
#include "TutorialStage.h"

#include "BackGround.h"
#include "Map.h"
#include "UpperObject.h"
#include "BaseCharacter.h"
#include "TutorialTarget.h"
#include "MiniMapEnter.h"
#include "ParryObject.h"

TutorialStage::TutorialStage()
{
	GameEngineInput::AddInputObject(this);
}

TutorialStage::~TutorialStage()
{
}

void TutorialStage::LevelStart(GameEngineLevel* _PrevLevel)
{
	TutorialParry.resize(3);

	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, 0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	// 리소스 Load
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Global\\Character");
	ContentsSpriteManager::CreateSingleSpriteDir("Resources\\Texture\\Tutorial");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Tutorial\\Parry");
	ContentsSpriteManager::CreateFolderSpriteDir("Resources\\Texture\\Tutorial\\Target");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Tutorial\\TargetExplosion");

	Player = CreateActor<BaseCharacter>(EUPDATEORDER::Player);
	Player->Transform.SetLocalPosition(PLAYERSTARTPOS);

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("TutorialMap.Png");
	float4 SpriteHalfScale = Sprite->GetSpriteData(0).GetScale().Half();

	TutorialBackGround = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	TutorialBackGround->BackGroundInit("Tutorial_BackGround.png");
	TutorialBackGround->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });

	TutorialBackGroundUpper = CreateActor<UpperObject>(EUPDATEORDER::BackGround);
	TutorialBackGroundUpper->UpperObjectInit("Tutorial_BackGround_Upper.png");
	TutorialBackGroundUpper->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });

	TutorialMap = CreateActor<Map>(EUPDATEORDER::Map);
	TutorialMap->MapInit("TutorialMap.Png");
	TutorialMap->PixelMapInit("TutorialBitMap.Png");
	TutorialMap->Transform.SetLocalPosition({ SpriteHalfScale.X, -SpriteHalfScale.Y });

	Target = CreateActor<TutorialTarget>(EUPDATEORDER::Map);
	Target->Transform.SetLocalPosition(TARGETPOS);

	{
		std::shared_ptr<ParryObject> Parry = CreateActor<ParryObject>(EUPDATEORDER::Map);
		Parry->Transform.SetLocalPosition(PARRYPOS1);
		Parry->ParryActive();

		TutorialParry[0] = Parry;
	}

	{
		std::shared_ptr<ParryObject> Parry = CreateActor<ParryObject>(EUPDATEORDER::Map);
		Parry->Transform.SetLocalPosition(PARRYPOS2);
		Parry->ParryInactive();

		TutorialParry[1] = Parry;
	}

	{
		std::shared_ptr<ParryObject> Parry = CreateActor<ParryObject>(EUPDATEORDER::Map);
		Parry->Transform.SetLocalPosition(PARRYPOS3);
		Parry->ParryInactive();

		TutorialParry[2] = Parry;
	}
	
	TutorialExit = CreateActor<MiniMapEnter>(EUPDATEORDER::Map);
	TutorialExit->EnterSpriteInit("Tutorial_Exit.png");
	TutorialExit->SetEnterLevel("MiniMapLevel");
	TutorialExit->Transform.SetLocalPosition(EXITPOS);
}

void TutorialStage::Update(float _Delta)
{
	StageLevel::ParryUpdate(_Delta);

	TutorialLevelCameraMove();

	if (true == GameEngineInput::IsDown(VK_ESCAPE, this))
	{
		GameEngineCore::ChangeLevel("MiniMapLevel");
	}

	TutorialParryObjectActive();
}

void TutorialStage::LevelEnd(GameEngineLevel* _NextLevel)
{
	StageLevel::LevelEnd(_NextLevel);

	if (nullptr != TutorialBackGround)
	{
		TutorialBackGround->Death();
		TutorialBackGround = nullptr;
	}

	if (nullptr != TutorialBackGroundUpper)
	{
		TutorialBackGroundUpper->Death();
		TutorialBackGroundUpper = nullptr;
	}

	if (nullptr != TutorialMap)
	{
		TutorialMap->Death();
		TutorialMap = nullptr;
	}

	if (nullptr != Target)
	{
		Target->Death();
		Target = nullptr;
	}

	if (nullptr != TutorialExit)
	{
		TutorialExit->Death();
		TutorialExit = nullptr;
	}

	for (size_t i = 0; i < TutorialParry.size(); i++)
	{
		if (nullptr != TutorialParry[i])
		{
			TutorialParry[i]->Death();
			TutorialParry[i] = nullptr;
		}
	}

	TutorialParry.clear();
}




void TutorialStage::TutorialParryObjectActive()
{
	size_t VectorSize = TutorialParry.size();

	for (size_t i = 0; i < VectorSize; i++)
	{
		std::shared_ptr<ParryObject> CurParry = TutorialParry[i];

		size_t NextIndex = i + 1;

		if (VectorSize <= NextIndex)
		{
			NextIndex = 0;
		}

		std::shared_ptr<ParryObject> NextParry = TutorialParry[NextIndex];

		if (false == CurParry->GetParryActivation() && true == CurParry->GetParry())
		{
			CurParry->ParryReset();
			NextParry->ParryActive();
		}
	}
}

void TutorialStage::TutorialLevelCameraMove()
{
	float4 PlayerPos = Player->Transform.GetWorldPosition();
	float4 WinScale = GameEngineCore::MainWindow.GetScale();

	if (PlayerPos.X < WinScale.Half().X)
	{
		return;
	}

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("TutorialMap.Png");
	float4 SpriteScale = Sprite->GetSpriteData(0).GetScale();

	if (PlayerPos.X > SpriteScale.X - WinScale.Half().X)
	{
		return;
	}

	float4 MovePos = { PlayerPos.X, -WinScale.Half().Y, -500 };

	GetMainCamera()->Transform.SetLocalPosition(MovePos);
	TutorialBackGround->Transform.SetLocalPosition(MovePos);
	TutorialBackGroundUpper->Transform.SetLocalPosition(MovePos);
}
