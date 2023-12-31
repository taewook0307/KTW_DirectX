﻿#include "PreCompile.h"
#include "UpperObject.h"

#include "Map.h"

UpperObject::UpperObject()
{
}

UpperObject::~UpperObject()
{
}

void UpperObject::Start()
{
	UpperObjectRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperPlayer);
}

void UpperObject::Update(float _Delta)
{
	if (true == Map::MainMap->GetPixelMapRenderSwitch())
	{
		UpperObjectRenderer->Off();
	}
	else
	{
		UpperObjectRenderer->On();
	}
}

void UpperObject::UpperObjectInit(std::string_view _FileName, int _Order /*= 0*/, bool _WinSizeOn /*= true*/)
{
	UpperObjectRenderer->SetSprite(_FileName, _Order);

	if (true == _WinSizeOn)
	{
		float4 WinScale = GameEngineCore::MainWindow.GetScale();

		UpperObjectRenderer->SetImageScale(WinScale);
	}
	else
	{
		UpperObjectRenderer->AutoSpriteSizeOn();
	}
}