#pragma once

#include "ParryObject.h"

#define PIRATEBULLETCOLLISIONSCALE { 34.0f, 28.0f }
#define PIRATEBULLETCOLLISIONPOSITION { 17.0f, 0.0f }
#define ADJUSTVALUE 38.0f

class PirateBullet : public ParryObject
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

	void CameraOutCheck();
	void MoveStart();
	void MoveUpdate(float _Delta);

	virtual void HitCheck();
	void DeathStart();

	float Speed = 500.0f;
	EPIRATEBULLETSTATE CurState = EPIRATEBULLETSTATE::None;
	std::string State = "";

	void StateUpdate(float _Delta);
	void ChangeState(EPIRATEBULLETSTATE _CurState);
	virtual void ChangeAnimation(std::string_view _State);

	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineCollision> BulletCollision = nullptr;
private:
};