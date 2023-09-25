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

	float4 WinHalfScale = GameEngineCore::MainWindow.GetScale().Half();

	PirateBossActor = CreateActor<PirateBoss>(EUPDATEORDER::Monster);
	PirateBossActor->Transform.SetLocalPosition({ 500.0f, 0.0f});
	ShipBossActor = CreateActor<ShipBoss>(EUPDATEORDER::Monster);
	ShipBossActor->Transform.SetLocalPosition({ WinHalfScale.X + 20.0f, -WinHalfScale.Y });
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