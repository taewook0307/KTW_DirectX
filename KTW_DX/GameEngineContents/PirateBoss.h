#pragma once

#include "BaseBoss.h"

class PirateBoss : public BaseBoss
{
public:
	// constrcuter destructer
	PirateBoss();
	~PirateBoss();

	// delete Function
	PirateBoss(const PirateBoss& _Other) = delete;
	PirateBoss(PirateBoss&& _Other) noexcept = delete;
	PirateBoss& operator=(const PirateBoss& _Other) = delete;
	PirateBoss& operator=(PirateBoss&& _Other) noexcept = delete;

protected:

private:

};