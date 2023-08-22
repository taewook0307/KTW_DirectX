#include "PreCompile.h"
#include "GameEngineDevice.h"
#include "GameEngineTransform.h"

#include "GameEngineVertex.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineShader.h"
#include "GameEngineRasterizer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineConstantBuffer.h"

void GameEngineDevice::ResourcesInit()
{

	// �������ؿ��� �������ִ� ���� �������� ���ҽ����� ���⿡�� ������� �̴ϴ�.
	// �⺻ �Ž�
	// �⺻ �ؽ�ó
	// �⺻ ���̴�
	// ���⿡�� �ڱ� �ؽ�ó �ε�����������.

	{
		// ������ ���̴��� ���δ� ���δ� �ε��ϴ� �ڵ带 ģ��.
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineCoreShader");
		Dir.MoveChild("GameEngineCoreShader");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fx" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
			GameEngineFile& File = Files[i];
			GameEngineShader::AutoCompile(File);
		}
	}


	{
		std::vector<GameEngineVertex2D> Vertex;
		Vertex.resize(4 * 6);

		GameEngineVertex2D BaseVertexs[4];

		BaseVertexs[0] = { { -0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[1] = { { 0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[2] = { { 0.5f, 0.5f, -0.5f, 1.0f } };
		BaseVertexs[3] = { { -0.5f, 0.5f, -0.5f, 1.0f } };

		// �ո�
		Vertex[0] = BaseVertexs[0];
		Vertex[1] = BaseVertexs[1];
		Vertex[2] = BaseVertexs[2];
		Vertex[3] = BaseVertexs[3];

		// �޸�
		Vertex[4].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, 180.0f);
		Vertex[5].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, 180.0f);
		Vertex[6].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, 180.0f);
		Vertex[7].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, 180.0f);

		// �����̳� ������
		Vertex[8].POSITION = float4::VectorRotationToDegY(BaseVertexs[0].POSITION, 90.0f);
		Vertex[9].POSITION = float4::VectorRotationToDegY(BaseVertexs[1].POSITION, 90.0f);
		Vertex[10].POSITION = float4::VectorRotationToDegY(BaseVertexs[2].POSITION, 90.0f);
		Vertex[11].POSITION = float4::VectorRotationToDegY(BaseVertexs[3].POSITION, 90.0f);

		// �����̳� ������
		Vertex[12].POSITION = float4::VectorRotationToDegY(BaseVertexs[0].POSITION, -90.0f);
		Vertex[13].POSITION = float4::VectorRotationToDegY(BaseVertexs[1].POSITION, -90.0f);
		Vertex[14].POSITION = float4::VectorRotationToDegY(BaseVertexs[2].POSITION, -90.0f);
		Vertex[15].POSITION = float4::VectorRotationToDegY(BaseVertexs[3].POSITION, -90.0f);

		// ���ų� �Ʒ�
		Vertex[16].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, 90.0f);
		Vertex[17].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, 90.0f);
		Vertex[18].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, 90.0f);
		Vertex[19].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, 90.0f);

		Vertex[20].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, -90.0f);
		Vertex[21].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, -90.0f);
		Vertex[22].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, -90.0f);
		Vertex[23].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, -90.0f);

		GameEngineVertexBuffer::Create("Box", Vertex);
	}

	{
		std::vector<GameEngineVertex2D> Vertex;
		Vertex.resize(4);

		Vertex[0] = { { -0.5f, -0.5f, 0.0f, 1.0f } };
		Vertex[1] = { { 0.5f, -0.5f, 0.0f, 1.0f } };
		Vertex[2] = { { 0.5f, 0.5f, 0.0f, 1.0f } };
		Vertex[3] = { { -0.5f, 0.5f, 0.0f, 1.0f } };

		GameEngineVertexBuffer::Create("Rect", Vertex);


		std::vector<unsigned int> Index =
		{
			0, 1, 2,
			0, 2, 3
		};

		GameEngineIndexBuffer::Create("Rect", Index);
	}

	{
		std::vector<GameEngineVertex2D> Vertex;
		Vertex.resize(4);

		Vertex[0] = { { -1.0f, -1.0f, 0.0f, 1.0f } };
		Vertex[1] = { { 1.0f, -1.0f, 0.0f, 1.0f } };
		Vertex[2] = { { 1.0f, 1.0f, 0.0f, 1.0f } };
		Vertex[3] = { { -1.0f, 1.0f, 0.0f, 1.0f } };

		GameEngineVertexBuffer::Create("FullRect", Vertex);


		std::vector<unsigned int> Index =
		{
			0, 1, 2,
			0, 2, 3
		};

		GameEngineIndexBuffer::Create("FullRect", Index);
	}

	// ���߿� ���������
	{
		// �ణ�����Ҽ� �ִ�.
		// �׷���ī�忡���� ����Ʈ �е� ��Ģ�� 
		// sizeof(TransformData) ����Ʈ�е� ��Ģ��
		// �޶� �׸��� �ٸ��ٰ� �ν��Ҽ� �ִ�. 
		// �����ؾ� �Ѵ�.
		GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData", ShaderType::Vertex, 0);
	}

	{

		//D3D11_FILL_MODE FillMode;
		// ������ �Ҷ� ä��� ��带 �����Ѵ�.

		// �����ߴµ� z������ ����?
		// D3D11_CULL_NONE => ������ ���� ��������.
		// D3D11_CULL_BACK => z�� ������ �ȼ����� �Ȱ��� ����.
		// D3D11_CULL_FRONT => z�� ������ �ȼ����� �Ȱ��� ����.
		// 
		// 0, 1, 2,
		// 0, 2, 3
		// �ε��� ������ �׸��� ������ ������ ũ��.

		// �̳༮�� �ε��� ����

		//D3D11_CULL_MODE CullMode;
		//BOOL FrontCounterClockwise;
		//INT DepthBias;
		//FLOAT DepthBiasClamp;
		//FLOAT SlopeScaledDepthBias;
		//BOOL DepthClipEnable;
		//BOOL ScissorEnable;
		//BOOL MultisampleEnable;
		//BOOL AntialiasedLineEnable;

		D3D11_RASTERIZER_DESC Desc = {};
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		// Desc.DepthClipEnable = TRUE;
		std::shared_ptr<GameEngineRasterizer> Rasterizer = GameEngineRasterizer::Create("EngineRasterizer", Desc);
	}
}