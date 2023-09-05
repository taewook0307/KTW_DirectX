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
	Up,
	Down,
	Left,
	Right,
	RightUp,
	LeftUp,
	RightDown,
	LeftDown
};