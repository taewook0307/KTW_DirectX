#pragma once

enum class ActorDir
{
	None,
	Left,
	Right
};

// Character
enum class CharacterAimDir
{
	None,
	Straight,
	StraightUp,
	StraightDown,
	Up,
	Down
};

enum class CharacterState
{
	None,
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
	DuckShoot,
	Parry,
	SpecialAttack,
	Hit,
	Death
};

enum class MiniMapCharacterState
{
	None,
	Idle,
	Run
};

// Bullet
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

enum class Direction8
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

// Boss
enum class BossPhase
{
	Phase1,
	Phase2,
	Phase3
};

enum class FirstBossState
{
	None,
	Intro,
	Idle,
	Move,
	Attack,
	Death,
	Turn,
	Slime
};

// etc
enum class MainMenuSelect
{
	Start,
	Exit
};