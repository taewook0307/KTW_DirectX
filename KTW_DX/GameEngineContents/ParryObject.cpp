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
	ParryRenderer->CreateAnimation("ParryActive", "TutorialParryOn");
	ParryRenderer->CreateAnimation("ParryInactive", "TutorialParryOff");

	ParryRenderer->ChangeAnimation("ParryActive");
	ParryRenderer->AutoSpriteSizeOn();

	ParryCollision = CreateComponent<GameEngineCollision>(CollisionOrder::ParryObject);
	
	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("TutorialParryOff");
	float4 SpriteScale = Sprite->GetSpriteData(0).GetScale();

	ParryCollision->Transform.SetLocalScale(SpriteScale);
}

void ParryObject::Update(float _Delta)
{
	if (true == ParryActivation)
	{
		ParryRenderer->ChangeAnimation("ParryActive");
	}
	else
	{
		ParryRenderer->ChangeAnimation("ParryInactive");
	}
}