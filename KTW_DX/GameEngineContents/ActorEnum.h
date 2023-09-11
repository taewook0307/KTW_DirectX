#pragma once

enum class CharacterState
{
	Intro,
	Idle,
	Run,
	Jump,
	Dash,
	Fall,
	Aim,
	Duck,
	Shoot,
	AimShoot,
	RunShoot,
	DuckShoot
};

enum class MiniMapCharacterState
{
	None,
	Idle,
	Run
};

enum class CharacterDir
{
	None,
	Left,
	Right
};

enum class CharacterAimDir
{
	None,
	Straight,
	StraightUp,
	StraightDown,
	Up,
	Down
};

enum class MainMenuSelect
{
	Start,
	Exit
};

enum class BulletType
{
	Normal
};

enum class BulletState
{
	None,
	Spawn,
	Move,
	Death
};

enum class BulletDirection
{
	None,
	Up,
	RightUp,
	Right,
	RightDown,
	Down,
	LeftDown,
	Left,
	LeftUp
};