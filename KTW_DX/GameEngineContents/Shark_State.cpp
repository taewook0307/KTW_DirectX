#include "PreCompile.h"
#include "Shark.h"

void Shark::FinStart()
{
	ChangeAnimation("Fin");
	AttackCollision->Off();
	Renderer->SetAutoScaleRatio(0.7f);
	Renderer->SetRenderOrder(ERENDERORDER::PrevBoss);
}
void Shark::FinUpdate(float _Delta)
{
	float4 MovePos = float4::LEFT * FinSpeed * _Delta;

	Transform.AddLocalPosition(MovePos);

	float4 SharkPos = Transform.GetWorldPosition();

	if (-830.0f > SharkPos.X)
	{
		Renderer->SetAutoScaleRatio(1.0f);
		Renderer->SetRenderOrder(ERENDERORDER::Boss);
		ChangeState(ESHARKSTATE::Entry);
		return;
	}
}

void Shark::EntryStart()
{
	Transform.SetLocalPosition({ -830.0f, -670.0f });
	AttackCollision->On();
	ChangeAnimation("Entry");
}
void Shark::EntryUpdate(float _Delta)
{
	float4 MovePos = float4::RIGHT * Speed * _Delta;

	Transform.AddLocalPosition(MovePos);

	float4 SharkPos = Transform.GetWorldPosition();

	if (-30.0f < SharkPos.X)
	{
		ChangeState(ESHARKSTATE::Bite);
		return;
	}
}

void Shark::BiteStart()
{
	ChangeAnimation("Bite");
}

void Shark::LeaveStart()
{
	ChangeAnimation("Leave");
}
void Shark::LeaveUpdate(float _Delta)
{
	float4 MovePos = float4::LEFT * LeaveSpeed * _Delta;

	Transform.AddLocalPosition(MovePos);

	float4 SharkPos = Transform.GetWorldPosition();

	if (-760.0f > SharkPos.X)
	{
		Death();
	}
}