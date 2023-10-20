#pragma once

#include <GameEngineCore/GameEngineActor.h>

#define TARGETRENDERERPOSITION { 0.0f, 95.0f }
#define TARGETCOLLISIONSCALE { 60.0f, 60.0f }

class TutorialTarget : public GameEngineActor
{
	friend class Bullet;
public:
	// constrcuter destructer
	TutorialTarget();
	~TutorialTarget();

	// delete Function
	TutorialTarget(const TutorialTarget& _Other) = delete;
	TutorialTarget(TutorialTarget&& _Other) noexcept = delete;
	TutorialTarget& operator=(const TutorialTarget& _Other) = delete;
	TutorialTarget& operator=(TutorialTarget&& _Other) noexcept = delete;

protected:

private:
	void CreateExplosionEffect();

	std::shared_ptr<GameEngineSpriteRenderer> MainRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> TargetRenderer = nullptr;

	std::shared_ptr<GameEngineCollision> MainCollision = nullptr;
	std::shared_ptr<GameEngineCollision> TargetCollision = nullptr;

	int HitCount = 0;

	void Start() override;
	void Update(float _Delta) override;

	void PlusHitCount()
	{
		++HitCount;
	}
};