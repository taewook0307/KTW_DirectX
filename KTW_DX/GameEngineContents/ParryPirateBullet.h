#pragma once

#include "PirateBullet.h"
#include "ParryObject.h"

class ParryPirateBullet : public PirateBullet, public ParryObject
{
public:
	// constrcuter destructer
	ParryPirateBullet();
	~ParryPirateBullet();

	// delete Function
	ParryPirateBullet(const ParryPirateBullet& _Other) = delete;
	ParryPirateBullet(ParryPirateBullet&& _Other) noexcept = delete;
	ParryPirateBullet& operator=(const ParryPirateBullet& _Other) = delete;
	ParryPirateBullet& operator=(ParryPirateBullet&& _Other) noexcept = delete;

protected:

private:
	void ChangeAnimation(std::string_view _State) override;

	void Start() override;
	void Update(float _Delta) override;
};