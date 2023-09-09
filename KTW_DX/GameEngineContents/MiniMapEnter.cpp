﻿#include "PreCompile.h"
#include "MiniMapEnter.h"

MiniMapEnter::MiniMapEnter()
{
}

MiniMapEnter::~MiniMapEnter()
{
}

void MiniMapEnter::Start()
{
	EnterRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Map);
	EnterCollision = CreateComponent<GameEngineCollision>(CollisionOrder::FieldEnter);
}

void MiniMapEnter::Update(float _Delta)
{
	if (true == EnterCollision->Collision(CollisionOrder::Player))
	{
		EnterRenderer->AnimationPauseOff();

		if (true == GameEngineInput::IsDown('Z') || true == GameEngineInput::IsDown(VK_RETURN))
		{
			GameEngineCore::ChangeLevel(EnterLevel);
		}
	}
	else
	{
		EnterRenderer->AnimationPauseOn();
	}

}

void MiniMapEnter::EnterAnimationInit(std::string_view _AnimationName, std::string_view _SpriteName)
{
	EnterRenderer->CreateAnimation(_AnimationName, _SpriteName);
	EnterRenderer->ChangeAnimation(_AnimationName);
	EnterRenderer->AutoSpriteSizeOn();
	EnterRenderer->SetPivotType(PivotType::Bottom);

	std::shared_ptr<GameEngineSprite> CurSprite = GameEngineSprite::Find(_SpriteName);
	float4 SpriteScale = CurSprite->GetSpriteData(0).GetScale();

	EnterCollision->Transform.SetLocalScale(SpriteScale);

	EnterRenderer->AnimationPauseOn();
}