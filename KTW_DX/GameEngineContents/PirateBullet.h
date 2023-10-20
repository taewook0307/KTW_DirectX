#pragma once

#include "ParryObject.h"

#define PIRATEBULLETCOLLISIONSCALE { 34.0f, 28.0f }
#define PIRATEBULLETCOLLISIONPOSITION { 17.0f, 0.0f }
#define ADJUSTVALUE 60.0f

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
	float Speed = 500.0f;
	bool DirVectorSet = false;
	float4 DirVector = float4::LEFT;
	float4 PlayerPos = float4::ZERO;

	void PirateMove(float _Delta);
	void CameraOutCheck();
	virtual void HitCheck();

	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineCollision> BulletCollision = nullptr;

	GameEngineState PirateBulletState;
private:
};