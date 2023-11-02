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
	DevilRenderer->CreateAnimation("Devil_Intro_Loop", "Devil_Intro", DEVILANIMATIONINTER, 0, 2);
	DevilRenderer->CreateAnimation("Devil_Intro", "Devil_Intro", DEVILANIMATIONINTER, 3, -1, false);
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

	DevilRenderer->CreateAnimation("Devil_Idle", "Devil_Idle", DEVILANIMATIONINTER);
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

	DevilRenderer->CreateAnimation("Devil_Ram", "Devil_Ram", DEVILANIMATIONINTER, -1, -1, false);
	DevilRenderer->SetEndEvent("Devil_Ram", [=](GameEngineSpriteRenderer* _Renderer)
		{
			DevilRenderer->ChangeAnimation("Devil_Ram_Stay");
			CreateRamArm();
		}
	);
	DevilRenderer->CreateAnimation("Devil_Ram_Stay", "Devil_Ram", DEVILANIMATIONINTER, 29, 30, true);
	DevilRenderer->CreateAnimation("Devil_Ram_End", "Devil_Ram", DEVILANIMATIONINTER, 30, 0, false);
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
				if (true == DevilRenderer->IsCurAnimation("Devil_Ram_Stay"))
				{
					if (true == SummonDeathCheck())
					{
						SummonActors.clear();
						DevilRenderer->ChangeAnimation("Devil_Ram_End");
					}
				}
			};

		DevilState.CreateState(EDEVILSTATE::Ram, Para);
	}

	DevilRenderer->CreateAnimation("Devil_Serpent", "Devil_Serpent", DEVILANIMATIONINTER, -1, -1, false);
	DevilRenderer->SetEndEvent("Devil_Serpent", [=](GameEngineSpriteRenderer* _Renderer)
		{
			if (EACTORDIR::Left == SerpentDir)
			{
				DevilRenderer->ChangeAnimation("Devil_Serpent_Left");
			}
			else
			{
				DevilRenderer->ChangeAnimation("Devil_Serpent_Right");
			}
		}
	);

	DevilRenderer->CreateAnimation("Devil_Serpent_Left", "Devil_Serpent_Left", DEVILANIMATIONINTER, 0, 0, false);
	DevilRenderer->SetEndEvent("Devil_Serpent_Left", [=](GameEngineSpriteRenderer* _Renderer)
		{
			if (EACTORDIR::Left == SerpentDir)
			{
				DevilRenderer->ChangeAnimation("Devil_Serpent_Stay_Left");
				CreateSerpentHead();
			}
		}
	);
	DevilRenderer->CreateAnimation("Devil_Serpent_Stay_Left", "Devil_Serpent_Left", DEVILANIMATIONINTER, 1, 4, true);

	DevilRenderer->CreateAnimation("Devil_Serpent_Right", "Devil_Serpent_Right", DEVILANIMATIONINTER, 0, 0, false);
	DevilRenderer->SetEndEvent("Devil_Serpent_Right", [=](GameEngineSpriteRenderer* _Renderer)
		{
			if (EACTORDIR::Right == SerpentDir)
			{
				DevilRenderer->ChangeAnimation("Devil_Serpent_Stay_Right");
				CreateSerpentHead();
			}
		}
	);
	DevilRenderer->CreateAnimation("Devil_Serpent_Stay_Right", "Devil_Serpent_Right", DEVILANIMATIONINTER, 1, 4, true);

	DevilRenderer->CreateAnimation("Devil_Serpent_End_Left", "Devil_Serpent_Left", DEVILANIMATIONINTER, 4, 0, false);
	DevilRenderer->SetEndEvent("Devil_Serpent_End_Left", [=](GameEngineSpriteRenderer* _Renderer)
		{
			DevilRenderer->ChangeAnimation("Devil_Serpent_End");
		}
	);
	DevilRenderer->CreateAnimation("Devil_Serpent_End_Right", "Devil_Serpent_Right", DEVILANIMATIONINTER, 4, 0, false);
	DevilRenderer->SetEndEvent("Devil_Serpent_End_Right", [=](GameEngineSpriteRenderer* _Renderer)
		{
			DevilRenderer->ChangeAnimation("Devil_Serpent_End");
		}
	);
	DevilRenderer->CreateAnimation("Devil_Serpent_End", "Devil_Serpent", DEVILANIMATIONINTER, 29, 0, false);
	DevilRenderer->SetEndEvent("Devil_Serpent_End", [=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeSerpentDir();
			DevilState.ChangeState(EDEVILSTATE::Idle);
			return;
		}
	);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent) { DevilRenderer->ChangeAnimation("Devil_Serpent"); };
		Para.Stay = [=](float DeltaTime, GameEngineState* _Parent)
			{
				if (true == DevilRenderer->IsCurAnimation("Devil_Serpent_Stay_Left"))
				{
					if (true == SummonDeathCheck())
					{
						SummonActors.clear();
						DevilRenderer->ChangeAnimation("Devil_Serpent_End_Left");
					}
				}

				if (true == DevilRenderer->IsCurAnimation("Devil_Serpent_Stay_Right"))
				{
					if (true == SummonDeathCheck())
					{
						SummonActors.clear();
						DevilRenderer->ChangeAnimation("Devil_Serpent_End_Right");
					}
				}
			};

		DevilState.CreateState(EDEVILSTATE::Serpent, Para);
	}

	DevilRenderer->CreateAnimation("Devil_Spider", "Devil_Spider", DEVILANIMATIONINTER, -1, -1, false);
	DevilRenderer->SetEndEvent("Devil_Spider", [=](GameEngineSpriteRenderer* _Renderer)
		{
			DevilRenderer->ChangeAnimation("Devil_Spider_Stay");
			CreateSpiderHead();
		}
	);
	DevilRenderer->CreateAnimation("Devil_Spider_Stay", "Devil_Spider", DEVILANIMATIONINTER, 51, 65, true);
	DevilRenderer->CreateAnimation("Devil_Spider_End", "Devil_Spider", DEVILANIMATIONINTER, 65, 0, false);
	DevilRenderer->SetEndEvent("Devil_Spider_End", [=](GameEngineSpriteRenderer* _Renderer)
		{
			DevilState.ChangeState(EDEVILSTATE::Idle);
			return;
		}
	);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent) { DevilRenderer->ChangeAnimation("Devil_Spider"); };
		Para.Stay = [=](float DeltaTime, GameEngineState* _Parent)
			{
				if (true == DevilRenderer->IsCurAnimation("Devil_Spider_Stay"))
				{
					if (true == SummonDeathCheck())
					{
						SummonActors.clear();
						DevilRenderer->ChangeAnimation("Devil_Spider_End");
					}
				}
			};

		DevilState.CreateState(EDEVILSTATE::Spider, Para);
	}

	DevilRenderer->CreateAnimation("Devil_Attack", "Devil_Attack", DEVILANIMATIONINTER, -1, -1, false);
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
					if (true == SummonAttackBall)
					{
						CreateBall();
					}
					else
					{
						CreateFire();
					}

					DevilState.ChangeState(EDEVILSTATE::AttackEnd);
					return;
				}
			};

		DevilState.CreateState(EDEVILSTATE::AttackStay, Para);
	}

	DevilRenderer->CreateAnimation("Devil_Attack_End", "Devil_Attack", DEVILANIMATIONINTER, 7, 0, false);
	DevilRenderer->SetEndEvent("Devil_Attack_End", [=](GameEngineSpriteRenderer* _Renderer)
		{
			DevilRenderer->ChangeAnimation("Devil_Idle");
		}
	);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent)
			{
				TridentRenderer->Off();
				HeadRenderer->Off();
				BodyRenderer->Off();
				DevilRenderer->On();
			};
		Para.Stay = [&](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == DevilRenderer->IsCurAnimation("Devil_Idle"))
				{
					if (true == SummonDeathCheck())
					{
						SummonAttackBall = !SummonAttackBall;
						SummonActors.clear();
						DevilState.ChangeState(EDEVILSTATE::Idle);
						return;
					}

					if (true == SummonAttackBall)
					{
						BallMoveReq(_DeltaTime);
					}
					else
					{
						FireMoveReq(_DeltaTime);
					}
				}
			};

		DevilState.CreateState(EDEVILSTATE::AttackEnd, Para);
	}

	DevilState.ChangeState(EDEVILSTATE::Idle);
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
	EyeRenderer->CreateAnimation("Intro_Eye", "Intro_Eye", DEVILANIMATIONINTER, -1, -1, false);
	EyeRenderer->Transform.SetLocalPosition({ -85.0f, 230.0f });
	EyeRenderer->AutoSpriteSizeOn();
	EyeRenderer->Off();
}

void Devil::BodyRendererSetting()
{
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	BodyRenderer->CreateAnimation("Devil_Attack_Body", "Devil_Attack_Body", DEVILANIMATIONINTER);
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->SetPivotType(PivotType::Bottom);
	BodyRenderer->Off();
}

void Devil::HeadRendererSetting()
{
	HeadRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	HeadRenderer->CreateAnimation("Devil_Attack_Head", "Devil_Attack_Head", DEVILANIMATIONINTER);
	HeadRenderer->AutoSpriteSizeOn();
	HeadRenderer->SetPivotType(PivotType::Bottom);
	HeadRenderer->Off();
}

void Devil::TridentRendererSetting()
{
	TridentRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	TridentRenderer->CreateAnimation("Devil_Attack_Trident", "Devil_Attack_Trident", DEVILANIMATIONINTER, -1, -1, false);
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

void Devil::ChangeSerpentDir()
{
	if (EACTORDIR::Left == SerpentDir)
	{
		SerpentDir = EACTORDIR::Right;
	}
	else
	{
		SerpentDir = EACTORDIR::Left;
	}
}