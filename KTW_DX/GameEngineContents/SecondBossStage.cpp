#include "PreCompile.h"
#include "SecondBossStage.h"

#include "PirateBoss.h"

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
		Dir.MoveChild("Resources\\Texture\\SecondBossStage\\SecondBoss\\Pirate");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	PirateBossActor = CreateActor<PirateBoss>(EUPDATEORDER::Monster);
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