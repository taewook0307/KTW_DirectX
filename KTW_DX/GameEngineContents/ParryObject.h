#pragma once

class ParryObject : public GameEngineActor
{
public:
	// constrcuter destructer
	ParryObject();
	~ParryObject();

	// delete Function
	ParryObject(const ParryObject& _Other) = delete;
	ParryObject(ParryObject&& _Other) noexcept = delete;
	ParryObject& operator=(const ParryObject& _Other) = delete;
	ParryObject& operator=(ParryObject&& _Other) noexcept = delete;

	// Parry Ȱ��ȭ ����
	void ParryActive()
	{
		ParryActivation = true;
	}

	void ParryInactive()
	{
		ParryActivation = false;
	}

	bool GetParryActivation() const
	{
		return ParryActivation;
	}

	// ĳ���Ϳ� Parry�� �����ߴ��� ����
	void IsParry()
	{
		Parry = true;
	}

	void ParryReset()
	{
		Parry = false;
	}

	bool GetParry() const
	{
		return Parry;
	}

protected:
	bool ParryActivation = true;
	bool Parry = false;

	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> ParryCollision = nullptr;
private:
};