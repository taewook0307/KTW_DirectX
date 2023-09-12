#include "PreCompile.h"
#include "TutorialStage.h"

#include "BackGround.h"
#include "Map.h"
#include "UpperObject.h"
#include "BaseCharacter.h"
#include "MiniMapEnter.h"
#include "ParryObject.h"

TutorialStage::TutorialStage()
{
}

TutorialStage::~TutorialStage()
{
}

void TutorialStage::LevelStart(GameEngineLevel* _PrevLevel)
{
	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, -500 });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\Character\\Normal");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\Map\\Tutorial");
		std::vector<GameEngineFile> AllFiles = Dir.GetAllFile();

		size_t FileCount = AllFiles.size();

		for (size_t i = 0; i < FileCount; i++)
		{
			GameEngineFile File = AllFiles[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("TutorialMap.Png");
		GameEngineSprite::CreateSingle("TutorialBitMap.Png");
		GameEngineSprite::CreateSingle("Tutorial_BackGround.Png");
		GameEngineSprite::CreateSingle("Tutorial_BackGround_Upper.Png");
		GameEngineSprite::CreateSingle("Tutorial_Exit.Png");
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\Bullet");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\Parry");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	Player = CreateActor<BaseCharacter>(UpdateOrder::Player);
	Player->Transform.SetLocalPosition(PLAYERSTARTPOS);

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("TutorialMap.Png");
	float4 SpriteHalfScale = Sprite->GetSpriteData(0).GetScale().Half();

	TutorialBackGround = CreateActor<BackGround>(UpdateOrder::BackGround);
	TutorialBackGround->BackGroundInit("Tutorial_BackGround.png");
	TutorialBackGround->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });

	TutorialBackGroundUpper = CreateActor<UpperObject>(UpdateOrder::BackGround);
	TutorialBackGroundUpper->UpperObjectInit("Tutorial_BackGround_Upper.png");
	TutorialBackGroundUpper->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });

	TutorialMap = CreateActor<Map>(UpdateOrder::Map);
	TutorialMap->MapInit("TutorialMap.Png");
	TutorialMap->PixelMapInit("TutorialBitMap.Png");
	TutorialMap->Transform.SetLocalPosition({ SpriteHalfScale.X, -SpriteHalfScale.Y });

	TutorialParry1 = CreateActor<ParryObject>(UpdateOrder::Map);
	TutorialParry1->Transform.SetLocalPosition(PARRYPOS1);
	TutorialParry1->ParryOn();

	TutorialParry2 = CreateActor<ParryObject>(UpdateOrder::Map);
	TutorialParry2->Transform.SetLocalPosition(PARRYPOS2);
	TutorialParry2->ParryOff();

	TutorialParry3 = CreateActor<ParryObject>(UpdateOrder::Map);
	TutorialParry3->Transform.SetLocalPosition(PARRYPOS3);
	TutorialParry3->ParryOff();

	TutorialExit = CreateActor<MiniMapEnter>(UpdateOrder::Map);
	TutorialExit->EnterSpriteInit("Tutorial_Exit.png");
	TutorialExit->SetEnterLevel("MiniMapLevel");
	TutorialExit->Transform.SetLocalPosition(EXITPOS);
}

void TutorialStage::Update(float _Delta)
{
	float4 Check = Player->Transform.GetWorldPosition();

	TutorialLevelCameraMove();

	if (true == GameEngineInput::IsDown(VK_ESCAPE))
	{
		GameEngineCore::ChangeLevel("MiniMapLevel");
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