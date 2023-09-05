#pragma once

enum class CharacterState
{
	Idle,
	Run,
	Jump,
	Dash,
	Fall,
	Aim
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
	Straight,
	StraightUp,
	StraightDown,
	Up,
	Down
};