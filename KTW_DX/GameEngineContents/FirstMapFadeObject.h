#pragma once

#include "ParryObject.h"

class FirstMapFadeObject : public ParryObject
{
public:
	// constrcuter destructer
	FirstMapFadeObject();
	~FirstMapFadeObject();

	// delete Function
	FirstMapFadeObject(const FirstMapFadeObject& _Other) = delete;
	FirstMapFadeObject(FirstMapFadeObject&& _Other) noexcept = delete;
	FirstMapFadeObject& operator=(const FirstMapFadeObject& _Other) = delete;
	FirstMapFadeObject& operator=(FirstMapFadeObject&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};