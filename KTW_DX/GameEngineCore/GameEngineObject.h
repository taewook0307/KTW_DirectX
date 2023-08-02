#pragma once
#include "GameEngineTransform.h"

// �츮������ ���� �⺻����
// Start �̳༮�� ���۵ɶ�
// Update �̳༮�� ������Ʈ�ɶ�
// Release �̳༮�� ��������

// ���� :
class GameEngineObject
{
	friend class GameEngineLevel;
	friend class GameEngineCore;

public:
	// constrcuter destructer
	GameEngineObject();
	virtual ~GameEngineObject();

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	virtual void Start() {}
	virtual void Update(float _Delta) {}
	virtual void Release() {}


	virtual void On()
	{
		IsUpdateValue = true;
	}

	virtual void Off()
	{
		IsUpdateValue = false;
	}

	void Death()
	{
		this->IsDeathValue = true;
	}

	virtual bool IsUpdate()
	{
		return Parent == nullptr ? true == IsUpdateValue && false == IsDeathValue : Parent->IsUpdate() && true == IsUpdateValue && false == IsDeathValue;
	}

	virtual bool IsDeath()
	{
		return Parent == nullptr ? IsDeathValue : Parent->IsDeathValue && IsDeathValue;
	}

	int GetOrder()
	{
		return Order;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	float GetLiveTime()
	{
		return LiveTime;
	}

	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}

	void SetName(const std::string& _Name)
	{
		Name = _Name;
	}

	std::string GetName()
	{
		return Name;
	}

	template<typename ObjectType>
	std::shared_ptr<ObjectType> CreateChild(int _Order = 0)
	{
		std::shared_ptr<class GameEngineObject> NewChild = std::make_shared<ObjectType>();

		NewChild->Start();
		NewChild->Parent = this;
		Childs[_Order].push_back(NewChild);

		// GameEngineObject������ ����ϰ� �ִٸ�
		// ���� �߸�����ȯ�ϸ� Monster ���µ�? Player <= ��ģ���� �޸� ũ���ø� ����ŵ�ϴ�.
		// �̳༮�� ������ ������ �˼� ���� ������??????
		// �������Ͱ� ��Ӱ����� �ְ� �����Լ� ���̺��� ������ �ִٸ�
		// dynamic_cast�� ���ؼ� �����ϰ� ����ȯ�� �����ϴ�.
		// std::shared_ptr ��¥ �����ʹ� �ƴϱ� ������ dynamic_cast �ؾ��� ��Ȳ����
		// �Ʒ��� ���� �Լ��� ����ϸ� �ȴ�.
		return std::dynamic_pointer_cast<ObjectType>(NewChild);
	}

	virtual void AllUpdate(float _Delta);

protected:
	GameEngineObject* Parent;

	// �������� ���ؼ�
	std::map<int, std::list<std::shared_ptr<class GameEngineObject>>> Childs;


private:
	GameEngineTransform Transform;

	std::string Name;
	float LiveTime = 0.0f;
	int Order = 0;
	bool IsUpdateValue = true; // �̰� false�� ����� �˴ϴ�.
	bool IsDeathValue = false; // �ƿ� �޸𸮿��� ���������� �;�.

	void AddLiveTime(float _DeltaTime)
	{
		LiveTime += _DeltaTime;
	}

};

