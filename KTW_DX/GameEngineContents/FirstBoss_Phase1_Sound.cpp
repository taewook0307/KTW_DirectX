#include "PreCompile.h"
#include "FirstBoss.h"

void FirstBoss::Phase1MoveSoundPlay()
{
	GameEngineRandom Random;
	unsigned int Time = static_cast<unsigned int>(time(NULL));
	Random.SetSeed(static_cast<long long>(Time));

	int SoundNum = Random.RandomInt(0, 3);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_slime_small_jump_01.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_slime_small_jump_02.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_slime_small_jump_03.wav");
		break;
	default:
		GameEngineSound::SoundPlay("sfx_slime_small_jump_04.wav");
		break;
	}
}

void FirstBoss::Phase1LandSoundPlay()
{
	GameEngineRandom Random;
	unsigned int Time = static_cast<unsigned int>(time(NULL));
	Random.SetSeed(static_cast<long long>(Time));

	int SoundNum = Random.RandomInt(0, 4);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_slime_small_land_01.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_slime_small_land_02.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_slime_small_land_03.wav");
		break;
	case 3:
		GameEngineSound::SoundPlay("sfx_slime_small_land_04.wav");
		break;
	default:
		GameEngineSound::SoundPlay("sfx_slime_small_land_05.wav");
		break;
	}
}
