#pragma once

#include "PirateBullet.h"

class PirateBulletParry : public PirateBullet
{
public:
	// constrcuter destructer
	PirateBulletParry();
	~PirateBulletParry();

	// delete Function
	PirateBulletParry(const PirateBulletParry& _Other) = delete;
	PirateBulletParry(PirateBulletParry&& _Other) noexcept = delete;
	PirateBulletParry& operator=(const PirateBulletParry& _Other) = delete;
	PirateBulletParry& operator=(PirateBulletParry&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void ChangeAnimation(std::string_view _State) override;

	void HitCheck() override;
};