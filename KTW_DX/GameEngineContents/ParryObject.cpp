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
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Play);
	Renderer->CreateAnimation("ParryActive", "TutorialParryOn");
	Renderer->CreateAnimation("ParryInactive", "TutorialParryOff");

	Renderer->ChangeAnimation("ParryActive");
	Renderer->AutoSpriteSizeOn();

	ParryCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::ParryObject);
	
	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("TutorialParryOff");
	float4 SpriteScale = Sprite->GetSpriteData(0).GetScale();

	ParryCollision->Transform.SetLocalScale(SpriteScale);
}

void ParryObject::Update(float _Delta)
{
	if (true == ParryActivation)
	{
		Renderer->ChangeAnimation("ParryActive");
	}
	else
	{
		Renderer->ChangeAnimation("ParryInactive");
	}
}