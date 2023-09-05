#include "PreCompile.h"
#include "ContentsCore.h"

#include "LogoLevel.h"
#include "TitleLevel.h"
#include "StoryLevel.h"
#include "MiniMapLevel.h"
#include "FirstBossStage.h"

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
	GameEngineCore::CreateLevel<StoryLevel>("StoryLevel");
	GameEngineCore::CreateLevel<MiniMapLevel>("MiniMapLevel");
	GameEngineCore::CreateLevel<FirstBossStage>("FirstBossStage");
	GameEngineCore::ChangeLevel("FirstBossStage");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}