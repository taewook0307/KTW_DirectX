#pragma once

#include "BaseBoss.h"

class FirstBossPhase3 : public BaseBoss
{
public:
	// constrcuter destructer
	FirstBossPhase3();
	~FirstBossPhase3();

	// delete Function
	FirstBossPhase3(const FirstBossPhase3& _Other) = delete;
	FirstBossPhase3(FirstBossPhase3&& _Other) noexcept = delete;
	FirstBossPhase3& operator=(const FirstBossPhase3& _Other) = delete;
	FirstBossPhase3& operator=(FirstBossPhase3&& _Other) noexcept = delete;

protected:

private:

};