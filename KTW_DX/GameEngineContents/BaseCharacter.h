#pragma once
#include "BaseActor.h"

#define CHARACTERANIMATIONINTER 0.04f
#define IDLEINTER 0.08f

#define SPEED 400.0f
#define JUMPPOWER 1400.0f
#define SHOOTTIMER 0.2f
#define NODAMAGETIMER 2.0f

#define LEFTCHECKPOS { -20.0f, 40.0f }
#define RIGHTCHECKPOS { 20.0f, 40.0f }

#define CHARACTERCOLLISIONSCALE { 70.0f, 110.0f }
#define CHARACTERCOLLISIONPOS { 0.0f, 67.0f }

#define CHARACTERDUCKCOLLISIONSCALE { 140.0f, 60.0f }
#define CHARACTERDUCKCOLLISIONPOS { 0.0f, 30.0f }

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

	bool GetParrySuccess() const
	{
		return ParrySuccess;
	}

	bool GetCheat() const
	{
		return Cheat;
	}

	void CheatSwitch()
	{
		Cheat = !Cheat;
	}

	void ParrySuccessReset()
	{
		ParrySuccess = false;
	}
	
	ECHARACTERSTATE GetCurState() const
	{
		return CurState;
	}

protected:
	void DirChange();
	void AimDirChange();
	void CharacterMove(float _Delta);
	void ActorGravity(float _Delta, float4 _CheckPos) override;

	void CreateRunDust();
	void CreateJumpDust();
	void CreateDashDust(EACTORDIR _DustDir);
	void CreateParryEffect();
	void CreateSpecialDust(EDIRECTION8 _DustDirection);
protected:
	void StateUpdate(float _Delta);
	void ChangeState(ECHARACTERSTATE _CurState);
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

	void HitStart();
	void HitUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;

	EACTORDIR Dir = EACTORDIR::None;
	ECHARACTERAIMDIR AimDir = ECHARACTERAIMDIR::None;
	ECHARACTERSTATE CurState = ECHARACTERSTATE::None;
	std::string State = "";

	int Hp = 3;
	float Speed = SPEED;
	float DashSpeed = Speed * 2.0f;

	void ShootBaseState();
	void ShootAimState();
	void ShootRunState();
	void ShootDuckState();
	void SpecialShootState();

	float ShootTimer = SHOOTTIMER;
	bool Shoot = false;

	float NoDamageTimer = NODAMAGETIMER;
	bool NoDamage = false;

	bool StoolPass = false;

	bool ParrySuccess = false;

	bool Cheat = true;
private:
	std::shared_ptr<GameEngineSpriteRenderer> PlayerRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> PlayerCollision = nullptr;
};