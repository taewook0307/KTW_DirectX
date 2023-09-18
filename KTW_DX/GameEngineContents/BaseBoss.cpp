#include "PreCompile.h"
#include "BaseBoss.h"

#include "Map.h"

BaseBoss::BaseBoss()
{
}

BaseBoss::~BaseBoss()
{
}

void BaseBoss::BossGravity(float4 _CheckPos, float _Delta)
{
	GameEngineColor CheckColor = Map::MainMap->GetColor(_CheckPos, FLOORCOLOR);

	if (FLOORCOLOR != CheckColor)
	{
		GravityOn(_Delta);
	}
	else
	{
		GravityReset();
	}
}