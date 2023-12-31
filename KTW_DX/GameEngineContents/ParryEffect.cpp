﻿#include "PreCompile.h"
#include "ParryEffect.h"

ParryEffect::ParryEffect()
{
}

ParryEffect::~ParryEffect()
{
}

void ParryEffect::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PlayEffect);
	Renderer->CreateAnimation("ParryEffect", "Parry_Effect", PARRYEFFECTANIMATIONINTER);
	Renderer->SetEndEvent("ParryEffect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(0.8f);

	Renderer->ChangeAnimation("ParryEffect");
}