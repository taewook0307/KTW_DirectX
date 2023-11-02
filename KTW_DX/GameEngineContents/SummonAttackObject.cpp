#include "PreCompile.h"
#include "SummonAttackObject.h"

#include "SummonAttacker_Effect.h"

SummonAttackObject::SummonAttackObject()
{
}

SummonAttackObject::~SummonAttackObject()
{
}

void SummonAttackObject::CreateSummonEffect(const float4& _Pos)
{
	std::shared_ptr<SummonAttacker_Effect> Effect = GetLevel()->CreateActor<SummonAttacker_Effect>(EUPDATEORDER::Effect);
	Effect->Transform.SetLocalPosition(_Pos);
}

bool SummonAttackObject::CameraOutCheck(const float4& _Pos)
{
	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 WinHalfScale = GameEngineCore::MainWindow.GetScale().Half();

	float MinX = CameraPos.X - WinHalfScale.X;
	float MaxX = CameraPos.X + WinHalfScale.X;
	float MinY = CameraPos.Y + WinHalfScale.Y;
	float MaxY = CameraPos.Y - WinHalfScale.Y;

	float4 Pos = _Pos;

	if (MinX > Pos.X
		|| MaxX < Pos.X
		|| MinY < Pos.Y
		|| MaxY > Pos.Y)
	{
		return true;
	}

	return false;
}

bool SummonAttackObject::CameraOutCheck()
{
	float4 Pos = Transform.GetWorldPosition();
	return CameraOutCheck(Pos);
}