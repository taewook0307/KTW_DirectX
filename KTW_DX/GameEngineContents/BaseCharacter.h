#pragma once
#include "BaseActor.h"

#define CHARACTERANIMATIONINTER 0.04f
#define IDLEINTER 0.08f

#define JUMPPOWER 1400.0f
#define SHOOTTIMER 0.2f
#define SPEED 400.0f

#define LEFTCHECKPOS { -20.0f, 40.0f }
#define RIGHTCHECKPOS { 20.0f, 40.0f }

class BaseCharacter : public BaseActor
{
public:
	static BaseCharacter* MainCharacter;

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

	void AimShootStart();
	void AimShootUpdate(float _Delta);

	void RunShootStart();
	void RunShootUpdate(float _Delta);

	void DuckShootStart();
	void DuckShootUpdate(float _Delta);

	void ParryStart();
	void ParryUpdate(float _Delta);

	void SpecialAttackStart();
	void SpecialAttackUpdate(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;

	ActorDir Dir = ActorDir::None;
	CharacterAimDir AimDir = CharacterAimDir::None;
	CharacterState CurState = CharacterState::None;
	std::string State = "";

	float Speed = SPEED;
	float DashSpeed = Speed * 2.0f;

	void ShootBaseState();
	void ShootAimState();
	void ShootRunState();
	void ShootDuckState();
	void SpecialShootState();

	float ShootTimer = SHOOTTIMER;
	bool Shoot = false;

	bool StoolPass = false;

	bool ParrySuccess = false;

	bool Cheat = false;
private:
	std::shared_ptr<GameEngineSpriteRenderer> PlayerRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> PlayerCollision = nullptr;
};