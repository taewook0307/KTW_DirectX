#pragma once
#include "BaseActor.h"

#define JUMPPOWER 1200.0f
#define SHOOTTIMER 0.2f

#define LEFTCHECKPOS { -20.0f, 40.0f }
#define RIGHTCHECKPOS { 20.0f, 40.0f }

class BaseCharacter : public BaseActor
{
public:
	// constrcuter destructer
	BaseCharacter();
	~BaseCharacter();

	// delete Function
	BaseCharacter(const BaseCharacter& _Other) = delete;
	BaseCharacter(BaseCharacter&& _Other) noexcept = delete;
	BaseCharacter& operator=(const BaseCharacter& _Other) = delete;
	BaseCharacter& operator=(BaseCharacter&& _Other) noexcept = delete;

protected:
	void DirChange();
	void AimDirChange();
	void CharacterMove(float _Delta);
	void CharacterGravity(float _Delta, float4 _CheckPos);

protected:
	void ChangeState(CharacterState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimation(std::string_view _State);

	void IntroStart();
	void IntroUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

	void JumpStart();
	void JumpUpdate(float _Delta);

	void DashStart();
	void DashUpdate(float _Delta);

	void FallStart();
	void FallUpdate(float _Delta);

	void DuckStart();
	void DuckUpdate(float _Delta);

	void AimStart();
	void AimUpdate(float _Delta);

	void ShootStart();
	void ShootUpdate(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;

	CharacterDir Dir = CharacterDir::None;
	CharacterAimDir AimDir = CharacterAimDir::None;
	CharacterState CurState = CharacterState::Idle;
	std::string State = "";

	float Speed = 300.0f;
	float DashSpeed = 600.0f;


	float ShootTimer = SHOOTTIMER;
	bool Shoot = false;
private:
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer = nullptr;
};