#pragma once

#include <GameEngineCore/GameEngineActor.h>

class PirateBullet : public GameEngineActor
{
public:
	// constrcuter destructer
	PirateBullet();
	~PirateBullet();

	// delete Function
	PirateBullet(const PirateBullet& _Other) = delete;
	PirateBullet(PirateBullet&& _Other) noexcept = delete;
	PirateBullet& operator=(const PirateBullet& _Other) = delete;
	PirateBullet& operator=(PirateBullet&& _Other) noexcept = delete;

protected:
	bool DirVectorSet = false;
	float4 DirVector = float4::LEFT;
	float4 PlayerPos = float4::ZERO;

private:
	void CameraOutCheck();
	void MoveStart();
	void MoveUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

	float Speed = 500.0f;
	EPIRATEBULLETSTATE CurState = EPIRATEBULLETSTATE::None;
	std::string State = "";

	void ChangeState(EPIRATEBULLETSTATE _State);
	void StateUpdate(float _Delta);
	virtual void ChangeAnimation(std::string_view _State);

	std::shared_ptr<GameEngineSpriteRenderer> BulletRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> BulletCollision = nullptr;

private:
	void Start() override;
	void Update(float _Delta) override;
};