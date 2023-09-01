#include "PreCompile.h"
#include "ContentsCore.h"

#include "LogoLevel.h"
#include "TitleLevel.h"
#include "StoryLevel.h"
#include "MiniMapLevel.h"
#include "PlayLevel.h"

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
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::ChangeLevel("LogoLevel");

	// 자기 텍스처 로드해야 한다.
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}