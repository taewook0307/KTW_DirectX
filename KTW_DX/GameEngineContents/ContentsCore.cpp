#include "PreCompile.h"
#include "ContentsCore.h"

#include "LogoLevel.h"
#include "TitleLevel.h"
#include "MenuLevel.h"
#include "IntroLevel.h"
#include "MiniMapLevel.h"
#include "TutorialStage.h"
#include "FirstBossStage.h"
#include "SecondBossStage.h"
#include "OutroLevel.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GameEngineCore::CreateLevel<LogoLevel>("LogoLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<MenuLevel>("MenuLevel");
	GameEngineCore::CreateLevel<IntroLevel>("IntroLevel");
	GameEngineCore::CreateLevel<MiniMapLevel>("MiniMapLevel");
	GameEngineCore::CreateLevel<TutorialStage>("TutorialStage");
	GameEngineCore::CreateLevel<FirstBossStage>("FirstBossStage");
	GameEngineCore::CreateLevel<SecondBossStage>("SecondBossStage");
	GameEngineCore::CreateLevel<OutroLevel>("OutroLevel");
	GameEngineCore::ChangeLevel("FirstBossStage");

	GameEngineLevel::OffDebug();
}

void ContentsCore::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('K'))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}

	if (true == GameEngineInput::IsDown(VK_F1))
	{
		GameEngineCore::ChangeLevel("MiniMapLevel");
	}
	if (true == GameEngineInput::IsDown(VK_F2))
	{
		GameEngineCore::ChangeLevel("TutorialStage");
	}
	if (true == GameEngineInput::IsDown(VK_F3))
	{
		GameEngineCore::ChangeLevel("FirstBossStage");
	}
	if (true == GameEngineInput::IsDown(VK_F4))
	{
		GameEngineCore::ChangeLevel("SecondBossStage");
	}
}

void ContentsCore::Release()
{

}