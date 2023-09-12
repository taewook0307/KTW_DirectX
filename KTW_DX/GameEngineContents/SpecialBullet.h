#pragma once

#include "Bullet.h"

class SpecialBullet : public Bullet
{
public:
	// constrcuter destructer
	SpecialBullet();
	~SpecialBullet();

	// delete Function
	SpecialBullet(const SpecialBullet& _Other) = delete;
	SpecialBullet(SpecialBullet&& _Other) noexcept = delete;
	SpecialBullet& operator=(const SpecialBullet& _Other) = delete;
	SpecialBullet& operator=(SpecialBullet&& _Other) noexcept = delete;

protected:
	void ChangeBulletAnimation(std::string_view _State) override;

	void Start() override;
private:
	
};