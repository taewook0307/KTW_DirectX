#include "PreCompile.h"
#include "Card.h"

#include "BaseCharacter.h"

Card::Card()
{
}

Card::~Card()
{
}

void Card::Start()
{
	CardRenderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::UI);
	CardRenderer->CreateAnimation("Card_Spawn", "Card", 0.1f, 0, 0, false);
	CardRenderer->CreateAnimation("Card_Turn", "Card", 0.1f, -1, -1, false);
	CardRenderer->SetEndEvent("Card_Turn",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			if (true == CardRenderer->IsCurAnimationEnd())
			{
				CardRenderer->ChangeAnimation("Card_Idle");
			}
		}
	);
	CardRenderer->CreateAnimation("Card_Idle", "Card", 0.1f, 5, 5, true);
	CardRenderer->CreateAnimation("Card_Loop", "Card", 0.1f, -1, -1, true);
	CardRenderer->SetPivotType(PivotType::Bottom);
	CardRenderer->ChangeAnimation("Card_Spawn");

	std::shared_ptr<GameEngineTexture> CardTexture = GameEngineTexture::Find("hud_ch_card_flip_0001.png");
	TextureScale = CardTexture.get()->GetScale();

	CardRenderer->SetImageScale({ TextureScale.X, 0.0f, 1.0f, 1.0f });
	CardRenderer->RenderBaseInfoValue.VertexUVMul.Y = 0.0f;

	GameEngineInput::AddInputObject(this);
}

void Card::Update(float _Delta)
{
	CardCharge();
}

void Card::CardCharge()
{
	unsigned int CharacterHitSuccess = BaseCharacter::MainCharacter->GetHitSuccess();

	if (InitialValue > CharacterHitSuccess)
	{
		CardRenderer->ChangeAnimation("Card_Spawn");
		CardRenderer->SetImageScale({ TextureScale.X, 0.0f, 1.0f, 1.0f });
		CardRenderer->RenderBaseInfoValue.VertexUVMul.Y = 0.0f;
	}

	if (CurHitSuccess < CharacterHitSuccess)
	{
		CurHitSuccess = CharacterHitSuccess;
	}

	if (true == CardRenderer->IsCurAnimation("Card_Loop"))
	{
		return;
	}

	if (PrevHitSuccess == CurHitSuccess)
	{
		return;
	}

	unsigned int LoopCount = CurHitSuccess - PrevHitSuccess;

	for (unsigned int i = 0; i < LoopCount; i++)
	{
		float4 Scale = CardRenderer->GetImageTransform().GetLocalScale();

		float ScaleYValue = fabs(Scale.Y);

		if (ScaleYValue < TextureScale.Y)
		{
			float Plus = TextureScale.Y / 100.0f;
			CardRenderer->AddImageScale({ 0.0f, Plus, 0.0f, 0.0f });
		}
		else
		{
			CardRenderer->SetImageScale(TextureScale);
			CardRenderer->ChangeAnimation("Card_Turn");
		}

		if (1.0f > CardRenderer->RenderBaseInfoValue.VertexUVMul.Y)
		{
			CardRenderer->RenderBaseInfoValue.VertexUVMul.Y += 0.01f;
		}
		else
		{
			CardRenderer->RenderBaseInfoValue.VertexUVMul.Y = 1.0f;
		}
	}

	PrevHitSuccess = CurHitSuccess;
}

void Card::CardAdjust(int _Value)
{
	CardRenderer->ChangeAnimation("Card_Spawn");
	CurHitSuccess = _Value;
	PrevHitSuccess = InitialValue;

	unsigned int LoopCount = CurHitSuccess - PrevHitSuccess;

	for (unsigned int i = 0; i < LoopCount; i++)
	{
		float4 Scale = CardRenderer->GetImageTransform().GetLocalScale();

		float ScaleYValue = fabs(Scale.Y);

		if (ScaleYValue < TextureScale.Y)
		{
			float Plus = TextureScale.Y / 100.0f;
			CardRenderer->AddImageScale({ 0.0f, Plus, 0.0f, 0.0f });
		}
		else
		{
			CardRenderer->SetImageScale(TextureScale);
			CardRenderer->ChangeAnimation("Card_Turn");
		}

		if (1.0f > CardRenderer->RenderBaseInfoValue.VertexUVMul.Y)
		{
			CardRenderer->RenderBaseInfoValue.VertexUVMul.Y += 0.01f;
		}
		else
		{
			CardRenderer->RenderBaseInfoValue.VertexUVMul.Y = 1.0f;
		}
	}
}