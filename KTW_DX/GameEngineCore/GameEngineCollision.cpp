﻿#include "PreCompile.h"
#include "GameEngineCollision.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineCollisionGroup.h"

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}

void GameEngineCollision::Start()
{
	GetActor()->GetLevel()->PushCollision(GetDynamic_Cast_This<GameEngineCollision>());
}

bool GameEngineCollision::Collision(int _Order)
{
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->Collisions[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>());
}

bool GameEngineCollision::Collision(int _Order, const float4& _NextPos)
{
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->Collisions[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>(), _NextPos);
}

bool GameEngineCollision::Collision(int _Order, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Collision)
{
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->Collisions[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>(), _Collision);
}

bool GameEngineCollision::Collision(int _Order, const float4& _Next, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Collision)
{
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->Collisions[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>(), _Next, _Collision);
}

bool GameEngineCollision::CollisionEvent(int _Order, const EventParameter& _Event)
{
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->Collisions[_Order];
	return OtherGroup->CollisionEvent(GetDynamic_Cast_This<GameEngineCollision>(), _Event);
}

void GameEngineCollision::Release()
{
	// 내가 지금 사라질것인데. 예전에 나랑 충돌했던 충돌체들에게
	// 내가 죽으니 날 굳이 들고 있을 필요가 없다.
	for (GameEngineCollision* Collision : Others)
	{
		Collision->Others.erase(this);
	}
}