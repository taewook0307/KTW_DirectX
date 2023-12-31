#pragma once

enum class EACTORDIR
{
	None,
	Left,
	Right
};

// WorldMap
enum class EWORLDMAPSTATE
{
	Idle,
	IslandPortalCreate,
	DevilIslandPortalCreate,
	ToIdle
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
	Scared,
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

enum class EWORLDMAPCHARACTERSTATE
{
	None,
	Idle,
	Run,
	Clear
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
	Fall,
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
	Whistle,
	Death
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
	Attack,
	Wince,
	Transform,
	Charge,
	Beam,
	Death
};

enum class ESHIPBUBBLESTATE
{
	None,
	Appear,
	Move,
	Pop
};

enum class ESHIPBEAMSTATE
{
	None,
	Appear,
	End
};

// Devil
enum class EDEVILSTATE
{
	None,
	Intro,
	Idle,
	Attack,
	AttackStay,
	AttackEnd,
	Ram,
	Serpent,
	Spider,
	Death
};

enum class EDEVILARMSTATE
{
	Move,
	Clap,
	MoveBack
};

enum class ESPIDERHEADSTATE
{
	JumpStart,
	Jump,
	JumpToFall,
	Fall,
	Land
};

enum class ESERPENTSTATE
{
	Move,
	Back
};

enum class ESUMMONATTACKOBJECTSTATE
{
	Spawn,
	Idle,
	Move,
	Death
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

enum class EDOGFISHSTATE
{
	None,
	Jump,
	Landing,
	Move,
	Death
};

enum class ESUMMONDEVILSTATE
{
	Intro,
	Appear,
	Move,
	ComeBack,
	Death
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

enum class EWorldMapFlag
{
	Appear,
	Rise,
	Stay
};