#include "PreCompile.h"
#include "FirstMapParryObject.h"

FirstMapParryObject::FirstMapParryObject()
{
}

FirstMapParryObject::~FirstMapParryObject()
{
}

void FirstMapParryObject::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Play);
	Renderer->CreateAnimation("FirstBossParryActive", "FirstBossParryObject", 0.1f, -1, -1, false);

	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::Bottom);

	ParryCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::ParryObject);
	ParryCollision->SetCollisionType(ColType::AABBBOX2D);

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("FirstBossParryObject");
	float4 SpriteScale = Sprite->GetSpriteData(3).GetScale();

	ParryCollision->Transform.SetLocalScale(SpriteScale);
	ParryCollision->Transform.SetLocalPosition({ 0.0f, SpriteScale.Half().Y });
}

void FirstMapParryObject::Update(float _Delta)
{
	if (true == ParryActivation)
	{
		Renderer->ChangeAnimation("FirstBossParryActive");
	}
	else
	{
		if (nullptr != Renderer)
		{
			Renderer->Death();
			Renderer = nullptr;
		}
		Death();
	}
}