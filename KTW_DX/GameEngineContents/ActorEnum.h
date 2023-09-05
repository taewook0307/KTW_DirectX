#pragma once

enum class CharacterState
{
	Idle,
	Run,
	Jump,
	Dash,
	Fall
};

enum class MiniMapCharacterState
{
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
	Up,
	Down,
	Left,
	Right,
	RightUp,
	LeftUp,
	RightDown,
	LeftDown
};