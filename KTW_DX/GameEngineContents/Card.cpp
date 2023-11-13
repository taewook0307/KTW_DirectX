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

	CardRenderer->SetImageScale({ TextureScale.X, 0.0f, 0.0f, 1.0f });
	CardRenderer->RenderBaseInfoValue.VertexUVMul.Y = 0.0f;

	GameEngineInput::AddInputObject(this);
}

void Card::Update(float _Delta)
{
	float4 Check = CardRenderer->GetImageTransform().GetLocalPosition();
	
	OutputDebugStringA(Check.ToString().c_str());

	if (true == GameEngineInput::IsDown('9', this))
	{
		float4 Scale = CardRenderer->GetImageTransform().GetLocalScale();

		float Check = fabs(Scale.Y);

		if (Check < TextureScale.Y)
		{
			float Plus = TextureScale.Y / 10.0f;
			CardRenderer->AddImageScale({ 0.0f, Plus, 0.0f, 0.0f });
		}
		else
		{
			CardRenderer->SetImageScale(TextureScale);
			CardRenderer->ChangeAnimation("Card_Turn");
		}

		if (1.0f > CardRenderer->RenderBaseInfoValue.VertexUVMul.Y)
		{
			CardRenderer->RenderBaseInfoValue.VertexUVMul.Y += 0.1f;
		}
		else
		{
			CardRenderer->RenderBaseInfoValue.VertexUVMul.Y = 1.0f;
		}
	}

	if (true == GameEngineInput::IsDown('R', this))
	{
		CardRenderer->SetImageScale({ TextureScale.X, 0.0f });
		CardRenderer->RenderBaseInfoValue.VertexUVMul.Y = 0.0f;
	}
}