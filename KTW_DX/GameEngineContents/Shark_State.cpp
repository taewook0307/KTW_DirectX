#include "PreCompile.h"
#include "Shark.h"

void Shark::FinStart()
{
	ChangeAnimation("Fin");
}
void Shark::FinUpdate(float _Delta)
{

}

void Shark::EntryStart()
{
	ChangeAnimation("Entry");
}
void Shark::EntryUpdate(float _Delta)
{
	float4 MovePos = float4::RIGHT * Speed * _Delta;

	Transform.AddLocalPosition(MovePos);

	float4 SharkPos = Transform.GetWorldPosition();

	if (0.0f < SharkPos.X)
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
	float4 MovePos = float4::LEFT * Speed * _Delta;

	Transform.AddLocalPosition(MovePos);

	float4 SharkPos = Transform.GetWorldPosition();

	if (-760.0f > SharkPos.X)
	{
		Death();
	}
}