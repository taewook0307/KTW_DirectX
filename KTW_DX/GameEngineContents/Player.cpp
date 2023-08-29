#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

Player::Player()
{

}

Player::~Player()
{
}

void Player::Start()
{
	{

		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>();
		MainSpriteRenderer->SetSprite("cuphead_idle_0001.png");
	}

	/*{
		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer->SetSprite("NSet.png");
		Renderer->Transform.SetLocalPosition({ 0, -150, 0 });
		Renderer->Transform.SetLocalScale({ 50, 50, 100 });
	}

	{
		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer->SetSprite("NSet.png");
		Renderer->Transform.SetLocalPosition({ -150, 0, 0 });
		Renderer->Transform.SetLocalScale({ 50, 50, 100 });
	}

	{
		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer->SetSprite("NSet.png");
		Renderer->Transform.SetLocalPosition({ 150, 0, 0 });
		Renderer->Transform.SetLocalScale({ 50, 50, 100 });
	}*/
}

void Player::Update(float _Delta)
{
	float Speed = 100.0f;

	if (GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('W'))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('S'))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('Q'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}

	if (GameEngineInput::IsPress('E'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}
}