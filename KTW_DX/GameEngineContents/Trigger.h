#pragma once

class Trigger : public GameEngineActor
{
public:
	// constrcuter destructer
	Trigger();
	~Trigger();

	// delete Function
	Trigger(const Trigger& _Other) = delete;
	Trigger(Trigger&& _Other) noexcept = delete;
	Trigger& operator=(const Trigger& _Other) = delete;
	Trigger& operator=(Trigger&& _Other) noexcept = delete;

	void TriggerInit(int _Order, const float4& _Scale = float4::ONE, const float4& _Position = float4::ZERO, const float4& _Rotation = float4::ZERO);

	template <typename ENUMTYPE>
	void TriggerInit(ENUMTYPE _Order, const float4& _Scale = float4::ONE, const float4& _Position = float4::ZERO, const float4& _Rotation = float4::ZERO)
	{
		TriggerInit(static_cast<int>(_Order), _Scale, _Position, _Rotation);
	}

protected:

private:
	std::shared_ptr<GameEngineCollision> TriggerCollision = nullptr;
};