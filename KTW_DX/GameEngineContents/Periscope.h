#pragma once

#include "BaseSummonActor.h"

#define SUMMONPOS { 1050.0f, -720.0f }
#define SUMMONTIMER 3.0f

class Periscope : public BaseSummonActor
{
public:
	// constrcuter destructer
	Periscope();
	~Periscope();

	// delete Function
	Periscope(const Periscope& _Other) = delete;
	Periscope(Periscope&& _Other) noexcept = delete;
	Periscope& operator=(const Periscope& _Other) = delete;
	Periscope& operator=(Periscope&& _Other) noexcept = delete;

protected:

private:
	int SummonCount = 4;
	float SummonTimer = 0.0f;

	bool SummonStart = false;

	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> PeriscopeRenderer = nullptr;
};