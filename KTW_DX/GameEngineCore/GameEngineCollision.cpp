#include "PreCompile.h"
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
	if (false == GetLevel()->Collisions.contains(_Order))
	{
		return false;
	}
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->Collisions[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>());
}

bool GameEngineCollision::Collision(int _Order, const float4& _NextPos)
{
	if (false == GetLevel()->Collisions.contains(_Order))
	{
		return false;
	}
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->Collisions[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>(), _NextPos);
}

bool GameEngineCollision::Collision(int _Order, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Collision)
{
	if (false == GetLevel()->Collisions.contains(_Order))
	{
		return false;
	}
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->Collisions[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>(), _Collision);
}

bool GameEngineCollision::Collision(int _Order, const float4& _Next, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Collision)
{
	if (false == GetLevel()->Collisions.contains(_Order))
	{
		return false;
	}
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->Collisions[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>(), _Next, _Collision);
}

bool GameEngineCollision::CollisionLineEvent(int _Order, float4 _EndLine, const EventParameter& _Event)
{
	if (false == GetLevel()->Collisions.contains(_Order))
	{
		return false;
	}
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->Collisions[_Order];

	std::set<std::shared_ptr<GameEngineCollision>>::iterator Start = Others.begin();
	std::set<std::shared_ptr<GameEngineCollision>>::iterator End = Others.end();

	for (; Start != End; )
	{
		std::shared_ptr<GameEngineCollision> OtherCol = *Start;

		// ���⼭ �������̴�.
		if (false == OtherCol->IsDeath())
		{
			++Start;
			continue;
		}

		Start = Others.erase(Start);
	}

	// ������ ���� extents�� end�� ������ ����.
	Transform.ColData.OBB.Extents = _EndLine.Float3;

	return OtherGroup->CollisionEvent(GetDynamic_Cast_This<GameEngineCollision>(), _Event);
}

bool GameEngineCollision::CollisionEvent(int _Order, const EventParameter& _Event)
{
	if (false == GetLevel()->Collisions.contains(_Order))
	{
		return false;
	}
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->Collisions[_Order];

	std::set<std::shared_ptr<GameEngineCollision>>::iterator Start = Others.begin();
	std::set<std::shared_ptr<GameEngineCollision>>::iterator End = Others.end();

	for (; Start != End; )
	{
		std::shared_ptr<GameEngineCollision> OtherCol = *Start;

		// ���⼭ �������̴�.
		if (false == OtherCol->IsDeath())
		{
			++Start;
			continue;
		}

		Start = Others.erase(Start);
	}


	return OtherGroup->CollisionEvent(GetDynamic_Cast_This<GameEngineCollision>(), _Event);
}

void GameEngineCollision::Release()
{
	// ���� ���� ��������ε�. ������ ���� �浹�ߴ� �浹ü�鿡��
	// ���� ������ �� ���� ��� ���� �ʿ䰡 ����.
	//for (std::shared_ptr<GameEngineCollision> Collision : Others)
	//{
	//	Collision->Others.erase(GetDynamic_Cast_This<GameEngineCollision>());
	//}
}

void GameEngineCollision::Update(float _Delta)
{
	// �Լ��� ȣ��Ǵ°� ������ �̹� ó���� �Ѱ̴ϴ�.
	if (true == GameEngineLevel::IsDebug)
	{
		switch (CollisionType)
		{
		case ColType::SPHERE2D:
			GameEngineDebug::DrawSphere2D(Transform);
			break;
		case ColType::AABBBOX2D:
			GameEngineDebug::DrawBox2D(Transform);
			break;
		case ColType::OBBBOX2D:
			GameEngineDebug::DrawBox2D(Transform);
			break;
		case ColType::SPHERE3D:
			GameEngineDebug::DrawSphere2D(Transform);
			break;
		case ColType::AABBBOX3D:
			GameEngineDebug::DrawBox2D(Transform);
			break;
		case ColType::OBBBOX3D:
			GameEngineDebug::DrawBox2D(Transform);
			break;
		case ColType::MAX:
			break;
		default:
			break;
		}
	}
}