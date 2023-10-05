#pragma once

enum class EACTORDIR
{
	None,
	Left,
	Right
};

// Character
enum class ECHARACTERAIMDIR
{
	None,
	Straight,
	StraightUp,
	StraightDown,
	Up,
	Down
};

enum class ECHARACTERSTATE
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

enum class EMINIMAPCHARACTERSTATE
{
	None,
	Idle,
	Run
};

// Bullet
enum class EBULLETTYPE
{
	Normal
};

enum class EBULLETSTATE
{
	None,
	Spawn,
	Move,
	Death
};

enum class EDIRECTION8
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

// First Boss
enum class EBOSSPHASE
{
	Phase1,
	Phase2,
	Phase3
};

enum class EBOSSSTATE
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

// Second Boss
enum class EPIRATEBOSSSTATE
{
	None,
	Intro,
	Idle,
	Shoot,
	Knockout,
	Whistle
};

enum class EPIRATEBULLETSTATE
{
	None,
	Move,
	Death
};

enum class ESHIPBOSSSTATE
{
	None,
	Idle,
	Attack
};

//Enemy
enum class EBARRELSTATE
{
	None,
	Idle,
	SmashReady,
	Drop,
	Smash,
	SmashEnd
};

enum class ESHARKSTATE
{
	None,
	Fin,
	Entry,
	Bite,
	Leave
};

// etc
enum class EMAINMENUSELECT
{
	Start,
	Exit
};

enum class ESTAGERESULT
{
	None,
	Success,
	Fail
};