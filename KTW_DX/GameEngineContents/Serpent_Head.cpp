#include "PreCompile.h"
#include "Serpent_Head.h"

Serpent_Head::Serpent_Head()
{
}

Serpent_Head::~Serpent_Head()
{
}

void Serpent_Head::Start()
{
	SerpentRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	SerpentRenderer->CreateAnimation("Serpent_Head_Move", "Serpent_Head", 0.1f, 0, 23, true);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { SerpentRenderer->ChangeAnimation("Serpent_Head_Move"); };
		Para.Stay = [&](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == MoveEndCheck() && true == SerpentRenderer->IsCurAnimationEnd())
				{
					SerpentState.ChangeState(ESERPENTSTATE::Back);
					return;
				}
				else
				{
					SerpentMove(_DeltaTime);
				}
			};
		SerpentState.CreateState(ESERPENTSTATE::Move, Para);
	}

	SerpentRenderer->CreateAnimation("Serpent_Head_Back", "Serpent_Head", 0.1f, 24, -1, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { SerpentRenderer->ChangeAnimation("Serpent_Head_Back"); };
		Para.Stay = [&](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == SerpentRenderer->IsCurAnimationEnd())
				{
					Death();
				}
			};
		SerpentState.CreateState(ESERPENTSTATE::Back, Para);
	}

	SerpentRenderer->SetPivotType(PivotType::RightBottom);
	SerpentRenderer->AutoSpriteSizeOn();

	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	MoveEndPoint = WinScale.X - (WinScale.X * SERPENTENDPOINTRATIO);

	SerpentState.ChangeState(ESERPENTSTATE::Move);
}

void Serpent_Head::Update(float _Delta)
{
	SerpentState.Update(_Delta);
}

void Serpent_Head::SetLeftDir()
{
	SerpentDir = EACTORDIR::Left;
	SerpentRenderer->SetPivotType(PivotType::LeftBottom);
	SerpentRenderer->LeftFlip();

	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	MoveEndPoint = WinScale.X * SERPENTENDPOINTRATIO;
}

void Serpent_Head::SerpentMove(float _Delta)
{
	float4 MovePos = float4::ZERO;

	if (EACTORDIR::Left == SerpentDir)
	{
		MovePos = float4::LEFT * Speed * _Delta;
	}
	else if (EACTORDIR::Right == SerpentDir)
	{
		MovePos = float4::RIGHT * Speed * _Delta;
	}
	else
	{
		MsgBoxAssert("SerpentHead의 방향이 설정되지 않았습니다.");
		return;
	}

	Transform.AddLocalPosition(MovePos);
}

bool Serpent_Head::MoveEndCheck()
{
	float4 Pos = Transform.GetWorldPosition();

	if (EACTORDIR::Left == SerpentDir && MoveEndPoint > Pos.X)
	{
		return true;
	}

	if (EACTORDIR::Right == SerpentDir && MoveEndPoint < Pos.X)
	{
		return true;
	}

	return false;
}