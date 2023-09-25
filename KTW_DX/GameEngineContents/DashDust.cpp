﻿#include "PreCompile.h"
#include "DashDust.h"

DashDust::DashDust()
{
}

DashDust::~DashDust()
{
}

void DashDust::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PlayEffect);
	Renderer->CreateAnimation("DashDust", "Dash_Dust", DASHEFFECTANIMATIONINTER);
	Renderer->SetEndEvent("DashDust",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(0.8f);
	Renderer->SetPivotValue(float4{ 0.0f, 0.5f });

	Renderer->ChangeAnimation("DashDust");
}

void DashDust::Update(float _Delta)
{
	if (EACTORDIR::Left == DashDustDir)
	{
		Transform.SetLocalScale({ -1.0f, 1.0f });
	}
	else
	{
		Transform.SetLocalScale({ 1.0f, 1.0f });
	}
}