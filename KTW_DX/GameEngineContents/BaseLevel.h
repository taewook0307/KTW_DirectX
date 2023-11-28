#pragma once

class BaseLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BaseLevel();
	~BaseLevel();

	// delete Function
	BaseLevel(const BaseLevel& _Other) = delete;
	BaseLevel(BaseLevel&& _Other) noexcept = delete;
	BaseLevel& operator=(const BaseLevel& _Other) = delete;
	BaseLevel& operator=(BaseLevel&& _Other) noexcept = delete;

protected:
	template<typename ActorType, typename EnumType>
	void AllRemainActorDeath(EnumType _UpdateOrder)
	{
		std::vector<std::shared_ptr<ActorType>> RemainActors = GetObjectGroupConvert<ActorType>(_UpdateOrder);

		if (0 == RemainActors.size())
		{
			return;
		}

		for (size_t i = 0; i < RemainActors.size(); i++)
		{
			RemainActors[i]->Death();
		}
	}

	static GameEngineSoundPlayer BGMPlayer;

private:
	void Start() override;
};