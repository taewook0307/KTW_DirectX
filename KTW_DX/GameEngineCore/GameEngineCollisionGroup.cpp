#include "PreCompile.h"
#include "GameEngineCollisionGroup.h"
#include "GameEngineCollision.h"

GameEngineCollisionGroup::GameEngineCollisionGroup() 
{
}

GameEngineCollisionGroup::~GameEngineCollisionGroup() 
{
}



void GameEngineCollisionGroup::AllReleaseCheck()
{
	std::list<std::shared_ptr<class GameEngineCollision>>::iterator StartIter = Collisions.begin();
	std::list<std::shared_ptr<class GameEngineCollision>>::iterator EndIter = Collisions.end();

	for ( ; StartIter != EndIter; )
	{
		if (false == (*StartIter)->IsDeath())
		{
			++StartIter;
			continue;
		}

		StartIter = Collisions.erase(StartIter);
	}
}



bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Collision)
{
	if (false == _Collision->IsUpdate())
	{
		return false;
	}


	for (std::shared_ptr<class GameEngineCollision> Collision : Collisions)
	{
		if (Collision == _Collision)
		{
			continue;
		}

		if (false == Collision->IsUpdate())
		{
			continue;
		}

		if (true == GameEngineTransform::Collision({ _Collision->Transform.ColData , Collision->Transform.ColData, _Collision->GetCollisionType(), Collision->GetCollisionType() }))
		{
			return true;
		}
	}

	return false;
}

bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Collision, const float4& _NextPos)
{
	if (false == _Collision->IsUpdate())
	{
		return false;
	}

	CollisionData Data = _Collision->Transform.ColData;

	Data.OBB.Center.x += _NextPos.X;
	Data.OBB.Center.y += _NextPos.Y;
	Data.OBB.Center.z += _NextPos.Z;

	for (std::shared_ptr<class GameEngineCollision> Collision : Collisions)
	{
		if (Collision == _Collision)
		{
			continue;
		}

		if (false == Collision->IsUpdate())
		{
			continue;
		}

		if (true == GameEngineTransform::Collision({ Data , Collision->Transform.ColData, _Collision->GetCollisionType(), Collision->GetCollisionType() }))
		{
			return true;
		}
	}

	return false;
}

bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Collision, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function)
{
	if (false == _Collision->IsUpdate())
	{
		return false;
	}


	// static ���������� �����
	// std::list Nodes delete�� �Ѵ�.
	// �����峪 �̷��Ϳ��� ����������
	static std::vector<std::shared_ptr<GameEngineCollision>> ResultCollision;
	ResultCollision.clear();

	for (std::shared_ptr<class GameEngineCollision> Collision : Collisions)
	{
		if (Collision == _Collision)
		{
			continue;
		}

		if (false == Collision->IsUpdate())
		{
			continue;
		}

		if (true == GameEngineTransform::Collision({ _Collision->Transform.ColData , Collision->Transform.ColData, _Collision->GetCollisionType(), Collision->GetCollisionType() }))
		{
			ResultCollision.push_back(Collision);
		}
	}

	if (0 != ResultCollision.size())
	{
		_Function(ResultCollision);
		return true;
	}

	return false;

}


bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Collision, const float4& _NextPos, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function)
{
	if (false == _Collision->IsUpdate())
	{
		return false;
	}

	static std::vector<std::shared_ptr<GameEngineCollision>> ResultCollision;
	ResultCollision.clear();

	CollisionData Data = _Collision->Transform.ColData;

	Data.OBB.Center.x += _NextPos.X;
	Data.OBB.Center.y += _NextPos.Y;
	Data.OBB.Center.z += _NextPos.Z;

	for (std::shared_ptr<class GameEngineCollision> Collision : Collisions)
	{
		if (Collision == _Collision)
		{
			continue;
		}

		if (false == Collision->IsUpdate())
		{
			continue;
		}

		if (true == GameEngineTransform::Collision({ Data , Collision->Transform.ColData, _Collision->GetCollisionType(), Collision->GetCollisionType() }))
		{
			ResultCollision.push_back(Collision);
		}
	}

	if (0 != ResultCollision.size())
	{
		_Function(ResultCollision);
		return true;
	}

	return false;
}


bool GameEngineCollisionGroup::CollisionEvent(std::shared_ptr<GameEngineCollision> _Collision, const EventParameter& _Event)
{
	if (false == _Collision->IsUpdate())
	{
		return false;
	}

	static std::vector<std::shared_ptr<GameEngineCollision>> ResultCollision;
	ResultCollision.clear();

	for (std::shared_ptr<class GameEngineCollision> Collision : Collisions)
	{
		if (Collision == _Collision)
		{
			continue;
		}

		if (false == Collision->IsUpdate())
		{
			continue;
		}

		if (true == GameEngineTransform::Collision({ _Collision->Transform.ColData , Collision->Transform.ColData, _Collision->GetCollisionType(), Collision->GetCollisionType() }))
		{
			ResultCollision.push_back(Collision);
			continue;
		}

		// �ִ� �浹�� ���� ���߳�.
		if (true == _Collision->Others.contains(Collision))
		{
			if (_Event.Exit)
			{
				_Event.Exit(_Collision.get(), Collision.get());
			}

			_Collision->Others.erase(Collision);
		}
	}

	if (0 != ResultCollision.size())
	{
		// ResultCollision ���� �浹�� �ֵ�.
		
		for (size_t i = 0; i < ResultCollision.size(); i++)
		{
			std::shared_ptr<GameEngineCollision> Other = ResultCollision[i];
			if (false == _Collision->Others.contains(Other))
			{
				if (_Event.Enter)
				{
					_Event.Enter(_Collision.get(), Other.get());
				}

				_Collision->Others.insert(Other);
			}
			else 
			{
				if (_Event.Stay)
				{
					_Event.Stay(_Collision.get(), Other.get());
				}
			}
		}

		return true;
	}

	return false;
}

void GameEngineCollisionGroup::PushCollision(std::shared_ptr<GameEngineCollision> _Collision)
{
	if (nullptr == _Collision)
	{
		MsgBoxAssert("�������� �ʴ� �ݸ����� ����Ϸ��� �߽��ϴ�.");
		return;
	}

	Collisions.push_back(_Collision);
}
