#include "PreCompile.h"
#include "Devil.h"

Devil::Devil()
{
}

Devil::~Devil()
{
}

void Devil::Start()
{
	GameEngineInput::AddInputObject(this);

	EyeRendererSetting();
	BodyRendererSetting();
	HeadRendererSetting();
	TridentRendererSetting();
	
	DevilRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	DevilRenderer->AutoSpriteSizeOn();
	DevilRenderer->SetPivotType(PivotType::Bottom);
	DevilRenderer->CreateAnimation("Devil_Intro_Loop", "Devil_Intro", 0.1f, 0, 2);
	DevilRenderer->CreateAnimation("Devil_Intro", "Devil_Intro", 0.1f, 3, -1, false);
	DevilRenderer->SetFrameEvent("Devil_Intro", 4, [=](GameEngineSpriteRenderer* _State)
		{
			EyeRenderer->Off();
		}
	);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent)
			{
				DevilRenderer->ChangeAnimation("Devil_Intro_Loop");
				EyeRenderer->ChangeAnimation("Intro_Eye", true);
				EyeRenderer->On();
			};
		Para.Stay = [=](float DeltaTime, GameEngineState* _Parent)
			{
				if (true == EyeRenderer->IsCurAnimationEnd())
				{
					DevilRenderer->ChangeAnimation("Devil_Intro");
				}

				if (true == DevilRenderer->IsCurAnimation("Devil_Intro") && true == DevilRenderer->IsCurAnimationEnd())
				{
					DevilState.ChangeState(EDEVILSTATE::Idle);
					return;
				}
			};

		DevilState.CreateState(EDEVILSTATE::Intro, Para);
	}

	DevilRenderer->CreateAnimation("Devil_Idle", "Devil_Idle", 0.05f);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent) { DevilRenderer->ChangeAnimation("Devil_Idle"); };
		/*Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == GameEngineInput::IsDown('P', this))
				{
					DevilState.ChangeState(EDEVILSTATE::Spider);
					return;
				}
			};*/

		DevilState.CreateState(EDEVILSTATE::Idle, Para);
	}

	DevilRenderer->CreateAnimation("Devil_Ram", "Devil_Ram", 0.1f, -1, -1, false);
	DevilRenderer->CreateAnimation("Devil_Ram_Stay", "Devil_Ram", 0.1f, 29, 30, true);
	DevilRenderer->CreateAnimation("Devil_Ram_End", "Devil_Ram", 0.1f, 30, 0, false);
	DevilRenderer->SetEndEvent("Devil_Ram_End", [=](GameEngineSpriteRenderer* _Renderer)
		{
			DevilState.ChangeState(EDEVILSTATE::Idle);
			return;
		}
	);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent) { DevilRenderer->ChangeAnimation("Devil_Ram"); };
		Para.Stay = [=](float DeltaTime, GameEngineState* _Parent)
			{
				if (true == DevilRenderer->IsCurAnimationEnd() && true == DevilRenderer->IsCurAnimation("Devil_Ram"))
				{
					DevilRenderer->ChangeAnimation("Devil_Ram_Stay");
					CreateRamArm();
				}

				else if (true == DevilRenderer->IsCurAnimation("Devil_Ram_Stay"))
				{
					if (true == ArmDeathCheck())
					{
						Arms.clear();
						DevilRenderer->ChangeAnimation("Devil_Ram_End");
					}
				}
			};

		DevilState.CreateState(EDEVILSTATE::Ram, Para);
	}

	DevilRenderer->CreateAnimation("Devil_Spider", "Devil_Spider", 0.1f);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent) { DevilRenderer->ChangeAnimation("Devil_Spider"); };
		Para.Stay = [=](float DeltaTime, GameEngineState* _Parent)
			{
				if (true == DevilRenderer->IsCurAnimationEnd())
				{
					DevilState.ChangeState(EDEVILSTATE::Idle);
					return;
				}
			};

		DevilState.CreateState(EDEVILSTATE::Spider, Para);
	}

	DevilRenderer->CreateAnimation("Devil_Serpent", "Devil_Serpent", 0.1f);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent) { DevilRenderer->ChangeAnimation("Devil_Serpent"); };
		Para.Stay = [=](float DeltaTime, GameEngineState* _Parent)
			{
				if (true == DevilRenderer->IsCurAnimationEnd())
				{
					DevilState.ChangeState(EDEVILSTATE::Idle);
					return;
				}
			};

		DevilState.CreateState(EDEVILSTATE::Serpent, Para);
	}

	DevilRenderer->CreateAnimation("Devil_Attack", "Devil_Attack", 0.1f, -1, -1, false);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent) { DevilRenderer->ChangeAnimation("Devil_Attack"); };
		Para.Stay = [=](float DeltaTime, GameEngineState* _Parent)
			{
				if (true == DevilRenderer->IsCurAnimationEnd())
				{
					DevilState.ChangeState(EDEVILSTATE::AttackStay);
					return;
				}
			};

		DevilState.CreateState(EDEVILSTATE::Attack, Para);
	}

	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent)
			{
				DevilRenderer->ChangeAnimation("Devil_Attack_End");
				DevilRenderer->Off();
				HeadRenderer->On();
				HeadRenderer->ChangeAnimation("Devil_Attack_Head", true);
				BodyRenderer->On();
				BodyRenderer->ChangeAnimation("Devil_Attack_Body", true);
				TridentRenderer->On();
				TridentRenderer->ChangeAnimation("Devil_Attack_Trident", true);
			};
		Para.Stay = [=](float DeltaTime, GameEngineState* _Parent)
			{
				if (true == TridentRenderer->IsCurAnimationEnd())
				{
					DevilState.ChangeState(EDEVILSTATE::AttackEnd);
					return;
				}
			};

		DevilState.CreateState(EDEVILSTATE::AttackStay, Para);
	}

	DevilRenderer->CreateAnimation("Devil_Attack_End", "Devil_Attack", 0.1f, 7, 0, false);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent)
			{
				TridentRenderer->Off();
				HeadRenderer->Off();
				BodyRenderer->Off();
				DevilRenderer->On();
			};
		Para.Stay = [=](float DeltaTime, GameEngineState* _Parent)
			{
				if (true == DevilRenderer->IsCurAnimationEnd())
				{
					DevilState.ChangeState(EDEVILSTATE::Idle);
					return;
				}
			};

		DevilState.CreateState(EDEVILSTATE::AttackEnd, Para);
	}

	DevilState.ChangeState(EDEVILSTATE::Intro);
}

