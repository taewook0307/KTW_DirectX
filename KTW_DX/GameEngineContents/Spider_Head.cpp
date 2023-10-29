#include "PreCompile.h"
#include "Spider_Head.h"

#include "Map.h"

Spider_Head::Spider_Head()
{
}

Spider_Head::~Spider_Head()
{
}

void Spider_Head::Start()
{
	SpiderRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	SpiderRenderer->AutoSpriteSizeOn();
	SpiderRenderer->SetPivotType(PivotType::Bottom);

	SpiderRenderer->CreateAnimation("SpiderHead_Fall", "SpiderHead_Fall");
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				SpiderRenderer->ChangeAnimation("SpiderHead_Fall");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

				if (FLOORCOLOR == CheckColor)
				{
					SpiderState.ChangeState(ESPIDERHEADSTATE::JumpStart);
					return;
				}
			};
		SpiderState.CreateState(ESPIDERHEADSTATE::Fall, Para);
	}

	SpiderRenderer->CreateAnimation("SpiderHead_JumpStart", "SpiderHead_JumpStart");
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				SpiderRenderer->ChangeAnimation("SpiderHead_JumpStart");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == SpiderRenderer->IsCurAnimationEnd())
				{
					SpiderState.ChangeState(ESPIDERHEADSTATE::Jump);
					return;
				}
			};
		SpiderState.CreateState(ESPIDERHEADSTATE::JumpStart, Para);
	}

	SpiderRenderer->CreateAnimation("SpiderHead_Jump", "SpiderHead_Jump");
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				SetGravityForce(float4::UP * 2000.0f);
				SpiderRenderer->ChangeAnimation("SpiderHead_Jump");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				float GravityY = GetGravityForce().Y;

				if (20.0f >= GravityY)
				{
					SpiderState.ChangeState(ESPIDERHEADSTATE::JumpToFall);
					return;
				}
			};
		SpiderState.CreateState(ESPIDERHEADSTATE::Jump, Para);
	}

	SpiderRenderer->CreateAnimation("SpiderHead_JumpToFall", "SpiderHead_JumpToFall");
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				SpiderRenderer->ChangeAnimation("SpiderHead_JumpToFall");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == SpiderRenderer->IsCurAnimationEnd())
				{
					SpiderState.ChangeState(ESPIDERHEADSTATE::Fall);
					return;
				}
			};
		SpiderState.CreateState(ESPIDERHEADSTATE::JumpToFall, Para);
	}

	SpiderRenderer->CreateAnimation("SpiderHead_Land", "SpiderHead_Land");
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				SpiderRenderer->ChangeAnimation("SpiderHead_Land");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == SpiderRenderer->IsCurAnimationEnd())
				{
					SpiderState.ChangeState(ESPIDERHEADSTATE::JumpStart);
					return;
				}
			};
		SpiderState.CreateState(ESPIDERHEADSTATE::Land, Para);
	}

	SpiderState.ChangeState(ESPIDERHEADSTATE::Fall);
}

void Spider_Head::Update(float _Delta)
{
	SpiderState.Update(_Delta);

	if (1800.0f < GetGravityForce().Y)
	{
		float4 Pos = Transform.GetWorldPosition() + float4{ 0.0f, 80.0f };
		ActorHalfGravity(_Delta, Pos);
	}
	else
	{
		ActorGravity(_Delta, Transform.GetWorldPosition());
	}
}