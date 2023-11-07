#include "PreCompile.h"
#include "GameEngineMesh.h"


GameEngineMesh::GameEngineMesh() 
{
}

GameEngineMesh::~GameEngineMesh() 
{
}

void GameEngineMesh::InputAssembler1()
{
	if (nullptr == VertexBufferPtr)
	{
		MsgBoxAssert("�Ž��� ���õǾ� ���� �ʽ��ϴ�.");
		return;
	}

	VertexBufferPtr->Setting();

	GameEngineCore::GetContext()->IASetPrimitiveTopology(TOPOLOGY);
}

void GameEngineMesh::InputAssembler2()
{
	if (nullptr == IndexBufferPtr)
	{
		MsgBoxAssert("�Ž��� ���õǾ� ���� �ʽ��ϴ�.");
		return;
	}

	IndexBufferPtr->Setting();
}

void GameEngineMesh::Draw()
{
	GameEngineCore::GetContext()->DrawIndexed(IndexBufferPtr->GetIndexCount(), 0, 0);
}