void Devil::Update(float _Delta)
{
	DevilState.Update(_Delta);

	if (true == GameEngineInput::IsDown('1', this))
	{
		DevilState.ChangeState(EDEVILSTATE::Ram);
	}
	if (true == GameEngineInput::IsDown('2', this))
	{
		DevilState.ChangeState(EDEVILSTATE::Serpent);
	}
	if (true == GameEngineInput::IsDown('3', this))
	{
		DevilState.ChangeState(EDEVILSTATE::Attack);
	}
	if (true == GameEngineInput::IsDown('4', this))
	{
		DevilState.ChangeState(EDEVILSTATE::Spider);
	}
	if (true == GameEngineInput::IsDown('5', this))
	{
		DevilState.ChangeState(EDEVILSTATE::Intro);
	}
}

void Devil::EyeRendererSetting()
{
	EyeRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	EyeRenderer->CreateAnimation("Intro_Eye", "Intro_Eye", 0.1f, -1, -1, false);
	EyeRenderer->Transform.SetLocalPosition({ -85.0f, 230.0f });
	EyeRenderer->AutoSpriteSizeOn();
	EyeRenderer->Off();
}

void Devil::BodyRendererSetting()
{
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	BodyRenderer->CreateAnimation("Devil_Attack_Body", "Devil_Attack_Body");
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->SetPivotType(PivotType::Bottom);
	BodyRenderer->Off();
}

void Devil::HeadRendererSetting()
{
	HeadRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	HeadRenderer->CreateAnimation("Devil_Attack_Head", "Devil_Attack_Head");
	HeadRenderer->AutoSpriteSizeOn();
	HeadRenderer->SetPivotType(PivotType::Bottom);
	HeadRenderer->Off();
}

void Devil::TridentRendererSetting()
{
	TridentRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	TridentRenderer->CreateAnimation("Devil_Attack_Trident", "Devil_Attack_Trident", 0.1f, -1, -1, false);
	TridentRenderer->SetEndEvent("Devil_Attack_Trident", [=](GameEngineSpriteRenderer* _Parent)
		{
			TridentRenderer->Off();
			HeadRenderer->Off();
			BodyRenderer->Off();
			DevilRenderer->On();
		}
	);
	TridentRenderer->AutoSpriteSizeOn();
	TridentRenderer->Transform.SetLocalPosition({ 0.0f, 350.0f });
	TridentRenderer->Off();
}