#include "PreCompile.h"
#include "ContentsCore.h"

#include "LogoLevel.h"
#include "TitleLevel.h"
#include "MenuLevel.h"
#include "IntroLevel.h"
#include "MiniMapLevel.h"
#include "TutorialStage.h"
#include "FirstBossStage.h"
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
	GameEngineCore::CreateLevel<OutroLevel>("OutroLevel");
	GameEngineCore::ChangeLevel("FirstBossStage");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}