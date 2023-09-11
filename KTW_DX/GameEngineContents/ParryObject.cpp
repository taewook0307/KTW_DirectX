#include "PreCompile.h"
#include "ParryObject.h"

ParryObject::ParryObject()
{
}

ParryObject::~ParryObject()
{
}

void ParryObject::Start()
{
	ParryRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Play);
	ParryRenderer->CreateAnimation("ParryOn", "TutorialParryOn");
	ParryRenderer->CreateAnimation("ParryOff", "TutorialParryOff");

	ParryRenderer->ChangeAnimation("ParryOn");
	ParryRenderer->AutoSpriteSizeOn();

	ParryCollision = CreateComponent<GameEngineCollision>(CollisionOrder::ParryObject);
	
	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("TutorialParryOff");
	float4 SpriteScale = Sprite->GetSpriteData(0).GetScale();

	ParryCollision->Transform.SetLocalScale(SpriteScale);
}

void ParryObject::Update(float _Delta)
{
	if (true == Parry)
	{
		ParryRenderer->ChangeAnimation("ParryOn");
	}
	else
	{
		ParryRenderer->ChangeAnimation("ParryOff");
	}
}