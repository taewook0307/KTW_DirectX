#include "PreCompile.h"
#include "Ram_Arm_Right.h"

Ram_Arm_Right::Ram_Arm_Right()
{
}

Ram_Arm_Right::~Ram_Arm_Right()
{
}

void Ram_Arm_Right::Start()
{
	ArmRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	ArmRenderer->SetPivotType(PivotType::Right);
	ArmRenderer->AutoSpriteSizeOn();
	ArmRenderer->CreateAnimation("Ram_Arm_Move", "Ram_Arm", RAMARMANIMATIONINTER, 0, 4, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { ArmRenderer->ChangeAnimation("Ram_Arm_Move"); };
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				float4 Pos = Transform.GetWorldPosition();
				float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();
				if (Pos.X >= WinScaleHalf.X + 0.05f)
				{
					ArmState.ChangeState(EDEVILARMSTATE::Clap);
				}

				Transform.AddLocalPosition(float4::RIGHT * _DeltaTime * Speed);
			};
		ArmState.CreateState(EDEVILARMSTATE::Move, Para);
	}

	ArmRenderer->CreateAnimation("Ram_Arm_Clap", "Ram_Arm", RAMARMANIMATIONINTER, 5, 9, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { ArmRenderer->ChangeAnimation("Ram_Arm_Clap"); };
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == ArmRenderer->IsCurAnimationEnd())
				{
					ArmState.ChangeState(EDEVILARMSTATE::MoveBack);
				}
			};
		ArmState.CreateState(EDEVILARMSTATE::Clap, Para);
	}

	ArmRenderer->CreateAnimation("Ram_Arm_MoveBack", "Ram_Arm", RAMARMANIMATIONINTER, 10, 14, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { ArmRenderer->ChangeAnimation("Ram_Arm_MoveBack"); };
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				float4 Pos = Transform.GetWorldPosition();
				if (Pos.X <= 0.0f)
				{
					Death();
				}

				Transform.AddLocalPosition(float4::LEFT * _DeltaTime * Speed);
			};
		ArmState.CreateState(EDEVILARMSTATE::MoveBack, Para);
	}

	ArmState.ChangeState(EDEVILARMSTATE::Move);
}

void Ram_Arm_Right::Update(float _Delta)
{
	ArmState.Update(_Delta);
}