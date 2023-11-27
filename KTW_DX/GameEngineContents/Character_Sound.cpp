#include "PreCompile.h"
#include "BaseCharacter.h"

void BaseCharacter::ShootSoundPlay()
{
	if (ECHARACTERSTATE::Intro == CurState
		|| ECHARACTERSTATE::Death == CurState
		|| ECHARACTERSTATE::Hit == CurState)
	{
		ShootSound.Stop();
		IsShootSoundSet = false;
		return;
	}

	if (false == IsShootSoundSet && true == GameEngineInput::IsDown('X', this)
		|| false == IsShootSoundSet && true == GameEngineInput::IsPress('X', this))
	{
		ShootSound = GameEngineSound::SoundPlay("sfx_player_default_fire_loop_01.wav", 1000);
		IsShootSoundSet = true;
	}

	if (true == GameEngineInput::IsUp('X', this) || true == GameEngineInput::IsFree('X', this))
	{
		ShootSound.Stop();
		IsShootSoundSet = false;
	}

	return;
}

void BaseCharacter::DashSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 2);

	if (0 == SoundNum)
	{
		GameEngineSound::SoundPlay("sfx_player_dash_01.wav");
	}
	else if (1 == SoundNum)
	{
		GameEngineSound::SoundPlay("sfx_player_dash_02.wav");
	}
	else
	{
		GameEngineSound::SoundPlay("sfx_player_dash_03.wav");
	}
}

void BaseCharacter::DeathSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 1);

	if (0 == SoundNum)
	{
		GameEngineSound::SoundPlay("sfx_player_death_01.wav");
	}
	else
	{
		GameEngineSound::SoundPlay("sfx_player_death_02.wav");
	}
}

void BaseCharacter::HitSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 4);

	if (0 == SoundNum)
	{
		GameEngineSound::SoundPlay("sfx_player_hit_01.wav");
	}
	else if (1 == SoundNum)
	{
		GameEngineSound::SoundPlay("sfx_player_hit_02.wav");
	}
	else if (2 == SoundNum)
	{
		GameEngineSound::SoundPlay("sfx_player_hit_03.wav");
	}
	else if (3 == SoundNum)
	{
		GameEngineSound::SoundPlay("sfx_player_hit_04.wav");
	}
	else
	{
		GameEngineSound::SoundPlay("sfx_player_hit_05.wav");
	}
}

void BaseCharacter::JumpSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 2);

	if (0 == SoundNum)
	{
		GameEngineSound::SoundPlay("sfx_player_jump_01.wav");
	}
	else if (1 == SoundNum)
	{
		GameEngineSound::SoundPlay("sfx_player_jump_02.wav");
	}
	else
	{
		GameEngineSound::SoundPlay("sfx_player_jump_03.wav");
	}
}

void BaseCharacter::LandSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 1);

	if (0 == SoundNum)
	{
		GameEngineSound::SoundPlay("sfx_player_land_ground_01.wav");
	}
	else
	{
		GameEngineSound::SoundPlay("sfx_player_land_ground_02.wav");
	}
}

void BaseCharacter::ParrySoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 1);

	if (0 == SoundNum)
	{
		GameEngineSound::SoundPlay("sfx_player_parry_slap_01.wav");
	}
	else
	{
		GameEngineSound::SoundPlay("sfx_player_parry_slap_02.wav");
	}
}
