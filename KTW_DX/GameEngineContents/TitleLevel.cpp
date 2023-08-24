﻿#include "PreCompile.h"
#include "ContentsCore.h"
#include "TitleLevel.h"
#include "Player.h"


TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Start()
{
	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	std::shared_ptr<Player> NewPlayer = CreateActor<Player>();

	// GetMainCamera()->SetParent(NewPlayer);
	// CreateActor<GameEngineRenderer>();
}

void TitleLevel::Update(float _Delta)
{
	int a = 0;
}