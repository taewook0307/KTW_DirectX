#include "PreCompile.h"
#include "PirateBoss.h"

void PirateBoss::IntroSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 1);

	if (0 == SoundNum)
	{
		GameEngineSound::SoundPlay("sfx_pirate_laugh_01.wav");
	}
	else
	{
		GameEngineSound::SoundPlay("sfx_pirate_laugh_02.wav");
	}
}

void PirateBoss::ShootSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 3);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_pirate_gun_shoot_01.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_pirate_gun_shoot_02.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_pirate_gun_shoot_03.wav");
		break;
	default:
		GameEngineSound::SoundPlay("sfx_pirate_gun_shoot_04.wav");
		break;
	}
}