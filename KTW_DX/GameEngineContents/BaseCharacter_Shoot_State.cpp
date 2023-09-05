#include "PreCompile.h"
#include "BaseCharacter.h"

void BaseCharacter::AimStart()
{
	ChangeAnimation("Aim");
}

void BaseCharacter::AimUpdate(float _Delta)
{
	DirChange();
	AimDirChange();

	if (true == GameEngineInput::IsFree('C'))
	{
		ChangeState(CharacterState::Idle);
		return;
	}
}