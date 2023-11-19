#include "PreCompile.h"
#include "PirateBoss.h"

void PirateBoss::IntroSoundPlay()
{
	GameEngineRandom Random;
	unsigned int Time = static_cast<unsigned int>(time(NULL));
	Random.SetSeed(static_cast<long long>(Time));

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
	unsigned int Time = static_cast<unsigned int>(time(NULL));
	Random.SetSeed(static_cast<long long>(Time));

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