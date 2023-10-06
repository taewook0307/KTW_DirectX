#include "PreCompile.h"
#include "DogFish.h"

DogFish::DogFish()
{
}

DogFish::~DogFish()
{
}

void DogFish::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	Renderer->CreateAnimation("DogFish_Jump", "DogFish_Jump", 0.05f, 0, 3, false);
	Renderer->CreateAnimation("DogFish_JumpToFall", "DogFish_Jump", 0.05f, 4, 7, false);
	Renderer->CreateAnimation("DogFish_Fall", "DogFish_Jump", 0.05f, 8, 9, false);
	Renderer->CreateAnimation("DogFish_Landing", "DogFish_Landing", 0.05f, -1, -1, false);
	Renderer->SetEndEvent("DogFish_Landing",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(EDOGFISHSTATE::Move);
			return;
		}
	);
	Renderer->CreateAnimation("DogFish_Move", "DogFish_Move", 0.05f);
	Renderer->CreateAnimation("DogFish_Death", "DogFish_Death", 0.05f);

	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::Bottom);

	BodyCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::MonsterBody);
	BodyCollision->Transform.SetLocalScale(DOGFISHCOLLISIONSCALE);
	BodyCollision->Transform.SetLocalPosition(DOGFISHCOLLISIONPOSITION);

	ChangeState(EDOGFISHSTATE::Jump);
}

void DogFish::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (true == BodyCollision->Collision(ECOLLISIONORDER::Bullet))
	{
		--Life;
	}

	if (0 >= Life)
	{
		ChangeState(EDOGFISHSTATE::Death);
		return;
	}
}

void DogFish::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case EDOGFISHSTATE::Jump:
		return JumpUpdate(_Delta);
	case EDOGFISHSTATE::Landing:
		return LandingUpdate(_Delta);
	case EDOGFISHSTATE::Move:
		return MoveUpdate(_Delta);
	case EDOGFISHSTATE::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}

void DogFish::ChangeState(EDOGFISHSTATE _State)
{
	if (_State != CurState)
	{
		switch (_State)
		{
		case EDOGFISHSTATE::Jump:
			JumpStart();
			break;
		case EDOGFISHSTATE::Landing:
			LandingStart();
			break;
		case EDOGFISHSTATE::Move:
			MoveStart();
			break;
		case EDOGFISHSTATE::Death:
			DeathStart();
			break;
		default:
			break;
		}

		CurState = _State;
	}
}

void DogFish::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "DogFish_";

	AnimationName += _State;

	State = _State;

	Renderer->ChangeAnimation(AnimationName);
}