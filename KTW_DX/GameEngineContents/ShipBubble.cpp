#include "PreCompile.h"
#include "ShipBubble.h"

ShipBubble::ShipBubble()
{
}

ShipBubble::~ShipBubble()
{
}

void ShipBubble::Start()
{
	GameEngineInput::AddInputObject(this);

	BubbleRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::BossEffect);

	BubbleRenderer->CreateAnimation("ShipBubble_Appear", "ShipBubble_Appear", 0.05f);
	BubbleRenderer->SetEndEvent("ShipBubble_Appear",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(ESHIPBUBBLESTATE::Move);
			return;
		}
	);

	BubbleRenderer->CreateAnimation("ShipBubble_Move", "ShipBubble_Move", 0.05f);
	BubbleRenderer->CreateAnimation("ShipBubble_Pop", "ShipBubble_Pop");
	BubbleRenderer->SetEndEvent("ShipBubble_Pop",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			BubbleRenderer = nullptr;
			Death();
		}
	);

	BubbleRenderer->AutoSpriteSizeOn();
	BubbleRenderer->Transform.SetLocalPosition(SHIPBUBBLERENDERERPOS);

	AttackCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	AttackCollision->Transform.SetLocalPosition(SHIPBUBBLERENDERERPOS);
	AttackCollision->Transform.SetLocalScale(SHIPBUBBLECOLLISIONSCALE);

	ChangeState(ESHIPBUBBLESTATE::Appear);
}

void ShipBubble::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void ShipBubble::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case ESHIPBUBBLESTATE::Move:
		return MoveUpdate(_Delta);
	default:
		break;
	}
}

void ShipBubble::ChangeState(ESHIPBUBBLESTATE _CurState)
{
	if (_CurState != CurState)
	{
		switch (_CurState)
		{
		case ESHIPBUBBLESTATE::Appear:
			AppearStart();
			break;
		case ESHIPBUBBLESTATE::Move:
			MoveStart();
			break;
		case ESHIPBUBBLESTATE::Pop:
			PopStart();
			break;
		default:
			break;
		}

		CurState = _CurState;
	}
}

void ShipBubble::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "ShipBubble_";
	AnimationName += _State;
	State = _State;
	BubbleRenderer->ChangeAnimation(AnimationName);
}


void ShipBubble::AppearStart()
{
	ChangeAnimation("Appear");
}

void ShipBubble::MoveStart()
{
	ChangeAnimation("Move");
}

void ShipBubble::PopStart()
{
	ChangeAnimation("Pop");
}

void ShipBubble::MoveUpdate(float _Delta)
{
	Transform.AddLocalRotation({ 0.0f, 0.0f, RotSpeed * _Delta });
	Transform.AddLocalPosition(float4::LEFT * Speed * _Delta);

	if (true == AttackCollision->Collision(ECOLLISIONORDER::Player))
	{
		ChangeState(ESHIPBUBBLESTATE::Pop);
		return;
	}
}