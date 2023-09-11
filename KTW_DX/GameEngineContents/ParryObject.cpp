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