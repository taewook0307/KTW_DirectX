#include "PreCompile.h"
#include "SecondBossStage.h"

#include "PirateBoss.h"
#include "ShipBoss.h"

SecondBossStage::SecondBossStage()
{
}

SecondBossStage::~SecondBossStage()
{
}

void SecondBossStage::LevelStart(GameEngineLevel* _PrevLevel)
{
	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, -500 });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\SecondBossStage\\SecondBoss");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	float4 WinScale = GameEngineCore::MainWindow.GetScale();

	PirateBossActor = CreateActor<PirateBoss>(EUPDATEORDER::Monster);
	PirateBossActor->Transform.SetLocalPosition({ 1100.0f, -WinScaleHalf.Y});

	ShipBossActor = CreateActor<ShipBoss>(EUPDATEORDER::Monster);
	ShipBossActor->Transform.SetLocalPosition({ WinScale.X, -WinScale.Y });
}

void SecondBossStage::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_ESCAPE))
	{
		GameEngineCore::ChangeLevel("MiniMapLevel");
	}
}

void SecondBossStage::LevelEnd(GameEngineLevel* _NextLevel)
{

}