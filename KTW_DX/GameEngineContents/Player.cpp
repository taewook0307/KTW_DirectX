#include "PreCompile.h"
#include "Player.h"

#include <GameEngineCore/GameEngineTexture.h>

Player::Player()
{

}

Player::~Player()
{
}

void Player::Start()
{
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(RenderOrder::Play));
	MainSpriteRenderer->CreateAnimation("CupHead_Idle", "Idle");
	MainSpriteRenderer->ChangeAnimation("CupHead_Idle");
	MainSpriteRenderer->AutoSpriteSizeOn();
}

void Player::Update(float _Delta)
{
	float Speed = 300.0f;

	if (GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}
}