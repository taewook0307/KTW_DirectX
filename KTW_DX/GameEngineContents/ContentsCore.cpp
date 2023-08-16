﻿#include "PreCompile.h"
#include "ContentsCore.h"
#include "TitleLevel.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::ChangeLevel("TitleLevel");

	// 자기 텍스처 로드해야 한다.

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}