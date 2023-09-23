#pragma once

#include "ParryObject.h"

class FirstMapParryObject : public ParryObject
{
public:
	// constrcuter destructer
	FirstMapParryObject();
	~FirstMapParryObject();

	// delete Function
	FirstMapParryObject(const FirstMapParryObject& _Other) = delete;
	FirstMapParryObject(FirstMapParryObject&& _Other) noexcept = delete;
	FirstMapParryObject& operator=(const FirstMapParryObject& _Other) = delete;
	FirstMapParryObject& operator=(FirstMapParryObject&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};