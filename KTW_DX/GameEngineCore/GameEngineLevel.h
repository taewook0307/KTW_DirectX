#pragma once
#include "GameEngineObject.h"

// ���� :
// class GameEngineActor; �̷����ǰ�
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCore;

public:
	// constrcuter destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:

private:
	// LevelChange�� ��������
	// ���� ���� �����̸� LevelStart
	// ���� �׷� End
	virtual void LevelStart(GameEngineLevel* _PrevLevel) {}
	virtual void LevelEnd(GameEngineLevel* _NextLevel) {}

	// ���Ͱ��� ��ɵ�
	void AllUpdate(float _Delta) override;

	void Render(float _Delta);

	void ActorRelease();

	std::map<int, std::shared_ptr<class GameEngineCamera>> Cameras;

	//// �׳� 
	// std::map<int, std::list<std::shared_ptr<class GameEngineActor>>> AllActors;
};

