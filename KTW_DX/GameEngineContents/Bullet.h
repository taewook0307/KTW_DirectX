#pragma once

#include <GameEngineCore/GameEngineActor.h>

class Bullet : public GameEngineActor
{
public:
	// constrcuter destructer
	Bullet();
	~Bullet();

	// delete Function
	Bullet(const Bullet& _Other) = delete;
	Bullet(Bullet&& _Other) noexcept = delete;
	Bullet& operator=(const Bullet& _Other) = delete;
	Bullet& operator=(Bullet&& _Other) noexcept = delete;

	void SetBulletType(BulletType _Type)
	{
		Type = _Type;
	}

protected:
	void ChangeBulletState(BulletState _State);
	void StateUpdate(float _Delta);
	void ChangeBulletAnimation(std::string_view _State);

	void SpawnStart();
	void SpawnUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> BulletRenderer = nullptr;
	BulletType Type = BulletType::Normal;
	BulletState CurState = BulletState::None;
	std::string State = "";
};