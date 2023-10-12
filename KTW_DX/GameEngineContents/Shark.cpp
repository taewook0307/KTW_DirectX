#include "PreCompile.h"
#include "Shark.h"

#include "StageLevel.h"

Shark::Shark()
{
}

Shark::~Shark()
{
}

void Shark::Start()
{
	SharkRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	SharkRenderer->CreateAnimation("Shark_Fin", "Shark_Fin");
	SharkRenderer->CreateAnimation("Shark_Entry", "Shark_Entry", SHARKANMATIONINTER);
	SharkRenderer->CreateAnimation("Shark_Bite", "Shark_Bite", SHARKBITEANIMATIONINTER, -1, -1, false);
	SharkRenderer->SetEndEvent("Shark_Bite",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(ESHARKSTATE::Leave);
			return;
		}
	);
	SharkRenderer->CreateAnimation("Shark_Leave", "Shark_Leave", SHARKANMATIONINTER);

	SharkRenderer->AutoSpriteSizeOn();
	SharkRenderer->SetPivotType(PivotType::LeftBottom);

	AttackCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::MonsterBody);
	AttackCollision->SetCollisionType(ColType::AABBBOX2D);
	AttackCollision->Transform.SetLocalScale(SHARKCOLLISIONSCALE);
	AttackCollision->Transform.SetLocalPosition(SHARKCOLLISIONPOSITION);

	ChangeState(ESHARKSTATE::Fin);
}

void Shark::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (ESTAGERESULT::None != StageLevel::GetStageResult())
	{
		Death();
	}
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

void Shark::ChangeState(ESHARKSTATE _CurState)
{
	if (_CurState != CurState)
	{
		switch (_CurState)
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

		CurState = _CurState;
	}
}

void Shark::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "Shark_";

	AnimationName += _State;

	State = _State;

	SharkRenderer->ChangeAnimation(AnimationName);
}