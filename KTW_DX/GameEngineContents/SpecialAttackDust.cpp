#include "PreCompile.h"
#include "SpecialAttackDust.h"

SpecialAttackDust::SpecialAttackDust()
{
}

SpecialAttackDust::~SpecialAttackDust()
{
}

void SpecialAttackDust::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PlayEffect);
	Renderer->CreateAnimation("SpecialAttackDust", "Special_Dust", SPECIALATTACKEFFECTANIMATIONINTER);
	Renderer->SetEndEvent("SpecialAttackDust",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(0.8f);
	Renderer->SetPivotValue({ 0.2f, 0.5f });

	Renderer->ChangeAnimation("SpecialAttackDust");
}

void SpecialAttackDust::Update(float _Delta)
{
	if (EDIRECTION8::Left == SpecialAttackDustDirection)
	{
		Renderer->LeftFlip();
	}

	else if (EDIRECTION8::Right == SpecialAttackDustDirection)
	{
		Renderer->RightFlip();
	}

	else if (EDIRECTION8::Up == SpecialAttackDustDirection)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, 90.0f });
	}

	else if (EDIRECTION8::Down == SpecialAttackDustDirection)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, -90.0f });
	}

	else if (EDIRECTION8::LeftUp == SpecialAttackDustDirection)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, 135.0f });
	}

	else if (EDIRECTION8::LeftDown == SpecialAttackDustDirection)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, -135.0f });
	}

	else if (EDIRECTION8::RightUp == SpecialAttackDustDirection)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, 45.0f });
	}

	else if (EDIRECTION8::RightDown == SpecialAttackDustDirection)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, -45.0f });
	}
}