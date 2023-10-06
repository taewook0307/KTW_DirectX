#include "PreCompile.h"
#include "Shark.h"

Shark::Shark()
{
}

Shark::~Shark()
{
}

void Shark::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	Renderer->CreateAnimation("Shark_Fin", "Shark_Fin");
	Renderer->CreateAnimation("Shark_Entry", "Shark_Entry", SHARKANMATIONINTER);
	Renderer->CreateAnimation("Shark_Bite", "Shark_Bite", SHARKBITEANIMATIONINTER, -1, -1, false);
	Renderer->SetEndEvent("Shark_Bite",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(ESHARKSTATE::Leave);
			return;
		}
	);
	Renderer->CreateAnimation("Shark_Leave", "Shark_Leave", SHARKANMATIONINTER);

	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::LeftBottom);

	AttackCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::MonsterAttack);
	AttackCollision->Transform.SetLocalScale(SHARKCOLLISIONSCALE);
	AttackCollision->Transform.SetLocalPosition(SHARKCOLLISIONPOSITION);

	ChangeState(ESHARKSTATE::Fin);
}

void Shark::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Shark::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case ESHARKSTATE::Fin:
		return FinUpdate(_Delta);
	case ESHARKSTATE::Entry:
		return EntryUpdate(_Delta);
	case ESHARKSTATE::Leave:
		return LeaveUpdate(_Delta);
	default:
		break;
	}
}

void Shark::ChangeState(ESHARKSTATE _State)
{
	if (_State != CurState)
	{
		switch (_State)
		{
		case ESHARKSTATE::Fin:
			FinStart();
			break;
		case ESHARKSTATE::Entry:
			EntryStart();
			break;
		case ESHARKSTATE::Bite:
			BiteStart();
			break;
		case ESHARKSTATE::Leave:
			LeaveStart();
			break;
		default:
			break;
		}

		CurState = _State;
	}
}

void Shark::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "Shark_";

	AnimationName += _State;

	State = _State;

	Renderer->ChangeAnimation(AnimationName);
}