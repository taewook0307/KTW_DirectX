#pragma once

#define BULLETRATIO 0.8f
#define BULLETANIMATIONINTER 0.02f

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

	void SetBulletType(const EBULLETTYPE& _Type)
	{
		Type = _Type;
	}

	void SetBulletDir(const EDIRECTION8& _Dir)
	{
		BulletDir = _Dir;
	}

protected:
	void StateUpdate(float _Delta);
	void ChangeBulletState(EBULLETSTATE _CurState);
	virtual void ChangeBulletAnimation(std::string_view _State);

	void SpawnStart();
	void SpawnUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> BulletRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> BulletCollision = nullptr;

	EBULLETTYPE Type = EBULLETTYPE::Normal;
	EBULLETSTATE CurState = EBULLETSTATE::None;
	std::string State = "";

	EDIRECTION8 BulletDir = EDIRECTION8::None;

	int Att = 4;

	void PosCheck();
	void BulletHitSuccess(std::vector<std::shared_ptr<GameEngineCollision>> _Col);
	void ColCheck();
	bool TargetHit = false;
private:
};