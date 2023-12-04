#include "PreCompile.h"
#include "BaseBoss.h"

#include "BaseSummonActor.h"
#include "Map.h"

BaseBoss::BaseBoss()
{
}

BaseBoss::~BaseBoss()
{
}

bool BaseBoss::SummonDeathCheck()
{
	for (size_t i = 0; i < SummonActors.size(); i++)
	{
		bool Check = SummonActors[i]->IsDeath();

		if (false == Check)
		{
			return false;
		}
	}
	return true;
}

void BaseBoss::AllSummonDeath()
{
	for (size_t i = 0; i < SummonActors.size(); i++)
	{
		SummonActors[i]->Death();
	}

	SummonActors.clear();
}