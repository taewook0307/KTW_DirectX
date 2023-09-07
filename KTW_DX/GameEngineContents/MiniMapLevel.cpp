#include "PreCompile.h"
#include "MiniMapLevel.h"

#include "Map.h"
#include "MiniMapEnter.h"
#include "MiniMapCharacter.h"

MiniMapLevel::MiniMapLevel()
{
}

MiniMapLevel::~MiniMapLevel()
{
}

void MiniMapLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, -500 });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\Map");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		size_t FileSize = Files.size();

		for (size_t i = 0; i < FileSize; i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
		GameEngineSprite::CreateSingle("CupHead_MiniMap.png");
		GameEngineSprite::CreateSingle("CupHead_MiniMap_BitMap.png");
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\MiniMapEnter");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}


	// 미니맵 생성
	MiniMap = CreateActor<Map>(UpdateOrder::Map);
	MiniMap->MapInit("CupHead_MiniMap.png");
	MiniMap->BitMapInit("CupHead_MiniMap_BitMap.png");


	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find("CupHead_MiniMap.png");

	float4 MapTextureHalfScale = MapTexture->GetScale().Half();

	MiniMap->Transform.SetLocalPosition({ MapTextureHalfScale.X, -MapTextureHalfScale.Y });

	// 플레이 입구 생성
	TutorialEnter = CreateActor<MiniMapEnter>(UpdateOrder::Map);
	TutorialEnter->EnterAnimationInit("Tutorial_Enter_Ani", "TutorialEnter");
	TutorialEnter->Transform.SetLocalPosition(TUTORIALENTERPOS);

	FirstEnter = CreateActor<MiniMapEnter>(UpdateOrder::Map);
	FirstEnter->EnterAnimationInit("FirstBossMap_Enter_Ani", "FirstBossMapEnter");
	FirstEnter->Transform.SetLocalPosition(FIRSTBOSSENTERPOS);

	// 캐릭터 생성
	Character = CreateActor<MiniMapCharacter>(UpdateOrder::Player);
	Character->Transform.SetLocalPosition(CHARACTERSTARTPOS);
}

void MiniMapLevel::Update(float _Delta)
{
	float4 Check = Character->Transform.GetWorldPosition();

	GetMainCamera()->Transform.SetLocalPosition(Character->Transform.GetWorldPosition());

	if (true == GameEngineInput::IsDown(VK_RETURN))
	{
		GameEngineCore::ChangeLevel("FirstBossStage");
	}
}