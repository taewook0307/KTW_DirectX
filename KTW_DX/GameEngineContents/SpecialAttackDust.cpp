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
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PlayEffect);
	Renderer->CreateAnimation("SpecialAttackDust", "Special_Dust", 0.05f);
	Renderer->SetEndEvent("SpecialAttackDust",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	Renderer->SetAutoScaleRatio(0.8f);
	Renderer->AutoSpriteSizeOn();

	Renderer->ChangeAnimation("SpecialAttackDust");
}

void SpecialAttackDust::Update(float _Delta)
{
	if (Direction8::Left == SpecialAttackDustDirection)
	{
		Transform.SetLocalScale({ -1.0f, 1.0f });
	}

	else if (Direction8::Right == SpecialAttackDustDirection)
	{
		Transform.SetLocalScale({ 1.0f, 1.0f });
	}

	else if (Direction8::Up == SpecialAttackDustDirection)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, 90.0f });
	}

	else if (Direction8::Down == SpecialAttackDustDirection)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, -90.0f });
	}

	else if (Direction8::LeftUp == SpecialAttackDustDirection)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, 135.0f });
	}

	else if (Direction8::LeftDown == SpecialAttackDustDirection)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, -135.0f });
	}

	else if (Direction8::RightUp == SpecialAttackDustDirection)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, 45.0f });
	}

	else if (Direction8::RightDown == SpecialAttackDustDirection)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, -45.0f });
	}
}