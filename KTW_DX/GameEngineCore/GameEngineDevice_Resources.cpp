#include "PreCompile.h"
#include "GameEngineDevice.h"
#include "GameEngineTransform.h"

#include "GameEngineVertex.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineShader.h"
#include "GameEngineRasterizer.h"
#include "GameEngineSampler.h"
#include "GameEngineVertexShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSprite.h"
#include "GameEngineBlend.h"
#include "GameEngineMesh.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineMaterial.h"
#include "GameEngineFont.h"
#include "GAMEENGINERENDERTARGET.H"

void GameEngineDevice::ResourcesInit()
{
	GameEngineFont::Load("����");

	{
		// ������ ���̴��� ���δ� ���δ� �ε��ϴ� �ڵ带 ģ��.
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("GameEngineResources");
		Dir.MoveChild("Textrure");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("NSet.png");

	}

	{
		std::vector<GameEngineVertex> Vertex;
		Vertex.resize(3);

		Vertex[0] = { { 1.0f, 0.0f, 0.0f, 1.0f } };
		Vertex[1] = { { 0.0f, 0.0f, 0.0f, 1.0f } };

		GameEngineVertexBuffer::Create("Line", Vertex);

		std::vector<unsigned int> Index =
		{
			0, 1
		};
		GameEngineIndexBuffer::Create("Line", Index);

		std::shared_ptr<GameEngineMesh> LineMesh = GameEngineMesh::Create("Line");
		LineMesh->SetTOPOLOGY(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		// LineMesh->SetTOPOLOGY(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	{
		std::vector<GameEngineVertex> Vertex;
		Vertex.resize(4 * 6);

		GameEngineVertex BaseVertexs[4];

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


	// Sphere
		// ���Ǿ�
	{
		GameEngineVertex V;
		std::vector<GameEngineVertex> VBVector;
		std::vector<UINT> IBVector;

		float Radius = 0.5f;
		// �ϱ������� �����մϴ�.
		V.POSITION = float4(0.0f, Radius, 0.0f, 1.0f);
		V.TEXCOORD = float4(0.5f, 0.0f);
		// �븻 ���� Ȥ�� �������Ͷ�� �Ҹ���
		// �鿡 ������ ���͸� �ǹ��ϰ� �ȴ�.
		// ���� �ݻ��Ҷ� �ʼ�.
		V.NORMAL = float4(0.0f, Radius, 0.0f, 1.0f);
		V.NORMAL.Normalize();
		V.NORMAL.W = 0.0f;
		V.TANGENT = float4(1.0f, 0.0f, 0.0f, 0.0f);
		V.BINORMAL = float4(0.0f, 0.0f, 1.0f, 0.0f);

		VBVector.push_back(V);

		UINT iStackCount = 16; // ���� ���� �����Դϴ�.
		UINT iSliceCount = 16; // ���κ��� ����

		float yRotAngle = GameEngineMath::PI / (float)iStackCount;
		float zRotAngle = (GameEngineMath::PI * 2) / (float)iSliceCount;

		// UV�� ���μ��� ���ݰ��� ���Ѵ�.
		float yUvRatio = 1.0f / (float)iStackCount;
		float zUvRatio = 1.0f / (float)iStackCount;

		for (UINT y = 1; y < iStackCount; ++y)
		{
			// �� ���ݿ� ���� ������
			float phi = y * yRotAngle;
			for (UINT z = 0; z < iSliceCount + 1; ++z)
			{
				float theta = z * zRotAngle;
				V.POSITION = float4{
					Radius * sinf(y * yRotAngle) * cosf(z * zRotAngle),
					Radius * cosf(y * yRotAngle),
					Radius * sinf(y * yRotAngle) * sinf(z * zRotAngle),
					1.0f // ��ġ ũ�� ���� ������ �ֱ� ���ؼ�
				};

				// V.Pos *= GameEngineRandom::RandomFloat(-0.9f, 0.1f);

				V.TEXCOORD = float4(yUvRatio * z, zUvRatio * y);
				V.NORMAL = V.POSITION.NormalizeReturn();
				V.NORMAL.W = 0.0f;

				V.TANGENT.X = -Radius * sinf(phi) * sinf(theta);
				V.TANGENT.Y = 0.0f;
				V.TANGENT.Z = Radius * sinf(phi) * cosf(theta);
				V.TANGENT = V.TANGENT.NormalizeReturn();
				V.TANGENT.W = 0.0f;

				V.BINORMAL = float4::Cross3D(V.TANGENT, V.NORMAL);
				V.BINORMAL = V.BINORMAL.NormalizeReturn();
				V.BINORMAL.W = 0.0f;


				VBVector.push_back(V);
			}
		}

		// ������
		V.POSITION = float4(0.0f, -Radius, 0.0f, 1.0f);
		V.TEXCOORD = float4(0.5f, 1.0f);
		V.NORMAL = float4(0.0f, -Radius, 0.0f, 1.0f);
		V.NORMAL.Normalize();
		V.NORMAL.W = 0.0f;
		V.TANGENT = float4(-1.0f, 0.0f, 0.0f, 0.0f);
		V.BINORMAL = float4(0.0f, 0.0f, -1.0f, 0.0f);
		VBVector.push_back(V);

		// �ε��� ���۸� ����ϴ�.
		IBVector.clear();

		// �ϱ����� �̷�� ���� ����°�.
		for (UINT i = 0; i < iSliceCount; i++)
		{
			// ������ ������ �ϱ���
			IBVector.push_back(0);
			IBVector.push_back(i + 2);
			IBVector.push_back(i + 1);
		}

		for (UINT y = 0; y < iStackCount - 2; y++)
		{
			for (UINT z = 0; z < iSliceCount; z++)
			{
				IBVector.push_back((iSliceCount + 1) * y + z + 1);
				IBVector.push_back((iSliceCount + 1) * (y + 1) + (z + 1) + 1);
				IBVector.push_back((iSliceCount + 1) * (y + 1) + z + 1);

				IBVector.push_back((iSliceCount + 1) * y + z + 1);
				IBVector.push_back((iSliceCount + 1) * y + (z + 1) + 1);
				IBVector.push_back((iSliceCount + 1) * (y + 1) + (z + 1) + 1);

			}
		}

		// ���������� ������ �ε���
		UINT iBotIndex = (UINT)VBVector.size() - 1;
		for (UINT i = 0; i < iSliceCount; i++)
		{
			// ������ ������ �ϱ���
			IBVector.push_back(iBotIndex);
			IBVector.push_back(iBotIndex - (i + 2));
			IBVector.push_back(iBotIndex - (i + 1));
		}

		GameEngineVertexBuffer::Create("Sphere", VBVector);
		GameEngineIndexBuffer::Create("Sphere", IBVector);

		GameEngineMesh::Create("Sphere");

		std::shared_ptr<GameEngineMesh> Mesh = GameEngineMesh::Create("DebugSphere", "Sphere", "Sphere");
	}


	{
		std::vector<GameEngineVertex> Vertex;
		Vertex.resize(4);

		// �̹����� �ڸ����� TEXCOORD���� �ٲ��� �ϴµ�.
		Vertex[0] = { { -0.5f, 0.5f, 0.0f, 1.0f }, {0.0f, 0.0f} };
		Vertex[1] = { { 0.5f, 0.5f, 0.0f, 1.0f } , {1.0f, 0.0f} };
		Vertex[2] = { { 0.5f, -0.5f, 0.0f, 1.0f }  , {1.0f, 1.0f} };
		Vertex[3] = { { -0.5f, -0.5f, 0.0f, 1.0f } , {0.0f, 1.0f} };

		GameEngineVertexBuffer::Create("Rect", Vertex);


		std::vector<unsigned int> Index =
		{
			0, 1, 2,
			0, 2, 3
		};

		GameEngineIndexBuffer::Create("Rect", Index);

		GameEngineMesh::Create("Rect");
	}



	{
		std::vector<GameEngineVertex> Vertex;
		Vertex.resize(4);

		Vertex[0] = { { -1.0f, 1.0f, 0.0f, 1.0f },  {0.0f, 0.0f} };
		Vertex[1] = { { 1.0f, 1.0f, 0.0f, 1.0f } , {1.0f, 0.0f} };
		Vertex[2] = { { 1.0f, -1.0f, 0.0f, 1.0f }  , {1.0f, 1.0f} };
		Vertex[3] = { { -1.0f, -1.0f, 0.0f, 1.0f } , {0.0f, 1.0f} };

		GameEngineVertexBuffer::Create("FullRect", Vertex);


		std::vector<unsigned int> Index =
		{
			0, 1, 2,
			0, 2, 3
		};

		GameEngineIndexBuffer::Create("FullRect", Index);

		GameEngineMesh::Create("FullRect");
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

	{
		// �̰� �����ϴ� ����
		// order�� 2d�������� ������ �Ǵ°��� �ƴ϶�
		// z�� ���� ������ �����ϰ� �Ǳ� ������
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		//BOOL DepthEnable;
		//D3D11_DEPTH_WRITE_MASK DepthWriteMask;
		//D3D11_COMPARISON_FUNC DepthFunc;
		//BOOL StencilEnable;
		//UINT8 StencilReadMask;
		//UINT8 StencilWriteMask;
		//D3D11_DEPTH_STENCILOP_DESC FrontFace;
		//D3D11_DEPTH_STENCILOP_DESC BackFace;

		Desc.DepthEnable = true;
		// ���� �׽�Ʈ�� �ϰ� �Ⱦ����� �ִ�.
		// Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;
		std::shared_ptr<GameEngineDepthStencil> Rasterizer = GameEngineDepthStencil::Create("EngineDepth", Desc);
	}


	{
		// �̰� �����ϴ� ����
		// order�� 2d�������� ������ �Ǵ°��� �ƴ϶�
		// z�� ���� ������ �����ϰ� �Ǳ� ������
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		//BOOL DepthEnable;
		//D3D11_DEPTH_WRITE_MASK DepthWriteMask;
		//D3D11_COMPARISON_FUNC DepthFunc;
		//BOOL StencilEnable;
		//UINT8 StencilReadMask;
		//UINT8 StencilWriteMask;
		//D3D11_DEPTH_STENCILOP_DESC FrontFace;
		//D3D11_DEPTH_STENCILOP_DESC BackFace;

		Desc.DepthEnable = true;
		// ���� �׽�Ʈ�� �ϰ� �Ⱦ����� �ִ�.
		// Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		Desc.StencilEnable = false;
		std::shared_ptr<GameEngineDepthStencil> Rasterizer = GameEngineDepthStencil::Create("AlwaysDepth", Desc);
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
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		// Desc.DepthClipEnable = TRUE;
		std::shared_ptr<GameEngineRasterizer> Rasterizer = GameEngineRasterizer::Create("EngineWireRasterizer", Desc);
	}


	{
		D3D11_BLEND_DESC Desc = {};

		// �̰� �� ������.
		// ���̹��۶�� �Ͱ� ������ �ֽ��ϴ�.
		// ���߿� ��
		// Desc.AlphaToCoverageEnable

		// ����Ÿ���� �����ϴ°Ͱ� ������ �ִµ�.
		// ����Ÿ���� �ѹ��� 8���� �����Ҽ� �ִ�.
		// �װ� 1�� �̻��� ���������� ���� �ٸ� ������ �ϰ� ������ �־��ٰų� ��� �ɼ��Դϴ�.
		// ���Ѵ��ϸ� 0��°�ɷ� ������ ��θ� �����Ѵ�.
		Desc.IndependentBlendEnable = false;

		// ���� �Ӱų�.
		Desc.RenderTarget[0].BlendEnable = true;

		// ���� ��ü�� ������� ��ڴ�.
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		// + ���� �ẻ���� �����.
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		// https://learn.microsoft.com/ko-kr/windows/win32/api/d3d11/ne-d3d11-d3d11_blend
		
		// src srcColor * src�� ����
		// 1, 0, 0(, 1) * 1.0f
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // src����

		// src 1, 0, 0, 1 * (1 - src�� ����)
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		// 
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

		std::shared_ptr<GameEngineBlend> Blend = GameEngineBlend::Create("AlphaBlend", Desc);
	}


	{

		D3D11_SAMPLER_DESC Desc = {};
		// �Ϲ����� �������� <= ��������.
		// D3D11_FILTER_MIN_MAG_MIP_
		// �� �Ӹʿ��� �������ö� �� ������ ������� �������ڴ�.
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		std::shared_ptr<GameEngineSampler> Rasterizer = GameEngineSampler::Create("EngineBaseSampler", Desc);
	}

	{

		D3D11_SAMPLER_DESC Desc = {};
		// �Ϲ����� �������� <= ��������.
		// D3D11_FILTER_MIN_MAG_MIP_
		// �� �Ӹʿ��� �������ö� �� ������ ������� �������ڴ�.
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		std::shared_ptr<GameEngineSampler> Sampler = GameEngineSampler::Create("EngineBaseWRAPSampler", Desc);
	}


	{

		D3D11_SAMPLER_DESC Desc = {};
		// �Ϲ����� �������� <= ��������.
		// D3D11_FILTER_MIN_MAG_MIP_
		// �� �Ӹʿ��� �������ö� �� ������ ������� �������ڴ�.
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		std::shared_ptr<GameEngineSampler> Rasterizer = GameEngineSampler::Create("POINT", Desc);
	}


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
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("2DTexture");
		Mat->SetVertexShader("TextureShader_VS");
		Mat->SetPixelShader("TextureShader_PS");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("2DTextureWire");
		Mat->SetVertexShader("DebugColor_VS");
		Mat->SetPixelShader("DebugColor_PS");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetRasterizer("EngineWireRasterizer");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("2DDebugLine");
		Mat->SetVertexShader("DebugLine_VS");
		Mat->SetPixelShader("DebugLine_PS");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetRasterizer("EngineRasterizer");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("TargetMerge");
		Mat->SetVertexShader("TargetMerge_VS");
		Mat->SetPixelShader("TargetMerge_PS");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetRasterizer("EngineRasterizer");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("FadePostEffect");
		Mat->SetVertexShader("FadePostEffect_VS");
		Mat->SetPixelShader("FadePostEffect_PS");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetRasterizer("EngineRasterizer");
	}



	GameEngineRenderTarget::MergeRenderUnitInit();


	// �������ؿ��� �������ִ� ���� �������� ���ҽ����� ���⿡�� ������� �̴ϴ�.
	// �⺻ �Ž�
	// �⺻ �ؽ�ó
	// �⺻ ���̴�
	// ���⿡�� �ڱ� �ؽ�ó �ε�����������.


}