#include "PreCompile.h"
#include "Card.h"

Card::Card()
{
}

Card::~Card()
{
}

void Card::Start()
{
	CardRenderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::UI);
	CardRenderer->CreateAnimation("Card", "Card");
	CardRenderer->AutoSpriteSizeOn();
	CardRenderer->SetPivotType(PivotType::Bottom);
	CardRenderer->ChangeAnimation("Card");

	GameEngineInput::AddInputObject(this);
}

void Card::Update(float _Delta)
{
	
}