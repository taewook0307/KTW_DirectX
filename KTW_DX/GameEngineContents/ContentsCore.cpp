#include "PreCompile.h"
#include "ContentsCore.h"

#include "LogoLevel.h"
#include "TitleLevel.h"
#include "MenuLevel.h"
#include "StoryLevel.h"
#include "MiniMapLevel.h"
#include "TutorialStage.h"
#include "FirstBossStage.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GameEngineSpriteRenderer::SetDefaultSampler("POINT");

	GameEngineCore::CreateLevel<LogoLevel>("LogoLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<MenuLevel>("MenuLevel");
	GameEngineCore::CreateLevel<StoryLevel>("StoryLevel");
	GameEngineCore::CreateLevel<MiniMapLevel>("MiniMapLevel");
	GameEngineCore::CreateLevel<TutorialStage>("TutorialStage");
	GameEngineCore::CreateLevel<FirstBossStage>("FirstBossStage");
	GameEngineCore::ChangeLevel("StoryLevel");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}